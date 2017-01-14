leyso: compile link

compile: 
	g++ -c _mainTester.cpp -std=c++11
	g++ -c Exceptions.cpp -std=c++11

run:
	./exe badname.txt 1 2

link:
	g++ -o exe _mainTester.o Exceptions.o
	
clean:
	rm *.o exe
	clear

clear:
	clear
	
