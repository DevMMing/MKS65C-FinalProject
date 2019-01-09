#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
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
    rpg()
  }
  else if (choice==2){
    puzzle();
  }
  else if (choice==3){
    chat();
  }
}
void rpg(){
}
void puzzle(){
}
void chat(){
}
/*Possible return soon after I finish kivy
int behavior(unit character){
  if 
}
int attk(unit attker,unit dfnder){
  
}*/
int main (){
  printf("Choose a game");
  printf(">>1.RPG");
  printf(">>2.Puzzle");
  printf(">>3.Chat");
  scanf(%d,choice);
  if(choice<4 && choice >0){
    game(choice);
  }
}
