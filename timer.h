/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2011-2015 André Müller
 *
 *****************************************************************************/

#ifndef AM_TIMER_H
#define AM_TIMER_H

#include <sstream>
#include <ctime>
#include <ratio>
#include <chrono>


namespace am {


/*****************************************************************************
 *
 *
 * @brief simple timer class
 *
 *
 *****************************************************************************/
class timer
{
    using basic_duration_t = std::chrono::milliseconds;

public:
    //---------------------------------------------------------------
    void
    start() noexcept {
        if(!running_) {
            running_ = true;
            start_ = std::chrono::high_resolution_clock::now();
        }
    }
    //-----------------------------------------------------
    void
    reset() noexcept {
        total_ = basic_duration_t(0);
        running_ = false;
    }
    //-----------------------------------------------------
    void
    restart() noexcept {
        reset();
        start();
    }

    //-----------------------------------------------------
    void
    stop() noexcept {
        if(running_) {
            stop_ = std::chrono::high_resolution_clock::now();
            total_ += std::chrono::duration_cast<basic_duration_t>(stop_-start_);
            running_ = false;
        }
    }


    //---------------------------------------------------------------
    bool
    running() const noexcept {
        return running_;
    }

    //-----------------------------------------------------
    int64_t
    milliseconds() const noexcept {
        return std::chrono::duration_cast<
            std::chrono::milliseconds>(current()).count();
    }

    int64_t
    full_seconds() const noexcept {
        return std::chrono::duration_cast<
            std::chrono::seconds>(current()).count();
    }

    int
    full_minutes() const noexcept {
        return std::chrono::duration_cast<
            std::chrono::minutes>(current()).count();
    }

    int
    full_hours() const noexcept {
        return std::chrono::duration_cast<
            std::chrono::hours>(current()).count();
    }


    //-----------------------------------------------------
    double
    seconds() const noexcept {
        return (milliseconds() / 1000.0);
    }

    double
    minutes() const noexcept {
        return (milliseconds() / 60000.0);
    }

    double
    hours() const noexcept {
        return (milliseconds() / 3600000.0);
    }


    //-----------------------------------------------------
    std::string
    hh_mm_ss() const noexcept
    {
        std::ostringstream ss;
        int h = static_cast<int>(full_hours());
        int m = static_cast<int>(full_minutes());
        int s = static_cast<int>(full_seconds());
        if(h < 10) ss << "0"; ss << h << ":";
        if(m < 10) ss << "0"; ss << m << ":";
        if(s < 10) ss << "0"; ss << s;
        return ss.str();
    }


private:
    //-----------------------------------------------------
    basic_duration_t
    current() const noexcept {
        if(!running_) return total_;

        return (
            total_ + (std::chrono::duration_cast<basic_duration_t>(
                std::chrono::high_resolution_clock::now() - start_)) );
    }

    //---------------------------------------------------------------
    std::chrono::high_resolution_clock::time_point start_, stop_;
    basic_duration_t total_ = basic_duration_t(0);
    bool running_ = false;
};



}  // namespace am


#endif
