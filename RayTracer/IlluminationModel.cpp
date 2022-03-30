#include "IlluminationModel.h"
#include <cmath>

#define EPSILON_F 0.001f
#define PI 3.1415

glm::vec3 BlinnPhong::calculateLIghting(const HitData& record, PointLight& pointLight, Material& material, Camera& camera)
{
    glm::vec3 diffuseColor(0,0,0);
    glm::vec3 specularColor(0,0,0);
    
    glm::vec3 lightDir = normalize(pointLight.position - record.hitPoint);
    glm::vec3 normal = record.normal;
    glm::vec3 viewDir = glm::normalize(camera.getPosition() - record.hitPoint);
    glm::vec3 halfway = glm::normalize(lightDir + viewDir);
    float distance = (pointLight.position - record.hitPoint).length();
    // calculate diffuse lighting 
    float NdotL = std::max(glm::dot(normal, lightDir), 0.0f);
    float diffuse = pointLight.intensity * NdotL;
    diffuseColor = diffuseColor + (material.diffuse->value(record.texCoords.x, record.texCoords.y)* 
        pointLight.color * diffuse * material.Kd);
    //calculate specular highlight
    float spec = pow(std::max(glm::dot(normal, halfway), 0.0f), material.Ke);
    specularColor = specularColor + (pointLight.color * pointLight.intensity * spec * material.Ks);

    return diffuseColor + specularColor;
}

glm::vec3 BlinnPhong::ImportanceSample(glm::vec2 Xi, glm::vec3 R, float specExponent)
{
    float alpha = std::acos(std::pow(Xi.x, 1 / (specExponent + 1)));
    float phi = 2 * Xi.y * PI;

    glm::vec3 H;
    H.x = sin(alpha)* cos(phi);
    H.y = sin(alpha) * sin(phi);
    H.z = cos(alpha);

    //
    glm::vec3 up = abs(R.z) < 0.999 ? glm::vec3(0.0, 0.0, 1.0) : glm::vec3(1.0, 0.0, 0.0);
    glm::vec3 tangent = glm::normalize(glm::cross(up,R));
    glm::vec3 bitangent = glm::cross(R, tangent);

    glm::vec3 sampleVec = tangent * H.x + bitangent * H.y + R * H.z;
    return glm::normalize(sampleVec);
}

glm::vec3 BlinnPhong::CalculateDiffuseDirection(glm::vec2 Xi, glm::vec3 N)
{
    float cosTheta = std::pow(Xi.x, 1.0f / (2.f));
    float sinTheta = sqrt(1.0f - cosTheta * cosTheta);
    float phi = 2 * 3.1415926 * Xi.y;

    glm::vec3 H;
    H.x = sinTheta * cos(phi);
    H.y = sinTheta * sin(phi);
    H.z = cosTheta;

    glm::vec3 up = abs(N.z) < 0.999 ? glm::vec3(0.0, 0.0, 1.0) : glm::vec3(1.0, 0.0, 0.0);
    glm::vec3 tangent = glm::normalize(glm::cross(up, N));
    glm::vec3 bitangent = glm::cross(N, tangent);

    glm::vec3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
    return glm::normalize(sampleVec);
}

glm::vec3 AshikhmanShirley::calculateLIghting(const HitData& record, PointLight& pointLight, Material& material, Camera& camera)
{
    //glm::vec3 lightDir = pointLight.position - record.hitPoint;
    //lightDir.normalize();
    //glm::vec3 normal = record.normal;
    //glm::vec3 tangent = record.tangent;
    //glm::vec3 biTangent = normal.cross(tangent);
    //biTangent.normalize();
    //glm::vec3 viewDir = camera.getPosition() - record.hitPoint;
    //viewDir.normalize();
    //glm::vec3 halfway = lightDir + viewDir;
    //halfway.normalize();

    //float dotLN = lightDir.dot(normal);
    //float dotVN = viewDir.dot(normal);
    //float dotHL = halfway.dot(lightDir);
    //float dotHN = halfway.dot(normal);
    //float dotHT = halfway.dot(tangent);
    //float dotHB = halfway.dot(biTangent);

    //float sqDotHT = dotHT * dotHT;
    //float sqDotHB = dotHB * dotHB;
    //float sqDotHN = dotHN * dotHN;

    //glm::vec3 F = fresnelSchlick(dotHL, material.diffuse);
    //glm::vec3 sBrdf = F * sqrt((material.Ke + 1.0f) * (material.Ke + 1.0f)) / (8.0f * 3.1415)
    //    * pow(dotHN, (material.Ke * sqDotHT + material.Ke * sqDotHB) / std::max(1.0f - sqDotHN, EPSILON_F))
    //    / (dotHL * std::max(dotLN, dotVN));

    //glm::vec3 dCoeff = material.diffuse * 28.0f / (23.0f * 3.1415);
    //glm::vec3 sCoeff = glm::vec3(1.0, 1.0, 1.0) - material.diffuse;
    //glm::vec3 dBrdf = dCoeff.cwiseProduct(sCoeff)
    //    * (1.0f - pow(1.0f - dotLN / 2.0, 5.0f))
    //    * (1.0f - pow(1.0f - dotVN / 2.0, 5.0f));

    return glm::vec3();
}
