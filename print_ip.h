#pragma once

#include <type_traits>
#include <cstdint>
#include <iostream>
#include <cstring>  

template<typename T>
struct type_is{
	using type = T;
};

// тип как параметр
template<typename T>
struct is_int {
	static const bool value = false;
};


// is_int <int>::value вернет true
template<>
struct is_int <int>{
	static const bool value = true;
};

// Добавляем специализацию для int8_t
template<>
struct is_int <int8_t>{
    static const bool value = true;
};

// Добавляем специализацию для int16_t
template<>
struct is_int <int16_t>{
    static const bool value = true;
};

// Добавляем специализацию для int64_t
template<>
struct is_int <int64_t>{
    static const bool value = true;
};

template <bool C, class T=void>
struct enable_if: type_is<T> {};

template<class T> 
struct enable_if<false, T> {};


// Основная функция print_ip с SFINAE
template<typename T, 
         typename = typename enable_if<is_int<T>::value>::type>
void print_ip(T ip) {
    // получение байтов
     unsigned char bytes[sizeof(T)];
    std::memcpy(bytes, &ip, sizeof(T));
    for (size_t i = sizeof(T); i > 0; --i) {
        std::cout << static_cast<unsigned int>(bytes[i - 1]);
        if (i > 1) std::cout << ".";
    }
    std::cout << std::endl;
}

// Для std::string
template<typename T,
         typename = typename enable_if<std::is_same<T, std::string>::value>::type>
void print_ip(const T &ip) {

        std::cout << ip<< std::endl;
}
