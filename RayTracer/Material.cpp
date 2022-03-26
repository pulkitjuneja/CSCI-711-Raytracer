#include "Material.h"


Material::Material(Texture* diffuse, float Ks, float Kr, float Ke) {
	this->diffuse = diffuse;
	this->Ks = Ks;
	this->Kd = 1.0f - Ks;
	this->Ke = Ke;
	this->Kr = Kr;
}