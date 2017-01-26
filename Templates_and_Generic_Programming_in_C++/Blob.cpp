//
//  Blob.cpp
//  Templates_and_Generic_Programming_in_C++
//
//  Created by Ferenc Szalma on 1/26/17.
//  Copyright © 2017 Ferenc Szalma. All rights reserved.
//

#include "Blob.hpp"

template <typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template <typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "Back on empty Blob");
    return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "Subscript is out of range");
    return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}



