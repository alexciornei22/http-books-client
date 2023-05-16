OBJ_DIR := ./build
INC_DIR := ./include
SRC_DIR := ./src

CXX := g++
CXXFLAGS := -Wall -I$(INC_DIR)
RM := rm -f

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
DEPS := $(wildcard $(INC_DIR)/*.hpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXEC := client

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(EXEC)

.PHONY: clean
clean:
	$(RM) $(EXEC) $(OBJ_DIR)/*