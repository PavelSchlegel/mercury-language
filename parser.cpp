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

    bool ParseSymbol(char symbol, std::string_view str, std::size_t& i)
    {
        if (str.size() == i) {
            return false;
        }
        if (str[i] != symbol) {
            return false;
        }
        i += 1;
        return true;
    }

    INode::Ptr ParseExpr0(std::string_view str, std::size_t& i)
    {
        INode::Ptr node = nullptr;
        auto curr = i;
        ParseWS(str, curr);
        if (!((node = ParseNumber(str, curr)) || (ParseSymbol('(', str, curr) && (node = ParseExpr(str, curr)) && ParseSymbol(')', str, curr)))) {
            return nullptr;
        }
        ParseWS(str, curr);
        i = curr;
        return node;
    }

    INode::Ptr ParseExpr1(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (auto node = ParseExpr0(str, curr)) {
            if (auto result = ParseOps1(node, str, curr)) {
                i = curr;
                return result;
            }
        }
        return nullptr;
    }

    INode::Ptr ParseOps1(INode::Ptr node, std::string_view str, std::size_t& i)
    {
        INode::Ptr result = nullptr;
        if ((result = ParseMul(node, str, i)) || (result = ParseDiv(node, str, i))) {
            return result;
        }
        return node;
    }

    INode::Ptr ParseMul(INode::Ptr a, std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseSymbol('*', str, curr)) {
            if (auto b = ParseExpr0(str, curr)) {
                i = curr;
                return ParseOps1(std::make_shared<Mul>(a, b), str, i);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseDiv(INode::Ptr a, std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseSymbol('/', str, curr)) {
            if (auto b = ParseExpr0(str, curr)) {
                i = curr;
                return ParseOps2(std::make_shared<Div>(a, b), str, i);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseExpr2(std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (auto node = ParseExpr1(str, curr)) {
            if (auto result = ParseOps2(node, str, curr)) {
                i = curr;
                return result;
            }
        }
        return nullptr;
    }

    INode::Ptr ParseOps2(INode::Ptr node, std::string_view str, std::size_t& i)
    {
        INode::Ptr result = nullptr;
        if ((result = ParseAdd(node, str, i)) || (result = ParseSub(node, str, i))) {
            return result;
        }
        return node;
    }

    INode::Ptr ParseAdd(INode::Ptr a, std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseSymbol('+', str, curr)) {
            if (auto b = ParseExpr1(str, curr)) {
                i = curr;
                return ParseOps2(std::make_shared<Add>(a, b), str, i);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseSub(INode::Ptr a, std::string_view str, std::size_t& i)
    {
        auto curr = i;
        if (ParseSymbol('-', str, curr)) {
            if (auto b = ParseExpr1(str, curr)) {
                i = curr;
                return ParseOps2(std::make_shared<Sub>(a, b), str, i);
            }
        }
        return nullptr;
    }

    INode::Ptr ParseExpr(std::string_view str, std::size_t& i)
    {
        return ParseExpr2(str, i);
    }

    INode::Ptr Parse(std::string_view str)
    {
        std::size_t i = 0;
        auto result = ParseExpr(str, i);
        if (result && (i == str.size())) {
            return result;
        }
        return nullptr;
    }

}
