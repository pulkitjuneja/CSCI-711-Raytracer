#include "IlluminationModel.h"
#include <cmath>

#define EPSILON_F 0.001f

Vector3f BlinnPhong::calculateLIghting(const HitData& record, PointLight& pointLight, Material& material, Camera& camera)
{
    Vector3f diffuseColor;
    Vector3f specularColor;
    
    Vector3f lightDir = pointLight.position - record.hitPoint;
    lightDir.normalize();
    Vector3f normal = record.normal;
    Vector3f viewDir = camera.getPosition() - record.hitPoint;
    viewDir.normalize();
    Vector3f halfway = lightDir + viewDir;
    halfway.normalize();
    float distance = (pointLight.position - record.hitPoint).length();
    // calculate diffuse lighting 
    float NdotL = std::max(normal.dot(lightDir), 0.0f);
    float diffuse = pointLight.intensity * NdotL;
    diffuseColor = diffuseColor + (record.texCoords* pointLight.color * diffuse * material.Kd);
    //calculate specular highlight
    float spec = pow(std::max(normal.dot(halfway), 0.0f), material.Ke);
    specularColor = specularColor + (pointLight.color * pointLight.intensity * spec * material.Ks);

    return diffuseColor + specularColor;
}

Vector3f AshikhmanShirley::calculateLIghting(const HitData& record, PointLight& pointLight, Material& material, Camera& camera)
{
    //Vector3f lightDir = pointLight.position - record.hitPoint;
    //lightDir.normalize();
    //Vector3f normal = record.normal;
    //Vector3f tangent = record.tangent;
    //Vector3f biTangent = normal.cross(tangent);
    //biTangent.normalize();
    //Vector3f viewDir = camera.getPosition() - record.hitPoint;
    //viewDir.normalize();
    //Vector3f halfway = lightDir + viewDir;
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

    //Vector3f F = fresnelSchlick(dotHL, material.diffuse);
    //Vector3f sBrdf = F * sqrt((material.Ke + 1.0f) * (material.Ke + 1.0f)) / (8.0f * 3.1415)
    //    * pow(dotHN, (material.Ke * sqDotHT + material.Ke * sqDotHB) / std::max(1.0f - sqDotHN, EPSILON_F))
    //    / (dotHL * std::max(dotLN, dotVN));

    //Vector3f dCoeff = material.diffuse * 28.0f / (23.0f * 3.1415);
    //Vector3f sCoeff = Vector3f(1.0, 1.0, 1.0) - material.diffuse;
    //Vector3f dBrdf = dCoeff.cwiseProduct(sCoeff)
    //    * (1.0f - pow(1.0f - dotLN / 2.0, 5.0f))
    //    * (1.0f - pow(1.0f - dotVN / 2.0, 5.0f));

    return Vector3f();
}
