build:
	cmake -B build
	cmake --build build

format:
	cmake --build build --target format

tidy:
	cmake --build build --target tidy

test:
	cd build && ctest --output-on-failure

install:
	sudo cmake --build build --target install

clean:
	rm -rf build
