#include "Raytracer.h"
#include <mutex>

using namespace std;

static mutex coutMutex;

Vector3f RayTracer::trace(Ray& ray, int depth)
{
    if (depth >= MAX_DEPTH)
    {
        return Vector3f(0, 0, 0);
    }
    HitData rec;
    if (scene->intersects(ray, rec))
    {
        return calculateLighting(rec);
    }
    else
    {
        return scene->sceneAmbience;
    }
}

void RayTracer::render(RenderOptions* options)
{
    unsigned int numThreads = thread::hardware_concurrency();
    vector<thread> threads;

    unsigned int threadIndex = 0;
    cout << numThreads;

    Vector3f* frameBuffer = new Vector3f[options->height * options->width];

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

void RayTracer::renderRow(RenderOptions* options, Vector3f* frameBuffer)
{
    MAX_DEPTH = options->maxDepth;
    int ns = 1;
    do
    {
        int j = nextRow++;
        int startIndex = (options->height - j - 1) * options->width;

        for (int i = 0; i < options->width; i++)
        {
            Vector3f color(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float x = float(i + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / float(options->width);
                float y = float(j + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / float(options->height);
                Ray ray = scene->camera.getCameraRay(x, y);
                // Vector3f dir(x, y, -1);
                // dir = dir.normalize();
                // Ray ray(origin, dir);
                color = color + trace(ray, 0);
            }
            color = color / ns;
            color = Vector3f(sqrt(color.x), sqrt(color.y), sqrt(color.z));
            frameBuffer[startIndex++] = color;
        }

        ++rowsRendered;
        //if (rowsRendered % 10 == 0)
        //{
        //    lock_guard<mutex> lock(coutMutex);
        //    cout << rowsRendered << "/" << options->height << " rows rendered" << endl;
        //}

    } while (nextRow < options->height);
}

Vector3f RayTracer::calculateLighting(const HitData& record)
{
    Vector3f diffuseColor;
    Vector3f specularColor;
    Material& material = record.hitObject->material;

    for(int i = 0; i<scene->pointLights.size(); i++) {
        PointLight& pointLight = scene->pointLights[i];

        Vector3f normal = record.normal;
        Vector3f lightDir = pointLight.position - record.hitPoint;
        lightDir.normalize();
        Vector3f viewDir = scene->camera.getPosition() - record.hitPoint;
        viewDir.normalize();
        Vector3f halfway = lightDir + viewDir;
        halfway.normalize();
        float distance = (pointLight.position - record.hitPoint).length();

        Vector3f shadowRayorig = record.hitPoint + (lightDir * 0.001);
        Ray shadowRay(shadowRayorig, lightDir);
        HitData shadowRec;

        if (scene->intersects(shadowRay, shadowRec)) {
            continue;
        }
        // calculate diffuse lighting 
        float NdotL = max(normal.dot(lightDir), 0.0f);
        float diffuse = pointLight.intensity * NdotL;
        diffuseColor = diffuseColor + (material.diffuse * pointLight.color * diffuse * material.Kd);
        //calculate specular highlight
        float spec = pow(max(normal.dot(halfway), 0.0f), material.Ke);
        specularColor = specularColor + (pointLight.color * pointLight.intensity * spec * material.Ks );
    }

    return diffuseColor + specularColor;
}

void RayTracer::setScene(Scene* scene)
{
    this->scene = scene;
}

void RayTracer::writeToImgae(Vector3f* frameBuffer, RenderOptions* options)
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