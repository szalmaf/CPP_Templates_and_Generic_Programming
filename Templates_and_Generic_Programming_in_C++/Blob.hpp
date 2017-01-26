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

using namespace std;

// 16.1.2 Class Templates section
template <typename T> class Blob
{
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    Blob();
    Blob(initializer_list<T> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(move(t)); }
    void pop_back();
    T& back();
    T& operator[](size_type i);
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string &msg) const;
};


#endif /* Blob_hpp */
