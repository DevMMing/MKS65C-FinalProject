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
	read(clients[i],buf,sizeof(buf));
	memset(buf,0,BUFFER_SIZE);
	servers[i]=fork();
	if(!servers[i]){
		close(clients[i]);
		return 0;
	}
	i++;
}	
printf("Server is no longer accepting players.\n");
  // shutdown(listen_socket, SHUT_RD);
  for (int k =0; k < MAX_CLIENTS; k++) {
    snprintf(buf, sizeof(buf), "You are player %i!", k + 1); // show board, tell that you are player X or O, ask for input
    write(clients[k], buf, sizeof(buf));
  }
  while (1) {
		for(int j =0; j < MAX_CLIENTS; j++){
			read(clients[j],buf,sizeof(buf));
			write(clients[j],buf,sizeof(buf));
		}
	}
	return 0;
}