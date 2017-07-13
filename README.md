AM parallel
==========

Header-only parallel programming primitives for C++14.

The repo also includes some examples.


## Classes

#### task\_thread
 - pausable thread
 - basis for parallel\_task\_queue

#### parallel\_executor
 - runs a batch of tasks in parallel
 - works on task iterators, doesn't own tasks
 - forwards call args to all tasks
 - blocks calling thread until all tasks are finished

#### parallel\_task\_queue
 - runs tasks in parallel
 - enqueue & run can interleave
 - owns tasks


## Requirements
  - requires (mostly) C++14 conforming compiler
  - tested with g++ {5.3, 7.2}
