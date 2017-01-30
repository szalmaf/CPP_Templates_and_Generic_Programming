//
//  main.cpp
//  Templates_and_Generic_Programming_in_C++
//
//  Created by Ferenc Szalma on 8/5/16.
//  Copyright © 2016 Ferenc Szalma. All rights reserved.
//

// C++ Primer, Chapter 16, Templates and Generic Programming

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Blob.hpp"

using namespace std;

// 16.2 compare()
// Template parameter list can't be empty
template <typename T>
int compare(const T& v1, const T& v2)
{
    if(v1 > v2) return -1;
    if(v1 < v2) return 1;
    return 0;
}
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    cout << N << endl;
    return strcmp(p1, p2);
}

class A
{
public:
    int Counter;
};
template<A* aa> // non-type template parameter of type pointer to A
struct Coin
{
    static void DoStuff()
    {
        aa->Counter;
    }
};
A a;

// inline is after template
template <typename T>
inline T min(const T&, const T&);

// Defining class template
template <class T> class Queue
{
public:
    Queue();
    T &front();
    const T& front() const;
    void push(const T&);
    void pop();
    bool empty() const;
private:
    
};

template <typename T> int compare(const T&, const T&);
int (*pf1) (const int&, const int&) = compare;

template<class Type> Type calc(const Type* array, int size);
template<class Type> Type fcn(Type p1, Type p2);
double dobj;
float fobj;
char cobj;
int ai[5] = {2,3,4,5,6};
// char c = calc(cobj, 'c');
// double d = calc(dobj, fobj);
// int i = fcn(ai, cobj);

void func(int (*) (const int&, const int&)); // func is a pointer to a fn
void func(int (*) (const string&, const string&));
// func(compare<int>);

// 16.4
template<typename IT, typename T>
bool findp(const IT & itb, const IT & ite, const T & val)
{
    auto it = itb;
//    while(it != ite && *it != val) // Iterate until end of list or until it finds the element
//        ++it;
//    auto it2 = itb + 2; // Cant't add 2 if itb is a list operator
    for(; it != ite && *it != val; ++it);
    if(it != ite)
        return true;
    else
        return false;
}

// 16.5
template<unsigned N, typename T>
void print(const T (&itb)[N]) // Takes a ref to an array of T type and of size N
{
    auto it = itb;
    for(; it != (itb+N); ++it)
        cout << *it << endl;
}

// 16.6
template<unsigned N, typename T>
const T * beginMy(const T (&arr)[N])
{
    return arr;
}
template<unsigned N, typename T>
const T * endMy(const T (&arr)[N])
{
    return arr + N;
}

// 16.7
template<unsigned N, typename T>
constexpr unsigned arr_size(const T (&arr)[N])
{
    return N;
}

template <typename T> // T is a container type
typename T::value_type top(const T& c) // top function returns T's value_type
{
    if (!c.emtpy())
        return c.back();
    else
        return typename T::value_type(); // T::value_type() returns the default value for the T containers eleme type's (e.g. for vector<int> it returns a (int)0)
}



// 16.19
template<typename C = vector<int>> // Default template argument is vector<int>
void prn(const C& c)
{
    for(typename C::size_type i = 0; i < c.size(); ++i)
        cout << c[i] << endl;
}
template<typename C = vector<int>>
void prn2(const C& c)
{
    for(auto it = begin(c); it < end(c); ++it)
        cout << *it << endl;
}

template <typename T, typename F = less<T>> // Default template parameter, a function, F, which set to the less<T> class fn
int compare2(const T& v1, const T& v2, F f = F()) // f = F() says to use less<T> as default; F f without = F(), no default fn, fn must be provided
{
    if(f(v1, v2))
        return -1;
    else if(f(v2, v1))
        return 1;
    return 0;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    cout << compare(0, 1) << endl;
    
    string st1 = "Hello ", st2 = " World";
    cout << compare(st1, st2) << endl;
    cout << compare("Hello ", "World") << endl; // int compare(const char (&p1)[N], const char (&p2)[M])
    
// error    cout << compare(short(1), 1) << endl;

//    &p refers to a global object, which has static lifetime, so it can be a non-type template parameter
    Coin<&a>::DoStuff();
    cout << a.Counter << endl;

//    Won't compile since the A class does not have operator<, which is needed in compare()
//    A a1, a2;
//    compare(a1, a2);
    
    vector<int> v{1,2,3,4};
    bool bv = findp(v.begin(), v.end(), 4);
    list<string> sl{"hello", "world"};
    bool bl = findp(sl.begin(), sl.end(), "world");
    
    char ca[] = {'a','b','c'};
    print(ca);
    
    auto aitb = beginMy(ca);
    auto aite = endMy(ca);
    auto prnt = [](auto x){ cout << x << endl; };
    for_each(aitb, aite, prnt);
    
    unsigned n = arr_size(ca);
    
    Blob<int> ia;
    Blob<int> ia2 = {0,1,2,3,4};
    Blob<int> squares = {0,1,2,3,4,5,6,7,8,9};
    squares.fmaps([](auto x){ return x*x; });
    auto sqfn = [](int x){ return x*x; };
    auto srqs = squares.fmap(sqfn);
    function<double(int)> tms = [](auto x){ return 2.5 * x; };
    auto srqs2 = squares.fmap(tms);
    auto tupfn = [](auto x){ return std::move(make_tuple(x, x*x, x*x*x)); };
//    function<tuple<int, int, int>(int)> tupfn = [](auto x){ return std::move(make_tuple(x, x*x, x*x*x)); };
    auto tpl = tupfn(2);
    auto sqrs3 = squares.fmap(tupfn);
    Blob<tuple<int, int, int>> sqrs4(tupfn, squares); // Use Blob fmap helper constructor instead of fmap above; strangely, need return signature
    auto a = string();
    
    
    prn<vector<int>>({1,2,3});
    prn2<vector<int>>({1,2,3});
    prn<>({1,2,3});
    prn2<>({1,2,3});
    
    auto comp = compare2(1,2);
    
    std::cout << "Hello, World!\n";
    return 0;
}
