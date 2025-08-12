#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) 
{
    if (argc != 2) 
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange exchange("data.csv");

    std::ifstream input(argv[1]);
    if (!input.is_open()) 
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(input, line); // skip header

    while (std::getline(input, line)) 
    {
        std::stringstream ss(line);
        std::string date, valueStr;

        if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) 
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = date.erase(date.find_last_not_of(" \t") + 1); //Borrar espacios del final
        valueStr = valueStr.substr(valueStr.find_first_not_of(" \t")); //borrar espacios del principio

        if (!BitcoinExchange::isValidDate(date)) 
        {
            std::cerr << "Error: invalid date => " << line << std::endl;
            continue;
        }

        float value;
        if (!BitcoinExchange::isValidValue(valueStr, value)) 
        {
            if (value < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            else
                std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        float rate = exchange.getClosestRate(date);
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
    return 0;
}
