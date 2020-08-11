.PHONY: clean run

all: src/*.c
	gcc src/*.c -o extract_tool

run:
	./extract_tool

clean:
	rm -rf extract_tool
