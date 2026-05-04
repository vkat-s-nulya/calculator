include .env
export

build:
	cmake -B build
	cmake --build build

format:
	cmake --build build --target format

tidy:
	cmake --build build --target tidy

test:
	cd build && ctest --output-on-failure

test-valgrind:
	cd build && ctest -T memcheck --output-on-failure

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 \
		./build/calculator '{"a": 10, "b": 3, "op": "add"}'

perf:
	perf record -g --call-graph dwarf -F 999 -o perf.data \
		./build/calculator '{"a": 10, "b": 3, "op": "add"}'
	perf report -i perf.data --stdio --no-children --percent-limit 1 | head -80

install:
	sudo cmake --build build --target install

clean:
	rm -rf build
