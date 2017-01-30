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
#include <type_traits>

using namespace std;

// 16.1.2 Class Templates section
template <typename T> class Blob
{
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    // per http://stackoverflow.com/questions/26665152/compiler-does-not-deduce-template-parameters-map-stdvector-stdvector/26665222?noredirect=1#comment70983575_26665222
    template<typename F> using result_of_t = typename result_of<F>::type;
    
    Blob();
    Blob(initializer_list<T> il);
    template<typename Func, typename U> Blob(Func fn, const Blob<U> &b); // fmap helper constructor; Func is T(U)
    template<typename IT> Blob(IT, IT);
    
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
    template <typename Func> Blob<result_of_t<Func(T)>> fmap(Func);

private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string &msg) const;
};


template <typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template <typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

template <typename T>
template <typename Func, typename U> // Func signature is T(U)
Blob<T>::Blob(Func fn, const Blob<U> &b) : data(make_shared<vector<T>>(b.size()))
{
    transform(b.begin(), b.end(), std::begin(*data), fn);
}

template<typename T>
template<typename IT>
Blob<T>::Blob(IT b, IT e) : data(make_shared<vector<int>>(b, e)) {}

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
template <typename Func>
Blob<result_of_t<Func(T)>> Blob<T>::fmap(Func fn) // Blob<int>::fmap(<double>)
{
    Blob<result_of_t<Func(T)>> b(fn, *this); // construct Blob<double> from *this, which is Blob<int>
    return std::move(b);
}


#endif /* Blob_hpp */
