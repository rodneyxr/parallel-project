#include "simplex.hpp"

void Simplex::Add(Vector3 support) {
    this->mutex.lock();
    this->supports.push_back(support);
    this->mutex.unlock();
}

Vector3 Simplex::GetLast() {
    return this->supports.back();
}

