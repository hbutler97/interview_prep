//
// Created by hbutl on 12/28/2019.
//

#include <iostream>
#include <stdexcept>
#include <cassert>
#include "SORTER.h"
#include "MEASUREMENT.h"

void SELECTION::sort(std::vector<uint32_t> &array) {
    /*
     * Algorithm
     * 1. index through the input buffer starting with the first element
     * 2. for every iteration, find the smallest value in the buffer
     * 3. once found swap the smallest element with the current location in the buffer
     */
    for(size_t i = 0; i < array.size(); i++) {
        size_t min_value = i;
        for(size_t j = i; j < array.size(); j++) {
            if(array[j] <=array[min_value]) // check for stability
                min_value = j;
        }
        swap(array, min_value,i);
    }

}
//SORTER
void SORTER::swap(std::vector<uint32_t> &buffer, std::size_t a, std::size_t b) {
    assert(a < buffer.size());
    assert(b < buffer.size());
    uint32_t temp = buffer[a];
    buffer[a] = buffer[b];
    buffer[b] = temp;
}

bool SORTER_SELECTOR::checkSorted(std::vector<uint32_t> &array) {
    bool pass = true;
    if(array.empty()){
        std::cout << "Input vector is empty.  Can't check if it is sorted" << std::endl;
        pass = false;
    }
    for(size_t i = 0; i < array.size() - 1 && pass ; i++)
        pass = array[i] <= array[i + 1];
    return pass;
}

void SORTER_SELECTOR::sort(std::string &sort_algorithm, std::vector<uint32_t> &array) {
    MEASUREMENT measure;
    if(array.empty())
        throw SORT_EXCEPT("Input vector is empty.  Nothing to sort");
    if(m_map.find(sort_algorithm) == m_map.end()) {
        std::cout << sort_algorithm << " Algorithm is not an option" << std::endl;
        std::cout << "Please enter one of the following algorithms:" << std::endl;
        for(const auto &algorithm :m_map)
            std::cout << algorithm.first << std::endl;
        throw SORT_EXCEPT("Invalid sorting algorithm specified");
    }
    else {
        std::cout << "Starting " << sort_algorithm << " sort" << std::endl;
        measure.start();
        m_map[sort_algorithm]->sort(array);
        measure.stop();
        measure.report();
    }
}

void BUBBLE::sort(std::vector<uint32_t> &array) {
    /*
     * Algorithm
     * 1. starting at the end of the array, index through the array and swap
     * adjacent elements if the element on the left is larger than the right
     * 2. repeat this until you n times and for every iteration of n, terminating the above
     * loop at the nth element
     */
    for(size_t i = 0; i < array.size(); ++i) {
        for(size_t j = array.size() - 1 ; j > i; --j){
            if(array[j] < array[j-1])
                swap(array, j, j - 1);
        }
    }
}

void INSERTION::sort(std::vector<uint32_t> &array) {
    /*
     * Algorithm
     * 1. scan array from right to left
     * 2. for each iteration, compare current location with the next location
     * 3. if next location is > current swap the location.
     * 4. do this recursively to reduce the problem set
     */
    sortHelper(array, array.size());
}

void INSERTION::sortHelper(std::vector<uint32_t> &array, size_t numb_elements) {

    if(numb_elements <= 1)
        return;
    sortHelper(array, numb_elements-1);
    size_t index = numb_elements - 1;
    uint32_t value = array[index];
    bool found_slot = false;
    for(size_t i = index; (i > 0) & (!found_slot); --i) {
        if(array[i-1] > value) {
            array[i] = array[i - 1];
            array[i-1] = value;
        }
        else
            found_slot = true;
    }
}
