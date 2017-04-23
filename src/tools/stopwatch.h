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
    clock_t time_start = 0;
    clock_t time_stop = 0;

public:
    void start() {
        reset();
        this->time_start = clock();
    }

    void stop() {
        this->time_stop = clock();
        elapsedTime = double(time_stop - time_start) / CLOCKS_PER_SEC;
    }

    void reset() {
        this->elapsedTime = -1;
        this->time_start = 0;
        this->time_stop = 0;
    }

    double get_seconds() {
        return elapsedTime;
    }

public:
    friend std::ostream &operator<<(std::ostream &os, const stop_watch &watch) {
        os << "Elapsed Time: " << watch.elapsedTime;
        return os;
    }

};

#endif //PARALLEL_STOPWATCH_H
