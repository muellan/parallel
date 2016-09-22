AM parallel
==========

Collection of parallel programming primitives for C++

**Note**: All classes and functions are work in progress. Interfaces are still likely 
to change over time, documentation is very poor so far and tests are rudimentary at best. 

All components are header-only.

See the "*_demo.cpp" files for usage examples.

## facilities

#### task_thread
 - pausable thread
 - basis for parallel_task_queue

#### parallel_executor
 - runs a batch of tasks in parallel
 - works on task iterators, doesn't own tasks
 - forwards call args to all tasks
 - blocks calling thread until all tasks are finished

#### parallel_task_queue
 - runs tasks in parallel
 - enqueue & run can interleave
 - owns tasks

#### timer
 - simple std::chrono based timer

## Prerequisites
  - requires (mostly) C++14 conforming compiler
  - tested with g++ 5.3
