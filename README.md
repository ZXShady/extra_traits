# extra_traits

simple library for some missing type traits I always need.


has_operator_*

simple type aliases


```cpp
index_constant<Value> = std::integral_constant<std::size_t,Value>;

always_false<Types...> = std::false_type;
always_true<Types...> = std::false_type;

```

utility functions

```cpp
as_const(T&)
as_volatile(T&)
as_cv(T&)
forward_like<Like>(T&)
```

modifying traits
```cpp
remove_all_pointers<int******> -> int;
remove_all_pointers<float(*)[]> -> float[];
```


much more but I can't document it right now such as copy_*,clone_* from [paper](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1016r0.pdf)

is_explicitly_constructible<T,Args...>
is_implicitly_constructible<T,Args...>

there is also is_*_default_constructible and is_*_copy_constructible and is_*_move_contructible

