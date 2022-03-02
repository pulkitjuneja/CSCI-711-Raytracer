#include "Material.h"


Material::Material(Vector3f diffuse, float Ks, float Ka, float Ke) {
	this->diffuse = diffuse;
	this->Ks = Ks;
	this->Kd = 1.0f - Ks;
	this->Ke = Ke;
	this->Ka = Ka;
}