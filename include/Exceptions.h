#include <stdexcept>

class invalid_operation : public std::exception
{
    public:
        virtual char const *what() const noexcept{
            return "invalid (or unsupported) operation";
        }
};

class invalid_expression : public std::exception
{
    public:
        virtual char const *what() const noexcept{
            return "invalid (or unsupported) expression";
        }
};