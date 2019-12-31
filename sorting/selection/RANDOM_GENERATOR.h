//
// Created by hbutl on 12/27/2019.
//

#ifndef SELECTION_RANDOM_GENERATOR_H
#define SELECTION_RANDOM_GENERATOR_H
#include <random>
#include <memory>
#include <chrono>

class RANDOM_GENERATOR {
public:
    explicit RANDOM_GENERATOR(uint32_t low=1, uint32_t high=std::numeric_limits<uint32_t>::max());
    RANDOM_GENERATOR(const RANDOM_GENERATOR&) = delete;
    RANDOM_GENERATOR& operator =(const RANDOM_GENERATOR&) = delete;
    uint32_t getNumber();
    ~RANDOM_GENERATOR() = default;
private:
    std::unique_ptr<std::default_random_engine> m_generator;
    std::unique_ptr<std::uniform_int_distribution<uint32_t>> m_distribution;
};


#endif //SELECTION_RANDOM_GENERATOR_H
