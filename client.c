#include "networking.h"
static void sighandler(int signo){
  if (signo == SIGINT){
    printf("Game exited\n");
    exit(0);
  }
}

int main(int argc, char **argv) {
  int server_socket;
  char buffer[BUFFER_SIZE];
	//char *locations[27]={"Beach","Broadway Theater","Casino","Circus Tent","Bank","Day Spa","Hotel","Restaurant","Supermarket","Service Station","Hospital","Embassy","Military Base","Police Station","School","University","Airplane","Ocean Liner","Passenger Train","Submarine","Cathedral","Corporate Party","Movie Studio","Crusader Army","Pirate Ship","Polar Station","Space Station"};
 if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
system("clear");
//printf("Create Game(.create)\t\t\t\t\t\t\t\t\t\t");
//printf("Join Game(.join)\n");
  read(server_socket,buffer,sizeof(buffer));
  printf("%s",buffer);
  memset(buffer,0,BUFFER_SIZE);	  
  fgets(buffer,sizeof(buffer),stdin);
  *strchr(buffer, '\n') = 0;
  write(server_socket,buffer,sizeof(buffer));
  memset(buffer,0,BUFFER_SIZE);	  
  read(server_socket,buffer,sizeof(buffer));
  if(!atoi(buffer)){
	  read(server_socket,buffer,sizeof(buffer));
  printf("%s",buffer);
  memset(buffer,0,BUFFER_SIZE);	  
	  while((atoi(buffer)<3) || (atoi(buffer)>8)){
		  fgets(buffer,sizeof(buffer),stdin);
		  *strchr(buffer, '\n') = 0;
		  if((atoi(buffer)<3) || (atoi(buffer)>8)){
		  printf("Invalid input, try again.\n");}
		  else{
		  write(server_socket,buffer,sizeof(buffer));
		  }
		  
	  }
  }
  signal(SIGINT, sighandler);
  int token=read(server_socket,buffer,sizeof(buffer));
  printf("%s",buffer);
  memset(buffer,0,BUFFER_SIZE);
	while(token){
	printf("%s",buffer);
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
	memset(buffer,0,BUFFER_SIZE);
	token=read(server_socket,buffer,sizeof(buffer));
  }
  char * shtdwn = "Server has gone down. All users have been kicked";
   printf("\n\nWoops: %s\n", shtdwn);
}
