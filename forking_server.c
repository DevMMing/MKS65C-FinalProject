#include "networking.h"
//only works with one server and ctrl+c same terminal
void broadcast(char *msg);
void categorize();
const char* getfield(char* line, int num);
int randNum();
typedef struct {
	int fd;
	char name[BUFFER_SIZE];
	int points;
	char role[BUFFER_SIZE];
} client_t;
typedef struct{
	char name[BUFFER_SIZE];
	char roles[8][BUFFER_SIZE];
}location_t;
location_t *locations[28];
location_t *currLoc;
client_t *clients[MAX_CLIENTS];
int playerC=MAX_CLIENTS;
int taken[8];
int main() {
	for(int i=0;i<28;i++){
		locations[i]=(location_t *)calloc(1,sizeof(location_t));
	memset(locations[i]->name,0,BUFFER_SIZE);
	for(int j=0;j<8;j++){
		memset(locations[i]->roles[j],0,BUFFER_SIZE);
	}
}
	categorize();
	/*for(int i=0;i<28;i++){
		printf("----Start----\n");
		printf("Location : %s\n",locations[i]->name);
		for(int j=0;j<8;j++){
			printf("%s\n",locations[i]->roles[j]);
		}
		printf("----End----\n");
	}*/
	for(int i=0;i<MAX_CLIENTS;i++){
	clients[i]=(client_t *)calloc(1,sizeof(client_t));
	clients[i]->fd=0;
	memset(clients[i]->name,0,BUFFER_SIZE);
	clients[i]->points=0;
}
  int listen_socket;
  int numOfTurns=0;
  int active=0;
  char buffer[BUFFER_SIZE];
  listen_socket = server_setup();//first client sets up limit
  while(active<playerC){
	clients[active]->fd=server_connect(listen_socket);
	  strcpy(buffer,"Welcome to Spyfall\n");
	  strcat(buffer,"What is your name?");
      write(clients[active]->fd,buffer,sizeof(buffer));
	  memset(buffer,0,sizeof(buffer));
	  read(clients[active]->fd,buffer,sizeof(buffer));
	  printf("This is %s\n",buffer); 
	  strcpy(clients[active]->name,buffer);
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"%d",active);
		write(clients[active]->fd,buffer,sizeof(buffer));
		memset(buffer,0,sizeof(buffer));	  
	if(!active){//only for client one
		strcpy(buffer,"Number of players(3-8): ");
		write(clients[active]->fd,buffer,sizeof(buffer));
		memset(buffer,0,sizeof(buffer));
		read(clients[active]->fd,buffer,sizeof(buffer));
		playerC=atoi(buffer);
		memset(buffer,0,sizeof(buffer));
	  }
	  strcpy(buffer,"Awaiting connections...\n");
	  write(clients[active]->fd,buffer,sizeof(buffer));
	  memset(buffer,0,sizeof(buffer));
	  active++;
  }
  for(int i =0;i<playerC;i++){
  printf("Player %d: %s\n",i+1,clients[i]->name);
  }
  currLoc=locations[abs(randNum())%28];
  int spyEx=0;
 for(int i=0;i<playerC;i++){
	 int roleG;
	 if(spyEx){
	 roleG=abs(randNum())%(8-i);
	 }
	 else{
		 if(i!=playerC-1){
			if(abs(randNum())%2){
				roleG=abs(randNum())%(8-i);
			}
			else{
				roleG=0;
				spyEx=1;
			}
		 }
		 else{
			 roleG=0;
			 spyEx=1;
		 } 
	 }
	 for(int j=0;j<roleG;j++){
		 if(taken[roleG]){
		 roleG++;
		 }
	 }
	 taken[roleG]=1;
		 strcpy(clients[i]->role,currLoc->roles[roleG]);
		 snprintf(buffer,100,"Your role is %s\n",clients[i]->role);
		 printf("%s",buffer);
		write(clients[i]->fd,buffer,sizeof(buffer));
		memset(buffer,0,sizeof(buffer));
	 }
	 client_t *tempPlayer=(client_t *)calloc(1,sizeof(client_t));
	 client_t *currPlayer=clients[abs(randNum())%playerC];
  while (numOfTurns<20) {
    for(int i=0;i<playerC;i++){
		if(clients[i]->fd!=currPlayer->fd){
			snprintf(buffer,120,"Waiting for %s's turn to finish\n",currPlayer->name);
			write(clients[i]->fd,buffer,sizeof(buffer));
			memset(buffer,0,sizeof(buffer));
		}
	}
	sprintf(buffer,"What would you like to do? \n0.Question(.q) \t\t\t\t\t\t\t1.Accuse(.a)\n");
	write(currPlayer->fd,buffer,sizeof(buffer));
	memset(buffer,0,sizeof(buffer));
	read(currPlayer->fd,buffer,sizeof(buffer));
	printf("THING[%s]",buffer);
		if(!strncmp(buffer,".q",2)){
		memset(buffer,0,sizeof(buffer));
		/*strcpy(buffer,"Who would you like to question?\n");
		for(int j=0;j<playerC;j++){
			if(clients[j]->fd !=currPlayer->fd){
			char msg[BUFFER_SIZE];
			snprintf(msg,100,"%s\n",clients[j]->name);
			strcat(buffer,msg);
			}
		}
		write(currPlayer->fd,buffer,sizeof(buffer));
		memset(buffer,0,sizeof(buffer));
		read(currPlayer->fd,buffer,sizeof(buffer));//has to be player name
		for(int k=0;k<playerC;k++){
				if(!strcmp(clients[k]->name,buffer)){
					tempPlayer=clients[k];
				}
			}*/
		tempPlayer=clients[abs(randNum())%playerC];//random because parsing for name is broken
		memset(buffer,0,sizeof(buffer));
		strcpy(buffer,"What is your question?");
		write(currPlayer->fd,buffer,sizeof(buffer));
		memset(buffer,0,sizeof(buffer));
		read(currPlayer->fd,buffer,sizeof(buffer));
		strcat(buffer,"\nYour response:");
		write(tempPlayer->fd,buffer,sizeof(buffer));
		memset(buffer,0,sizeof(buffer));
		read(tempPlayer->fd,buffer,sizeof(buffer));
		write(currPlayer->fd,buffer,sizeof(buffer));
		currPlayer=tempPlayer;
		numOfTurns++;
		}
		else if(!strncmp(buffer,".a",2)){
			char accuse[120];
			memset(buffer,0,sizeof(buffer));
			strcpy(buffer,"Who do you think is a Spy?");
			write(currPlayer->fd,buffer,sizeof(buffer));
			memset(buffer,0,sizeof(buffer));
			read(currPlayer->fd,buffer,sizeof(buffer));
			strcpy(accuse,buffer);
			memset(buffer,0,sizeof(buffer));
			int yes_count=0;
			int no_count=0;
			for(int a=0;a<playerC;a++){
				sprintf(buffer,"Do you think %s, is the Spy?(y/n)",accuse);
				write(clients[a]->fd,buffer,sizeof(buffer));
				memset(buffer,0,sizeof(buffer));
				read(clients[a]->fd,buffer,sizeof(buffer));
				if(!strcmp(&buffer[0],"y")){
				yes_count++;
				}
				else if(!strcmp(&buffer[0],"n")){
				no_count++;
				}
				else{
					memset(buffer,0,sizeof(buffer));
					strcpy(buffer,"Invalid input. Vote has been terminated");
					write(clients[a]->fd, buffer,sizeof(buffer));
				}
			}
			if(yes_count >=no_count){
				printf("yes");
				exit(1);
			}
			else{
				printf("no");
				exit(1);
			}
		}
		else{
			memset(buffer,0,sizeof(buffer));
		stpcpy(buffer,"Invalid input, try again.\n");
		write(currPlayer->fd,buffer,sizeof(buffer));
		memset(buffer,0,sizeof(buffer));
		}
	}
	system("pause");
	return 0;
}

void broadcast(char * msg) {
	for(int i=0;i<playerC;i++){
		write(clients[i]->fd, msg, sizeof(msg));
	}
  }
 void categorize(){
	 int i=0;
	FILE* stream = fopen("location.csv", "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
		if(i){
			for(int j=1;j<9;j++){
				char* tmp = strdup(line);
				char* tmp2=strdup(line);
				char* tmp3=strdup(line);
				if(j==1){
					strcpy(locations[i-1]->name,getfield(tmp,j));
					strcpy(locations[i-1]->roles[j-1],"SPY");
				}
				else{
				strcpy(locations[i-1]->roles[j-1],getfield(tmp2, j));
				}
				//printf("Field %d would be %s\n", j,getfield(tmp3, j));
				// NOTE strtok clobbers tmp
				free(tmp);
			}
		}
		i++;
    }
 }
 const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
int randNum(){
  int c;
  int file = open("/dev/random",O_RDONLY);
  read(file,&c,sizeof(c));
  close(file);
  return c;
}