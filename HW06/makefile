leyso: compile link clear run

compile: 
	g++ -c _mainTest.cpp -std=c++11
	g++ -c CPUProgramDyn.cpp -std=c++11

run:
	./exe deneme.txt 0

link:
	g++ -o exe _mainTest.o CPUProgramDyn.o
	
clean:
	rm *.o exe
	clear

clear:
	clear
