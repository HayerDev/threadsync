#compiler and flags
CC = gcc
CFLAGS = -Wall -g -pthread

#dir
SRC_DIR = src
TEST_DIR = test
INCLUDE_DIR = include
BIN_DIR = bin

#source and object
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_LIST_FILES = $(TEST_DIR)/testlist.c
MONITOR_TEST_FILES = $(TEST_DIR)/monitortest.c
OBJ_FILES = $(filter-out $(SRC_DIR)/main.o, $(SRC_FILES:.c=.o))

#exc
MAIN_EXEC = $(BIN_DIR)/main
TEST_LIST_EXEC = $(BIN_DIR)/testlist
MONITOR_TEST_EXEC = $(BIN_DIR)/monitortest

# default target
all: $(MAIN_EXEC)

# main application
$(MAIN_EXEC): $(filter-out $(TEST_DIR)/%, $(OBJ_FILES))
	$(CC) $(CFLAGS) $^ -o $@

# test list
$(TEST_LIST_EXEC): $(OBJ_FILES) $(TEST_LIST_FILES:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

# monitor test
$(MONITOR_TEST_EXEC): $(OBJ_FILES) $(MONITOR_TEST_FILES:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

# generic rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

#clean
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(BIN_DIR)/*

#run tests
test: $(TEST_LIST_EXEC)
	./$(TEST_LIST_EXEC)

test_monitor: $(MONITOR_TEST_EXEC)
	./$(MONITOR_TEST_EXEC)

.PHONY: all clean test test_monitor
