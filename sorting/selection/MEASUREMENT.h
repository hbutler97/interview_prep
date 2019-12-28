//
// Created by hbutl on 12/28/2019.
//

#ifndef SELECTION_MEASUREMENT_H
#define SELECTION_MEASUREMENT_H


#include <chrono>

class MEASUREMENT {
public:
    MEASUREMENT();
    void start();
    void stop();
    void report();
    MEASUREMENT(const MEASUREMENT&) = delete;
    MEASUREMENT& operator =(const MEASUREMENT&) = delete;
private:
    std::chrono::high_resolution_clock::time_point m_t1;
    std::chrono::high_resolution_clock::time_point m_t2;duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
};


#endif //SELECTION_MEASUREMENT_H
