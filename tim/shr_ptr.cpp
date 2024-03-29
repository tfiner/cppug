// To compile this, make sure you have gcc-46:
//
// g++-4 -std=c++0x shr_ptr.cpp -o shr && ./shr
//
#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

class A {
public:
    virtual void update() = 0;
};

class B : public A {
public:
    virtual void update() { std::cout << __FUNCTION__ << std::endl; }
};

typedef std::shared_ptr< A > APtr;
typedef std::list< APtr > APtrs;

int main() {
    APtrs aptrs;
    aptrs.push_back( APtr(new B) );

    // C++98, this works for just about all compilers.
    for ( APtrs::iterator i = aptrs.begin(); i != aptrs.end(); ++i )
        (*i)->update();

    // C++11 auto keyword, compiler knows the type automatically.
    for ( auto i = aptrs.begin(); i != aptrs.end(); ++i )
        (*i)->update();

    // C++11, love the new for each.  Only GCC46
    for ( auto ap : aptrs )
        ap->update();

    // C++11 lambda, lambda, bo-blamda!  GCC46 & VS 2010 SP1 can do this.
    std::for_each( aptrs.begin(), aptrs.end(), [](APtr a) { a->update(); } );

    return 0;
}
