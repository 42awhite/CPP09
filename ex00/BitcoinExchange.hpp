#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

class BitcoinExchange 
{
private:
    std::map<std::string, float> _prices;

public:
    // Canonical Form
    BitcoinExchange();                                      // Constructor por defecto
    BitcoinExchange(const BitcoinExchange& other);          // Constructor por copia
    BitcoinExchange& operator=(const BitcoinExchange& other); // Operador de asignación
    ~BitcoinExchange();                                     // Destructor

    // Constructor con archivo
    BitcoinExchange(const std::string& file);

    // Métodos principales
    void processInputFile(const std::string& filename) const;
    float getClosestRate(const std::string& date) const;
    //validadores
    static bool isValidDate(const std::string& date);
    static bool isValidValue(const std::string& valueStr, float& value);
};

#endif
