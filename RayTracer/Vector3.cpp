//#include "Vector3.h"
//
//template <class T>
//float Vector3<T>::lengthSquared() const
//{
//	return x * x + y * y + z * z;
//}
//
//template <class T>
//Vector3<T>::Vector3(const Vector3& c)
//{
//	x = c.x;
//	y = c.y;
//	z = c.z;
//}
//
//template <class T>
//Vector3<T>& Vector3<T>::normalize()
//{
//	float length = sqrt(lengthSquared());
//	if (length > 0)
//	{
//		float invLength = 1 / length;
//		x = x * invLength;
//		y = y * invLength;
//		z = z * invLength;
//	}
//	return *this;
//}
//
//template <class T>
//float Vector3<T>::dot(Vector3<T> vec) const
//{
//	return x * vec.x + y * vec.y + z * vec.z;
//}
//
//template <class T>
//Vector3<T> Vector3<T>::operator*(const T& f) const
//{
//	return Vector3<T>(x * f, y * f, z * f);
//}
//
//template <class T>
//Vector3<T> Vector3<T>::operator*(const Vector3<T>& v) const
//{
//	return Vector3<T>(x * v.x, y * v.y, z * v.z);
//}
//
//template <class T>
//Vector3<T> Vector3<T>::operator+(const Vector3<T>& v)
//{
//	return Vector3<T>(x + v.x, y + v.y, z + v.z);
//}
//
//template <class T>
//Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const
//{
//	return Vector3<T>(x - v.x, y - v.y, z - v.z);
//}
//
//template <class T>
//Vector3<T> Vector3<T>::operator/(const T& f)
//{
//	return Vector3<T>(x / f, y / f, z / f);
//}
//
//template <class T>
//Vector3<T> Vector3<T>::operator-()
//{
//	return Vector3(-x, -y, -z);
//}
//
//template <class T>
//Vector3<T> Vector3<T>::cross(Vector3<T> other) const
//{
//	T x = this->y * other.z - this->z * other.y;
//	T y = this->z * other.x - this->x * other.z;
//	T z = this->x * other.y - this->y * other.x;
//	return Vector3<T>(x, y, z);
//}
//
//typedef Vector3<float> Vector3f;
//typedef Vector3<int> Vector3i;
