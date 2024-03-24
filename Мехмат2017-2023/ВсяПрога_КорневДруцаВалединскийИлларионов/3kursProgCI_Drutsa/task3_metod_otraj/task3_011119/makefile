opt=-O3
a.out:  Algoritm.o metod_otraj.o 
	g++ $(opt) Algoritm.o metod_otraj.o -o a.out

Algoritm.o: Algoritm.cpp Algoritm.h
	g++ -c $(opt) Algoritm.cpp -o Algoritm.o

metod_otraj.o: metod_otraj.cpp Algoritm.h
	g++ -c $(opt) metod_otraj.cpp -o metod_otraj.o

clean:
	rm -f metod_otraj.o Algoritm.o a.out
