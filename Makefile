# ============ PROJECT CONFIG ============ #
PROJECT     := pthreadpool
TARGET      := bin/test_$(PROJECT)

# ============ COMPILER CONFIG ============ #
CC          := gcc
CFLAGS      := -std=c11 -pthread -Wall -Wextra -Werror
INCLUDES    := -Iincludes -I/usr/local/include
LDFLAGS     := -L/usr/local/lib64 -lcmocka -Wl,-rpath=/usr/local/lib64 -pthread

# ============ DIRECTORY STRUCTURE ============ #
SRC_DIR     := src
OBJ_DIR     := obj
BIN_DIR     := bin
TEST_DIR    := test

# ============ FILE DISCOVERY ============ #
SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TEST_SRC    := $(TEST_DIR)/test_$(PROJECT).c
TEST_OBJ    := $(OBJ_DIR)/test_$(PROJECT).o

# ============ BUILD RULES ============ #
.PHONY: all clean test

all: $(TARGET)

# Link final executable
$(TARGET): $(OBJS) $(TEST_OBJ) | $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@
	@echo "Successfully built $@"

# Compile main source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile test file
$(TEST_OBJ): $(TEST_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories if needed
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Run tests
test: $(TARGET)
	@echo "\n=== RUNNING TESTS ==="
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

# Debug build (adds -g flag)
debug: CFLAGS += -g
debug: clean all