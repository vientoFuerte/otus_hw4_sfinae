#pragma once
#if 1
// тип как параметр
template<typename T>
struct is_int {
	static const bool value = false;
}

template<>
struct is_int <int_8>{
	static const bool value = true;
}

// is_int <int_8>:: value вернет true


// тип как результатremov
template<typename T>
struct remove_const {
	using type = T;
}

template<typename T>
struct remove_const <const T>{
	using type = T;
}

//remove_const<int>:: type a1;
//remove_const<const int>:: type a2;


//наследование

template<typename T>
struct type_is{
	using type = T;
}

template<typename T>
struct remove_const: type_is<T> {};

template<typename T>
struct remove_const <const T>: type_is<T> {};

template<typename T>

using remove_const_t = typename remove_const<T>::type


//sfinae

template <bool C, Class T, Class F>
struct conditional: type_is<T> {};

template <class T, class F>
struct conditional<false, T, F> : type_is<F> {};
//sfinae



template <bool C, Class T>
struct enable_if: type_is<T> {};

template <Class T>
struct enable_if: <false, T> {};

enable_if<false, int> :: type;


namespace first_attempt{

template<typename T>
auto sort_container(T &container) ->decltype container.sort
   container.sort();
   
template<typename T>
auto sort_container(T &container) ->void
   std::sort( container.begin(), container.end())
   
}

#endif
