#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av)
{
	Element elemtents;
	for (int i = 1; av[i]; i++)
	{
		unsigned int nb = parseNumber(av[i]);
		elemtents.value = nb; // initlize our vector of struct element with vl and empty chain
		vec.push_back(elemtents);
	}
}

void PmergeMe::TrimStr(std::string& str)
{
	size_t start = str.find_first_not_of(" \t\n\r\f\v");
	if (start == std::string::npos)
		throw std::runtime_error("Error: invalid input.");
	size_t end = str.find_last_not_of(" \t\n\r\f\v");
	str = str.substr(start, end - start + 1);
}

unsigned int PmergeMe::parseNumber(std::string in)
{
	if (in.empty() || in.find("0123456789 \t\r\v\n") != in.npos)
		throw std::runtime_error("Error: invalid input.");
	TrimStr(in); // remove spaces from begin and end of string
	char *end = NULL;
	long number = std::strtol(in.c_str(), &end, 10);
	if (*end || errno == ERANGE || number < 0 || number > __INT_MAX__)
		throw std::runtime_error("Error: invalid input.");
	return number;
}

void PmergeMe::printVec(std::vector<int> vect)
{
	for (size_t i = 0; i < vect.size(); i++)
		std::cout << vect[i] << " ";
	std::cout << "\n";
}