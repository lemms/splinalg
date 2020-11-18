// sparse_csr_mat.h
// Copyright Laurence Emms 2020

#pragma once

#include <cassert>
#include <vector>

namespace sparse {

template <typename C, typename T>
class CSRMatrix {
    std::vector<T> _values;
    std::vector<C> _columns;
    std::vector<C> _rows;
public:
    CSRMatrix() {_rows.push_back(static_cast<C>(0));}

    typename std::vector<C>::iterator row_begin_col(const C& i);
    typename std::vector<C>::iterator row_end_col(const C& i);
    typename std::vector<C>::const_iterator crow_begin_col(const C& i) const;
    typename std::vector<C>::const_iterator crow_end_col(const C& i) const;

    typename std::vector<T>::iterator row_begin(const C& i);
    typename std::vector<T>::iterator row_end(const C& i);
    typename std::vector<T>::const_iterator crow_begin(const C& i) const;
    typename std::vector<T>::const_iterator crow_end(const C& i) const;

    // Push back row
    void push_back_row(
        const std::vector<C>& columns,
        const std::vector<T>& values);

    // Linear access time in the rows
    T get(const C& i, const C& j) const;

    // Number of elements
    size_t size() const;
    size_t num_rows() const;
};

template <typename C, typename T>
typename std::vector<C>::iterator
CSRMatrix<C, T>::row_begin_col(const C& i)
{
    return _columns.begin() + _rows[i];
}

template <typename C, typename T>
typename std::vector<C>::iterator
CSRMatrix<C, T>::row_end_col(const C& i)
{
    return _columns.begin() + _rows[i + 1];
}

template <typename C, typename T>
typename std::vector<C>::const_iterator
CSRMatrix<C, T>::crow_begin_col(const C& i) const
{
    return _columns.cbegin() + _rows[i];
}

template <typename C, typename T>
typename std::vector<C>::const_iterator
CSRMatrix<C, T>::crow_end_col(const C& i) const
{
    return _columns.cbegin() + _rows[i + 1];
}

template <typename C, typename T>
typename std::vector<T>::iterator
CSRMatrix<C, T>::row_begin(const C& i)
{
    return _values.begin() + _rows[i];
}

template <typename C, typename T>
typename std::vector<T>::iterator
CSRMatrix<C, T>::row_end(const C& i)
{
    return _values.begin() + _rows[i + 1];
}

template <typename C, typename T>
typename std::vector<T>::const_iterator
CSRMatrix<C, T>::crow_begin(const C& i) const
{
    return _values.cbegin() + _rows[i];
}

template <typename C, typename T>
typename std::vector<T>::const_iterator
CSRMatrix<C, T>::crow_end(const C& i) const
{
    return _values.cbegin() + _rows[i + 1];
}

template <typename C, typename T>
void CSRMatrix<C, T>::push_back_row(
    const std::vector<C>& columns,
    const std::vector<T>& values)
{
    assert(columns.size() == values.size());
    _values.insert(_values.end(), values.begin(), values.end());
    _columns.insert(_columns.end(), columns.begin(), columns.end());
    _rows.push_back(_rows.back() + columns.size());
}

// Linear access time in the rows
template <typename C, typename T>
T CSRMatrix<C, T>::get(const C& i, const C& j) const
{
    C row_start = _rows[i];
    C row_end = _rows[i + 1];
    for (C c = row_start; c < row_end; ++c) {
        if (_columns[c] == j) {
            return _values[c];
        }
    }
    return static_cast<T>(0);
}

// Number of elements
template <typename C, typename T>
size_t CSRMatrix<C, T>::size() const
{
    return _values.size();
}

template <typename C, typename T>
size_t CSRMatrix<C, T>::num_rows() const
{
    return _rows.size() - 1;
}

} // namespace sparse
