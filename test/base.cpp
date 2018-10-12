#include <iostream>
#include <cassert>
#include "baseType.hpp"
#include "list.hpp"
#include "maybe.hpp"

/**************************
*          Tools          *
**************************/
// if a < 5 then Nothing else Just (a-5)
template<class a>
struct safeSub5M : cond<typename less<a,Int_<5>>::value,
    Nothing,
    Just<typename sub<a,Int_<5>>::value>>{};

// simply add 3
template<class a>
struct add3{
    using value = typename add<a,Int_<3>>::value;
};
template<class a>
struct add3M{
    using value = Just<typename add3<a>::value>;
};

// tri 1 = [1,1,1]
template<class V>
struct tri{
    using value = App<App<App<Empty,V>,V>,V>;
};

// quick sort
template<class LS>
struct sort;
template<>
struct sort<Empty>{
    using value = Empty;
};
template<class V>
struct sort<App<Empty,V>>{
    using value = App<Empty,V>;
};
template<class LS, class PIVOT>
struct sort<App<LS,PIVOT>>{
    template<class x, class L> struct filterLess;
    template<class x, class L, class V>
    struct filterLess<x,App<L,V>> :
        concat< typename filterLess<x,L>::value, typename cond<typename less<V,x>::value,
            App<Empty,V>, Empty >::value >{};
    template<class x>
    struct filterLess<x,Empty>{ using value = Empty; };

    template<class x, class L> struct filterGreater;
    template<class x, class L, class V>
    struct filterGreater<x,App<L,V>> :
        concat< typename filterGreater<x,L>::value, typename cond<typename greaterEq<V,x>::value,
            App<Empty,V>, Empty>::value >{};
    template<class x>
    struct filterGreater<x,Empty>{ using value = Empty; };

    using lessPart    = typename sort< typename filterLess<PIVOT,LS>::value >::value;
    using greaterPart = typename sort< typename filterGreater<PIVOT,LS>::value >::value;
    using value       = typename concatAll< App<App<App<Empty, lessPart>, App<Empty,PIVOT>>, greaterPart> >::value;
};

int main (){
    { // Functor Maybe
        using A = Nothing;                  assert( -1 == A::toInt::real );
        using B = Just<Int_<3>>;            assert( 3  == B::toInt::real );
        std::cout << "Functor Maybe OK." << std::endl;
    }
    { // Monad Maybe
        using A = Just<Int_<12>>;           assert( 12 == A::toInt::real );
        using B = bind<A,safeSub5M>::value; assert( 7  == B::toInt::real );
        using C = bind<B,add3M>::value;     assert( 10 == C::toInt::real );
        using D = bind<C,safeSub5M>::value; assert( 5  == D::toInt::real );
        using E = bind<D,add3M>::value;     assert( 8  == E::toInt::real );
        using F = bind<E,safeSub5M>::value; assert( 3  == F::toInt::real );
        using G = bind<F,safeSub5M>::value; assert( -1 == G::toInt::real );
        using H = bind<G,add3M>::value;     assert( -1 == H::toInt::real );
        std::cout << "Monad Maybe OK." << std::endl;
    }
    { // Functor List
        using A = Empty;                    assert( 0     == A::toInt::real );
        using B = App<A, Int_<6>>;          assert( 6     == B::toInt::real );
        using C = App<B, Int_<4>>;          assert( 64    == C::toInt::real );
        using D = fmap<add3,C>::value;      assert( 97    == D::toInt::real );
        using E = concat<D,B>::value;       assert( 976   == E::toInt::real );
        using F = concatAll< App<App<App<Empty,D>,C>,B> >::value;
                                            assert( 97646 == F::toInt::real );
        using G = sort<F>::value;           assert( 46679 == G::toInt::real );
        std::cout << "Functor List OK." << std::endl;
    }
    { // Monad List
        using A = App<Empty,Int_<5>>;       assert( 5          == A::toInt::real );
        using B = bind<A,tri>::value;       assert( 555        == B::toInt::real );
        using C = bind<B,tri>::value;       assert( 555555555  == C::toInt::real );
        std::cout << "Monad List OK." << std::endl;
    }
}
