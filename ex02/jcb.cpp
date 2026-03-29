#include <iostream>
#include <vector>

size_t jacob(size_t nb)
{
	if (nb == 0)
		return 0;
	if (nb == 1)
		return 1;
	return (jacob(nb-1) + (2 * jacob(nb - 2)));
}

std::vector<int> generatejacobOrder(size_t pendSize)
{
	std::vector<int> jacobSeq;
	std::vector<int> fillOrder;
	std::vector<int> previous;

	//******************** GENERATE JACOB SEQUENCE ********************//
	size_t j = 0;
	for (j = 0;jacob(j) <= pendSize; j++) // pen[4]
	{
		if (jacob(j) > 1) // jacob values >= 3, cuz we had the 1 
		{
			jacobSeq.push_back(jacob(j)); // jacob filled
			previous.push_back(jacob(j - 1));  // previous jacob
		}
	
	}
	
	//****************** EXTRACT ORDER FROM JACOB SEQ *****************//
	for (size_t i = 0; i < jacobSeq.size(); i++)
	{
		for(int n = jacobSeq[i]; n > previous[i]; n--)
			//fillOrder.push_back(n)
			fillOrder.push_back(n); // For n = 3 (prev = 1): insert b3, b2 → 2 elements
		// n bash nakhd ra9m b index 
	}
	
	
	//************************ LEFT IN REVERSE ************************//
		for (size_t leftOver = jacob(j) - 1; leftOver >= pendSize; leftOver--)
				fillOrder.push_back(leftOver);
		// end - 1 bash nakhd ra9m b index 
	return fillOrder;
}

int main()
{
	std::vector seq = generatejacobOrder(7);
	for (size_t i = 0; i < seq.size(); i++)
		std::cout << seq[i] << " ";
	std::cout << std::endl;
}