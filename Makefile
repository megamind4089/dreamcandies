.PHONY: clean run test

CFLAGS += -Wno-multichar
CFLAGS += -g -Og	# GDB symbols

all: run

run: compile
	./extract_tool

compile: src/*.c
	gcc src/*.c -Iinc $(CFLAGS) -o extract_tool

test: unittest/*.c
	mkdir -p build
	gcc -Iinc $(CFLAGS) -o build/file_utils_test unittest/file_utils_test.c src/file_utils.c src/buffer.c
	gcc -Iinc $(CFLAGS) -o build/str_utils_test unittest/str_utils_test.c src/str_utils.c src/buffer.c
	./build/file_utils_test
	./build/str_utils_test

clean:
	rm -rf extract_tool
	rm -rf build
