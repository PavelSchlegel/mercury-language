#pragma once
#include <string_view>
#include <optional>
#include <memory>

namespace mercury {

    class INode
    {
    public:
        using Ptr = std::shared_ptr<INode>; // INode*
        virtual int Calc() const noexcept = 0;
        virtual ~INode() = default;
    };

    class Number: public INode
    {
        int value;
    public:
        explicit Number(int value) noexcept
        : value(value)
        {}
        int Calc() const noexcept override
        {
            return value;
        }
    };

    class Add: public INode
    {
        INode::Ptr a, b;
    public:
        Add(INode::Ptr a, INode::Ptr b) noexcept
        : a(a), b(b)
        {}
        int Calc() const noexcept override
        {
            return a->Calc() + b->Calc();
        }
    };

    class Sub: public INode
    {
        INode::Ptr a, b;
    public:
        Sub(INode::Ptr a, INode::Ptr b) noexcept
        : a(a), b(b)
        {}
        int Calc() const noexcept override
        {
            return a->Calc() - b->Calc();
        }
    };

    class Mul: public INode
    {
        INode::Ptr a, b;
    public:
        Mul(INode::Ptr a, INode::Ptr b) noexcept
        : a(a), b(b)
        {}
        int Calc() const noexcept override
        {
            return a->Calc() * b->Calc();
        }
    };

    class Div: public INode
    {
        INode::Ptr a, b;
    public:
        Div(INode::Ptr a, INode::Ptr b) noexcept
        : a(a), b(b)
        {}
        int Calc() const noexcept override
        {
            return a->Calc() / b->Calc();
        }
    };

    void ParseWS(std::string_view str, std::size_t& i);

    std::optional<int> ParseDigit(std::string_view str, std::size_t& i);
    INode::Ptr ParseNumber(std::string_view str, std::size_t& i);
    INode::Ptr ParseAdd(std::string_view str, std::size_t& i);
    INode::Ptr ParseSub(std::string_view str, std::size_t& i);
    INode::Ptr ParseMul(std::string_view str, std::size_t& i);
    INode::Ptr ParseDiv(std::string_view str, std::size_t& i);
    INode::Ptr ParseExpr(std::string_view str, std::size_t& i);

    INode::Ptr Parse(std::string_view str);

}
