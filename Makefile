BUILD_DIR=cmake-build-debug
BIN_DIR=bin

default: 
	cmake -H./ -B./$(BUILD_DIR)
	cmake --build ./$(BUILD_DIR) --target all -- -j8

all: clean default

clean: 
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*
