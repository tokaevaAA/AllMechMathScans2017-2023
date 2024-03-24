opt=-o3
a.out: Algoritm.o metod_otraj.o
	g++ Algoritm.o metod_otraj.o

Algoritm.o: Algoritm.cpp Algoritm.h
	g++ -c Algoritm.cpp

metod_otraj.o: metod_otraj.cpp Algoritm.h
	g++ -c $(opt) metod_otraj.cpp

clean:
	rm -f metod_otraj.o Algoritm.o a.out
