#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>

class RPN
{
    private:
        std::stack<int> stack;
        std::string arg;
        RPN& operator=(const RPN& obj);
        RPN();
        RPN(const RPN& obj);
    public:
        RPN(std::string setarg);
        void parse_str();
        ~RPN();
};