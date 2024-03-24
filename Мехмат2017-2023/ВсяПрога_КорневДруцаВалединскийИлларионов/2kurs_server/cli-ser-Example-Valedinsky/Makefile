CFLAGS = -W -Wall -Werror
CC = g++

all : tcp udp

tcp : cli_tcp ser_tcp

udp : cli_udp ser_udp

cli_tcp : cli_tcp.o
	$(CC) $(CFLAGS) cli_tcp.o -o cli_tcp

cli_tcp.o : cli_tcp.cpp
	$(CC) $(CFLAGS) -c cli_tcp.cpp -o cli_tcp.o

ser_tcp : ser_tcp.o
	$(CC) $(CFLAGS) ser_tcp.o -o ser_tcp

ser_tcp.o : ser_tcp.cpp
	$(CC) $(CFLAGS) -c ser_tcp.cpp -o ser_tcp.o

cli_udp : cli_udp.o
	$(CC) $(CFLAGS) cli_udp.o -o cli_udp

cli_udp.o : cli_udp.cpp
	$(CC) $(CFLAGS) -c cli_udp.cpp -o cli_udp.o

ser_udp : ser_udp.o
	$(CC) $(CFLAGS) ser_udp.o -o ser_udp

ser_udp.o : ser_udp.cpp
	$(CC) $(CFLAGS) -c ser_udp.cpp -o ser_udp.o



clean :
	rm *.o cli_tcp ser_tcp cli_udp ser_udp