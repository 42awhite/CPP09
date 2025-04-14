#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

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
    BitcoinExchange(const std::string& dbFile);

    // Métodos principales
    float getClosestRate(const std::string& date) const;
    static bool isValidDate(const std::string& date);
    static bool isValidValue(const std::string& valueStr, float& value);
};

#endif
