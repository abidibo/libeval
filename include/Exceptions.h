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

#endif /* INCLUDE_EXCEPTIONS_H_ */