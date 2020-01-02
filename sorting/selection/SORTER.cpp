//
// Created by hbutl on 12/28/2019.
//

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cmath>
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

void INSERTION_ITER::sort(std::vector<uint32_t> &array) {
    for(size_t j = 1; j < array.size(); j++){
        size_t index = j;
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
}

void MERGE::sort(std::vector<uint32_t> &array) {
    //Need to check input
    //what about odd case for array size
    merge_sort(array, 0, array.size() -1);
}

void MERGE::merge_sort(std::vector<uint32_t> &array, size_t begin, size_t end) {
    if(end <= begin)
        return;
    size_t l_begin = begin;
    size_t l_end = (begin + end)/2;
    size_t r_begin = l_end + 1;
    size_t r_end = end;
    merge_sort(array, l_begin, l_end);
    merge_sort(array, r_begin , r_end);
    merge(array,l_begin,l_end,r_begin,r_end);
}

void MERGE::merge(std::vector<uint32_t> &array, size_t l_begin, size_t l_end, size_t r_begin, size_t r_end) {

    std::vector<uint32_t> temp_buffer((l_end - l_begin + 1) + (r_end - r_begin + 1));
    size_t left = l_begin;
    size_t right = r_begin;
    size_t index = 0;
    while(left <= l_end && right <= r_end) {
        if(array[left] <= array[right])
            temp_buffer[index++] = array[left++];
        else
            temp_buffer[index++] = array[right++];
    }
    while(left <= l_end)
        temp_buffer[index++] = array[left++];

    while(right <= r_end)
        temp_buffer[index++] = array[right++];

    left = l_begin;
    index = 0;
    while(left <= r_end)
        array[left++] = temp_buffer[index++];
}

void MERGE_ITER::sort(std::vector<uint32_t> &array) {
    MERGE merge;
    for (size_t i = 2; i < array.size(); i = i * 2) {
        for (size_t j = 0; array.size(); j = j + i) {
            size_t l_begin = j;
            size_t l_end =  j + i ;
            size_t r_begin = l_end + 1;
            size_t r_end = r_begin + i -1;
            merge.merge(array, l_begin, l_end, r_begin, r_end);
        }
    }

}

void QUICK::sort(std::vector<uint32_t> &array) {
    quick_sort(array,0,array.size() - 1);
}

void QUICK::quick_sort(std::vector<uint32_t> &array, size_t begin, size_t end) {
    if(end <= begin)
        return;
    RANDOM_GENERATOR rand_number(begin, end);
    size_t pivot_index = rand_number.getNumber();
    swap(array,pivot_index, begin);
    size_t low(begin + 1);
    size_t high = low;
    for(high = low; high <= end; high++){
        if(array[high] < array[begin]){
            swap(array,low, high);
            low++;
        }
    }
    swap(array,begin,low-1);

    quick_sort(array,begin,low-1);
    quick_sort(array,low, end);
}
