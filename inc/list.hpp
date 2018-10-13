#ifndef LIST_HPP
#define LIST_HPP
#include "functor.hpp"
#include "monad.hpp"
#include "baseType.hpp"

/**************************
*        data List        *
**************************/
// for convenience, assume all elem less than 10, concat them literally
struct Empty{
    using toInt = Int_<0>;
};
// [1,2,3] `App` 4 = [1,2,3,4]
template<class L, class V>
struct App{
    using toInt = typename add<typename multiply<Int_<10>, typename L::toInt>::value, V>::value;
};
template<class V>
struct App<Empty,V>{
    using toInt = V;
};

// [1,2,3] `concat` [4,5,6] = [1,2,3,4,5,6]
// it should be in monoid
template<class L1, class L2>
struct concat;
template<class L>
struct concat<L,Empty>{
    using value = L;
};
template<class L1, class L2, class V>
struct concat<L1,App<L2,V>>{
    using value = App<typename concat<L1,L2>::value, V>;
};
// only work for List of List
template<class L>
struct concatAll;
template<>
struct concatAll<Empty>{
    using value = Empty;
};
template<class L, class V>
struct concatAll<App<L,V>>{
    using value = typename concat<typename concatAll<L>::value, V>::value;
};

// it should be in foldable
template<template <class...> class F, class S, class L>
struct foldl;
template<template <class...> class F, class S, class L, class V>
struct foldl<F,S,App<L,V>> : F< typename foldl<F,S,L>::value, V >{};
template<template <class...> class F, class S>
struct foldl<F,S,Empty>{
    using value = S;
};

template<template <class...> class F, class S, class L>
struct foldr;
template<template <class...> class F, class S, class L, class V>
struct foldr<F,S,App<L,V>> : foldr< F, typename F<V,S>::value, L >{};
template<template <class...> class F, class S, class V>
struct foldr<F,S,App<Empty,V>> : F< V, S >{};
template<template <class...> class F, class S>
struct foldr<F,S,Empty>{
    using value = S;
};

/**************************
*         Functor         *
**************************/
// instance Functor List
template<template <class> class F>
struct fmap<F,Empty>{
    using value = Empty;
};
template<template <class> class F, class L, class V>
struct fmap<F,App<L,V>>{
    using value = App<typename fmap<F,L>::value, typename F<V>::value>;
};


/**************************
*          Monad          *
**************************/
// instance Monad List
template<template <class> class F>
struct bind<Empty,F>{
    using value = Empty;
};
template<class L, class V, template <class> class F>
struct bind<App<L,V>,F>{
    using value = typename concatAll< typename fmap<F,App<L,V>>::value >::value;
};
#endif
