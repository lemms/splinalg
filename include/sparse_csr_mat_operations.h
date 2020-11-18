// sparse_csr_mat_operations.h
// Copyright Laurence Emms 2020

#pragma once

#include "sparse_csr_mat.h"

namespace sparse {

// out must be an empty vector
template <typename C, typename T, template <typename, typename> typename V>
void matmul(V<C, T>& out, const CSRMatrix<C, T>& mat, const V<C, T>& in)
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
        out.push_back(r, acc);
    }
}

} // namespace sparse
