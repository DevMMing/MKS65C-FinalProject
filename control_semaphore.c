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

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};

int main(int argc, char *argv[]){
  if(argc == 2){

    //semaphore
    int sem;

    //Shared memory stuffz
    key_t key = 823;
    int shmid;
    char * data;

    //file
    FILE * file;
    
    if(!strcmp(argv[1],"-c")){
      
      //creates semaphore
      sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
      
      if(sem == -1){
	printf("error %d: %s\n", errno, strerror(errno));
      }else{
	
	//creates shared memory
	shmid = shmget(key, 200, IPC_CREAT | IPC_EXCL | 0644);
	data = shmat(shmid, (void *)0, 0);

	//creates file
	int naming_convention = open("story.txt", O_CREAT | IPC_EXCL, 0644);
	
      }
    }
    else if(!strcmp(argv[1],"-r")){
      sem = semget(KEY, 1, 0);
      if(sem == -1){
	printf("error %d: %s\n", errno, strerror(errno));
      }else{

	//removes the semaphore
	semctl(sem, IPC_RMID, 0);
	
	//removes shared memory
	shmid = shmget(key, 200, 0);
        shmctl(shmid, IPC_RMID, NULL);
	
	//removes file
	remove("story.txt");
	
      }
    }
    else if(!strcmp(argv[1],"-v")){
      sem = semget(KEY, 1, 0);
      if(sem == -1){
	printf("error %d: %s\n", errno, strerror(errno));
      }else{
	
        //views data in file
	char line[100];
        file = fopen("story.txt", "r");
	while(fgets(line, 100, file)){
	  printf("%s\n",line);
	}
        fclose(file);
      }
    }
  }
  return 0;
}
