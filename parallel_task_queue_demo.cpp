/*****************************************************************************
 *
 * AM numeric facilities
 *
 * released under MIT license
 *
 * 2008-2015 André Müller
 *
 *****************************************************************************/

#include "parallel_task_queue_demo.h"

#include "parallel_task_queue.h"
#include "timer.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <random>


namespace demo {


//-------------------------------------------------------------------
double parallel_sum(const std::vector<double>& v) {
    constexpr int n = 64;

    am::parallel_function_queue q;

    auto psums = std::vector<double>(n+1, 0.0);
    const auto chunk = v.size() / n;
    for(int i = 0; i < n; ++i) {
        q.enqueue([&,i]{
            psums[i] = std::accumulate(begin(v) + (i*chunk),
                                       begin(v) + ((i+1)*chunk), 0.0);
        });
    }
    if(v.size() % n > 0) {
        q.enqueue([&]{
            psums.back() = std::accumulate(begin(v) + (chunk*n), end(v), 0.0);
        });
    }

    q.wait();
    return std::accumulate(begin(psums), end(psums), 0.0);
}



//-------------------------------------------------------------------
void use_parallel_task_queue()
{
    constexpr size_t n = 1 << 26;
    std::cout << "creating " << n << " values... " << std::flush;

    am::timer time;
    time.start();

    auto nums = std::vector<double>(n);
    std::iota(begin(nums), end(nums), 0);

    time.stop();
    std::cout << time.milliseconds() << " ms" << std::endl;

    time.restart();
    // auto sum = std::accumulate(nums.begin(), nums.end(), 0.0);
    auto sum = parallel_sum(nums);

    time.stop();
    std::cout << "summing:  " << time.milliseconds() << " ms\n"
              << "result:   " << sum << std::endl;
}



} // namespace demo
