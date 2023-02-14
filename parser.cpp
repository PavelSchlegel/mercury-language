#include "parser.hpp"

namespace mercury {

    bool ParseDigit(std::string_view str, std::size_t& i)
    {
        if (str.size() == i) {
            return false;
        }
        switch (str[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                i += 1;
                return true;
            default:
                return false;
        }
    }

    bool ParseNumber(std::string_view str, std::size_t& i)
    {
        if (ParseDigit(str, i)) {
            while (ParseDigit(str, i));
            return true;
        }
        return false;
    }

    bool Parse(std::string_view str)
    {
        std::size_t i = 0;
        return ParseNumber(str, i) && (i == str.size());
    }

}
