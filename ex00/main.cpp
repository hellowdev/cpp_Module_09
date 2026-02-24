#include "BitcoinExchange.hpp"

int main(int ac, char *arg[])
{
    if (ac != 2)
    {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }
    std::ifstream inpfile(arg[1]); // input file
    std::ifstream data_base("data.csv"); // input file

    if (!inpfile)
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