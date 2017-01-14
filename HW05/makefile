leyso: compile link

compile: 
	g++ -c _mainTest.cpp -std=c++11
	g++ -c CPUProgram.cpp -std=c++11
	g++ -c CPU.cpp -std=c++11
	g++ -c Memory.cpp -std=c++11
	g++ -c Computer.cpp -std=c++11

run:
	./exe sqrsum.txt 0

link:
	g++ -o exe _mainTest.o CPU.o CPUProgram.o Memory.o Computer.o
	
clean:
	rm *.o exe
	clear

clear:
	clear
