#include "BitcoinExchange.hpp"

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

BitcoinExchange::BitcoinExchange(const std::string& dbFile) 
{
    std::ifstream file(dbFile.c_str()); //Prepara el archivo para lectura. 
    if (!file.is_open()) 
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) 
    {
        std::stringstream ss(line); // Crea un string a partir de la línea.
        std::string date, valueStr;
        if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr))
            continue;
        float value = std::strtof(valueStr.c_str(), NULL); //convierte de string a float
        _prices[date] = value;
    }
}

// En BitcoinExchange.cpp (implementación)
void BitcoinExchange::processInputFile(const std::string& filename) const
{
    std::ifstream input(filename.c_str());
    if (!input.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(input, line); // saltar encabezado

    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string date, valueStr;
        if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        date = date.erase(date.find_last_not_of(" \t") + 1);
        valueStr = valueStr.substr(valueStr.find_first_not_of(" \t"));
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
        float rate = getClosestRate(date);
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}


// Devuelve el rate de la fecha más cercana anterior
float BitcoinExchange::getClosestRate(const std::string& date) const 
{
    std::map<std::string, float>::const_iterator it = _prices.lower_bound(date);
    if (it == _prices.end() || it->first != date) 
    {
        if (it == _prices.begin())
        {
            std::cout << "Error: There is no valid value for the date" << date << std::endl;
            return 0.0f;
        }
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
    std::istringstream yss(date.substr(0, 4));
    std::istringstream mss(date.substr(5, 2));
    std::istringstream dss(date.substr(8, 2));
    if (!(yss >> y) || !(mss >> m) || !(dss >> d))
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
