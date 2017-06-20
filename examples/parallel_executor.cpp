/*****************************************************************************
 *
 * AM numeric facilities
 *
 * released under MIT license
 *
 * 2015-2017 André Müller
 *
 *****************************************************************************/

#include <iostream>

#include "../include/parallel_executor.h"
#include "timer.h"



//-------------------------------------------------------------------
struct test_task
{
    test_task(int taskid): id(taskid) {}

    void operator () (int ms = 8) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    int id;
};



//-------------------------------------------------------------------
int main()
{
    using namespace am;

    std::cout << "executing parallel tasks" << std::endl;

    timer time;
    std::vector<test_task> tasks1;
    parallel_executor<std::vector<test_task>::iterator,int> runner1(8);

    for(int i = 0; i < 1000; ++i) {
        tasks1.emplace_back(i);
    }

    time.start();
    runner1(tasks1, 6);
    time.stop();

    time.start();
    runner1(tasks1, 10);
    time.stop();


    std::vector<std::function<void()>> tasks2;
    parallel_executor<std::vector<std::function<void()>>::iterator> runner2(8);

    for(int i = 0; i < 126; ++i) {
        tasks2.push_back([i](){
            std::this_thread::sleep_for(std::chrono::milliseconds(i));
        });
    }

    time.start();
    runner2(begin(tasks2), end(tasks2));
    time.stop();

    tasks2.clear();
    for(int i = 0; i < 89; ++i) {
        tasks2.push_back([i](){
            std::this_thread::sleep_for(std::chrono::milliseconds(2*i));
        });
    }

    time.start();
    runner2(begin(tasks2), end(tasks2));
    time.stop();


    std::cout << "finished tasks in " << time.milliseconds() << " ms" << std::endl;
}


