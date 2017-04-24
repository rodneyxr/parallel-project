#include "aabb.h"

bool aabb::Run(const Entity &e1, const Entity &e2) {
    Vector3 e1_min = FindMinimumPoint(e1);
    Vector3 e1_max = FindMaximumPoint(e1);
    Vector3 e2_min = FindMinimumPoint(e2);
    Vector3 e2_max = FindMaximumPoint(e2);

    return (e1_max.x > e2_min.x &&
            e1_min.x < e2_max.x &&
            e1_max.y > e2_min.y &&
            e1_min.y < e2_max.y &&
            e1_max.z > e2_min.z &&
            e1_min.z < e2_max.z);
}

Vector3 aabb::FindMinimumPoint(const Entity &e) {
    Vector3 min_point = e.GetPoints()->front();
    double min = min_point.Magnitude();

    std::vector<Vector3>::const_iterator iter = e.GetPoints()->begin();
    for (advance(iter, 1); iter != e.GetPoints()->end(); ++iter) {
        double tmp_min = iter->Magnitude();
        if (tmp_min < min) {
            min = tmp_min;
            min_point = *iter;
        }
    }

    return min_point;
}

Vector3 aabb::FindMaximumPoint(const Entity &e) {
    Vector3 max_point = e.GetPoints()->front();
    double max = max_point.Magnitude();

    std::vector<Vector3>::const_iterator iter = e.GetPoints()->begin();
    for (advance(iter, 1); iter != e.GetPoints()->end(); ++iter) {
        double tmp_max = iter->Magnitude();
        if (tmp_max > max) {
            max = tmp_max;
            max_point = *iter;
        }
    }

    return max_point;
}
