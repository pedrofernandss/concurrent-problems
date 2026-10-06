#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MA 10 //macacos que andam de A para B
#define MB 10 //macacos que andam de B para A

int numAB = 0;
int numBA = 0;

pthread_mutex_t numMacacosAB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t numMacacosBA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockCorda = PTHREAD_MUTEX_INITIALIZER; //lock do recurso compartilhado

void * macacoAB(void * a) {
    int i = *((int *) a);

    while(1){
    
        pthread_mutex_lock(&numMacacosAB);
            numAB++;
            if(numAB == 1){
              pthread_mutex_lock(&lockCorda);
            };
        pthread_mutex_unlock(&numMacacosAB);
        
	printf("Macaco %d passado de A para B \n",i);
	sleep(1);
	
	pthread_mutex_lock(&numMacacosAB);
	    numAB--;
	    if(numAB == 0){
	      pthread_mutex_unlock(&lockCorda);
	    };
	pthread_mutex_unlock(&numMacacosAB);	    
    }
    pthread_exit(0);
}

void * macacoBA(void * a) {
    int i = *((int *) a);
    sleep(1);
    while(1){
        
        pthread_mutex_lock(&numMacacosBA);
          numBA++;
          if(numBA == 1){
            pthread_mutex_lock(&lockCorda);
          }
        pthread_mutex_unlock(&numMacacosBA);
      
	printf("Macaco %d passado de B para A \n",i);
	sleep(1);
	
	pthread_mutex_lock(&numMacacosBA);
	  numBA--;
	  if(numBA == 0){
	    pthread_mutex_unlock(&lockCorda);
	  }
	pthread_mutex_unlock(&numMacacosBA);
    }
    pthread_exit(0);
}

int main(int argc, char * argv[])
{
    pthread_t macacos[MA+MB];
    int *id;
    int i = 0;

    for(i = 0; i < MA+MB; i++){
        id = (int *) malloc(sizeof(int));
        *id = i;
        if(i%2 == 0){
          if(pthread_create(&macacos[i], NULL, &macacoAB, (void*)id)){
            printf("Não pode criar a thread %d\n", i);
            return -1;
          }
        }else{
          if(pthread_create(&macacos[i], NULL, &macacoBA, (void*)id)){
            printf("Não pode criar a thread %d\n", i);
            return -1;
          }
        }
    }

    //pthread_join(gorilas[0], NULL);
  
    pthread_join(macacos[0], NULL);
    return 0;
}
