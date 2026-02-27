#include "RPN.hpp"


int main(int ac, char *av[])
{
    if (ac != 2)
    {
        std::cerr << "Error: wrong argumets\n";
        return 1;
    }
    RPN pol(av[1]);
    try
    {
        pol.parse_str();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}