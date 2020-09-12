all: QuadraticEquationSolver

QuadraticEquationSolver: src/main.o src/QuadEq.o src/TestEq.o
	g++ src/main.o src/QuadEq.o src/TestEq.o -o QuadraticEquationSolver

main.o: src/main.cpp
	g++ -c src/main.cpp

QuadEq.o: src/QuadEq.cpp
	g++ -c src/QuadEq.cpp

TestEq.o: src/TestEq.cpp
	g++ -c src/TestEq.cpp

clean:
	rm src/*.o

clean_exe:
	rm QuadraticEquationSolver
