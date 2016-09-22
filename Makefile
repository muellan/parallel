ARTIFACT  = pardemo
COMPILER  = g++
DIALECT   = -std=c++14 
WARNINGS  = -Wall -Wextra -Wpedantic
OPTIMIZE  = -march=native -O3
LDFLAGS   = -s

BUILD_DIR = build
OBJS      = demos.o parallel_executor_demo.o parallel_task_queue_demo.o


#--------------------------------------------------------------------
.PHONY: clean

demo: $(BUILD_DIR) $(ARTIFACT)

clean : 
	rm -f *.exe
	rm -f $(ARTIFACT)
	rm -f $(BUILD_DIR)/*
	rmdir $(BUILD_DIR)


#--------------------------------------------------------------------
FLAGS      = $(MACROS) $(DIALECT) $(OPTIMIZE) $(WARNINGS)
BUILD_OBJS = $(OBJS:%=$(BUILD_DIR)/%)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 

$(ARTIFACT): $(BUILD_OBJS)
	$(COMPILER) -o $(ARTIFACT) $(BUILD_OBJS) $(LDFLAGS)

$(BUILD_DIR)/demos.o : demos.cpp
	$(COMPILER) $(FLAGS) -c $< -o $(BUILD_DIR)/demos.o

$(BUILD_DIR)/parallel_executor_demo.o : parallel_executor_demo.cpp parallel_executor_demo.h
	$(COMPILER) $(FLAGS) -c $< -o $(BUILD_DIR)/parallel_executor_demo.o

$(BUILD_DIR)/parallel_task_queue_demo.o : parallel_task_queue_demo.cpp parallel_task_queue_demo.h
	$(COMPILER) $(FLAGS) -c $< -o $(BUILD_DIR)/parallel_task_queue_demo.o

