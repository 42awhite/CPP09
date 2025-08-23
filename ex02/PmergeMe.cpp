#include "PmergeMe.hpp"

//Canonical form
PmergeMe::PmergeMe() : _timeVec(0), _timeDeq(0)
{}

// Copy constructor
PmergeMe::PmergeMe(const PmergeMe& other)
    : _vec(other._vec), _deq(other._deq), _timeVec(other._timeVec), _timeDeq(other._timeDeq)
{}

// Assignment operator
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
        _timeVec = other._timeVec;
        _timeDeq = other._timeDeq;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{}

/*
CHULETA FUNCIONES VECTORES:
    *push_back -> Añade un elemento al final de un contenedor: [5, 10] -> [5, 10, 42]
*/

//Funciones
void PmergeMe::loadInput(int argc, char** argv)
{
    if (argc < 2)
        throw std::runtime_error("Error: No input numbers");
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        //recorrer cada número para ver que todos son dígitos.
        for(size_t j = 0; j < arg.size(); j++)
        {
            if (!isdigit(arg[j]))
                throw std::runtime_error("Error: Invalid input");
        }
        long num = std::atol(arg.c_str());
        if (num <= 0 || num > __INT_MAX__)
            throw std::runtime_error("Error: Invalid input");
        _vec.push_back(static_cast<int>(num));
        _deq.push_back(static_cast<int>(num));
    }
}

void PmergeMe::displayBefore() const
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::displayAfter() const
{
    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::displayTimes() const
{
    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << _timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : " << _timeDeq << " us" << std::endl;
}

void PmergeMe::sortAndMeasure()
{
    clock_t start_vec, end_vec;
    clock_t start_deq, end_deq;

    //Vec
    start_vec = clock();
    fordJohnsonVector(_vec);
    end_vec = clock();
    _timeVec = (double)(end_vec - start_vec) / CLOCKS_PER_SEC * 1e6;
    //Deque
    start_deq = clock();
    fordJohnsonDeque(_deq);
    end_deq = clock();
    _timeDeq = (double)(end_deq - start_deq) / CLOCKS_PER_SEC * 1e6;
}

// Implementación de Ford–Johnson

void binaryInsert(std::vector<int>& vec, int value, int start, int end) {
    int low = start;
    int high = end;
    while (low < high) 
    {
        int mid = (low + high) / 2;
        if (vec[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }
    vec.insert(vec.begin() + low, value);
}

void binaryInsert(std::deque<int>& deq, int value, int start, int end) {
    int low = start;
    int high = end;
    while (low < high) {
        int mid = (low + high) / 2;
        if (deq[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }
    deq.insert(deq.begin() + low, value);
}

void PmergeMe::fordJohnsonVector(std::vector<int>& vec)
{
    if (vec.size() <= 1)
        return;

    std::vector<int> bigger; // Larger elements of pairs
    std::vector<int> smaller; // Smaller elements of pairs

    //Formar pares
    size_t i = 0;
    for (; i + 1 < vec.size(); i += 2) //Puede ser un while?
    {
        if (vec[i] < vec[i + 1]) 
        {
            smaller.push_back(vec[i]);
            bigger.push_back(vec[i + 1]);
        } 
        else 
        {
            smaller.push_back(vec[i + 1]);
            bigger.push_back(vec[i]);
        }
    }
    if (i < vec.size()) 
    {
        // Odd element left, add to bigger
        bigger.push_back(vec[i]);
    }
    // Recursively sort bigger array
    fordJohnsonVector(bigger);

    // Start with bigger array as base
    vec = bigger;

    // Insert smaller elements using binary insertion
    for (size_t j = 0; j < smaller.size(); ++j) 
        binaryInsert(vec, smaller[j], 0, vec.size());
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return;
    std::deque<int> bigger;
    std::deque<int> smaller;
    
    size_t i = 0;
    for (; i + 1 < deq.size(); i += 2) {
        if (deq[i] < deq[i + 1]) {
            smaller.push_back(deq[i]);
            bigger.push_back(deq[i + 1]);
        } else {
            smaller.push_back(deq[i + 1]);
            bigger.push_back(deq[i]);
        }
    }
    if (i < deq.size()) {
        bigger.push_back(deq[i]);
    }
    // Recursively sort bigger array
    fordJohnsonDeque(bigger);

    deq = bigger;

    // Insert smaller elements
    for (size_t j = 0; j < smaller.size(); ++j) {
        binaryInsert(deq, smaller[j], 0, deq.size());
    }
}
