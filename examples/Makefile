.PHONY: clean 

INCLUDE  = ../include
FILTER   = *
SOURCES  = $(wildcard $(FILTER).cpp)
EXECS    = $(notdir $(SOURCES:.cpp=))
FLAGS    = -I $(INCLUDE) -std=c++14 -O3 -Wall -pthread

INCLUDES = \
    $(INCLUDE)/parallel_executor.h \
    $(INCLUDE)/parallel_task_queue.h \
    $(INCLUDE)/task_thread.h \
    timer.h

.PHONY: all clean

all: $(EXECS)

% : %.cpp $(INCLUDES)
	g++ $(FLAGS) -o $@ $<

clean:
	find -type f -not -name "*.cpp" -not -name "*.h" -not -name "Makefile" -not -name "runall" | xargs rm
