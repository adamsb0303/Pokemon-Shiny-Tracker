CXXFLAGS=-std=c++11 -Wpedantic -Wall -Wextra -Werror -Weffc++ -Wzero-as-null-pointer-constant

all: pst
pst: *.cpp
	g++ $(CXXFLAGS) *.cpp -o pst
check: pst
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes ./pst
clean:
	/bin/rm pst
