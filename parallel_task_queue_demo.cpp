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
void use_parallel_task_queue()
{
    using namespace std::chrono_literals;

    auto concurrency = std::thread::hardware_concurrency();
    am::parallel_task_queue<std::function<void()>> q{concurrency};
    std::cout << "concurrency: " << concurrency << std::endl;

    constexpr int n = 100;
    std::array<int,n> check;
    for(auto& x : check) x = 0;
    std::array<double,n> vals;
    for(auto& x : vals) x = 0.0;

    am::timer time;
    time.start();
    for(int i = 0; i < n; ++i) {
        q.enqueue([&check,&vals,i]() {
            check[i] = i;

            double v = 0.0;
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            auto urng = std::mt19937_64(seed);
            auto distr = std::uniform_real_distribution<double>{-1,1};
            for(int j = 0; j < 10000000; ++j) {
                v += distr(urng);
            }
            vals[i] = v;
//            auto distr = std::uniform_int_distribution<int>{1,100};
//            std::this_thread::sleep_for(std::chrono::milliseconds(100 + distr(urng)));
        });
    }

    q.wait();
    time.stop();

    for(int i = 0; i < n; ++i) {
        if(check[i] != i) {
            std::cout << "ERROR\n";
            for(auto x : check) std::cout << x << '\n';
            return;
        }
    }

    std::cout << "DONE: " << time.milliseconds() << " ms" << std::endl;

    double sum = std::accumulate(begin(vals), end(vals), 0.0);
    std::cout << "SUM:  " << sum << std::endl;
}



} // namespace demo
