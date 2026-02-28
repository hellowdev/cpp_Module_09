#include "RPN.hpp"

RPN::~RPN(){}
RPN::RPN(std::string setarg) : arg(setarg){}

int is_oper(char check)
{
	if (check == '-' || check == '+' || check == '*' || check == '/')
		return 1;
	return 0;
	
}
void RPN::parse_str()
{
	unsigned int nb = 0;
	char operation = '\0';
	if (arg.empty() || arg.find_first_not_of(" \t\n\v\f\r") == std::string::npos 
	|| arg.find_first_not_of("0123456789-+/* \t\n\v\f\r") != std::string::npos) 
		throw std::logic_error("Error");
	std::stringstream parse(arg);
	size_t i = 0;
	while (i < arg.size()) 
	{
		if (is_oper(arg[i]) && stack.size() < 2)
			throw std::logic_error("Error");
		if (std::isdigit(arg[i]))
		{
			if ((parse >> nb) && nb > 9)
				throw std::logic_error("Error");
			stack.push(nb);
		}
		if (stack.size() >= 2 && is_oper(arg[i]))
		{
			int valone = stack.top(); // 8 9 + == 
			stack.pop();
			int valtwo = stack.top();
			stack.pop();
			if (arg[i] == '-')
				stack.push(valtwo - valone);
			else if (arg[i] == '+')
				stack.push(valtwo + valone);
			else if (arg[i] == '*')
				stack.push(valtwo * valone);
			else if (arg[i] == '/')
			{
				if (valone == 0)
					throw std::logic_error("Error");
				stack.push(valtwo / valone);
			}
			parse >> operation;
		}
		i++;
	}
	if (stack.size() != 1)
		throw std::logic_error("Error");
	std::cout << stack.top() << '\n';
}