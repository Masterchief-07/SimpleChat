cc = clang++
inc = include/
src = src/
test = test/
params = -Wall -Werror -Wpedantic -pthreads -std=c++17 -I$(inc) -lncurses

all: main test

main: main.cpp $(src)window.cpp
	$(cc) $(params) $^ -o $@

test: $(test)testserver $(test)testclient $(test)testwindow

$(test)testwindow: $(test)testwindow.cpp $(src)window.cpp 
	$(cc) $(params) $^ -o $@
$(test)testclient: $(test)testclient.cpp $(src)window.cpp 
	$(cc) $(params) $^ -o $@
$(test)testserver: $(test)testserver.cpp $(src)window.cpp 
	$(cc) $(params) $^ -o $@

clean:
	rm -rf main  $(test)testserver $(test)testclient $(test)testwindow
