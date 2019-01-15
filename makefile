forking: client fserver

select: sclient sserver

sserver: select_server.o networking.o
	gcc -g -o server select_server.o networking.o

fserver: forking_server.o networking.o
	gcc -g -o server forking_server.o networking.o

sclient: select_client.o networking.o
	gcc -g -o client select_client.o networking.o

client: client.o networking.o
	gcc -g -o client client.o networking.o

select_client.o: select_client.c networking.h
	gcc -g -c select_client.c

client.o: client.c networking.h
	gcc -g -c client.c

select_server.o: select_server.c networking.h
	gcc -g -c select_server.c

forking_server.o: forking_server.c networking.h
	gcc -g -c forking_server.c

networking.o: networking.c networking.h
	gcc -g -c networking.c

clean:
	rm *.o
	rm *~
