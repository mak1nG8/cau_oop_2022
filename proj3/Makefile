a: main.o inf_int.o calculator.o
	g++ -std=c++14 -o a main.o inf_int.o calculator.o

main.o: inf_int.h calculator.h main.cpp
	g++ -std=c++14 -c -o main.o main.cpp

inf_int.o: inf_int.h inf_int.cpp
	g++ -std=c++14 -c -o inf_int.o inf_int.cpp

calculator.o: calculator.cpp calculator.h inf_int.h
	g++ -std=c++14 -c -o calculator.o calculator.cpp