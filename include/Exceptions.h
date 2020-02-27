#ifndef INCLUDE_EXCEPTIONS_H_
#define INCLUDE_EXCEPTIONS_H_
#include <stdexcept>

class InvalidOperation : public std::exception
{
    public:
        virtual char const *what() const noexcept{
            return "invalid (or unsupported) operation";
        }
};

class InvalidExpression : public std::exception
{
    public:
        virtual char const *what() const noexcept{
            return "invalid (or unsupported) expression";
        }
};

class InvalidOperand : public std::exception
{
    public:
        virtual char const *what() const noexcept{
            return "invalid (or unsupported) operand";
        }
};

class InvalidAssignment : public std::exception
{
    public:
        virtual char const *what() const noexcept{
            return "invalid assignment to operand";
        }
};

class UninitializedVariables : public std::exception
{
    public:
        virtual char const *what() const noexcept{
            return "missing variables initialization";
        }
};

#endif /* INCLUDE_EXCEPTIONS_H_ */