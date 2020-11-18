// Copyright Laurence Emms 2020

#include <iostream>

#include "sparse_map_vector.h"
#include "sparse_list_vector.h"

int main(int argc, char** argv) {
    std::cout << "Test Sparse Linear Algebra Library." << std::endl;

    sparse::MapVector<int, float> map_vector;
    map_vector.insert(1, 1.0f);
    map_vector.insert(2, 2.0f);
    map_vector.insert(3, 3.0f);

    std::cout << "Map Vector: "
        << map_vector.get(0) << ", "
        << map_vector.get(1) << ", "
        << map_vector.get(2) << ", "
        << map_vector.get(3) << std::endl;

    sparse::ListVector<int, float> list_vector;
    list_vector.push_back(1, 1.0f);
    list_vector.push_back(2, 2.0f);
    list_vector.push_back(3, 3.0f);

    std::cout << "Map Vector: "
        << list_vector.get(0) << ", "
        << list_vector.get(1) << ", "
        << list_vector.get(2) << ", "
        << list_vector.get(3) << std::endl;

    return 0;
}
