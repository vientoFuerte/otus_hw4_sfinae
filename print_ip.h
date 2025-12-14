#pragma once

#include <type_traits>
#include <cstdint>
#include <iostream>
#include <cstring>  
#include <vector>
#include <list>
#include <tuple>

/**
 * @brief Шаблонная структура для передачи типа
 * @tparam T Тип для передачи
 */
template<typename T>
struct type_is{
	using type = T;
};

// тип как параметр
template<typename T>
struct is_int {
	static const bool value = false;
};


/**
 * @brief Специализация is_int для типа int32_t
 */
template<>
struct is_int <int32_t>{
	static const bool value = true;
};

/**
 * @brief Специализация is_int для типа int8_t
 */
template<>
struct is_int <int8_t>{
    static const bool value = true;
};

/**
 * @brief Специализация is_int для типа int16_t
 */
template<>
struct is_int <int16_t>{
    static const bool value = true;
};


/**
 * @brief Специализация is_int для типа int64_t
 */
template<>
struct is_int <int64_t>{
    static const bool value = true;
};


// Проверка на vector<int>
template<typename T>
struct is_vector_int_or_list_short {
    static const bool value = false;
};

template<>
struct is_vector_int_or_list_short<std::vector<int>> {
    static const bool value = true;
};
template<>
struct is_vector_int_or_list_short<std::list<short>> {
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
void print_ip(const T &ip, int=0) {

        std::cout << ip<< std::endl;
}

// Для vector<int> и list<short> (использован дополнительный фиктивный параметр, чтобы отличать от версии std::string)
template<typename T,
     typename = typename enable_if<is_vector_int_or_list_short<T>::value>::type>
void print_ip(const T &ip, long=0) {

	 for (auto it = ip.begin(); it != ip.end(); ++it) {
		    std::cout << *it;
		 // Если это не последний элемент, выводим точку
        if (std::next(it) != ip.end()) {
            std::cout << ".";
        }	
		}

		std::cout << std::endl;
}


// Общий шаблон является ли тип кортежем, по умолчанию false
template<typename T>
struct is_tuple {
    static const bool value = false;
};

// Специализация для std::tuple с любыми параметрами
template<typename... Args>
struct is_tuple<std::tuple<Args...>> {
    static const bool value = true;
};

// Базовый шаблон для проверки все типы в tuple одинаковы
template<typename... Args>
struct is_homogeneous_tuple {
    static const bool value = false;
};

// Cпециализация для кортежа с одним элементом.
template<typename T>
struct is_homogeneous_tuple<std::tuple<T>> {
    static const bool value = true;
};

//Специализация для кортежа с несколькими параметрами
// std::conjunction_v -  вспомогательная переменная шаблона (variable template), которая:
// Принимает список типов с булевыми значениями (::value)
// Применяет к ним логическое И (&&) и возвращает результат во время компиляции 
template<typename T, typename... Rest>
struct is_homogeneous_tuple<std::tuple<T, Rest...>> {
    static const bool value = std::conjunction_v<
        std::is_same<T, Rest>...> && is_homogeneous_tuple<std::tuple<Rest...>>::value;
};

// Вспомогательная функция для печати tuple
template<size_t I, typename... Args>
typename std::enable_if<I == sizeof...(Args), void>::type
    print_tuple(const std::tuple<Args...>&) {}
    
    
//I - текущий индекс элемента
//Args... - пакет типов элементов кортежа
template<size_t I, typename... Args>
typename std::enable_if<I < sizeof...(Args), void>::type
    print_tuple(const std::tuple<Args...>& t) {
    if (I != 0) {
        std::cout << ".";
    }
    std::cout << std::get<I>(t);
    print_tuple<I + 1, Args...>(t);
}

// Для std::tuple
template<typename T,
    //typename = typename enable_if<...>::type> механизм выбора перегрузок SFINAE
    typename = typename enable_if<
    is_tuple<T>::value && // является ли T кортежем
    is_homogeneous_tuple<T>::value // все элементы кортежа одного типа
     >::type>
    void print_ip(const T& ip) {
    print_tuple<0>(ip); //рекурсивный вызов функции печати кортежа, начиная с нулевого элемента.
    std::cout << std::endl;
}
