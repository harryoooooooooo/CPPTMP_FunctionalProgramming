# CPPTMP_FunctionalProgramming
implement functional programming by C++ template meta programming

## Rules
* Functions' return value is stored in the member type **value**. ex. `f<x,y>::value`
* Struct names starting with uppercase are *Type Constructors*. They are final type, thus there is no member **value**. For convenience, they can be converted to Int_<> by **toInt**. ex. `Just<Int_<5>>::toInt`

## Base type
In order to deal all the stuff only on **type**, that is, not something **non-type**(ex. 7, 'a', false). We wrap int and bool to Int_<> and Bool_<>. The member **real** is a real variable, so we can print them by cout. ex. `Int_<12>::real`

## Maybe
constructors:
* `Nothing::toInt` == `Int_<-1>`
* `Just<Int_<8>>::toInt` == `Int_<8>`

## List
constructors:
* `Empty::toInt` == `Int_<0>`
* `App<App<App<Empty,Int_<2>>,Int_<1>>,Int_<3>>::toInt` == `Int_<213>`. Simply concat them. It would mess up if elems are not in [1..9], but it is just a presentation error.
