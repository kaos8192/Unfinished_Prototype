all: test create

test: gates.u gates.cpp
	uncic gates.u
	g++ --std=c++17 -g -Wall -Wfatal-errors -Wno-sign-compare gates.o gates.cpp -o test -lcppunit

create: gates.cpp test.cpp
	g++ --std=c++17 -g -Wall -Wfatal-errors -Wno-sign-compare gates.cpp test.cpp -o create

.phony: create clean dist

run_tests: test
	clear
	./test

run_create: create
	clear
	./create

clean: test create
	rm -f test
	rm -f create
