#include <iostream>
#include <cassert>
#include "baseType.hpp"
#include "maybe.hpp"
#include "utility.hpp"

template<class... a>
struct add4 : _curry<add4,4,a...>{};
template<class a, class b, class c, class d>
struct add4<a,b,c,d>{
    using t1 = typename add<a,b>::value;
    using t2 = typename add<t1,c>::value;
    using value = typename add<t2,d>::value;
};


// add4 :: int -> int -> int -> int -> int
using A = Int_<5>;
using B = add4<A,A,A,A>::value; // use add4 directly
using C = Just<Int_<10>>;
using D = fmap<add4<A,A,A>::curry,C>::value; // high-order function
template<class... T>
using E = add4<A>::curry<T...>; // E :: int -> int -> int -> int
template<class... T>
using F = E<A,A>::curry<T...>;  // F :: int -> int
using G = fmap<F,C>::value;

// F<A,A> a; // CE: too more arguments

int main(){
    assert( 20 == B::toInt::real );
    assert( 10 == C::toInt::real );
    assert( 25 == D::toInt::real );
    assert( 25 == G::toInt::real );
    std::cout << "Currying OK." << std::endl;
}
