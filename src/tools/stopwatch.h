#ifndef PARALLEL_STOPWATCH_H
#define PARALLEL_STOPWATCH_H

#include <ctime>
#include <ostream>

/**
 * This class provides a simple interface for timing pieces of code.
 *
 * Example:
 *      stop_watch sw;
 *      sw.start();
 *      // code to time here
 *      sw.stop();
 *      std::cout << sw.get_seconds() << std::endl;
 *
 */
class stop_watch {

    double elapsedTime = -1;
    std::chrono::steady_clock::time_point time_start;
    std::chrono::steady_clock::time_point time_stop;

public:
    void start() {
        this->time_start = std::chrono::steady_clock::now();
    }

    void stop() {
        this->time_stop = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds> (time_stop - time_start).count() / 1000000000.0;
    }

    void reset() {
        this->elapsedTime = -1;
    }

    double get_seconds() {
        return elapsedTime;
    }

public:
    friend std::ostream &operator<<(std::ostream &os, const stop_watch &watch) {
        os << "Elapsed Time: " << watch.elapsedTime << " seconds.";
        return os;
    }

};

#endif //PARALLEL_STOPWATCH_H
