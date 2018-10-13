#ifndef MAYBE_HPP
#define MAYBE_HPP
#include "functor.hpp"
#include "monad.hpp"
#include "baseType.hpp"

/**************************
*        data Maybe       *
**************************/
// for convenience, Nothing equal to -1, Just i equal to i
struct Nothing{
    using toInt = Int_<-1>;
};
template<class T>
struct Just{
    using toInt = T;
};


/**************************
*         Functor         *
**************************/
// instance Functor Maybe
template<template <class...> class F>
struct fmap<F,Nothing>{
    using value = Nothing;
};
template<template <class...> class F, class V>
struct fmap<F,Just<V>>{
    using value = Just<typename F<V>::value>;
};


/**************************
*          Monad          *
**************************/
// instance Monad Maybe
template<template <class...> class F>
struct bind<Nothing,F>{
    using value = Nothing;
};
template<class V, template <class...> class F>
struct bind<Just<V>,F>{
    using value = typename F<V>::value;
};
#endif
