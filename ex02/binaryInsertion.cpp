#include "PmergeMe.hpp"

//******************************************************************************************* */

void PmergeMe::insertloser(Element loser, std::vector<Element>& mainChain, int startRange, int end)
{
	int newRange = end / 2; // 4
	int max = end;
	while (1)
	{

		if (loser.value < mainChain[startRange + newRange].value) // 
		{
			max = newRange - 1; // 3
			// startRange += newRange + 1;
		}
		else
		{
			startRange = startRange + newRange + 1; // 2
		}
		newRange = newRange / 2; // 0
		if (newRange == 0)
		{
			if (loser.value > mainChain[startRange].value)
			{

				mainChain.insert(mainChain.begin() + startRange + newRange, loser);
			}
			else
				mainChain.insert(mainChain.begin() + startRange, loser);
			
			return ;
		}
	}
}

void PmergeMe::BinaryInsertionSearch(std::vector<int> jacobOrder, std::vector<Element> pend, std::vector<Element>& mainChain)
{
	std::vector<Element> orderedPend;
	std::vector<int> winPos;

	// loop through jacob vector and take the elements with its winner position in mainChain 
	std::cout << "-----------STAAART OF BINARY SEARCH----------\n";
	for (size_t i = 0; i < jacobOrder.size(); i++)
	{
		int idx = jacobOrder[i];
		orderedPend.push_back(pend[idx]); // take ordered elements from pend
		winPos.push_back(idx + 1); // here we track winner position for each pend
	}
	for (size_t i = 0; i < orderedPend.size(); i++)
	{
		std::cout << "sorted mainChain: ";
		for (size_t i = 0; i < mainChain.size(); i++)
			std::cout << mainChain[i].value << " ";
		std::cout << "\n";
		std::cout << "insert this loser: " << orderedPend[i].value << "\n";
		std::cout << "Winner of loser: " << winPos[i] << "\n";
		insertloser(orderedPend[i], mainChain, 0, winPos[i]);
		for (size_t j = 0; j < winPos.size(); j++)
			winPos[j]++;
	}
}

//******************************************************************************************* */
