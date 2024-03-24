opt=-O3
a.out:  matrices.o Algoritm.o synchronize.o get_time.o  main.o 
	g++ $(opt) matrices.o Algoritm.o synchronize.o get_time.o  main.o -o a.out -lpthread

matrices.o: matrices.cpp matrices.h
	g++ -c $(opt) matrices.cpp -o matrices.o -lpthread

Algoritm.o: Algoritm.cpp Algoritm.h
	g++ -c $(opt) Algoritm.cpp -o Algoritm.o -lpthread

synchronize.o: synchronize.cpp synchronize.h
	g++ -c $(opt) synchronize.cpp -o synchronize.o -lpthread

get_time.o: get_time.cpp get_time.h
	g++ -c $(opt) get_time.cpp -o get_time.o -lpthread


main.o: main.cpp
	g++ -c $(opt) main.cpp -o main.o -lpthread


clean:
	rm -f main.o Algoritm.o  matrices.o synchronize.o get_time.o  a.out
