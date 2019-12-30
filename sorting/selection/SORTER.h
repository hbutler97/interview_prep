//
// Created by hbutl on 12/28/2019.
//

#ifndef SORTER_H
#define SORTER_H
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <memory>

class SORT_EXCEPT : std::runtime_error {
public:
    explicit SORT_EXCEPT(const char *msg) : runtime_error(msg) {m_message = this->what();};
    std::string getMessage(){return m_message;};
private:
    std::string m_message;
};

class SORTER {
public:
    virtual void sort(std::vector<uint32_t> &array) = 0;

protected:
    static void swap(std::vector<uint32_t> &buffer, std::size_t a, std::size_t b);
};
class SORTER_SELECTOR {
public:
    SORTER_SELECTOR();
    void sort(std::string &sort_algorithm, std::vector<uint32_t> &array);
    static bool checkSorted(std::vector<uint32_t> &array);
private:
    std::unordered_map<std::string, std::unique_ptr<SORTER>> m_map;
};
class SELECTION : public SORTER {
public:
    SELECTION();
    SELECTION(const SELECTION&) = delete;
    SELECTION& operator =(const SELECTION&) = delete;
    void sort(std::vector<uint32_t> &array) override;
private:
};
#endif //SORTER_H
