#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/shm.h>

#define KEY 0xdeadbeef

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};

int main(int argc, char *argv[]){
  if(argc == 2){
    int sem;
    if(!strcmp(argv[1],"-c")){
      sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
      if(sem == -1){
	printf("error %d: %s\n", errno, strerror(errno));
	//sem = semget(KEY, 1, 0);
	//int v = semctl(sem, 0, GETVAL, 0);
	//printf("semctl returned: %d\n", v);
      }else{
	//union semun un;
	//un.val = 1;
	//int r = semctl(sem, 0, SETVAL, un);
	//printf("semctl returned: %d\n", r);

	
	//down
	struct sembuf buf;
	buf.sem_num = 1;
	buf.sem_flg = SEM_UNDO;
	buf.sem_op = -1;
        if(semop(sem,&buf,1) == -1){
	  printf("error %d: %s\n", errno, strerror(errno));
	}

	
	//shared memory stuffz
	key_t key = 823;
	int shmid;
	char * data;
	shmid = shmget(key, 200, 0644 | IPC_CREAT);
	data = shmat(shmid, (void *)0, 0);

	
	//Enter line
	printf("%s\n","Enter the line you want to enter");
	char line[100];
        scanf("%[^\n]", line);
	strcpy(data, line);
	shmdt(data);

	
	//up
	buf.sem_op = 1;
	semop(sem,&buf,1);

	
      }
    }
    else if(!strcmp(argv[1],"-r")){
      sem = semget(KEY, 1, 0);
      if(sem == -1){
	printf("error %d: %s\n", errno, strerror(errno));
	//sem = semget(KEY, 1, 0);
	//int v = semctl(sem, 0, GETVAL, 0);
	//printf("semctl returned: %d\n", v);
      }else{

	
	//down
	struct sembuf buf;
	buf.sem_num = 1;
	buf.sem_flg = SEM_UNDO;
	buf.sem_op = -1;
        if(semop(sem,&buf,1) == -1){
	  printf("error %d: %s\n", errno, strerror(errno));
	}

	
	//shared memory stuffz
	key_t key = 823;
	int shmid;
	char * data;
	shmid = shmget(key, 200, 0);
	data = shmat(shmid, (void *)0, 0);

	
	//Removes data
        shmctl(shmid, IPC_RMID, NULL);
	shmdt(data);

	
	//Removes the semaphore
	semctl(sem, IPC_RMID, 0);

	
	//up
	buf.sem_op = 1;
	semop(sem,&buf,1);

	
      }
    }
    else if(!strcmp(argv[1],"-v")){
      sem = semget(KEY, 1, 0);
      if(sem == -1){
	printf("error %d: %s\n", errno, strerror(errno));
	//sem = semget(KEY, 1, 0);
	//int v = semctl(sem, 0, GETVAL, 0);
	//printf("semctl returned: %d\n", v);
      }else{

	
	//down
	struct sembuf buf;
	buf.sem_num = 1;
	buf.sem_flg = SEM_UNDO;
	buf.sem_op = -1;
        if(semop(sem,&buf,1) == -1){
	  printf("error %d: %s\n", errno, strerror(errno));
	}

	
	//shared memory stuffz
	key_t key = 823;
	int shmid;
	char * data;
	shmid = shmget(key, 200, 0);
	data = shmat(shmid, (void *)0, 0);

	
	//Views data
	if(data){
	  printf("data : %s\n",data);
	}else{
	  printf("No data stored");
	}
	shmdt(data);

	
	//up
	buf.sem_op = 1;
	semop(sem,&buf,1);

	
      }
    }
  }
  return 0;
}
