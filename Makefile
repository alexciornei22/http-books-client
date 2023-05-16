CXX := g++
CXXFLAGS := -Wall
RM := rm -f

OBJ_DIR := ./build
SRC_DIR := ./src

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXEC := client

build: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(EXEC)

.PHONY: clean
clean:
	$(RM) $(EXEC) $(OBJS)