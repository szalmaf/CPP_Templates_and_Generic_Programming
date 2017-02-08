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
#include "BlobPtr.hpp"

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
//template <unsigned N, unsigned M>
//int compare(char (&p1)[N], char (&p2)[M])
//{
//    cout << N << endl;
//    return strcmp(p1, p2);
//}

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

template <typename T = int> // default type is int
class Numbers
{
public:
    Numbers(T n = 0) : n(n) {} // Default argument of constructor is 0
private:
    T n;
};

class DebugDelete // Class can replace `delete`; class has internal template function, the call operator
{
public:
    DebugDelete(ostream &s = cerr) : os(s) {}
    template<typename T> void operator()(T *p) const
    {
        cout << "Deleting unique pointer: " << endl;
        delete p;
    }
private:
    ostream &os;
};

// 16.25
// extern template class vector<string> // This declaration means that vector<string> template wont be instantiated in this file
// template class vector<Sales_data> // This declaration means that the vector<Sales_data> template will be instantiated in this file

// 16.26
class NoDefault
{
public:
    NoDefault();
    NoDefault(int i)
    {};
private:
    int i;
};

// 16.27
template<typename T> class Stack {};
void f1(Stack<char> x) {};
class Exercise
{
    Stack<double> & rsd;
    Stack<int> si;
};

template <typename T> void f1(T, T) {};
template <typename T1, typename T2> void f2(T1, T2) {};

// 16.40
template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0)
{
    return *beg;
}

// 16.41
// Trailing return type in decltype should guarantee to return sum
// If e.g. long long is exhausted, it won't work
template <typename T>
auto sum(T x, T y) -> decltype(x + y)
{
    return x + y;
}

class myInt
{
public:
    myInt(const int& i = 0) : i(i) {}
    myInt& operator++()
    {
        ++i;
        return *this;
    }
    myInt& operator--()
    {
        --i;
        return *this;
    }
private:
    int i;
};


// 16.42
template <typename T> void g(T&& val)
{
    int a = 1;
}
template <typename T> void gT(T val)
{
    int a = 1;
}
template <typename T> void gCrt(const T& val)
{
    int a = 1;
}
template <typename T> void gv(T&& val)
{
    vector<T> v;
}


int main(int argc, const char * argv[]) {

    myInt mi;
    auto& mi2 = ++mi;
    auto& mi3 = --mi;
    
    cout << compare(0, 1) << endl;
    
    string st1 = "Hello ", st2 = " World";
    char *ch1 = "Hello ", *ch2 = "World";
    cout << compare(st1, st2) << endl;
    cout << compare("Hello ", "World") << endl; // int compare(const char (&p1)[N], const char (&p2)[M])
    cout << compare(ch1, ch2);
    
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
    
    Numbers<long double> n1;
    Numbers<> n2; // Empty tempalte type argument -> need to use default int type as argument
    
    int *ip = new int;
    DebugDelete dd; // Deleter object
    dd(ip); // Delete int object will writing into cerr
    double *dp = new double;
    DebugDelete()(dp); // Create a temporary DebugDelete object then call it on the double
    unique_ptr<int, DebugDelete> up(new int, DebugDelete()); // point to and int and has specialize delete: DebugDelete() obj
    
    vector<int> vi = {1,2,3,4,5};
    Blob<int> bi(begin(vi), end(vi));
    
//    NoDefault nd; // no default constructor defined (only declared) so this wont work
    NoDefault nd2(1);
    vector<NoDefault> vnd;
    
    Stack<char> *sc;
    f1(*sc);
    int iObj = sizeof(Stack<string>);
    BlobPtr<int> bp(bi); cout << *bp << ", ";
    auto xx = ++bp; cout << *bp << ", ";
    auto yy = --bp; cout << *bp << endl;
    
    compare("hi", "world");
//    compare("bye", "dad"); // call to compare is ambiguous (const &T) vs const (*pc)[N]

    int i = 0, j = 42, *p1 = &i, *p2 = &j;
    const int *cp1 = &i, *cp2 = &j;
    f1(p1,p2);
    f2(p1,p2);
    f1(cp1,cp2);
    f2(cp1,cp2);
//    f1(p1,cp1); // cannot call on (*, const *) fn on (T, T)
    f2(p1,cp1);
    
//    auto v3 = {'a', 'b', 'c'};
//    auto v3 = {1,2,3};
    auto v3 = {2.1, 2.2, 2.3};
    auto pt = fcn3(v3.begin(), v3.end()); //returns int, int, couble
    
    auto s = sum(10000000000000000000, 10000000000000000000);
    
    int ii = 1;
    const int ci = ii;
    g(ii); // int&
    g(ci); // const int&
    g(ii * ci); // int&&
    gT(ii);
    gT(ci);
    gT(ii * ci);
    gCrt(ii);
    gCrt(ci);
    gCrt(ii * ci);
    gv(42);
//    gv(ii);  wont work: T will be int&, and vector<int&> can't be instantiated
    
    string s1("hi!"), s2;
    s2 = move(string("bye!"));
    s2 = move(s1);
    
    int iii = 1;
    int &&rvr = move(iii);
    
    std::cout << "Hello, World!\n";
    return 0;
}
