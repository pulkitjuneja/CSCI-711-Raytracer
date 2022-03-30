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
        return glm::vec3(0, 0, 0);
    }
    HitData rec;
    if (scene->intersects(ray, rec))
    {
        glm::vec3 localIllumination = calculateLighting(rec);
        glm::vec3 indirectIllumniation(0,0,0);
        if (depth < MAX_DEPTH) {
            if (rec.hitObject->material.Kr > 0) {
                glm::vec3 viewDir = glm::normalize(scene->camera.getPosition() - rec.hitPoint);
                glm::vec3 reflectionDir = reflect(viewDir, rec.normal);
                float weight = 0;
                for (int i = 0; i < 24; i++) {
                    auto selector = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                    if (selector < rec.hitObject->material.Kd) {
                        glm::vec2 Xi = glm::vec2((float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
                        glm::vec3 sampleDir = blinnPhong.CalculateDiffuseDirection(Xi, rec.normal);
                        Ray sampleRay(rec.hitPoint + rec.normal * glm::vec3(0.001), sampleDir);
                        float NdotL = std::clamp(0.00001f, glm::dot(rec.normal, sampleDir), 1.0f);
                        glm::vec3 diffuseReflection = trace(sampleRay, depth + 1) * NdotL;
                        indirectIllumniation = indirectIllumniation + diffuseReflection * rec.hitObject->material.diffuse->value(rec.texCoords.x, rec.texCoords.y);
                    } 
                    
                    else if (rec.hitObject->material.Kd < selector && selector < rec.hitObject->material.Ks) {

                        glm::vec2 Xi = glm::vec2((float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
                        glm::vec3 sampleDir = blinnPhong.ImportanceSample(Xi, reflectionDir, rec.hitObject->material.Ke);
                        Ray sampleRay(rec.hitPoint + rec.normal * glm::vec3(0.001), sampleDir);
                        float NdotL = std::clamp(0.00001f, glm::dot(rec.normal, sampleDir), 1.0f);
                        indirectIllumniation = indirectIllumniation + trace(sampleRay, depth + 1) * NdotL;
                        weight += NdotL;
                    }
                }
                indirectIllumniation = indirectIllumniation / 24.0f;
                //Ray reflectionRay(rec.hitPoint + rec.normal * glm::vec3(0.001), reflectionDir);
                //indirectIllumniation = indirectIllumniation + trace(reflectionRay, depth + 1) * rec.hitObject->material.Kr;
            }
        }
        return localIllumination + indirectIllumniation;
    }
    else
    {
        return scene->sceneAmbience;
    }
}

glm::vec3 RayTracer::reflect(glm::vec3& S, glm::vec3& N)
{
    float D = glm::dot(S, N);
    glm::vec3 ref = (N * glm::vec3(2) * D) - S;
    return ref;
}

void RayTracer::render(RenderOptions* options)
{
    unsigned int numThreads = thread::hardware_concurrency();
    vector<thread> threads;

    unsigned int threadIndex = 0;
    cout << numThreads;

    glm::vec3* frameBuffer = new glm::vec3[options->height * options->width];

    while (threadIndex < numThreads && threadIndex < options->height)
    {
        threads.emplace_back(thread(&RayTracer::renderRow, this, options, frameBuffer));
        ++threadIndex;
    }

    for (auto& worker : threads)
    {
        worker.join();
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
            frameBuffer[startIndex++] = color;
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

        if (scene->intersects(shadowRay, shadowRec)) {
            continue;
        }

        finalColor = finalColor + blinnPhong.calculateLIghting(record, pointLight, material, scene->camera);
    }

    return finalColor;
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