#include <iostream>
#include "parser.hpp"
#include <string>

int main()
{
    for (std::string line; std::getline(std::cin, line);) {
        if(line.empty()) {
            std::cout << std::endl;
        } else {
            auto node = mercury::Parse(line);
            if(node != nullptr) {
                std::cout << node->Calc() << std::endl;
            } else {
                std::cout << "Invalid input!" << std::endl;
            }
        }
    }

    return 0;
}