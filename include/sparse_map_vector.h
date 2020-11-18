// sparse_map_vector.h
// Copyright Laurence Emms 2020

#pragma once

#include <optional>
#include <unordered_map>

namespace sparse {

template <typename C, typename T>
class MapVector {
    std::unordered_map<C, T> _values;

public:
    MapVector() {}

    typename std::unordered_map<C, T>::iterator begin() {return _values.begin();}
    typename std::unordered_map<C, T>::iterator end() {return _values.end();}
    typename std::unordered_map<C, T>::const_iterator cbegin() {return _values.cbegin();}
    typename std::unordered_map<C, T>::const_iterator cend() {return _values.cend();}

    void insert(const C& c, const T& t);

    T get(const C& c) const;
};

template <typename C, typename T>
void MapVector<C, T>::insert(const C& c, const T& t) {
    _values.insert(std::make_pair(c, t));
}

template <typename C, typename T>
T MapVector<C, T>::get(const C& c) const {
    auto it = _values.find(c);
    if (it != _values.end()) {
        return it->second;
    }
    return static_cast<T>(0);
}

} // namespace sparse
