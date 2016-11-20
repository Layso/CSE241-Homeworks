all: compile

run:
	./exe test.txt 1

compile: compile.c
	g++ main.o -o exe

compile.c: 
	g++ -c main.cpp

clean: 
	rm *.o exe tmp.txt
	clear
