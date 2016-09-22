/*****************************************************************************
 *
 * AM numeric facilities
 *
 * released under MIT license
 *
 * 2008-2015 André Müller
 *
 *****************************************************************************/

#include <iostream>

#include "parallel_executor_demo.h"
#include "parallel_task_queue_demo.h"


int main()
{
    std::cout << "parallel_executor" << std::endl;
    demo::use_parallel_executor();

    std::cout << "parallel_task_queue" << std::endl;
    demo::use_parallel_task_queue();
}
