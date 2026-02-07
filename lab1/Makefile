SRC_DIR = src
BUILD_DIR = build
TESTS_DIR = tests

MAIN_FILE = $(SRC_DIR)/lab1.cpp
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out $(MAIN_FILE),$(SOURCES)))
DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%_DEBUG.o, $(filter-out $(MAIN_FILE),$(SOURCES)))

USER_INPUT = $(SRC_DIR)/data
TEST_SOURCES = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_TARGETS = $(patsubst $(TESTS_DIR)/%.cpp,$(BUILD_DIR)/%.out,$(TEST_SOURCES))

# правило для сборки объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	@mkdir -p build
	g++ -DNDEBUG -c -o $@ $<

# debug
$(BUILD_DIR)/%_DEBUG.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	@mkdir -p build
	g++ -g -c -o $@ $<

$(BUILD_DIR)/debug.out: $(MAIN_FILE) $(DEBUG_OBJECTS)
	g++ -g -o $@ $^

debug: $(BUILD_DIR)/debug.out
	gdb $<

# leaks
$(BUILD_DIR)/leaks.out: $(MAIN_FILE) $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	g++ -fsanitize=address -o $@ $^

leaks: $(BUILD_DIR)/leaks.out
	cat $(USER_INPUT) | $<

# tests
$(BUILD_DIR)/test_%.out: $(TESTS_DIR)/test_%.cpp $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	@g++ -g -o $@ $^

test_rect_basic_methods: $(BUILD_DIR)/test_rect_basic_methods.out
	@echo "Запуск теста простых методов..."
	@./$< && echo "Тест пройден\n" || (echo "Тест не пройден\n" && exit 1)
	
test_rect_properties: $(BUILD_DIR)/test_rect_properties.out
	@echo "Запуск теста геттеров и сеттеров..."
	@./$< && echo "Тест пройден\n" || (echo "Тест не пройден\n" && exit 1)

test_rect_operations: $(BUILD_DIR)/test_rect_operations.out
	@echo "Запуск теста других функций..."
	@./$< && echo "Тест пройден\n" || (echo "Тест не пройден\n" && exit 1)

test_bounding_rect: $(BUILD_DIR)/test_bounding_rect.out
	@echo "Запуск теста bounding_rect..."
	@./$< && echo "Тест пройден\n" || (echo "Тест не пройден\n" && exit 1)

test: test_rect_basic_methods test_rect_operations test_bounding_rect test_rect_properties
	@echo "Все тесты успешно пройдены!"


# launch
$(BUILD_DIR)/launch.out: $(MAIN_FILE) $(DEBUG_OBJECTS)
	g++ -g -o $@ $^

launch: $(BUILD_DIR)/launch.out
	./$<

# чистка
clean:
	rm -rf $(BUILD_DIR)