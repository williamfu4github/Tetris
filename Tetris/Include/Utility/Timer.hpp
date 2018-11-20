#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();
    void startTimer();
    void pauseTimer();
    void clearTimer();    // not used
    std::chrono::steady_clock::duration getAccumulatedTime() const;
    
private:
    std::chrono::steady_clock::time_point* timePoint;
    std::chrono::steady_clock::duration* timeDuration;
};

#endif
