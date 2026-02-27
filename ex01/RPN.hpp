#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>

class RPN
{
    private:
        std::stack<int> stk;
        std::string arg;
    public:
        RPN();
        RPN(std::string setarg);
        // RPN& operator=(const RPN& obj);
        // RPN(const RPN& obj);
        void parse_str();
        ~RPN();
};