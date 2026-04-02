#include "PmergeMe.hpp"
//*************************PARSING VECTOR****************************************************************** */
PmergeMe::PmergeMe(char **av)
{
	ElementVec vecElem;
	ElementDeq deqElem;
	for (int i = 1; av[i]; i++)
	{
		unsigned int nb = parseNumber(av[i]);
		vecElem.value = nb; // initlize our vector of struct element with vl and empty chain
		deqElem.value = nb;
		vec.push_back(vecElem);
		deq.push_back(deqElem);
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
//******************************************************************************************* */

//********************************BINARY SEARCH AND INSERT VECTOR*********************************************************** */

void PmergeMe::insertloser(ElementVec loser, std::vector<ElementVec>& mainChain, int min, int end)
{
	int max = end;
	int middle = end / 2;

	while (min <= max)
	{
		if (loser.value > mainChain[min + middle].value)
			min = (middle + min) + 1; 
		else
			max = (middle + min) - 1;
		middle = (max - min) / 2;
	}
	mainChain.insert(mainChain.begin() + min, loser);
}


void PmergeMe::BinaryInsertionSearch(std::vector<int> jacobOrder, std::vector<ElementVec> pend, std::vector<ElementVec>& mainChain)
{
	std::vector<ElementVec> orderedPend;
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
		insertloser(orderedPend[i], mainChain, 0, winPos[i]);
		for (size_t j = 0; j < winPos.size(); j++)
			winPos[j]++;
	}
}

//******************************************************************************************* */
//******************************************JACOBSTAHL VECTOR************************************************* */
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
//******************************************************************************************* */
//**************************************PAIRING VECTOR***************************************************** */
void PmergeMe::pairing(std::vector<ElementVec>& winners, std::vector<ElementVec> elements) // 
{
    size_t size = elements.size();
    for (size_t i = 0; i < size; i += 2)
    {
        if (elements[i].value > elements[i + 1].value)
        {
            elements[i].losers.push_back(elements[i + 1]);
            winners.push_back(elements[i]);
        }
        else	
        {
            elements[i + 1].losers.push_back(elements[i]);
            winners.push_back(elements[i + 1]);
        }
    }
}
//******************************************************************************************* */
//*************************************FORDJOHNSON ALGO VECTOR****************************************************** */
std::vector<ElementVec> PmergeMe::fordJohnsonVec(std::vector<ElementVec> elements)
{
    if (elements.size() == 1) // BASE CASE
        return elements;

    ElementVec stragler;
    bool hasStragler = false;
    if (elements.size() % 2)
    {
        hasStragler = true;
        stragler = elements.back();
        elements.pop_back();
    }
    std::vector<ElementVec> winners;
    pairing(winners, elements); // Each winner now carries its loser in its chain!

    std::vector<ElementVec> mainChain = fordJohnsonVec(winners);
    /*---------UNWIDING RECURSION----------*/
 // EXTRACT LOSERS FROM MAINCHAIN AND ADD THEM TO THE PEND
    std::vector<ElementVec> pend;
    for (size_t i = 0; i < mainChain.size(); i++) // loop thrgout mainChain and rm last loser of each one and add them to the pends
    {
        pend.push_back(mainChain[i].losers.back());
        mainChain[i].losers.pop_back();
    }
//  INSERT FIRST PEND ELEMENT
    mainChain.insert(mainChain.begin(), pend[0]);
/* INSERT REMAINING WITH JACOBSTHAL */
    std::vector<int> jacobOrder = generatejacobOrder(pend.size());

     // if pend has jst two element no need to do jacoborder, jst insert the remaining element
     // the first element in inserted before as first loser 
    if (pend.size() == 2)
        insertloser(pend[1], mainChain, 0, mainChain.size() - 1);
    else
        BinaryInsertionSearch(jacobOrder, pend, mainChain);
    //insrt stragler
    if (hasStragler)
        insertloser(stragler, mainChain, 0, mainChain.size() - 1);
    return mainChain;
}

std::vector<ElementVec> PmergeMe::sortVec()
{    

    if (vec.size() == 1)
        return vec;
    std::vector<ElementVec> sorted = fordJohnsonVec(vec);
    // std::cout << ">>>>>>>>>>>> FINAL RESULT: ";
    return sorted;

}
//***********************************DEEEEEQUUEEE******************************************************** */
//********************************BINARY SEARCH AND INSERT DEQUE*********************************************************** */

void PmergeMe::insertloserDeq(ElementDeq loser, std::deque<ElementDeq>& mainChain, int min, int end)
{
	int max = end;
	int middle = end / 2;

	while (min <= max)
	{
		if (loser.value > mainChain[min + middle].value)
			min = (middle + min) + 1; 
		else
		{
			max = (middle + min) - 1;
			
		}
		middle = (max - min) / 2;
	}
	mainChain.insert(mainChain.begin() + min, loser);
}


void PmergeMe::BinaryInsertionSearchDeq(std::deque<int> jacobOrder, std::deque<ElementDeq> pend, std::deque<ElementDeq>& mainChain)
{
	std::deque<ElementDeq> orderedPend;
	std::deque<int> winPos;

	// loop through jacob deque and take the elements with its winner position in mainChain 
	for (size_t i = 0; i < jacobOrder.size(); i++)
	{
		int idx = jacobOrder[i];
		orderedPend.push_back(pend[idx]); // take ordered elements from pend
		winPos.push_back(idx + 1); // here we track winner position for each pend
	}
	for (size_t i = 0; i < orderedPend.size(); i++)
	{
		insertloserDeq(orderedPend[i], mainChain, 0, winPos[i]);
		for (size_t j = 0; j < winPos.size(); j++)
			winPos[j]++;
	}
}

//******************************************************************************************* */
//******************************************JACOBSTAHL DEQUE************************************************* */
size_t PmergeMe::jacobDeq(size_t nb)
{
	if (nb == 0)
		return 0;
	if (nb == 1)
		return 1;
	return (jacob(nb-1) + (2 * jacob(nb - 2)));
}

std::deque<int> PmergeMe::generatejacobOrderDeq(size_t pendSize)
{
	std::deque<int> jacobSeq;
	std::deque<int> fillOrder;
	std::deque<int> previous;

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
//******************************************************************************************* */
//**************************************PAIRING DEQUE***************************************************** */
void PmergeMe::pairingDeq(std::deque<ElementDeq>& winners, std::deque<ElementDeq> elements) // 
{
    size_t size = elements.size();
    for (size_t i = 0; i < size; i += 2)
    {
        if (elements[i].value > elements[i + 1].value)
        {
            elements[i].losers.push_back(elements[i + 1]);
            winners.push_back(elements[i]);
        }
        else	
        {
            elements[i + 1].losers.push_back(elements[i]);
            winners.push_back(elements[i + 1]);
        }
    }
}
//******************************************************************************************* */
//*************************************FORDJOHNSON ALGO DEQUE****************************************************** */
std::deque<ElementDeq> PmergeMe::fordJohnsonDeq(std::deque<ElementDeq> elements)
{
    if (elements.size() == 1) // BASE CASE
        return elements;

    ElementDeq stragler;
    bool hasStragler = false;
    if (elements.size() % 2)
    {
        hasStragler = true;
        stragler = elements.back();
        elements.pop_back();
    }
    std::deque<ElementDeq> winners;
    pairingDeq(winners, elements); // Each winner now carries its loser in its chain!

    std::deque<ElementDeq> mainChain = fordJohnsonDeq(winners);
    /*---------UNWIDING RECURSION----------*/
 // EXTRACT LOSERS FROM MAINCHAIN AND ADD THEM TO THE PEND
    std::deque<ElementDeq> pend;
    for (size_t i = 0; i < mainChain.size(); i++) // loop thrgout mainChain and rm last loser of each one and add them to the pends
    {
        pend.push_back(mainChain[i].losers.back());
        mainChain[i].losers.pop_back();
    }
//  INSERT FIRST PEND ELEMENT
    mainChain.insert(mainChain.begin(), pend[0]);
/* INSERT REMAINING WITH JACOBSTHAL */
    std::deque<int> jacobOrder = generatejacobOrderDeq(pend.size());

     // if pend has jst two element no need to do jacoborder, jst insert the remaining element
     // the first element in inserted before as first loser 
    if (pend.size() == 2)
        insertloserDeq(pend[1], mainChain, 0, mainChain.size() - 1);
    else
        BinaryInsertionSearchDeq(jacobOrder, pend, mainChain);
    //insrt stragler
    if (hasStragler)
        insertloserDeq(stragler, mainChain, 0, mainChain.size() - 1);
    return mainChain;
}

std::deque<ElementDeq> PmergeMe::sortDeq()
{
    if (deq.size() == 1)
        return deq;
    std::deque<ElementDeq> sorted = fordJohnsonDeq(deq);
    // std::cout << ">>>>>>>>>>>> FINAL RESULT: ";
    return sorted;

}
PmergeMe::~PmergeMe(){}