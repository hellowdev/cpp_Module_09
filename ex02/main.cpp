#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	try
	{
		PmergeMe inp(av);
		inp.sort();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}