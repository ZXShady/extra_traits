# extra_traits

simple library for some missing type traits I always need.

Minimum C++11 with support for variadic macros and variaidc templates

all these are avaiablein namespace `zxshady::tmp` and all type traits have _t and _v shortcuts if aviable.


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
has_operator_\*<T>::member; // whether it is a member function
has_operator_\*<T>::free; // whether it is a free function
has_operator_\*<T>::overloaded; // equalivent to member || free
has_operator_\*<T>::value; // whether it has the operator or not
```

simple type aliases


```cpp
index_constant<Value> = std::integral_constant<std::size_t,Value>;

always_false<Types...> = std::false_type;
always_true<Types...> = std::true_type;

```

utility functions

```cpp
as_const(T&)
as_volatile(T&)
as_cv(T&)
forward_like<Like>(T&)
```

utility traits


```cpp
 underlying_type_or<T,OrElse>::type // if T is an enum then get the underlying type otherwise OrElse type
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




much more but I can't document it right now such as copy\_\*,clone\_\* from [paper](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1016r0.pdf) and type_list

is_explicitly_constructible<T,Args...>
is_implicitly_constructible<T,Args...>

there is also is_[explicitly|implicitly]_default_constructible and is\_[explicitly|implicitly]\_copy_constructible and is\_[explicitly|implicitly]\_move_contructible

