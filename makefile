cc = clang++
inc = include/
src = src/
test = test/
params = -Wall -Werror -Wpedantic -pthreads -std=c++17 -I$(inc) -lncurses

all: main

main: main.cpp $(src)window.cpp
	$(cc) $(params) $^ -o $@

clean:
	rm -rf main  
