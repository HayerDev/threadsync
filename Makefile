#compiler and flags
CC = gcc
CFLAGS = -Wall -g

#dir
SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include
BIN_DIR = bin

#source and object
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o) $(TEST_FILES:.c=.o)

#exc
MAIN_EXEC = $(BIN_DIR)/main
TEST_LIST_EXEC = $(BIN_DIR)/testlist

all: $(MAIN_EXEC)

$(MAIN_EXEC): $(filter-out $(TEST_DIR)/%, $(OBJ_FILES))
	$(CC) $(CFLAGS) $^ -o $@

# test list
$(TEST_LIST_EXEC): $(filter-out $(SRC_DIR)/main.o, $(OBJ_FILES))
	$(CC) $(CFLAGS) $^ -o $@

# generic rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

#clean
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(BIN_DIR)/*

#run test
test: $(TEST_LIST_EXEC)
	./$(TEST_LIST_EXEC)

.PHONY: all clean test
