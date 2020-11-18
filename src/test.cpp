// test.cpp
// Copyright Laurence Emms 2020

#include <iostream>

#include "sparse_csr_mat.h"
#include "sparse_csr_mat_operations.h"
#include "sparse_list_vector.h"
#include "sparse_map_vector.h"

int main(int argc, char** argv) {
    std::cout << "Test Sparse Linear Algebra Library." << std::endl;

    sparse::ListVector<int, float> list_vector;
    list_vector.push_back(1, 1.0f);
    list_vector.push_back(2, 2.0f);
    list_vector.push_back(3, 3.0f);

    std::cout << "List Vector: "
        << list_vector.get(0) << ", "
        << list_vector.get(1) << ", "
        << list_vector.get(2) << ", "
        << list_vector.get(3) << std::endl;

    sparse::MapVector<int, float> map_vector;
    map_vector.insert(1, 1.0f);
    map_vector.insert(2, 2.0f);
    map_vector.insert(3, 3.0f);

    std::cout << "Map Vector: "
        << map_vector.get(0) << ", "
        << map_vector.get(1) << ", "
        << map_vector.get(2) << ", "
        << map_vector.get(3) << std::endl;


    sparse::CSRMatrix<int, float> csr_matrix(4, 4);

    csr_matrix.push_back_row({0}, {1.0f});
    csr_matrix.push_back_row({1}, {2.0f});
    csr_matrix.push_back_row({2}, {3.0f});
    csr_matrix.push_back_row({3}, {4.0f});

    std::cout << "CSR Matrix:" << std::endl;
    std::cout << csr_matrix.get(0, 0) << ", "
        << csr_matrix.get(0, 1) << ", "
        << csr_matrix.get(0, 2) << ", "
        << csr_matrix.get(0, 3) << std::endl;
    std::cout << csr_matrix.get(1, 0) << ", "
        << csr_matrix.get(1, 1) << ", "
        << csr_matrix.get(1, 2) << ", "
        << csr_matrix.get(1, 3) << std::endl;
    std::cout << csr_matrix.get(2, 0) << ", "
        << csr_matrix.get(2, 1) << ", "
        << csr_matrix.get(2, 2) << ", "
        << csr_matrix.get(2, 3) << std::endl;
    std::cout << csr_matrix.get(3, 0) << ", "
        << csr_matrix.get(3, 1) << ", "
        << csr_matrix.get(3, 2) << ", "
        << csr_matrix.get(3, 3) << std::endl;

    sparse::ListVector<int, float> list_mul_vector;

    sparse::matmul(list_mul_vector, csr_matrix, list_vector);

    std::cout << "List mul Vector: "
        << list_mul_vector.get(0) << ", "
        << list_mul_vector.get(1) << ", "
        << list_mul_vector.get(2) << ", "
        << list_mul_vector.get(3) << std::endl;

    sparse::MapVector<int, float> map_mul_vector;

    sparse::matmul(map_mul_vector, csr_matrix, map_vector);

    std::cout << "Map mul Vector: "
        << map_mul_vector.get(0) << ", "
        << map_mul_vector.get(1) << ", "
        << map_mul_vector.get(2) << ", "
        << map_mul_vector.get(3) << std::endl;

    sparse::CSRMatrix<int, float> mul_matrix(4, 4);

    mul_matrix.push_back_row({0, 1, 2, 3}, {1.0f, 2.0f, 3.0f, 4.0f});
    mul_matrix.push_back_row({0, 1, 2, 3}, {5.0f, 6.0f, 7.0f, 8.0f});
    mul_matrix.push_back_row({0, 1, 2, 3}, {9.0f, 10.0f, 11.0f, 12.0f});
    mul_matrix.push_back_row({0, 1, 2, 3}, {13.0f, 14.0f, 15.0f, 16.0f});

    std::cout << "Mul Matrix:" << std::endl;
    std::cout << mul_matrix.get(0, 0) << ", "
        << mul_matrix.get(0, 1) << ", "
        << mul_matrix.get(0, 2) << ", "
        << mul_matrix.get(0, 3) << std::endl;
    std::cout << mul_matrix.get(1, 0) << ", "
        << mul_matrix.get(1, 1) << ", "
        << mul_matrix.get(1, 2) << ", "
        << mul_matrix.get(1, 3) << std::endl;
    std::cout << mul_matrix.get(2, 0) << ", "
        << mul_matrix.get(2, 1) << ", "
        << mul_matrix.get(2, 2) << ", "
        << mul_matrix.get(2, 3) << std::endl;
    std::cout << mul_matrix.get(3, 0) << ", "
        << mul_matrix.get(3, 1) << ", "
        << mul_matrix.get(3, 2) << ", "
        << mul_matrix.get(3, 3) << std::endl;

    sparse::CSRMatrix<int, float> out_mul_matrix(4, 4);

    sparse::matmul(out_mul_matrix, mul_matrix, mul_matrix);

    std::cout << "Out mul Matrix:" << std::endl;
    std::cout << out_mul_matrix.get(0, 0) << ", "
        << out_mul_matrix.get(0, 1) << ", "
        << out_mul_matrix.get(0, 2) << ", "
        << out_mul_matrix.get(0, 3) << std::endl;
    std::cout << out_mul_matrix.get(1, 0) << ", "
        << out_mul_matrix.get(1, 1) << ", "
        << out_mul_matrix.get(1, 2) << ", "
        << out_mul_matrix.get(1, 3) << std::endl;
    std::cout << out_mul_matrix.get(2, 0) << ", "
        << out_mul_matrix.get(2, 1) << ", "
        << out_mul_matrix.get(2, 2) << ", "
        << out_mul_matrix.get(2, 3) << std::endl;
    std::cout << out_mul_matrix.get(3, 0) << ", "
        << out_mul_matrix.get(3, 1) << ", "
        << out_mul_matrix.get(3, 2) << ", "
        << out_mul_matrix.get(3, 3) << std::endl;

    return 0;
}
