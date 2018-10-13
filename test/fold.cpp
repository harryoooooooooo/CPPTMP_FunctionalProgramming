#include <iostream>
#include <cassert>
#include "baseType.hpp"
#include "list.hpp"
#include "utility.hpp"

template<class a, class b> // int -> bool -> int
struct f : add< a, typename cond<b, Int_<2>, Int_<-1>>::value >{};

template<class a, class b> // bool -> int -> int
struct g : add< typename cond<a, Int_<2>, Int_<-1>>::value, b >{};


using A = App<App<App<Empty,Bool_<true>>,Bool_<false>>,Bool_<true>>;
using B = typename concat<A,A>::value;
using C = foldl<f,Int_<1>,A>::value;
using D = foldl<f,Int_<1>,B>::value;
using E = foldr<g,Int_<1>,A>::value;
using F = foldr<g,Int_<1>,B>::value;

int main(){
    assert( 4 == C::toInt::real );
    assert( 7 == D::toInt::real );
    assert( 4 == E::toInt::real );
    assert( 7 == F::toInt::real );
    std::cout << "fold OK." << std::endl;
}
