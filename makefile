forking: client fserver

fserver: forking_server.o networking.o
	gcc -g -o server forking_server.o networking.o

client: client.o networking.o
	gcc -g -o client client.o networking.o

client.o: client.c networking.h
	gcc -g -c client.c

forking_server.o: forking_server.c networking.h
	gcc -g -c forking_server.c

networking.o: networking.c networking.h
	gcc -g -c networking.c

clean:
	rm *.o
	rm *~
