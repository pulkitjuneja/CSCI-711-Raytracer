#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Global.h"
#include <math.h>
#include <glm.hpp>

template <class T>
class Vector3
{
public:
	T x, y, z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	Vector3(glm::vec3& i) : x(i.x), y(i.y), z(i.z) {}
	float lengthSquared() const;
	float length() const;
	Vector3(const Vector3& c);
	Vector3<T>& normalize();
	float dot(Vector3<T> vec) const;
	Vector3<T> cross(Vector3<T> vec) const;
	Vector3<T> operator*(const T& f) const;
	Vector3<T> operator*(const Vector3<T>& v) const;
	Vector3<T> operator+(const Vector3<T>& v) const;
	Vector3<T> operator-(const Vector3<T>& v) const;
	Vector3<T> operator/(const T& f);
	Vector3<T> operator-();
};

template <class T>
float Vector3<T>::lengthSquared() const
{
	return x * x + y * y + z * z;
}

template<class T>
inline float Vector3<T>::length() const
{
	return std::sqrt(lengthSquared());
}

template <class T>
Vector3<T>::Vector3(const Vector3& c)
{
	x = c.x;
	y = c.y;
	z = c.z;
}

template <class T>
Vector3<T>& Vector3<T>::normalize()
{
	float length = sqrt(lengthSquared());
	if (length > 0)
	{
		float invLength = 1 / length;
		x = x * invLength;
		y = y * invLength;
		z = z * invLength;
	}
	return *this;
}

template <class T>
float Vector3<T>::dot(Vector3<T> vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

template <class T>
Vector3<T> Vector3<T>::operator*(const T& f) const
{
	return Vector3<T>(x * f, y * f, z * f);
}

template <class T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& v) const
{
	return Vector3<T>(x * v.x, y * v.y, z * v.z);
}

template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const
{
	return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const
{
	return Vector3<T>(x - v.x, y - v.y, z - v.z);
}

template <class T>
Vector3<T> Vector3<T>::operator/(const T& f)
{
	return Vector3<T>(x / f, y / f, z / f);
}

template <class T>
Vector3<T> Vector3<T>::operator-()
{
	return Vector3(x == 0 ? x : -x, y == 0 ? y : -y, z == 0 ? z : -z);
}

template <class T>
Vector3<T> Vector3<T>::cross(Vector3<T> other) const
{
	T x = this->y * other.z - this->z * other.y;
	T y = this->z * other.x - this->x * other.z;
	T z = this->x * other.y - this->y * other.x;
	return Vector3<T>(x, y, z);
}
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

#endif
