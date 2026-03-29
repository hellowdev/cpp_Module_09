#include "PmergeMe.hpp"

//******************************************************************************************* */

int PmergeMe::insertloser(Element loser, std::vector<Element>& mainChain, int start, int end)
{
	int range = end - start;
	if (range == 0)
    {
        mainChain.insert(mainChain.begin() + start, loser);
        return start;
    }
    int mid = range / 2;

    if (loser.value < mainChain[mid + start].value)
        return insertloser(loser, mainChain, start, mid + start);
    return insertloser(loser, mainChain, mid + start + 1, end);
}

void PmergeMe::BinaryInsertionSearch(std::vector<int> jacobOrder, std::vector<Element> pend, std::vector<Element>& mainChain)
{
	std::vector<Element> orderedPend;
	std::vector<int> winPos;

	// loop through jacob vector and take the elements with its winner position in mainChain 
	for (size_t i = 0; i < jacobOrder.size(); i++)
	{
		int idx = jacobOrder[i];
		orderedPend.push_back(pend[idx]); // take ordered elements from pend
		winPos.push_back(idx + 1); // here we track winner position for each pend 
	}
	for (size_t i = 0; i < orderedPend.size(); i++)
	{
		int insertPos = insertloser(orderedPend[i], mainChain, 0, winPos[i]);
		for (size_t j = 0; j < winPos.size(); j++)
		{
			if (winPos[j] >= insertPos)
				winPos[j]++;
		}
	}
}

//******************************************************************************************* */
