all:main

main: main.o
	g++ main.o -o main -ggdb -g3

main.o: main.cpp
	g++ -c main.cpp -o main.o -ggdb -g3



.PHONY:
clean:
	rm main main.o