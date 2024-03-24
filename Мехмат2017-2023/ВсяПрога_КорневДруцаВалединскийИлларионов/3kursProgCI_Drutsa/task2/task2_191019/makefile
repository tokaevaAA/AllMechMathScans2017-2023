opt=-O3
a.out:  Algoritm.o sobstv_znachenia.o 
	g++ $(opt) Algoritm.o sobstv_znachenia.o -o a.out

Algoritm.o: Algoritm.cpp Algoritm.h
	g++ -c $(opt) Algoritm.cpp -o Algoritm.o

sobstv_znachenia.o: sobstv_znachenia.cpp Algoritm.h
	g++ -c $(opt) sobstv_znachenia.cpp -o sobstv_znachenia.o

clean:
	rm -f sobstv_znachenia.o Algoritm.o a.out
