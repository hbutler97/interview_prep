//
// Created by hbutl on 12/28/2019.
//
#include <iostream>
#include <ratio>
#include "MEASUREMENT.h"

MEASUREMENT::MEASUREMENT()
{

}

void MEASUREMENT::start() {
    m_t1 = std::chrono::high_resolution_clock::now();
}

void MEASUREMENT::stop() {
    m_t2 = std::chrono::high_resolution_clock::now();
}

void MEASUREMENT::report() {
    std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(m_t2 - m_t1);
    std::cout << "Time: " << timeSpan.count() << " seconds" << std::endl;
}
