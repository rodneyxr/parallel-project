#ifndef PARALLEL_VECTOR3_H
#define PARALLEL_VECTOR3_H

#include <sstream>
#include <ostream>

class Vector3 {

public:
    double x, y, z;

    Vector3() : Vector3(0.0) {};

    Vector3(double xyz) : Vector3(xyz, xyz, xyz) {};

    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    /**
     * Calculates the distance between two Vector3 instances. The order of the
     * parameters does not affect the result.
     *
     * @param v1 The first instance to use in the distance calculation.
     * @param v2 The second instance to use in the distance calculation.
     * @return the distance between v1 and v2.
     */
    static double Distance(const Vector3 &v1, const Vector3 &v2);

    /**
     * @return the scalar triple product: (A x B) x C
     */
    static Vector3 TripleProduct(const Vector3 &a, const Vector3 &b, const Vector3 &c);

    /**
     * @return the dot product of the two vectors.
     */
    double Dot(const Vector3 &v) const;

    /**
     * @return a new negated Vector3 instance.
     */
    Vector3 Negate() const;

    /**
     * @return the cross product of this vector with v.
     */
    Vector3 Cross(const Vector3 &v) const;

    /**
     * @return the sum of all dimensions in this vector.
     */
    double Magnitude() const;

    /**
     * @return the unit vector (vector with a magnitude of 1).
     */
    Vector3 Unit() const;

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &d) {
        os << "{" << d.x << "," << d.y << "," << d.z << "}";
        return os;
    }

};

namespace vec3 {
    static const Vector3 back{0, 0, -1};
    static const Vector3 down{0, -1, 0};
    static const Vector3 forward{0, 0, 1};
    static const Vector3 left{-1, 0, 0};
    static const Vector3 one{1, 1, 1};
    static const Vector3 right{1, 0, 0};
    static const Vector3 up{0, 1, 0};
    static const Vector3 zero{0, 0, 0};
}

/* Operators */
inline Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

inline Vector3 operator*(const Vector3 &lhs, const double &rhs) {
    return Vector3{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

inline Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

inline Vector3 operator/(const Vector3 &lhs, const double &rhs) {
    return Vector3{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

inline Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

inline Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

inline bool operator==(const Vector3 &lhs, const Vector3 &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

#endif //PARALLEL_VECTOR3_H
