//
// Created by hbutl on 12/28/2019.
//

#ifndef SELECTION_SORTER_H
#define SELECTION_SORTER_H
#include <vector>
#include <cstdint>

class SORTER {
public:
    SORTER();
    SORTER(const SORTER&) = delete;
    SORTER& operator =(const SORTER&) = delete;
    bool sort(std::vector<uint32_t> &array);
    bool checkSorted(std::vector<uint32_t> &array);

private:
    void swap(std::vector<uint32_t> &buffer, std::size_t a, std::size_t b);
};


#endif //SELECTION_SORTER_H
