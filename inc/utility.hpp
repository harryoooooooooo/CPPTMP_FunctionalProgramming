// currying, deriving this with self name and max argument count
template<template <class...> class F, size_t MAX_ARG, class... argh>
struct _curry{
    static_assert(sizeof...(argh)<MAX_ARG, "too more arguments");
    template<class... argt> using curry = F<argh..., argt...>;
};

// conditional operator
template<class Cond, class Then, class Else>
struct cond;
template<class Then, class Else>
struct cond<Bool_<true>,Then,Else>{
    using value = Then;
};
template<class Then, class Else>
struct cond<Bool_<false>,Then,Else>{
    using value = Else;
};
