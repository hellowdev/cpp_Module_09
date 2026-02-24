#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

class BitcoinExchange
{
    private:
        std::map<std::string, double> map;
        std::string inpDate;
        double inpValue;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& obj);
        BitcoinExchange& operator=(const BitcoinExchange& obj);
        ~BitcoinExchange();

        void storing_db(std::ifstream& data_base);
        void treating_inp(std::ifstream& inpfile);
        void print_data();
        void parse_lines(std::istringstream& parse, std::string& line);
        void calculate_btc();
};


