#ifndef BASETYPE_HPP
#define BASETYPE_HPP

/**************************
*        base type        *
**************************/
template<long long x>
struct Int_{
    using toInt = Int_<x>;
    static constexpr auto real = x;
};
template<bool x>
struct Bool_{
    using toInt = Int_<(long long)x>;
    static constexpr auto real = x;
};

/**************************
*       arithmetice       *
**************************/
// add Int
template<class a, class b>
struct add;

template<long long x, long long y>
struct add<Int_<x>, Int_<y>>{
    using value = Int_<x+y>;
};

// subtract Int
template<class a, class b>
struct sub;

template<long long x, long long y>
struct sub<Int_<x>, Int_<y>>{
    using value = Int_<x-y>;
};

// multiply Int
template<class a, class b>
struct multiply;

template<long long a, long long b>
struct multiply<Int_<a>, Int_<b>>{
    using value = Int_<a*b>;
};

// logical not
template<class a>
struct lnot;
template<bool a>
struct lnot<Bool_<a>>{
    using value = Bool_<(!a)>;
};

// logical and
template<class a, class b>
struct land;
template<bool a, bool b>
struct land<Bool_<a>,Bool_<b>>{
    using value = Bool_<(a&&b)>;
};

// logical or
template<class a, class b>
struct lor;
template<bool a, bool b>
struct lor<Bool_<a>,Bool_<b>>{
    using value = Bool_<(a||b)>;
};

// compare Int
template<class a, class b>
struct less;
template<long long x, long long y>
struct less<Int_<x>, Int_<y>>{
    using value = Bool_<(x<y)>;
};

template<class a, class b>
struct greater : less<b,a>{};

template<class a, class b>
struct lessEq : lnot<typename greater<a,b>::value>{};

template<class a, class b>
struct greaterEq : lnot<typename less<a,b>::value>{};

template<class a, class b>
struct eq : land<typename lessEq<a,b>::value, typename greaterEq<a,b>::value>{};

template<class a, class b>
struct neq : lnot<typename eq<a,b>::value>{};

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
#endif
