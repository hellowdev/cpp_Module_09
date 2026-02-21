
#include "BitcoinExchange.hpp"
// std::map<int, std::string> test;

    // test[1] = "tommy";
    // test[2] = "Jenny";
    // test[2] = "cowby";
    // for (std::map<int, std::string>::iterator it = test.begin() ; it != test.end(); it++)
    // {
    //     std::cout << it->first << " value: " << it->second << '\n';
    // }

int main(int ac, char *arg[])
{
    if (ac != 2)
    {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }
    std::ifstream inpfile(arg[1]); // input file
    std::ifstream data_base("data.csv"); // input file

    if (!inpfile || !data_base)
    {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }
    BitcoinExchange btc;
    try
    {
        btc.storing_db(data_base); // read my DB
        btc.treating_inp(inpfile);

    }
    catch (std::exception& exp)
    {
        std::cerr << exp.what() << '\n';
    }

    

    return 0;
    
}