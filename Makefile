.PHONY: clean run

all: run

run: compile
	./extract_tool

compile: src/*.c
	gcc src/*.c -Iinc -o extract_tool

test: unittest/*.c
	mkdir -p build
	gcc -Iinc -g -Og -o build/file_utils_test unittest/file_utils_test.c src/file_utils.c
	gcc -Iinc -g -Og -o build/str_utils_test unittest/str_utils_test.c src/str_utils.c
	./build/file_utils_test
	./build/str_utils_test

clean:
	rm -rf extract_tool
	rm -rf build
