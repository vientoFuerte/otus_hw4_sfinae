cmake_minimum_required(VERSION 3.12)

project(print_ip)

#option(WITH_BOOST_TEST "Whether to build Boost test" ON)
# Опция для включения Doxygen
option(WITH_DOXYGEN "Build Doxygen documentation" OFF)

add_executable(print_ip main.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


# Тест (если файл test.cpp существует)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
    # Ищем установленный gtest
    find_package(GTest REQUIRED)
    
    # Тестовый исполняемый файл
    add_executable(print_ip_tests test.cpp)
    
    # Линкуем с системным gtest
    target_link_libraries(print_ip_tests PRIVATE GTest::gtest GTest::gtest_main)
    
    # Тесты
    enable_testing()
    add_test(NAME AllTests COMMAND print_ip_tests)
else()
    message(WARNING "test.cpp not found, tests will not be built")
endif()


if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror -Wunused -Wunused-variable -Wunused-parameter
    )
endif()

target_compile_definitions(print_ip PRIVATE 
    $<$<CONFIG:Debug>:ENABLE_DEBUG_LOGGING>
    $<$<CONFIG:RelWithDebInfo>:ENABLE_DEBUG_LOGGING>
)


install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_FILE_NAME "print_ip.deb")
set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)

