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

void PmergeMe::parse_str(std::string& str)
{
	unsigned int nb;
	std::stringstream checkstr(str);
	size_t start = str.find_first_not_of(" \t\n\r\f\v");
	if (start == std::string::npos)
		throw std::runtime_error("Error: invalid input.");
	checkstr >> nb;
	if ((checkstr >> nb))
		throw std::runtime_error("Error: invalid input.");

}

unsigned int PmergeMe::parseNumber(std::string in)
{
	if (in.find_first_not_of("0123456789 \t\r\v\n") != std::string::npos)
		throw std::runtime_error("Error: invalid input.");
	parse_str(in);
	char *end = NULL;
	long number = std::strtol(in.c_str(), &end, 10);
	if (errno == ERANGE || number < 0 || number > __INT_MAX__)
		throw std::runtime_error("Error: invalid input.");
	return number;
}

void PmergeMe::printVec(std::vector<int> vect)
{
	for (size_t i = 0; i < vect.size(); i++)
		std::cout << vect[i] << " ";
	std::cout << "\n";
}