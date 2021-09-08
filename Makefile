main: main.o
	gcc main.o -o main -lstdc++
main.o: main.cpp
	gcc -c main.cpp
clean:
	rm -f main main.o