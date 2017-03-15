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

