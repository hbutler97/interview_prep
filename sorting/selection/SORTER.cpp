//
// Created by hbutl on 12/28/2019.
//

#include <iostream>
#include "SORTER.h"
#include "MEASUREMENT.h"



SELECTION::SELECTION() = default;

void SELECTION::sort(std::vector<uint32_t> &array) {
    /*
     * Algorithm
     * 1. index through the input buffer starting with the first element
     * 2. for every iteration, find the smallest value in the buffer
     * 3. once found swap the smallest element with the current location in the buffer
     */
    MEASUREMENT measure;
    measure.start();
    for(size_t i = 0; i < array.size(); i++) {
        size_t min_value = i;
        for(size_t j = i; j < array.size(); j++) {
            if(array[j] <=array[min_value]) // check for stability
                min_value = j;
        }
        swap(array, min_value,i);
    }
    measure.stop();
    measure.report();
}
//SORTER
void SORTER::swap(std::vector<uint32_t> &buffer, std::size_t a, std::size_t b) {
    //add error checking on bounds
    uint32_t temp = buffer[a];
    buffer[a] = buffer[b];
    buffer[b] = temp;
}

bool SORTER_SELECTOR::checkSorted(std::vector<uint32_t> &array) {
    bool pass = true;
    for(size_t i = 0; i < array.size() - 1 && pass ; i++)
        pass = array[i] <= array[i + 1];
    return pass;
}

SORTER_SELECTOR::SORTER_SELECTOR() {
    m_map["selection"] = std::make_unique<SELECTION>();
}

void SORTER_SELECTOR::sort(std::string &sort_algorithm, std::vector<uint32_t> &array) {
    //add exception
    if(m_map.find(sort_algorithm) == m_map.end()) {
        std::cout << sort_algorithm << " Algorithm is not an option" << std::endl;
        std::cout << "Please enter one of the following algorithms:" << std::endl;
        for(const auto &algorithm :m_map)
            std::cout << algorithm.first << std::endl;
    }
    else
       m_map[sort_algorithm]->sort(array);
}
