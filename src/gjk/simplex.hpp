#ifndef PARALLEL_SIMPLEX_HPP
#define PARALLEL_SIMPLEX_HPP

#include <vector>
#include <mutex>
#include "../tools/vector3.hpp"

class Simplex {

    /* list of support vectors used by the GJK algorithm */
    std::vector<Vector3> supports;

    /* mutex is used to thread safe operations on this simplex */
    std::mutex mutex;

public:

    /**
     * Adds a support vector to this simplex.
     *
     * @param support The support vector to add.
     */
    void Add(Vector3 support);

    unsigned long long Size() { return supports.size(); }

    Vector3 Get(int index) { return supports[index]; }

    /**
     * Removes a Vector3 from this simplex.
     * NOTE: Index should be less than the size of the Simplex.
     *
     * @param index the index of the Vector3 to remove.
     */
    void Remove(int index) {
        supports.erase(supports.begin() + index);
    }

    /**
     * @return The last support vector that was added to the Simplex.
     */
    Vector3 GetLast();

};


#endif //PARALLEL_SIMPLEX_HPP
