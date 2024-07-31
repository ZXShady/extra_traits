# extra_traits

simple library for some missing type traits I always need when making unreadable meta programs.

Minimum C++11 with support for variadic macros and variaidc templates and type traits library.

all these are available in namespace `zxshady::tmp` and all type traits have _t and _v shortcuts if available.


has_operator_*

| Category | Operator |
|---|---|
| Increment/Decrement | post_increment |
| | pre_decrement |
| | pre_increment |
| | post_increment |
| Unary | dereference |
| | negate |
| | complement |
| | unary_minus |
| | unary_plus |
| Bitwise | bit_and |
| | bit_or |
| | bit_xor |
| | bit_and_assign |
| | bit_or_assign |
| | bit_xor_assign |
| Shift | left_shift |
| | left_shift_assign |
| | right_shift |
| | right_shift_assign |
| Logical | logical_and |
| | logical_not |
| | logical_or |
| Arithmetic | plus |
| | minus |
| | modulus |
| | multiply |
| | divide |
| | plus_assign |
| | minus_assign |
| | modulus_assign |
| | multiply_assign |
| | divide_assign |
| Comparison | equal_to |
| | not_equal_to |
| | less |
| | less_equal |
| | greater |
| | greater_equal |
| Special | arrow |
| | subscript |
| | call |

each has_operator_\* has 4 static members

```cpp
has_operator_XXX<T>::member; // whether it is a member function
has_operator_XXX<T>::free; // whether it is a free function
has_operator_XXX<T>::overloaded; // equalivent to member || free
has_operator_XXX<T>::value; // whether it has the operator or not
```

simple type aliases

```cpp

template<std::size_t Value>
using index_constant = std::integral_constant<std::size_t,Value>;

// this is avaiable in C++17
template<auto Value> 
using constant = std::integral_constant<decltype(Value),Value>;


template<typename...>
using always_false = std::false_type; (var alias : false_v)

template<typename...>
using always_true = std::true_type; (var alias: true_v)

template<typename T,typename...>
using type_t = T;

template<typename T> // since C++14
using is_inheritable = bool_constant<std::is_class_v<T> && !std::is_final_v<T> >;

template<typename...>
struct empty_base {};

```

utility functions

```cpp
as_const(T&)
as_volatile(T&)
as_cv(T&)
forward_like<Like>(T&)
```

Standard Library Features in previous C++ versions
```cpp
// in "extra_traits/standard_library_features.hpp"
std::disjunction
std::conjunction
std::negation
std::is_null_pointer
std::bool_constant
std::type_identity
std::integer_sequence
std::remove_cvref
std::void_t
std::is_scoped_enum
std::is_bounded_array
std::is_unbounded_array
```

utility traits


```cpp
 template<typename Enum,typename OrElse>
 underlying_type_or<Enum,OrElse>::type // if `Enum` is an enum then get the underlying type otherwise OrElse type useful to not cause hard errors


 template<bool Condition,typename Base>
 inherit_if<Condition,Base>::type // if Condition is true then inherit from Base otherwise inherit from empty_base<Base>

```


unary traits
```cpp
is_scoped_enum<Enum>::value
is_unscoped_enum<Enum>::value
```

modifying traits
```cpp
remove_all_pointers<int******> -> int;
remove_all_pointers<float(*)[]> -> float[];
```

## Qualifications Copying and Maniplating Traits

- from [paper](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1016r0.pdf)

*Note each `copy_xxxxx` trait has a corrosponding `clone_xxxxx` (except `copy_signedness` there is no corrosponding `clone_signedness`)* which is equal to `copy_xxxxx<From,remove_xxxxx_t<To>>`*



<h3 id ="copy_const">
copy_const&ltFrom,To&gt 
</h3>
<details>
  <summary>Show Table</summary>
  
```cpp
From                  -> To
const From            -> const To
volatile From         -> To
const volatile From   -> const To
--------------------------------
From&                 -> To
const From&           -> To
volatile From&        -> To
const volatile From&  -> To
--------------------------------
From&&                -> To
const From&&          -> To
volatile From&&       -> To
const volatile From&& -> To
```
</details>  


<h3 id ="copy_volatile">
copy_volatile&ltFrom,To&gt 
</h3>
<details>
  <summary>Show Table</summary>
  
```cpp
From                  -> To
const From            -> To
volatile From         -> volatile To
const volatile From   -> volatile To
--------------------------------
From&                 -> To
const From&           -> To
volatile From&        -> To
const volatile From&  -> To
--------------------------------
From&&                -> To
const From&&          -> To
volatile From&&       -> To
const volatile From&& -> To
```
</details>  

## copy_cv<From,To>
<p> is a short cut for  <a href="#copy_const">copy_const_t</a>
&ltFrom,<a href="#copy_volatile">copy_volatile_t</a>&ltFrom,To&gt&gt
</p>

## copy_cv<From,To>
<p> is a short cut for  <a href="#copy_const">copy_const_t</a>
&ltFrom,<a href="#copy_volatile">copy_volatile_t</a>&ltFrom,To&gt&gt
</p>



<h3 id ="copy_reference">
copy_reference&ltFrom,To&gt 
</h3>
<details>
  <summary>Show Table</summary>
  
  # NOTE: this uses reference collapsing rules, which may not be wanted if you do not want it then use `clone_reference`.
```cpp
From                  -> To
const From            -> To
volatile From         -> To
const volatile From   -> To
--------------------------------
From&                 -> To&
const From&           -> To&
volatile From&        -> To&
const volatile From&  -> To&
--------------------------------
From&&                -> To&&
const From&&          -> To&&
volatile From&&       -> To&&
const volatile From&& -> To&&
```
</details>  

## copy_cvref<From,To>
a short cut for "copy_reference<From, [copy_reference_t](#copy_reference)<To, [copy_cv_t](#copy_cv)<remove_reference_t\<From\>, remove_reference_t\<To\>>>>"

<h3 id ="copy_pointer">
copy_pointer&ltFrom,To&gt 
</h3>
<details>
  <summary>Show Table</summary>
  
```cpp
From                  -> To
const From            -> To
volatile From         -> To
const volatile From   -> To
--------------------------------
From*                 -> To*
From*const            -> To*
From*volatile         -> To*
From*const volatile   -> To*
```
</details>  


<h3 id ="copy_all_pointers">
copy_all_pointers&ltFrom,To&gt 
</h3>
<details>
  <summary>Show Table</summary>
  
```cpp
From                  -> To
const From            -> To
volatile From         -> To
const volatile From   -> To
--------------------------------
From**                 -> To**
From**const            -> To**
From**volatile         -> To**
From**const volatile   -> To**
```
</details>  







<h3 id="is_explicitly_constructible">
is_explicitly_constructible<T,Args...>
</h3>
tests for whether the type is explicitly constructible given the Args


```cpp
using namespace zxshady::tmp;

struct A {
    explicit A(int,int);
    /*implicit*/ A(int,int,int);
};
is_explicitly_constructible<A,int,int>::value; // true
is_explicitly_constructible<A,int,int,int>::value; // false
is_explicitly_constructible<A,char*>::value; // false

```
## is_implicitly_constructible<T,Args...>

the opposite of [is_explicitly_constructible\<T,Args...\>](#is_explicitly_constructible) it checks whether the type is implictly constructible

```cpp
using namespace zxshady::tmp;

struct A {
    explicit A(int,int);
    /*implicit*/ A(int,int,int);
};
is_implicitly_constructible<A,int,int>::value; // false
is_implicitly_constructible<A,int,int,int>::value; // true
is_implicitly_constructible<A,char*>::value; // false
```


## type_list<Types...>

a container that contains types.

## *static members*
<p id="size"></p><details>
<summary>size</summary>
a static constant equal to `sizeof...(Types)`

```cpp
using List = type_list<int,char,long>;
static_assert(List::size == 3);
```
</details>

<p id="is_empty"></p><details>
<summary>is_empty</summary>
a static boolean constant equal to size == 0

```cpp
using List = type_list<int,char,long>;
using List2 = type_list<>;
static_assert(!List::is_empty);
static_assert(List2::is_empty);
```
</details>


<p id="at"></p><details>
<summary>at&ltIndex&gt</summary>
index into the types from the list.
if the index is out of bounds a `static_assert` will fire.

```cpp
using List = type_list<int,char,long>;
static_assert(std::is_same_v<char,List::template at<1>>);
```
</details>

<p id="at_or"></p><details>
<summary>at_or&ltIndex,OrType&gt</summary>
index into the types from the list. if the index is out of bounds
then returns the OrType instead of failing.
```cpp
using List = type_list<int,char,long>;
static_assert(std::is_same_v<long,List::template at_or<2,void>>); 
static_assert(std::is_same_v<void,List::template at_or<5,void>>);
```
</details>

<p id="front"></p><details>
<summary>front</summary>
equal to `List::template at<0>`

```cpp
using List = type_list<int,char,long>;
static_assert(std::is_same_v<int,List::front>); 
```
</details>


<p id="back"></p><details>
<summary>back</summary>
equal to `List::template at<size-1>`

```cpp
using List = type_list<int,char,long>;
static_assert(std::is_same_v<long,List::back>); 
```
</details>


<p id="push_back"></p><details>
<summary>push_back&ltT&gt</summary>
pushes T into the end of the list like `std::list::push_back`

```cpp
using List = type_list<int,char,long>;
using NewList = List::template push_back<const char*>;
static_assert(std::is_same_v<const char*,NewList::back>); 
```
</details>


<p id="push_front"></p><details>
<summary>push_front&ltT&gt</summary>
pushes T into the front of the list like `std::list::push_front`

```cpp
using List = type_list<int,char,long>;
using NewList = List::template push_front<const char*>;
static_assert(std::is_same_v<const char*,NewList::front>); 
```
</details>



<p id="append"></p><details>
<summary>append&ltTypes...&gt</summary>
pushes multiple Types into the end of the list.

```cpp
using List = type_list<int,char,long>;
using NewList = List::template append<void,const char*>;
static_assert(std::is_same_v<const char*,NewList::front>); 
static_assert(std::is_same_v<void,NewList::template at<3>>); 
```
</details>


<p id="prepend"></p><details>
<summary>prepend&ltTypes...&gt</summary>
pushes multiple Types into the front of the list.

```cpp
using List = type_list<int,char,long>;
using NewList = List::template prepend<void,const char*>;
static_assert(std::is_same_v<void,NewList::back>); 
static_assert(std::is_same_v<const char*,NewList::template at<1>>); 
```
</details>

<p id="reverse"></p><details>
<summary>reverse</summary>
reverses the list

```cpp
using List = type_list<int,char,long>;
using NewList = List::reverse;
static_assert(std::is_same_v<long,NewList::back>); 
static_assert(std::is_same_v<int,NewList::front>); 
```
</details>


<p id="pop_front"></p><details>
<summary>pop_front</summary>
pops the first type in the list

```cpp
using List = type_list<int,char,unsigned int,long>;
using NewList = List::pop_front;
static_assert(std::is_same_v<char,NewList::front>); 
```
</details>


<p id="pop_back"></p><details>
<summary>pop_back</summary>
pops the last type in the list

```cpp
using List = type_list<int,char,unsigned int,long>;
using NewList = List::pop_back;
static_assert(std::is_same_v<unsigned int,NewList::back>); 
```
</details>

<p id="transform"></p><details>
<summary>transform&ltTransformTrait&gt</summary>
apply the TransformTrait to every type in the list,

```cpp
using List = type_list<int,char,long>;
static_assert(std::is_same_v<List::template transform<std::add_const>,type_list<const int,const char,const long> >); 
```
</details>

<p id="rename_to"></p><details>
<summary>rename_to&ltTemplate&gt</summary>

```cpp
using List = type_list<int,custom_allocator<int>>;

static_assert(std::is_same_v<List::template rename_to<std::vector>,std::vector<int,custom_allocator<int>> >); 
```
</details>


<p id="insert"></p><details>
<summary>insert&ltIndex,Types...&gt</summary>

```cpp
using List = type_list<int,char,long>;

static_assert(std::is_same_v<List::template insert<1,unsigned int,void>,type_list<int,char,unsigned int ,void,long> >); 
```
</details>

<p id="erase"></p><details>
<summary>erase&ltIndex&gt</summary>

```cpp
using List = type_list<int,void,char>;

static_assert(std::is_same_v<List::template erase<1>,type_list<int,char> >); 
```
</details>


<p id="erase_if"></p><details>
<summary>erase_if&ltPredicate&gt</summary>

```cpp
using List = type_list<int,const void,char,const long>;

static_assert(std::is_same_v<List::template erase_if<std::is_const>,type_list<int,char> >); 
```
</details>

<p id="slice"></p><details>
<summary>slice&ltBegin,End = size&gt</summary>

```cpp
using List = type_list<int[1],int[2],int[3],int[4]>;

static_assert(std::is_same_v<List::template slice<0>,type_list<int[1],int[2],int[3],int[4]>>); 
static_assert(std::is_same_v<List::template slice<1>,type_list<int[2],int[3],int[4]>>);
static_assert(std::is_same_v<List::template slice<1,2>,type_list<int[1],int[4]>>); 
static_assert(std::is_same_v<List::template slice<4>>,type_list<>>); 

```
</details>


<p id="drop_first"></p><details>
<summary>drop_first&ltCount&gt</summary>

```cpp
using List = type_list<int[1],int[2],int[3],int[4]>;

static_assert(std::is_same_v<List::template drop_first<0>,type_list<int[1],int[2],int[3],int[4]>>); 
static_assert(std::is_same_v<List::template drop_first<1>,type_list<int[2],int[3],int[4]>>);
static_assert(std::is_same_v<List::template drop_first<2>,type_list<int[3],int[4]>>); 
static_assert(std::is_same_v<List::template drop_first<4>>,type_list<>>); 

```
</details>

<p id="drop_last"></p><details>
<summary>drop_last&ltCount&gt</summary>

```cpp
using List = type_list<int[1],int[2],int[3],int[4]>;

static_assert(std::is_same_v<List::template drop_last<0>,type_list<int[1],int[2],int[3],int[4]>>); 
static_assert(std::is_same_v<List::template drop_last<1>,type_list<int[1],int[2],int[3]>>);
static_assert(std::is_same_v<List::template drop_last<2>,type_list<int[1],int[2]>>); 
static_assert(std::is_same_v<List::template drop_last<4>>,type_list<>>); 
```

</details>


<p id="replace_at"></p><details>
<summary>replace_at&ltIndex,T&gt</summary>

```cpp
using List = type_list<int,char,long>;


static_assert(std::is_same_v<List::template replace_at<0,void>, type_list<void,char,long>>);
static_assert(std::is_same_v<List::template replace_at<1,void>, type_list<int,void,long>>);
static_assert(std::is_same_v<List::template replace_at<2,void>, type_list<int,char,void>>);

```
</details>

## Free Functions

<p id="find_if"></p><details>
<summary>find_if&ltPredicate,Pos = 0&gt</summary>
*note* returns std::size_t(-1) on not found 

```cpp
using List = type_list<int,char,const long,volatile void>;


static_assert(find_if<std::is_const>(List{}) == 2);
static_assert(find_if<std::is_void>(List{}) == 3);

```
</details>


<p id="find"></p><details>
<summary>find&ltT,Pos = 0&gt</summary>

```cpp
using List = type_list<int,char,long>;


static_assert(find<void>(List{}) == std::size_t(-1));
static_assert(find<char>(List{}) == 1);

```
</details>



there is still more methods.

documentation incomplete...