// sparse_csr_mat_operations.h
// Copyright Laurence Emms 2020

#pragma once

namespace sparse {

template <typename C, typename T>
class CSRMatrix;

template <typename C, typename T>
class ListVector;

template <typename C, typename T>
class MapVector;

// out must be an empty vector
template <typename C, typename T>
void matmul(ListVector<C, T>& out, const CSRMatrix<C, T>& mat, const ListVector<C, T>& in)
{
    for (int r = 0, r_end = mat.num_rows(); r < r_end; ++r) {
        typename std::vector<C>::const_iterator col_begin = mat.crow_begin_col(r);
        typename std::vector<C>::const_iterator col_end = mat.crow_end_col(r);
        typename std::vector<T>::const_iterator col_value = mat.crow_begin(r);
        if (col_begin == col_end) {
            // Empty row
            continue;
        }
        T acc = static_cast<T>(0);
        typename std::vector<std::pair<C, T>>::const_iterator in_it = in.cbegin();
        for (; col_begin != col_end && in_it != in.cend(); ++col_begin, ++col_value) {
            while (in_it->first < *col_begin) {
                ++in_it;
            }
            if (in_it->first == *col_begin) {
                acc += *col_value * in_it->second;
            }
        }
        out.push_back(r, acc);
    }
}

// out must be an empty vector
template <typename C, typename T>
void matmul(MapVector<C, T>& out, const CSRMatrix<C, T>& mat, const MapVector<C, T>& in)
{
    for (int r = 0, r_end = mat.num_rows(); r < r_end; ++r) {
        typename std::vector<C>::const_iterator col_begin = mat.crow_begin_col(r);
        typename std::vector<C>::const_iterator col_end = mat.crow_end_col(r);
        typename std::vector<T>::const_iterator col_value = mat.crow_begin(r);
        if (col_begin == col_end) {
            // Empty row
            continue;
        }
        T acc = static_cast<T>(0);
        for (; col_begin != col_end; ++col_begin, ++col_value) {
            acc += *col_value * in.get(*col_begin);
        }
        out.insert(r, acc);
    }
}

} // namespace sparse
