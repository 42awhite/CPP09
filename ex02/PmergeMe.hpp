#ifndef PMERGEME_HPP
#define PMERGEME_HPP

/*# Genera 3000 números aleatorios entre 1 y 100000 (Linux)
./PmergeMe $(shuf -i 1-100000 -n 3000)*/

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <algorithm>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int>  _deq;

    double _timeVec;
    double _timeDeq;

public:
// Canonical form
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

//Funciones
    void loadInput(int argc, char** argv);
    void sortAndMeasure();
    void displayBefore() const;
    void displayAfter() const;
    void displayTimes() const;

    //Implementación de Ford–Johnson
    void fordJohnsonVector(std::vector<int>& vec);
    void fordJohnsonDeque(std::deque<int>& deq);
};

#endif
