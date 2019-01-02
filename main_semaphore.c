#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

#define KEY 0xdeadbeef

int main(){
  //file stuffz
  int file = open("story.txt", O_RDWR | O_APPEND);
  char * lastline;
  char line[100];
  
  //shared memory stuffz
  key_t key = 12581;
  int shmid;
  //int * data
  char * data;
  
  shmid = shmget(key, 200, 0644 | IPC_CREAT | IPC_EXCL);
  data = shmat(shmid, (void *)0, 0);
  if(shmid == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    printf("last line : %s",data);
    printf("%s\n","enter next line");
    scanf("%[^\n]\n", line);
    //*data = sizeof(line);
    strcpy(data,line);
    if(write(file, line, sizeof(line)) < 0){
      exit(1);
    }
  }else{
    printf("%s\n","this is the first line");
    scanf("%[^\n]\n", line);
    //*data = sizeof(line);
    strcpy(data,line);
    if(write(file, line, sizeof(line)) < 0){
      exit(1);
    }
  }

  shmdt(data);//closes data
  close(file);//closes file
  return 0;
}
