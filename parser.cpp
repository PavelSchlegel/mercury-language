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

    bool ParseAdd(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return false;
            }
            if (str[curr] == '+') {
                curr += 1;
                if (ParseNumber(str, curr)) {
                    i = curr;
                    return true;
                }
            }
        }
        return false;
    }

    bool ParseSub(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return false;
            }
            if (str[curr] == '-') {
                curr += 1;
                if (ParseNumber(str, curr)) {
                    i = curr;
                    return true;
                }
            }
        }
        return false;
    }

    bool ParseMul(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return false;
            }
            if (str[curr] == '*') {
                curr += 1;
                if (ParseNumber(str, curr)) {
                    i = curr;
                    return true;
                }
            }
        }
        return false;
    }

    bool ParseDiv(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return false;
            }
            if (str[curr] == '/') {
                curr += 1;
                if (ParseNumber(str, curr)) {
                    i = curr;
                    return true;
                }
            }
        }
        return false;
    }

    bool ParseExpr(std::string_view str, std::size_t& i)
    {
        return ParseAdd(str, i) || ParseDiv(str, i) || ParseMul(str, i) || ParseSub(str, i) || ParseNumber(str, i);
    }

    bool Parse(std::string_view str)
    {
        std::size_t i = 0;
        return ParseExpr(str, i) && (i == str.size());
    }

}
