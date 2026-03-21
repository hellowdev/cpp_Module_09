#include "PmergeMe.hpp"

int lvl = 0;

void pree(std::vector<Element> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i].value << " ";
    std::cout << std::endl;
}

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
    lvl++;
    std::cout << "------------level[" << lvl << "]--------------\n";
    if (elements.size() == 1) // BASE CASE
        return std::cout << "BASE CASE!\n", elements;

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
    std::cout << "winn: "; pree(winners);
    std::cout << "pend: ";
    for (size_t i = 0; i < winners.size(); i++)
    {
        std::cout << winners[i].losers.back().value << " ";
    }
    std::cout << "\n";
    
    std::vector<Element> mainChain = fordJohnsonVec(winners);
    
    /*---------UNWIDING RECURSION----------*/
    lvl--;
    std::cout << "------------level[" << lvl << "]--------------\nsortedwinn: "; pree(mainChain);
    std::vector<Element> pend;
    for (size_t i = 0; i < mainChain.size(); i++) // loop thrgout mainChain and rm last loser of each one and add them to the pends
    {
        pend.push_back(mainChain[i].losers.back());
        mainChain[i].losers.pop_back();
    }
    // std::cout << "level: " << lvl << " pend: "; pree(pend);

    std::cout << "INSERT FISRT LOSER: [" << pend[0].value << "]\n";
    mainChain.insert(mainChain.begin(), pend[0]); // FIRST INSERT in MainChain

    std::vector<int> jacobOrder = generatejacobOrder(pend.size());
    printVec(jacobOrder);

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

void PmergeMe::sort()
{    
    if (vec.size() == 1)
        return ; // hna khas tprinti one elem
    std::vector<Element> sorted = fordJohnsonVec(vec);
    std::cout << ">>>>>>>>>>>> FINAL RESULT: ";pree(sorted);
}

PmergeMe::~PmergeMe(){}