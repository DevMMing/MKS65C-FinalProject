#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main() {
  int clients[MAX_CLIENTS],servers[MAX_CLIENTS];
  int listen_socket;
  int f;
  listen_socket = server_setup();
  char buf[BUFFER_SIZE];
 memset(buf,0,BUFFER_SIZE);
int i=0;
while(i <MAX_CLIENTS){
	clients[i]=server_connect(listen_socket);
	memset(buf,0,BUFFER_SIZE);
	servers[i]=fork();
	if(!servers[i]){
		subserver(clients[i]);
		close(clients[i]);
		return 0;
	}
	else{
		close(clients[i]);
	}
	i++;
}
printf("Server is no longer accepting players.\n");
  // shutdown(listen_socket, SHUT_RD);
  for (int i =0; i < MAX_CLIENTS; i++) {
    snprintf(buf, sizeof(buf), "You are player %i!", i + 1); // show board, tell that you are player X or O, ask for input
    write(clients[i], buf, sizeof(buf));
  }
  while (1) {
		for(int i =0; i < MAX_CLIENTS; i++){
			//printf("%i",clients[i]);
			read(clients[i],buf,sizeof(buf));
			write(clients[i],buf,sizeof(buf));
		}
	}
	return 0;
}
void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}