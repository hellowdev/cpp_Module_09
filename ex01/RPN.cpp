#include "RPN.hpp"

RPN::RPN(){}
RPN::~RPN(){}
RPN::RPN(std::string setarg) : arg(setarg){}

void RPN::parse_str()
{
    unsigned int nb = 0;
    // char operation = '\0';
    if (arg.empty() || arg.find_first_not_of(" \t\n\v\f\r") == std::string::npos 
    || arg.find_first_not_of("0123456789-+/* \t\n\v\f\r") != std::string::npos) 
        throw std::logic_error("Error: invalid str");

    std::stringstream parse(arg);
    // int i = 0;
    while (!parse.eof())
    {
        if (!(parse >> nb))
            throw std::logic_error("Error");
        
    }
    // if (!(parse >> nb));
    // if (nb > 9)
    //     throw std::logic_error("Error: number not valid");
    std::cout << nb << '\n';

}