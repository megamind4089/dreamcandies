.PHONY: clean run test

CFLAGS += -Wno-multichar
CFLAGS += -g -Og	# GDB symbols

all: compile

run: compile
	@rm -rf output
	@mkdir -p output
	@./extract_sample

compile: src/*.c
	@gcc src/*.c -Iinc $(CFLAGS) -o extract_sample

test: unittest/*.c
	@mkdir -p build
	@gcc -Iinc $(CFLAGS) -o build/file_utils_test unittest/file_utils_test.c src/file_utils.c src/buffer.c
	@gcc -Iinc $(CFLAGS) -o build/str_utils_test unittest/str_utils_test.c src/str_utils.c src/buffer.c
	@./build/file_utils_test
	@./build/str_utils_test

clean:
	@rm -rf extract_sample
	@rm -rf build
	@rm -rf output/*
