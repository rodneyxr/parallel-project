#include <cmath>
#include "vector3.hpp"

double Vector3::Distance(const Vector3 &v1, const Vector3 &v2) {
    double x, y, z;
    x = v1.x - v2.x;
    x *= x;
    y = v1.y - v2.y;
    y *= y;
    z = v1.z - v2.z;
    z *= z;
    return sqrt(x + y + z);
}

Vector3 Vector3::TripleProduct(const Vector3 &a, const Vector3 &b, const Vector3 &c) {
    return b * c.Dot(a) - a * c.Dot(b);
}

double Vector3::Dot(const Vector3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::Negate() const {
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::Cross(const Vector3 &v) const {
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double Vector3::Magnitude() const {
    return x + y + z;
}

Vector3 Vector3::Unit() const {
    double m = Magnitude();
    if (m == 0)
        return Vector3(0.0);
    return Vector3(x / m, y / m, z / m);
}
