//
//  Blob.hpp
//  Templates_and_Generic_Programming_in_C++
//
//  Created by Ferenc Szalma on 1/26/17.
//  Copyright © 2017 Ferenc Szalma. All rights reserved.
//

#ifndef Blob_hpp
#define Blob_hpp

#include <stdio.h>
#include <vector>
#include <functional>

using namespace std;

// 16.1.2 Class Templates section
template <typename T> class Blob
{
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    
    
    Blob();
    Blob(initializer_list<T> il);
    template<typename U> Blob(function<T(U)> fn, const Blob<U> &b);
    Blob(function<T(T)> fn, const Blob<T> &b);
    
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(move(t)); }
    void pop_back();
    T& back();
    T& operator[](size_type i);
    typename vector<T>::iterator begin() const { return (*data).begin(); };
    typename vector<T>::iterator end() const { return (*data).end(); };
    
    void fmaps(function<T(T)>); // fmap on self
    template <typename R> Blob<R> fmap(function<R(T)>);
    Blob<T> fmap(function<T(T)>);

private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string &msg) const;
};


template <typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template <typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

template <typename T>
Blob<T>::Blob(function<T(T)> fn, const Blob<T> &b) : data(make_shared<vector<T>>(b.size()))
{
    transform(b.begin(), b.end(), std::begin(*data), fn);
}

template <typename T>
template <typename U>
Blob<T>::Blob(function<T(U)> fn, const Blob<U> &b) : data(make_shared<vector<T>>(b.size()))
{
    transform(b.begin(), b.end(), std::begin(*data), fn);
}

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

template <typename T>
void Blob<T>::fmaps(function<T(T)> fn) {
    for_each(std::begin(*data), std::end(*data), fn);
//    transform(begin(*data), end(*data), begin(*data), fn);
}

template <typename T>
template <typename R>
Blob<R> Blob<T>::fmap(function<R(T)> fn) // Blob<int>::fmap(<double>)
{
    Blob<R> b(fn, *this); // construct Blob<double> from *this, which is Blob<int>
    return std::move(b);
}
template <typename T>
Blob<T> Blob<T>::fmap(function<T(T)> fn)
{
    Blob<T> b(fn, *this);
    return std::move(b);
}



#endif /* Blob_hpp */
