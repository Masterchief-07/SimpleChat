cc = clang++
inc = include/
src = src/
build = build/
params = -Wall -Werror -Wpedantic -pthreads -std=c++17 -I$(inc)

all: main

main: window.o
	$(cc) $(params) $^ -o $@

window.o: $(src)window.cpp
	$(cc) $(params) -lncurses -c $^

