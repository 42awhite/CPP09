#include "RPN.hpp"

//Forma canónica
RPN::RPN(){}

RPN::RPN(const RPN &other) 
{ 
    *this = other; 
}

RPN &RPN::operator=(const RPN &other) 
{
    if (this != &other)
        this->_stack = other._stack;
    return *this;
}

RPN::~RPN(){}

//Functions
bool RPN::isOperator(const std::string &token) const
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::applyOperator(const std::string &op, int a, int b) const 
{
    if (op == "+") 
        return a + b;
    if (op == "-") 
        return a - b;
    if (op == "*") 
        return a * b;
    if (op == "/") {
        if (b == 0)
            throw std::runtime_error("Error");
        return a / b;
    }
    throw std::runtime_error("Error");
}

//.top = devuelve número encima del stack
//.pop = borra el número que está encima del stack
//.push = Mete nuevo n en la cima del stack
int RPN::evaluate(const std::string &expr) 
{
    while (!_stack.empty())
        _stack.pop();

    std::istringstream iss(expr);
    std::string token;
    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error");
            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            int result = applyOperator(token, a, b);
            _stack.push(result); 
        }
        // 3) Si es número válido (un solo dígito 0-9)
        else if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
            _stack.push(std::atoi(token.c_str()));
        else
            throw std::runtime_error("error");
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error");
    return _stack.top();
}