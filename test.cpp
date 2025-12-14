#include "print_ip.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(PrintIpTest, DirectTest) {
    // Сохраняем оригинальный буфер
    auto* old_buf = std::cout.rdbuf();
    
    // Тест 1
    std::stringstream buf1;
    std::cout.rdbuf(buf1.rdbuf());
    print_ip(int8_t{-1});
    EXPECT_EQ(buf1.str(), "255\n");
    
    // Тест 2  
    std::stringstream buf2;
    std::cout.rdbuf(buf2.rdbuf());
    print_ip(int64_t{8875824491850138409} );
    EXPECT_EQ(buf2.str(), "123.45.67.89.101.112.131.41\n");
    
    // Тест 3
    std::stringstream buf3;
    std::cout.rdbuf(buf3.rdbuf());
    print_ip(std::vector<int>{100, 200, 300, 400});
    EXPECT_EQ(buf3.str(), "100.200.300.400\n");
    
    // Восстанавливаем буфер
    std::cout.rdbuf(old_buf);
}

  




