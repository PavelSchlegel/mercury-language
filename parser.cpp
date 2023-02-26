#include <exception>
#include <memory>
#include <optional>
#include <stdexcept>
#include "parser.hpp"

namespace mercury {

    void ParseWS(std::string_view str, std::size_t& i)
    {
        while(str[i] == ' ') {
            i += 1;
        }
    }

    std::optional<int> ParseDigit(std::string_view str, std::size_t& i)
    {
        if (str.size() == i) {
            return std::nullopt;
        }
        char symbol = str[i];
        switch (symbol) {
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
                return symbol - '0';
            default:
                return std::nullopt;
        }
    }

    INode::Ptr ParseNumber(std::string_view str, std::size_t& i)
    {
        if (auto digit = ParseDigit(str, i)) {
            auto result = *digit;
            while(auto digit = ParseDigit(str, i)) {
                result *= 10;
                result += *digit;
            }
            return std::make_shared<Number>(result); // new Number(result)
        }
        return nullptr;
    }

    INode::Ptr ParseAdd(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (auto a = ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return nullptr;
            }
            if (str[curr++] != '+') {
                return nullptr;
            }
            if (auto b = ParseNumber(str, curr)) {
                i = curr;
                return std::make_shared<Add>(a, b);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseSub(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (auto a = ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return nullptr;
            }
            if (str[curr++] != '-') {
                return nullptr;
            }
            if (auto b = ParseNumber(str, curr)) {
                i = curr;
                return std::make_shared<Sub>(a, b);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseMul(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (auto a = ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return nullptr;
            }
            if (str[curr++] != '*') {
                return nullptr;
            }
            if (auto b = ParseNumber(str, curr)) {
                i = curr;
                return std::make_shared<Mul>(a, b);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseDiv(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (auto a = ParseNumber(str, curr)) {
            if (str.size() == curr) {
                return nullptr;
            }
            if (str[curr++] != '/') {
                return nullptr;
            }
            if (auto b = ParseNumber(str, curr)) {
                i = curr;
                return std::make_shared<Div>(a, b);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseExpr(std::string_view str, std::size_t& i)
    {
        if (auto expr = ParseAdd(str, i)) {
            return expr;
        }
        if (auto expr = ParseSub(str, i)) {
            return expr;
        }
        if (auto expr = ParseMul(str, i)) {
            return expr;
        }
        if (auto expr = ParseDiv(str, i)) {
            return expr;
        }
        return ParseNumber(str, i);
    }

    INode::Ptr Parse(std::string_view str)
    {
        std::size_t i = 0;
        auto result = ParseExpr(str, i);
        if (result && i == str.size()) {
            return result;
        }
        return nullptr;
    }

}
