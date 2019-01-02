#include "pipe_networking.h"
#include <signal.h>
static void sighandler(int sig){

  if (sig == SIGINT){
    exit(0);
  }
if (sig == SIGUSR1)
    {
        printf("Received SIGUSR1!\n");
		printf("Parent Process: %d\n",getppid());
}

}
int main() {

  signal(SIGINT,sighandler);
  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  char * input = malloc(BUFFER_SIZE);
  char * output = malloc(BUFFER_SIZE);
  while(1){
    printf("My input to server: ");
    fgets(input,BUFFER_SIZE,stdin);
    strtok(input,"\n");
    write(to_server, input, BUFFER_SIZE);
    read(from_server, output, BUFFER_SIZE);
    printf("The server returns: %s\n\n", output);
  }
 return 0;
}
