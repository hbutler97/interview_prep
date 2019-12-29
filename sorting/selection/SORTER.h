//
// Created by hbutl on 12/28/2019.
//

#ifndef SORTER_H
#define SORTER_H
#include <vector>
#include <cstdint>

class SORTER {
public:
    virtual void sort(std::vector<uint32_t> &array) = 0;
    bool checkSorted(std::vector<uint32_t> &array);
protected:
    void swap(std::vector<uint32_t> &buffer, std::size_t a, std::size_t b);
};

class SELECTION : public SORTER {
public:
    SELECTION();
    SELECTION(const SELECTION&) = delete;
    SELECTION& operator =(const SELECTION&) = delete;
    void sort(std::vector<uint32_t> &array);
private:
};
#endif //SORTER_H
