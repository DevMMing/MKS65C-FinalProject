#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include "networking.h"
#define playerCount 2
typedef struct {// stats
  int attk;
  int dfns;
  int intll;
  int dxt;
  int hp;
  char * name;
  char * type;
}unit;
int game(int choice){
  if (choice==1){
    rpg();
  }
  else if (choice==2){
    puzzle();
  }
  else if (choice==3){
    chat();
  }
  else if(choice==4){
    printf("Currently coding is unavailable in this version. Try again later.");
  }
}
void rpg(client clientfd_1,client clientfd_2){//two clients must be on rpg
  printf("Welcome to Text");
  if(num_of_clients<2){
    printf("Waiting for Another Client....");
  }
  else if (num_of_clients==2){
    printf("Game started!");
    printf("Loading Game Assets...");
    thisisnotagame(clientfd_1,clientfd_2);
  }
  else{
    printf("Sorry, the game you tried to join is currently unavailable. Please try later.");
  }
}
void thisisnotagame(client clientfd_1,client clientfd_2){
      strcpy(clientfd_1->role,"Hero");
      strcpy(clientfd_2->role,"Villain");
      server_broadcast(clientfd_1,"You are the Hero");
      server_broadcast(clientfd_2,"You are the Villain");
      while(strcmp(clientfd_1,"dead")||strcmp(clientfd_2,"dead")){
        //stuff happens
      }
}
void puzzle(){//puzzle per client
  printf("Welcome to Puzzle");
  //load puzzle array
}
void chat(){//all clients
  printf("Welcome to chat");
  scanf(%s,str);
  server_broadcast(str,clientfd);
}
/*Possible return soon after I finish kivy(Soon tm....)
int behavior(unit character){
  if
}
int attk(unit attker,unit dfnder){

}*/
int main (){
  printf("Welcome to the Lobby");
  printf("Choose an option");
  printf(">>1.RPG");
  printf(">>2.Puzzle");
  printf(">>3.Chat");
  printf(">>4.Code");
  scanf(%d,choice);
  if(choice<5 && choice >0){
    game(choice);
  }
}
