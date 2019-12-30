//
// Created by hbutl on 12/27/2019.
//
#include <assert.h>
#include "RANDOM_GENERATOR.h"

RANDOM_GENERATOR::RANDOM_GENERATOR(uint32_t low, uint32_t high) {
    assert(low < high);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_generator = std::make_unique<std::default_random_engine>(seed);
    m_distribution = std::make_unique<std::uniform_int_distribution<uint32_t>>(low,high);
}

uint32_t RANDOM_GENERATOR::getNumber() {
    return m_distribution->operator()(*m_generator);
}
