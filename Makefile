main: main.o sparse_matrix_exceptions.o test_class.o
	g++ main.o sparse_matrix_exceptions.o test_class.o -o main -ggdb -g3

main.o: main.cpp
	g++ -c main.cpp -o main.o -ggdb -g3

test_class.o: test_class.cpp
	g++ -c test_class.cpp -o test_class.o

sparse_matrix_exceptions.o: sparse_matrix_exceptions.cpp
	g++ -c sparse_matrix_exceptions.cpp -o sparse_matrix_exceptions.o -ggdb -g3


.PHONY:
clean:
	rm main *.o