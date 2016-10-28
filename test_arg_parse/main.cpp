#include <iostream>

#include "tests.hpp"

int main(int argc, char *argv[])
{
    auto    options = test_program_options(argc, argv);
    
    std::cout << "STR:\t" << options.str_value << std::endl;
    std::cout << "INT:\t" << options.int_value << std::endl;
    std::cout << "FLAG:\t" << options.flag << std::endl;
    std::cout << "STRINGS:" << std::endl;
    for (const auto& str: options.str_vector_value) {
        std::cout << "\t" << str << std::endl;
    }
    std::cout << "INTS:" << std::endl;
    for (const auto& item: options.int_vector_value) {
        std::cout << "\t" << item << std::endl;
    }
    std::cout << "POS 0:\t" << options.pos_0 << std::endl;
    std::cout << "POS_N:" << std::endl;
    for (const auto& str: options.pos_N) {
        std::cout << "\t" << str << std::endl;
    }
    return 0;
}
