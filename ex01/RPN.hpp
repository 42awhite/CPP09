#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <cctype>

class RPN
{
    private:
        std::stack<int> _stack;
    public:
    //Canonical form
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
    //Functions
        int evaluate(const std::string &expr);
        bool isOperator(const std::string &token) const;
        int applyOperator(const std::string &op, int a, int b) const;
};

#endif