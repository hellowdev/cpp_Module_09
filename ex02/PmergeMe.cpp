#include "PmergeMe.hpp"
void PmergeMe::pairing(std::vector<Element>& winners, std::vector<Element> elements) // 
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

std::vector<Element> PmergeMe::fordJohnsonVec(std::vector<Element> elements)
{
    if (elements.size() == 1) // BASE CASE
        return elements;

    Element stragler;
    bool hasStragler = false;
    if (elements.size() % 2)
    {
        hasStragler = true;
        stragler = elements.back();
        elements.pop_back();
    }
    std::vector<Element> winners;
    pairing(winners, elements); // Each winner now carries its loser in its chain!
    std::vector<Element> mainChain = fordJohnsonVec(winners);
    /*---------UNWIDING RECURSION----------*/
    std::vector<Element> pend;
    for (size_t i = 0; i < mainChain.size(); i++) // loop thrgout mainChain and rm last loser of each one and add them to the pends
    {
        pend.push_back(mainChain[i].losers.back());
        mainChain[i].losers.pop_back();
    }
    mainChain.insert(mainChain.begin(), pend[0]); // FIRST INSERT in MainChain
    std::vector<int> jacobOrder = generatejacobOrder(pend.size());

     // if pend has jst two element no need to do jacoborder, jst insert the remaining element
     // the first element in inserted before as first loser 
    if (jacobOrder.empty() && pend.size() == 2)
        insertloser(pend[1], mainChain, 0, mainChain.size());
    BinaryInsertionSearch(jacobOrder, pend, mainChain);
    //insrt stragler
    if (hasStragler)
        insertloser(stragler, mainChain, 0, mainChain.size());
    return mainChain;
}

std::vector<Element> PmergeMe::sort()
{    
    if (vec.size() == 1)
        return vec;
    std::vector<Element> sorted = fordJohnsonVec(vec);
    // std::cout << ">>>>>>>>>>>> FINAL RESULT: ";
    return sorted;

}

PmergeMe::~PmergeMe(){}