// sparse_csc_mat.h
// Copyright Laurence Emms 2020

#pragma once

#include <cassert>
#include <vector>

namespace sparse {

template <typename C, typename T>
class CSCMatrix {
    C _current_col_end;
    C _num_rows;
    C _num_cols;
    std::vector<T> _values;
    std::vector<C> _rows;
    std::vector<C> _columns;
public:
    CSCMatrix(const C& num_rows, const C& num_cols);

    typename std::vector<C>::iterator col_begin_row(const C& i);
    typename std::vector<C>::iterator col_end_row(const C& i);
    typename std::vector<C>::const_iterator ccol_begin_row(const C& i) const;
    typename std::vector<C>::const_iterator ccol_end_row(const C& i) const;

    typename std::vector<T>::iterator col_begin(const C& i);
    typename std::vector<T>::iterator col_end(const C& i);
    typename std::vector<T>::const_iterator ccol_begin(const C& i) const;
    typename std::vector<T>::const_iterator ccol_end(const C& i) const;

    void add_col();

    // Push element into current column
    void push(const C& c, const T& t);

    // Push back column
    void push_back_col(
        const std::vector<C>& rows,
        const std::vector<T>& values);

    // Linear access time in the columns
    T get(const C& i, const C& j) const;

    // Number of elements
    size_t size() const;
    size_t num_rows() const;
    size_t num_cols() const;

    void clear();
};

template <typename C, typename T>
CSCMatrix<C, T>::CSCMatrix(const C& num_rows, const C& num_cols) :
    _current_col_end(0),
    _num_rows(num_rows),
    _num_cols(num_cols)
{
    _columns.reserve(_num_cols + 1);
    _columns.push_back(static_cast<C>(0));
}

template <typename C, typename T>
typename std::vector<C>::iterator
CSCMatrix<C, T>::col_begin_row(const C& i)
{
    return _rows.begin() + _columns[i];
}

template <typename C, typename T>
typename std::vector<C>::iterator
CSCMatrix<C, T>::col_end_row(const C& i)
{
    return _rows.begin() + _columns[i + 1];
}

template <typename C, typename T>
typename std::vector<C>::const_iterator
CSCMatrix<C, T>::ccol_begin_row(const C& i) const
{
    return _rows.cbegin() + _columns[i];
}

template <typename C, typename T>
typename std::vector<C>::const_iterator
CSCMatrix<C, T>::ccol_end_row(const C& i) const
{
    return _rows.cbegin() + _columns[i + 1];
}

template <typename C, typename T>
typename std::vector<T>::iterator
CSCMatrix<C, T>::col_begin(const C& i)
{
    return _values.begin() + _columns[i];
}

template <typename C, typename T>
typename std::vector<T>::iterator
CSCMatrix<C, T>::col_end(const C& i)
{
    return _values.begin() + _columns[i + 1];
}

template <typename C, typename T>
typename std::vector<T>::const_iterator
CSCMatrix<C, T>::ccol_begin(const C& i) const
{
    return _values.cbegin() + _columns[i];
}

template <typename C, typename T>
typename std::vector<T>::const_iterator
CSCMatrix<C, T>::ccol_end(const C& i) const
{
    return _values.cbegin() + _columns[i + 1];
}

template <typename C, typename T>
void CSCMatrix<C, T>::add_col()
{
    assert(_current_col_end < _num_cols + 1);
    _columns.push_back(_columns.back());
    ++_current_col_end;
}

// Push element into current row
template <typename C, typename T>
void CSCMatrix<C, T>::push(const C& c, const T& v)
{
    _rows.push_back(c);
    _values.push_back(v);
    ++_columns[_current_col_end];
}

template <typename C, typename T>
void CSCMatrix<C, T>::push_back_col(
    const std::vector<C>& rows,
    const std::vector<T>& values)
{
    assert(rows.size() == values.size());
    _values.insert(_values.end(), values.begin(), values.end());
    _rows.insert(_rows.end(), rows.begin(), rows.end());
    _columns.push_back(_columns.back() + rows.size());
    ++_current_col_end;
}

// Linear access time in the columns
template <typename C, typename T>
T CSCMatrix<C, T>::get(const C& i, const C& j) const
{
    if (j < static_cast<C>(_columns.size() - 1)) {
        C col_start = _columns[j];
        C col_end = _columns[j + 1];
        for (C r = col_start; r < col_end; ++r) {
            if (_rows[r] == i) {
                return _values[r];
            }
        }
    }
    return static_cast<T>(0);
}

// Number of elements
template <typename C, typename T>
size_t CSCMatrix<C, T>::size() const
{
    return _values.size();
}

template <typename C, typename T>
size_t CSCMatrix<C, T>::num_rows() const
{
    return _num_rows;
}

template <typename C, typename T>
size_t CSCMatrix<C, T>::num_cols() const
{
    return _num_cols;
}

template <typename C, typename T>
void CSCMatrix<C, T>::clear()
{
    _current_col_end = 0;
    _values.clear();
    _rows.clear();
    _columns.clear();
    _columns.push_back(static_cast<C>(0));
}

} // namespace sparse
