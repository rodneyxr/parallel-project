#include <limits>
#include <iostream>
#include "gjk.hpp"

bool gjk::Run(const Entity &e1, const Entity &e2) {
    Simplex simplex;

    // choose a search direction
    Vector3 d = vec3::up;

    // get the first Minkowski Difference point
    simplex.Add(Support(e1, e2, d));

    // negate d for the next point
    d = d.Negate();

    int debug_counter = 0;
    // start looping
    while (true) {
        debug_counter++;
        if (debug_counter == 3) return true;
        // add a new point to the simplex because we haven't terminated yet
        simplex.Add(Support(e1, e2, d));
        // make sure that the last point we added actually passed the origin
        if (simplex.GetLast().Dot(d) <= 0) {
            // if the point added last was not past the origin in the direction of d
            // then the Minkowski Sum cannot possibly contain the origin since
            // the last point added is on the edge of the Minkowski Difference
            return false;
        } else {
            // otherwise we need to determine if the origin is in
            // the current simplex
            if (ContainsOrigin(simplex, d)) {
                // if it does then we know there is a collision
                return true;
            }
        }
    }
}

Vector3 gjk::FindMaxPointInDirection(const Entity &entity, const Vector3 direction) {
    double max = -std::numeric_limits<double>::infinity();
    Vector3 max_vec;
    for (auto &vec : *entity.GetPoints()) {
        double dot = vec.Dot(direction);
        if (dot > max) {
            max = dot;
            max_vec = vec;
        }
    }
    return max_vec;
}

Vector3 gjk::Support(const Entity &e1, const Entity &e2, const Vector3 direction) {
    // get vertices on the edge of the entities in opposite directions
    Vector3 v1 = FindMaxPointInDirection(e1, direction);
    Vector3 v2 = FindMaxPointInDirection(e2, direction.Negate());

    // return the Minkowski Difference
    return v1 - v2;
}

bool gjk::ContainsOrigin(Simplex &simplex, Vector3 &direction) {
    Vector3 a = simplex.GetLast();
    Vector3 ao = a.Negate();
    if (simplex.Size() == 4) {
        // tetrahedron case
        Vector3 b = simplex.Get(2);
        Vector3 c = simplex.Get(1);
        Vector3 d = simplex.Get(0);

        // edge vectors
        Vector3 ab = b - a;
        Vector3 ac = c - a;
        Vector3 ad = d - a;

        // get surface normals of unchecked faces
        Vector3 abc = ab.Cross(ac);
        Vector3 acd = ac.Cross(ad);
        Vector3 adb = ad.Cross(ab);

        // check the if point is above or below surface normals of each face on the tetrahedron
        if (abc.Dot(ao) > 0) {
            simplex.Remove(3);
            direction = abc;
        } else if (acd.Dot(ao) > 0) {
            simplex.Remove(1);
            direction = acd;
        } else if (adb.Dot(ao) > 0) {
            simplex.Remove(2);
            direction = adb;
        } else {
            // was below all faces; must be in tetrahedron
            return true;
        }
    } else if (simplex.Size() == 3) {
        // triangle case
        Vector3 b = simplex.Get(1);
        Vector3 c = simplex.Get(0);

        // edge vectors
        Vector3 ab = b - a;
        Vector3 ac = c - a;

        // surface/edge normals
        Vector3 abc = ab.Cross(ac);
        Vector3 abPerp = Vector3::TripleProduct(ac, ab, ab).Unit();
        Vector3 acPerp = Vector3::TripleProduct(ab, ac, ac).Unit();

        if (abPerp.Dot(ao) > 0) {
            // remove the point not attached to the edge's normal
            simplex.Remove(0);
            direction = abPerp;
        } else if (acPerp.Dot(ao) > 0) {
            // remove the point not attached to the edge's normal
            simplex.Remove(1);
            direction = acPerp;
        } else {
            // it's within the triangle, but is it above or below?
            if (abc.Dot(ao) > 0) {
                direction = abc;
            } else {
                direction = abc.Negate();
            }
        }
    } else {
        // line segment case
        Vector3 b = simplex.Get(0);
        Vector3 ab = b - a;
        Vector3 bcPerp = Vector3::TripleProduct(ab, ao, ab).Unit();
        direction = bcPerp;
    }
    return false;
}
