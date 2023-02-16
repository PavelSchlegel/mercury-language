#pragma once
#include <string_view>

namespace mercury {

    bool ParseDigit(std::string_view str, std::size_t& i);
    bool ParseNumber(std::string_view str, std::size_t& i);
    bool ParsePlus(std::string_view str, std::size_t& i);
    bool ParseExpr(std::string_view str, std::size_t& i);

    bool Parse(std::string_view str);

}
