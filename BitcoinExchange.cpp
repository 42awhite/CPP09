#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

// Canonical Form
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _prices(other._prices) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) 
{
    if (this != &other)
        _prices = other._prices;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Constructor con archivo CSV
BitcoinExchange::BitcoinExchange(const std::string& dbFile) 
{
    std::ifstream file(dbFile.c_str());
    if (!file.is_open()) 
    {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        std::string date, valueStr;
        if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr))
            continue;
        float value = std::strtof(valueStr.c_str(), NULL);
        _prices[date] = value;
    }
}

// Devuelve el rate de la fecha más cercana anterior
float BitcoinExchange::getClosestRate(const std::string& date) const {
    std::map<std::string, float>::const_iterator it = _prices.lower_bound(date);
    if (it == _prices.end() || it->first != date) 
    {
        if (it == _prices.begin())
            return 0.0f;
        --it;
    }
    return it->second;
}

// Validación de fecha YYYY-MM-DD
bool BitcoinExchange::isValidDate(const std::string& date) 
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
        return false;
    return (y >= 2009 && m >= 1 && m <= 12 && d >= 1 && d <= 31);
}

// Validación de valor y conversión a float
bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) 
{
    std::stringstream ss(valueStr);
    ss >> value;
    if (ss.fail() || !ss.eof())
        return false;
    return (value >= 0.0f && value <= 1000.0f);
}
