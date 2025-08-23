#include "PmergeMe.hpp"

int main(int argc, char** argv) {
    try
    {
        PmergeMe sorter;
        sorter.loadInput(argc, argv);
        sorter.displayBefore();
        sorter.sortAndMeasure();
        sorter.displayAfter();
        sorter.displayTimes();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
