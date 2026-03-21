#include "PmergeMe.hpp"

// void PmergeMe::insertloser(Element loser, std::vector<Element>& mainChain, int start, int end)
// {
// 	int range = end - start;
// 	if (range <= 1)
// 	{
// 		if (loser.value < mainChain[start].value)
// 		{
// 			std::cout << loser.value << "\n";
// 			mainChain.insert(mainChain.begin() + start, loser);
// 		}
// 		else
// 		{
// 			// std::cout << "here2\n";
// 			std::cout << loser.value << "\n";
// 			mainChain.insert(mainChain.begin() + start - 1, loser);
// 		}
// 		return ;
// 	}
// 	int midd = range / 2;
// 	// std::cout << "mid: " << midd;
	
// 	// std::cout << " value: " << mainChain[midd + start].value << "\n";
// 	if (loser.value < mainChain[midd + start].value)
// 		insertloser(loser, mainChain, start, start + midd);
// 	else
// 		insertloser(loser, mainChain, midd + start, end);
// }


//******************************************************************************************* */

int PmergeMe::insertloser(Element loser, std::vector<Element>& mainChain, int start, int end)
{
	std::cout << "insert element [" << loser.value << "]\n";
	int range = end - start;
	if (range <= 0)
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


// void pree(std::vector<Element> vec)
// {
//     for (size_t i = 0; i < vec.size(); i++)
//         std::cout << vec[i].value << " ";
//     std::cout << std::endl;
// }


// int insertloser(Element loser, std::vector<Element>& mainChain, int start, int end)
// {
// 	int range = end - start;
//     if (range <= 0)
//     {
//         mainChain.insert(mainChain.begin() + start, loser);
//         return start;
//     }
//     int mid = range / 2;

//     if (loser.value < mainChain[mid + start].value)
//         insertloser(loser, mainChain, start, mid + start);
//     else
// 	{
//         insertloser(loser, mainChain, mid + start + 1, end);
// 	}
// 	return start;
// }

// int main(int ac, char **av)
// {
// 	std::vector<Element> mainChain;
// 	size_t i;
// 	for (i = 1; av[i]; i++)
// 	{
// 		Element e;
// 		e.value = atoi(av[i]);
// 		mainChain.push_back(e);
// 	}
	
// 	std::cout << "befour: ";pree(mainChain);
// 	Element p;
// 	p.value = 2;
// 	insertloser(p, mainChain, 2, 5);
// 	std::cout << "after: ";pree(mainChain);
// }