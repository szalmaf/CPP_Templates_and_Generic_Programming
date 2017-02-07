//
//  BlobPtr.hpp
//  Templates_and_Generic_Programming_in_C++
//
//  Created by Ferenc Szalma on 2/1/17.
//  Copyright © 2017 Ferenc Szalma. All rights reserved.
//

#ifndef BlobPtr_hpp
#define BlobPtr_hpp

#include <stdio.h>
#include <memory>
#include <vector>
#include "Blob.hpp"

using namespace std;


template <typename> class Blob; // forward declaration, needed in BlobPtr constructor

template<typename T>
class BlobPtr
{
public:
    BlobPtr() : curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    
    T& operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++(); // prefix operators
    BlobPtr& operator--();
private:
    shared_ptr<vector<T>> check(size_t, const string&) const;
    weak_ptr<vector<T>> wptr;
    size_t curr;
};


template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
    check(++curr, "beyond end of container");
    return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
    check(--curr, "before start of container");
    return *this;
}

template<typename T>
shared_ptr<vector<T>> BlobPtr<T>::check(size_t s, const string& str) const
{
    auto srdp = wptr.lock();
    if(s < srdp->size())
        return move(srdp);
    else
        throw out_of_range(str);
}


#endif /* BlobPtr_hpp */
