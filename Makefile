clean:
	rm *.out

test:
	g++ *.cpp -g -Wall -o testmain.out
	./testmain.out
debug:
	g++ *.cpp -g -Wall -o testmain.out
	gdb testmain.out
memtest:
	g++ *.cpp -g -Wall -o testmain.out
	valgrind --leak-check=full  ./testmain.out




