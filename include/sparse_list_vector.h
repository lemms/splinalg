// Copyright Laurence Emms 2020

#pragma once

#include <optional>
#include <vector>

namespace sparse {

template <typename C, typename T>
class ListVector {
    std::vector<std::pair<C, T>> _values;

public:
    ListVector() {}

    typename std::vector<std::pair<C, T>>::iterator begin() {return _values.begin();}
    typename std::vector<std::pair<C, T>>::iterator end() {return _values.end();}
    typename std::vector<std::pair<C, T>>::const_iterator cbegin() {return _values.cbegin();}
    typename std::vector<std::pair<C, T>>::const_iterator cend() {return _values.cend();}

    // Values must be inserted in coordinate order
    void push_back(const C& c, const T& t);

    T get(const C& c) const;
};

template <typename C, typename T>
void
ListVector<C, T>::push_back(const C& c, const T& t) {
    _values.push_back(std::make_pair(c, t));
}

template <typename C, typename T>
T ListVector<C, T>::get(const C& c) const {
    typename std::vector<std::pair<C, T>>::const_iterator iterator = _values.begin();
    while (iterator != _values.end()) {
        if (iterator->first == c) {
            return iterator->second;
        }
        iterator++;
    }
    return static_cast<T>(0);
}

} // namespace sparse
