main: main.o sparse_matrix_exceptions.o test_class.o
	g++ main.o sparse_matrix_exceptions.o test_class.o -o main

main.o: main.cpp SparseMatrix.h
	g++ -c main.cpp -o main.o

test_class.o: test_class.cpp
	g++ -c test_class.cpp -o test_class.o

sparse_matrix_exceptions.o: sparse_matrix_exceptions.cpp
	g++ -c sparse_matrix_exceptions.cpp -o sparse_matrix_exceptions.o


.PHONY:
clean:
	rm main *.o