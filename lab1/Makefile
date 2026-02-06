SRC_DIR = src
BUILD_DIR = build
TESTS_DIR = tests
MAIN_FILE = $(SRC_DIR)/lab1.cpp
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out $(MAIN_FILE),$(SOURCES)))

USER_INPUT = $(SRC_DIR)/data

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	@mkdir -p build
	g++ -g -c -o $@ $<

$(BUILD_DIR)/debug.out: $(MAIN_FILE) $(OBJECTS)
	g++ -g -o $@ $^

debug: $(BUILD_DIR)/debug.out
	gdb $<

$(BUILD_DIR)/leaks.out: $(MAIN_FILE) $(OBJECTS)
	g++ -fsanitize=address -o $@ $^

leaks: $(BUILD_DIR)/leaks.out
	cat $(USER_INPUT) | $<
