leyso: compile

compile: 
	g++ -c main.cpp -std=c++11
	g++ -c cpuProgram.cpp -std=c++11
	g++ -c cpu.cpp -std=c++11
	g++ -o exe main.o cpu.o cpuProgram.o

run:
	./exe sqrsum.txt 0

clean:
	rm *.o exe
	clear

clear:
	clear
