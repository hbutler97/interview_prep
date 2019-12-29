//
// Created by hbutl on 12/28/2019.
//

#include "SORTER.h"
#include "MEASUREMENT.h"

SELECTION::SELECTION() {
}

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
    return;
}
//SORTER
void SORTER::swap(std::vector<uint32_t> &buffer, std::size_t a, std::size_t b) {
    //add error checking on bounds
    uint32_t temp = buffer[a];
    buffer[a] = buffer[b];
    buffer[b] = temp;
    return;
}

bool SORTER::checkSorted(std::vector<uint32_t> &array) {
    bool pass = true;
    for(size_t i = 0; i < array.size() - 1 ; i++)
        pass = (array[i] <= array[i+1])?true:false;
    return pass;
}
