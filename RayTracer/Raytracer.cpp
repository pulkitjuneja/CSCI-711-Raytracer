#include "Raytracer.h"
#include <mutex>
#include <cmath>
#include <algorithm>
#include "IlluminationModel.h"
#include "Utils.h"

using namespace std;
static mutex coutMutex;

glm::vec3 RayTracer::trace(Ray& ray, int depth)
{
    if (depth >= MAX_DEPTH)
    {
        return glm::vec3(1, 1, 0);
    }
    HitData rec;
    if (scene->intersects(ray, rec))
    {
        glm::vec3 localIllumination = calculateLighting(rec);
        glm::vec3 indirectIllumniation(0,0,0);
        if (depth < MAX_DEPTH) {
            if (rec.hitObject->material.Kr > 0) {
                glm::vec3 viewDir = ray.direction;//glm::normalize(scene->camera.getPosition() - rec.hitPoint);
                glm::vec3 reflectionDir = reflect(viewDir, rec.normal);
                //float weight = 0;
                //for (int i = 0; i < 24; i++) {
                //    auto selector = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                //        if (selector < rec.hitObject->material.Kd) {
                //        glm::vec2 Xi = glm::vec2((float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
                //        glm::vec3 sampleDir = blinnPhong.CalculateDiffuseDirection(Xi, rec.normal);
                //        Ray sampleRay(rec.hitPoint + rec.normal * glm::vec3(0.001), sampleDir);
                //        float NdotL = std::clamp(0.00001f, glm::dot(rec.normal, sampleDir), 1.0f);
                //        glm::vec3 diffuseReflection = trace(sampleRay, depth + 1) * NdotL;
                //        indirectIllumniation = indirectIllumniation + diffuseReflection * rec.hitObject->material.diffuse->value(rec.texCoords.x, rec.texCoords.y);
                //    } 
                //    
                //    else if (rec.hitObject->material.Kd < selector && selector < rec.hitObject->material.Ks) {

                //        glm::vec2 Xi = glm::vec2((float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
                //        glm::vec3 sampleDir = blinnPhong.ImportanceSample(Xi, reflectionDir, rec.hitObject->material.Ke);
                //        Ray sampleRay(rec.hitPoint + rec.normal * glm::vec3(0.001), sampleDir);
                //        float NdotL = std::clamp(0.00001f, glm::dot(rec.normal, sampleDir), 1.0f);
                //        indirectIllumniation = indirectIllumniation + trace(sampleRay, depth + 1) * NdotL;
                //        weight += NdotL;
                //    }
                //}
                //indirectIllumniation = indirectIllumniation / 24.0f;
                Ray reflectionRay(rec.hitPoint + rec.normal * glm::vec3(0.001), reflectionDir);
                indirectIllumniation = indirectIllumniation + trace(reflectionRay, depth + 1) * (rec.hitObject->material.Kr);
            } 
            if (rec.hitObject->material.Kt > 0) {
                glm::vec3 normal = rec.normal;
                float refractionIndex = 1.0f / rec.hitObject->material.refractiveIndex;
                if (glm::dot(normal, -ray.direction) < 0)
                {
                    normal *= -1;
                    refractionIndex = rec.hitObject->material.refractiveIndex / 1.0f;

                }
                glm::vec3 refractedVector = glm::refract(ray.direction, normal, refractionIndex);

                if (refractedVector.x == 0 && refractedVector.y == 0 && refractedVector.z == 0)
                {
                    //total internal reflection
                    refractedVector = glm::reflect(ray.direction, normal);
                }

                Ray refractedRay;
                refractedRay = Ray(rec.hitPoint + 0.01f * refractedVector, refractedVector);

                glm::vec3 refractedColor = trace(refractedRay, depth + 1);
                indirectIllumniation += refractedColor * rec.hitObject->material.Kt;
            }
        }
        return localIllumination + indirectIllumniation;
    }
    else
    {
        return glm::vec3(1.0, 1.0, 1.0)  * (ray.direction.y * 0.5f + 0.5f);
    }
}

glm::vec3 RayTracer::reflect(glm::vec3& S, glm::vec3& N)
{
    glm::vec3 I = -S;
    float D = glm::dot(I, N);
    glm::vec3 ref = (N * glm::vec3(2) * D) - I;
    return ref;
}

bool RayTracer::refract(const glm::vec3 direction, const glm::vec3 normal, float niOverNt, glm::vec3& refracted) {
    float cosI = -glm::dot(direction, normal);
    float sinT2 = niOverNt * niOverNt * (1.0 - cosI * cosI);
    if (sinT2 > 1.0) {
        return false;
    }
    float cosT = sqrt(1.0 - sinT2);
    refracted = glm::normalize(direction * niOverNt + normal * (niOverNt * cosI - cosT));
    return true;
}

float RayTracer::calculateLogAverageLuminance(float* luminanceBuffer, int width, int height)
{
    double logAverage = 0;
    double delta = 0.00001;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            logAverage += log10(luminanceBuffer[i * width + j] + delta);
        }
    }
    logAverage = logAverage / ((float)(width * height));
    logAverage = exp(logAverage);
    return logAverage;
}

void RayTracer::applyReinhard(float logAverageLuminance, int width, int height, glm::vec3* frameBuffer)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            glm::vec3 temp = frameBuffer[i * width + j];
            temp = temp * (0.18f / logAverageLuminance);
            glm::vec3 newValue(temp.x / (1 + temp.x), temp.y / (1 + temp.y), temp.z / (1 + temp.z));
            frameBuffer[i * width + j] = newValue * maxLuminance;
        }
    }
}

void RayTracer::applyWard(float logAverageLuminance, int width, int height, glm::vec3* frameBuffer)
{
    float top = 1.219 + pow((maxLuminance / 2), 0.4);
    float bottom = 1.219 + pow(logAverageLuminance, 0.4);
    float sf = pow((top / bottom), 2.5);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            frameBuffer[i * width + j] = frameBuffer[i * width + j] * sf;
        }
    }

}

void RayTracer::applyAdaptiveLogMapping(float logAverageLuminance, int width, int height, glm::vec3* frameBuffer, float* luminanceBuffer)
{
    float scaledMaxLuminance = maxLuminance / logAverageLuminance;
    float exponent = log(0.85) / log(0.5);
    float denom1 = log10(scaledMaxLuminance + 1);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float scaledPixelLuminance = luminanceBuffer[i * width + j] / logAverageLuminance;
            float num2 = log(scaledPixelLuminance + 1);
            float luminanceRatio = scaledPixelLuminance / scaledMaxLuminance;
            float denom2 = log(2 + ((pow(luminanceRatio, exponent) * 8)));

            float Ld = (1 / denom1) * (num2 / denom2);
            frameBuffer[i * width + j] = frameBuffer[i * width + j] * (Ld);
        }
    }
}

void RayTracer::render(RenderOptions* options)
{
    unsigned int numThreads = thread::hardware_concurrency();
    vector<thread> threads;

    unsigned int threadIndex = 0;
    cout << numThreads;

    glm::vec3* frameBuffer = new glm::vec3[options->height * options->width];
    luminanceBuffer = new float[options->height * options->width];
    maxLuminance = -1; 

    while (threadIndex < numThreads && threadIndex < options->height)
    {
        threads.emplace_back(thread(&RayTracer::renderRow, this, options, frameBuffer));
        ++threadIndex;
    }

    for (auto& worker : threads)
    {
        worker.join();  
    }

    float logAverageLuminance = calculateLogAverageLuminance(luminanceBuffer, options->width, options->height);

    if (options->toneMappingOperator == ToneMappingOperator::Reinhard) {
        applyReinhard(logAverageLuminance, options->width, options->height, frameBuffer);
    }
    else if (options->toneMappingOperator == ToneMappingOperator::Ward) {
        applyWard(logAverageLuminance, options->width, options->height, frameBuffer);
    }
    else if (options->toneMappingOperator == ToneMappingOperator::ALM) {
        applyAdaptiveLogMapping(logAverageLuminance, options->width, options->height, frameBuffer, luminanceBuffer);
    }

    writeToImgae(frameBuffer, options);
}

void RayTracer::renderRow(RenderOptions* options, glm::vec3* frameBuffer)
{
    MAX_DEPTH = options->maxDepth;
    int ns = 8;
    do
    {
        int j = nextRow++;
        int startIndex = (options->height - j - 1) * options->width;

        for (int i = 0; i < options->width; i++)
        {
            glm::vec3 color(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float x = float(i + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / float(options->width);
                float y = float(j + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / float(options->height);
                Ray ray = scene->camera.getCameraRay(x, y);
                // glm::vec3 dir(x, y, -1);
                // dir = dir.normalize();
                // Ray ray(origin, dir);
                color = color + trace(ray, 0);
            }
            color = color / float(ns);
            color = glm::vec3(sqrt(color.x), sqrt(color.y), sqrt(color.z));
            frameBuffer[startIndex] = color;
            luminanceBuffer[startIndex] = (0.27 * color.x) + (0.67 * color.y) + (0.06 * color.z);
            if (luminanceBuffer[startIndex] > maxLuminance) {
                maxLuminance = luminanceBuffer[startIndex];
            }
            startIndex++;
        }

        ++rowsRendered;
        if (rowsRendered % 10 == 0)
        {
            lock_guard<mutex> lock(coutMutex);
            cout << rowsRendered << "/" << options->height << " rows rendered" << endl;
        }

    } while (nextRow < options->height);
}

glm::vec3 RayTracer::calculateLighting(const HitData& record)
{
    glm::vec3 finalColor(0,0,0);
    Material& material = record.hitObject->material;

    for(int i = 0; i<scene->pointLights.size(); i++) {
        PointLight& pointLight = scene->pointLights[i];

        glm::vec3 lightDir = glm::normalize(pointLight.position - record.hitPoint);

        glm::vec3 shadowRayorig = record.hitPoint + (lightDir * glm::vec3(0.001));
        Ray shadowRay(shadowRayorig, lightDir);
        HitData shadowRec;
        float shadowMultiplier = 1.0;
        if (scene->intersects(shadowRay, shadowRec)) {
            shadowMultiplier = 1 - shadowRec.hitObject->material.Kr;
            if (shadowMultiplier <= 0)
                continue;
        }

        finalColor = finalColor + blinnPhong.calculateLIghting(record, pointLight, material, scene->camera) * shadowMultiplier;
    }

    return finalColor;
}

float RayTracer::Schlick(float cosine, float niOverNt)
{
    float r0 = ((niOverNt - 1.0f) / (1.0f + niOverNt));
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * pow((1.0f - cosine), 5)   ;
}

void RayTracer::setScene(Scene* scene)
{
    this->scene = scene;
}

void RayTracer::writeToImgae(glm::vec3* frameBuffer, RenderOptions* options)
{
    ofstream ofs("finalImage.ppm", ios::out);
    ofs << "P3\n" << options->width << " " << options->height << "\n255\n";
    for (uint32_t i = 0; i < options->height * options->width; ++i)
    {
        int r = (int)(255 * clamp(frameBuffer[i].x, 0.0f, 1.0f));
        int g = (int)(255 * clamp(frameBuffer[i].y, 0.0f, 1.0f));
        int b = (int)(255 * clamp(frameBuffer[i].z, 0.0f, 1.0f));
        ofs << r << "\t" << g << "\t" << b << "\n";
    }
    ofs.close();
    delete[] frameBuffer;
}