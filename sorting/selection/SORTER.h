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
    ~SORT_EXCEPT() override= default;;
private:
    std::string m_message;
};

class SORTER {
public:
    virtual void sort(std::vector<uint32_t> &array) = 0;
    ~SORTER() = default;
protected:
    static void swap(std::vector<uint32_t> &buffer, std::size_t a, std::size_t b);

};

class SELECTION : public SORTER {
public:
    SELECTION() = default;
    SELECTION(const SELECTION&) = delete;
    SELECTION& operator =(const SELECTION&) = delete;
    void sort(std::vector<uint32_t> &array) override;
};

class BUBBLE : public SORTER {
public:
    BUBBLE() = default;
    BUBBLE(const BUBBLE&) = delete;
    BUBBLE& operator =(const BUBBLE&) = delete;
    void sort(std::vector<uint32_t> &array) override;
};
class INSERTION : public SORTER {
public:
    INSERTION() = default;
    INSERTION(const INSERTION&) = delete;
    INSERTION& operator =(const INSERTION&) = delete;
    void sort(std::vector<uint32_t> &array) override;
private:
    static void sortHelper(std::vector<uint32_t> &array, size_t numb_elements);
};
class INSERTION_ITER : public SORTER {
public:
    INSERTION_ITER() = default;
    INSERTION_ITER(const INSERTION_ITER&) = delete;
    INSERTION_ITER& operator =(const INSERTION_ITER&) = delete;
    void sort(std::vector<uint32_t> &array) override;
};
class MERGE : public SORTER {
public:
    MERGE() = default;
    MERGE(const MERGE&) = delete;
    MERGE& operator =(const MERGE&) = delete;
    void sort(std::vector<uint32_t> &array) override;
private:
    static void merge_sort(std::vector<uint32_t> &array, size_t begin, size_t end);
    static void merge(std::vector<uint32_t> &array, size_t l_begin, size_t l_end,
                     size_t r_begin, size_t r_end);
};
class SORTER_SELECTOR {
public:
    SORTER_SELECTOR(){
        m_map["selection"] = std::make_unique<SELECTION>();
        m_map["bubble"] = std::make_unique<BUBBLE>();
        m_map["insertion"] = std::make_unique<INSERTION>();
        m_map["insertion_iter"] = std::make_unique<INSERTION_ITER>();
        m_map["merge"] = std::make_unique<MERGE>();
    };
    void sort(std::string &sort_algorithm, std::vector<uint32_t> &array);
    static bool checkSorted(std::vector<uint32_t> &array);
    ~SORTER_SELECTOR()= default;;
private:
    std::unordered_map<std::string, std::unique_ptr<SORTER>> m_map;
};
#endif //SORTER_H
