#include "PmergeMe.hpp"

void before(char *av[])
{
	std::cout << "Before: ";
	for (size_t i = 1; av[i]; i++)
		std::cout << av[i] << " ";
	std::cout << std::endl;
}

void vecAfter(std::vector<ElementVec> vec)
{
	std::cout << "After:  ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i].value << " ";
    std::cout << std::endl;
}

int main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	try
	{
		PmergeMe inp(av);
		before(av);
		clock_t start = clock();
		/*vector*/
		std::vector<ElementVec> sortedVec = inp.sortVec();
    	clock_t end = clock();
		vecAfter(sortedVec);
    	double elapsed = double(end - start) / CLOCKS_PER_SEC;
    	std::cout << "Time to process a range of: " << (ac - 1) << " elements with std::vector : "
		<< std::fixed << std::setprecision(5) << elapsed << " seconds." << std::endl;
		/*deque*/
		start = clock();
		std::deque<ElementDeq> sortedDeq = inp.sortDeq();
    	end = clock();
		elapsed = double(end - start) / CLOCKS_PER_SEC;
    	std::cout << "Time to process a range of: " << (ac - 1) << " elements with std::deque : "
		<< std::fixed << std::setprecision(5) << elapsed << " seconds." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}