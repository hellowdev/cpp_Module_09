#include "PmergeMe.hpp"

size_t PmergeMe::jacob(size_t nb)
{
	if (nb == 0)
		return 0;
	if (nb == 1)
		return 1;
	return (jacob(nb-1) + (2 * jacob(nb - 2)));
}

std::vector<int> PmergeMe::generatejacobOrder(size_t pendSize)
{
	std::vector<int> jacobSeq;
	std::vector<int> fillOrder;
	std::vector<int> previous;

	//******************** GENERATE JACOB SEQUENCE ********************//
	size_t j;
	for (j = 0; jacob(j) <= pendSize ; j++) // pen[4]
	{
		if (jacob(j) > 1)
		{
			jacobSeq.push_back(jacob(j)); // jacob filled
			previous.push_back(jacob(j - 1));  // previous jacob // ghanhtajoh f order
		}	
	}
	
	//****************** EXTRACT ORDER FROM JACOB SEQ *****************//
	for (size_t i = 0; i < jacobSeq.size(); i++)
	{
		for(int n = jacobSeq[i]; n > previous[i]; n--)
			fillOrder.push_back(n - 1); // For n = 3 (prev = 1): insert b3, b2 → 2 elements
	}
	
	
	//************************ LEFT IN REVERSE ************************//
	for (size_t end = pendSize; end > jacob(j - 1); end--) // check if leftover
		fillOrder.push_back(end - 1);
	return fillOrder;
}
