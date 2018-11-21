#include "Utility/Timer.hpp"

namespace chrono = std::chrono;

Timer::Timer():
    timePoint(nullptr) {
    timeDuration = new chrono::steady_clock::duration(0);
}

Timer::~Timer() {
    delete timePoint;
    delete timeDuration;
}

// PRE: timer is not started or paused
void Timer::startTimer() {
    timePoint = new chrono::steady_clock::time_point(chrono::steady_clock::now());
}

// PRE: timer is started
void Timer::pauseTimer() {
    *timeDuration += (chrono::steady_clock::now() - *timePoint);
    delete timePoint;
    timePoint = nullptr;
}

void Timer::resetTimer() {
    delete timePoint;
    timePoint = nullptr;
    *timeDuration = chrono::steady_clock::duration(0);
}

// NOTE: may be called any time
chrono::steady_clock::duration Timer::getAccumulatedTime() const {
    chrono::steady_clock::duration accumulatedTime(*timeDuration);
    if (timePoint != nullptr) {
        accumulatedTime += (chrono::steady_clock::now() - *timePoint);
    }
    return accumulatedTime;
}
