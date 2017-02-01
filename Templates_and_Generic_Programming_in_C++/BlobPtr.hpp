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

using namespace std;

template<typename T>
class BlobPtr
{
public:
    BlobPtr() : curr(0) {}
    BlobPtr(BlobPtr &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    
    T& operator*() const
    {
        auto p = check(curr, "dereference past end");
    }
    BlobPtr& operator++(); // prefix operators
    BlobPtr& operator--();
private:
    shared_ptr<vector<T>> check(size_t, const string&) const;
    weak_ptr<vector<T>> wptr;
    size_t curr;
};




#endif /* BlobPtr_hpp */
