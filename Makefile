all:main

main: main.o matrix_bounds_exception.o test_class.o
	g++ main.o matrix_bounds_exception.o test_class.o -o main -ggdb -g3

main.o: main.cpp
	g++ -c main.cpp -o main.o -ggdb -g3

test_class.o: test_class.cpp
	g++ -c test_class.cpp -o test_class.o

matrix_bounds_exception.o: matrix_bounds_exception.cpp
	g++ -c matrix_bounds_exception.cpp -o matrix_bounds_exception.o -ggdb -g3

.PHONY:
clean:
	rm main main.o