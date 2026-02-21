#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::~BitcoinExchange(){}
void BitcoinExchange::print_data()
{
    for (std::map<std::string, double>::iterator it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first << " value: " << it->second << '\n';
    }
}
void BitcoinExchange::storing_db(std::ifstream& data_base)
{
    std::string line;
    std::getline(data_base, line);

    while (std::getline(data_base, line))
    {
        int idx = line.find_first_of(",");
        double value = atof(line.substr(idx + 1, line.size()).c_str());
        map[line.substr(0, idx)] = value; // from 0 to ',' then ',' to end
    }
    std::cout << std::fixed << std::setprecision(1);
    // print_data();
}
bool isLeapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool check_month(int year, int month, int day)
{
    if (month == 4 || month == 6 || month == 8 || month == 11)
    {   
        if (day <= 30)
            return true;
        return false;
    }
    else if (month != 2 && day <= 31)
        return true;
    else if (month == 2)
    {
        if (day <= 29 && isLeapYear(year))
            return true;
        return false;
    }
    return false;
}
void parse_lines(std::istringstream& parse, std::string& line)
{
    int year = 0;
    int month = 0;
    int day = 0;
    char fmin = '\0';
    char smin = '\0';
    char pipe = '\0';
    std::string tmp;
    
    parse >> year >> fmin >> month >> smin >> day >> pipe;
    if (pipe != '|' || year < 1 || year > 9999 || fmin != '-' || smin != '-' 
    || month < 1 || month > 12 || day < 0 || day > 31 
    || !check_month(year, month, day))
        throw std::invalid_argument("Error: bad input => " + tmp);
    // std::cout << year << fmin << month << smin << day << '\n';
    if (line.find_last_of(" \n\t\r\v\f") != 12 || line.size() == 13)
        throw std::invalid_argument("Error: bad input => " + tmp);
}

void BitcoinExchange::treating_inp(std::ifstream& inpfile)
{
    std::string line;
    
    std::getline(inpfile, line);
    if (line != "date | value")
        throw std::invalid_argument("Error: first line input");
    
    std::getline(inpfile, line);
    std::istringstream parse(line);
    std::string date;
    parse >> date;
    if (date.size() != 10)
        throw std::invalid_argument("Error: invalid date format");
    parse.seekg(0);
    parse_lines(parse, line);
    


    
}
    //     int cout = line.find_first_of("-");
    //     int nb = std::atoi(line.substr(0, cout).c_str());
    //     if (nb < 1 || nb > 9999)
    //         throw std::invalid_argument("Invalid Year");
    //     // if(std::count(line.begin(), line.end(), '-') != 2
    //     // || line.find_first_of(" \t\n\r\v\f") != std::string::npos)