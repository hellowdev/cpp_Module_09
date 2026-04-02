#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : inpValue(0){}
BitcoinExchange::~BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj)
{
    map = obj.map;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& obj)
{
    map.operator=(obj.map);
    return *this;
}
// *************/PRINT_MAP/****************/
void BitcoinExchange::print_data()
{
    for (std::map<std::string, double>::iterator it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first << " value: " << it->second << '\n';
    }
}
// ****************/------------/***************/

// ****************/STORING FROM DB TO MAP CONT/***************/
void BitcoinExchange::storing_db(std::ifstream& data_base)
{
    std::string line;
    std::getline(data_base, line);

    while (std::getline(data_base, line))
    {
        int idx = line.find_first_of(",");
        double value = atof(line.substr(idx + 1).c_str());
        map[line.substr(0, idx)] = value; // from 0 to ',' then ',' to end
    }
}
// ****************/------------/***************/


void BitcoinExchange::calculate_btc()
{
    std::map<std::string, double>::iterator it;
    
    it = map.lower_bound(inpDate); // pointing on map["data"] >= inpData
    if ((it == map.end() || it != map.begin()) && !map.count(inpDate))
        it--;
    else if (!map.count(inpDate) && it == map.begin())
       throw std::invalid_argument("date not found => " + inpDate);
    std::cout << inpDate << " => " << inpValue << " = "<< it->second * inpValue << '\n';
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
        if ((day == 29 && isLeapYear(year)) || day < 29)
            return true;
        return false;
    }
    return false;
}
/************PARSING AND CHECK EACH LINE***********/
void BitcoinExchange::parse_lines(std::istringstream& parse, std::string& line)
{
    int year = 0;
    int month = 0;
    int day = 0;
    char fmin = '\0';
    char smin = '\0';
    char pipe = '\0';
    char *ptr = NULL;

    parse >> inpDate;
    if (inpDate.size() != 10)
        throw std::invalid_argument("Error: bad input => " + inpDate);
    parse.seekg(0);
    parse >> year >> fmin >> month >> smin >> day >> pipe;
    if (pipe != '|' || year < 1900 || year > 3000 || fmin != '-' || smin != '-' 
    || month < 1 || month > 12 || day < 1 || !check_month(year, month, day))
        throw std::invalid_argument("Error: bad input => " + inpDate);

    std::string tmp = parse.str().substr(parse.tellg()); // extracted line after pipe to the end 
    inpValue = strtod(tmp.c_str(), &ptr);
    if (line.find_last_of(" \n\t\r\v\f") != 12 || line.size() == 13 || *ptr)
        throw std::invalid_argument("Error: bad input => " + inpDate);
    if (inpValue > 1000)
        throw std::invalid_argument("Error: too large a number.");
    if (inpValue < 0)
        throw std::invalid_argument("Error: not a positive number.");
}
/****************************************************/

/************READING EACH LINE FROM INP FILE***********/
void BitcoinExchange::treating_inp(std::ifstream& inpfile)
{
    std::string line;
    std::getline(inpfile, line);
    if (line != "date | value")
        throw std::invalid_argument("Error: first line input"); // this should stop the program or not?
    while (std::getline(inpfile, line))
    {
        std::istringstream parse(line);
        try
        {
            parse_lines(parse, line);
            calculate_btc();
            
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
}
/********************************************/