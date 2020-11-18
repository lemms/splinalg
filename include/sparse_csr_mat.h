// sparse_csr_mat.h
// Copyright Laurence Emms 2020

#pragma once

#include <cassert>
#include <vector>

namespace sparse {

template <typename C, typename T>
class CSRMatrix {
    C _current_row_end;
    C _num_rows;
    C _num_cols;
    std::vector<T> _values;
    std::vector<C> _columns;
    std::vector<C> _rows;
public:
    CSRMatrix(const C& num_rows, const C& num_cols);

    typename std::vector<C>::iterator row_begin_col(const C& i);
    typename std::vector<C>::iterator row_end_col(const C& i);
    typename std::vector<C>::const_iterator crow_begin_col(const C& i) const;
    typename std::vector<C>::const_iterator crow_end_col(const C& i) const;

    typename std::vector<T>::iterator row_begin(const C& i);
    typename std::vector<T>::iterator row_end(const C& i);
    typename std::vector<T>::const_iterator crow_begin(const C& i) const;
    typename std::vector<T>::const_iterator crow_end(const C& i) const;

    void add_row();

    // Push element into current row
    void push(const C& c, const T& t);

    // Push back row
    void push_back_row(
        const std::vector<C>& columns,
        const std::vector<T>& values);

    // Linear access time in the rows
    T get(const C& i, const C& j) const;

    // Number of elements
    size_t size() const;
    size_t num_rows() const;
    size_t num_cols() const;
};

template <typename C, typename T>
CSRMatrix<C, T>::CSRMatrix(const C& num_rows, const C& num_cols) :
    _current_row_end(0),
    _num_rows(num_rows),
    _num_cols(num_cols)
{
    _rows.reserve(_num_rows + 1);
    _rows.push_back(static_cast<C>(0));
}

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
void CSRMatrix<C, T>::add_row()
{
    assert(_current_row_end < _num_rows + 1);
    _rows.push_back(_rows.back());
    ++_current_row_end;
}

// Push element into current row
template <typename C, typename T>
void CSRMatrix<C, T>::push(const C& c, const T& v)
{
    _columns.push_back(c);
    _values.push_back(v);
    ++_rows[_current_row_end];
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
    ++_current_row_end;
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
    return _num_rows;
}

template <typename C, typename T>
size_t CSRMatrix<C, T>::num_cols() const
{
    return _num_cols;
}

} // namespace sparse
