#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define TRUE 1

#define NE 3 //numero de escritores
#define NL 10 //numero de leitores

pthread_mutex_t lock_bd = PTHREAD_MUTEX_INITIALIZER; //lock para controlar o acesso ao recurso compartilhado (banco de dados)
pthread_mutex_t lock_nl = PTHREAD_MUTEX_INITIALIZER; //

int num_leitores = 0;

void * reader(void *arg);
void * writer(void *arg);
void read_data_base(int i);
void use_data_read(int i);
void think_up_data(int i);
void write_data_base(int i);

int main() {

	pthread_t r[NL], w[NE];
	int i;
        int *id;
        /* criando leitores */
    	for (i = 0; i < NL ; i++) {
	   id = (int *) malloc(sizeof(int));
           *id = i;
		 pthread_create(&r[i], NULL, reader, (void *) (id));
	}
	 /* criando escritores */
	for (i = 0; i< NE; i++) {
	   id = (int *) malloc(sizeof(int));
           *id = i;
		 pthread_create(&w[i], NULL, writer, (void *) (id));
	}
	pthread_join(r[0],NULL);
	return 0;
}

void * reader(void *arg) {
	int i = *((int *) arg);
	while(TRUE) {
	
                 pthread_mutex_lock(&lock_nl); //crio um lock no numero de escritores para que eu não tenha duas thread atualizando o valor ao mesmo tempo
			 num_leitores++;
		         if(num_leitores == 1){ //primeiro leitor fecha o lock do recurso compartilhado (banco de dados) para impedir escritores
		             pthread_mutex_lock(&lock_bd);
		         }
                 pthread_mutex_unlock(&lock_nl);//unlock no numero de escritores após a atualização

                      read_data_base(i);       //acessa o recurso compartilhado
		 
                 pthread_mutex_lock(&lock_nl); //crio um lock no numero de escritores para que eu não tenha duas thread atualizando o valor ao mesmo tempo
		         num_leitores--;
		         if(num_leitores == 0){ //ultimo leitor abre o lock do recurso compartilhado (bando de dados) para permitir escritores
		             pthread_mutex_unlock(&lock_bd);
		         }
                 pthread_mutex_unlock(&lock_nl);
                 
                 use_data_read(i);        /* região não crítica */
	}
        pthread_exit(0);
}

void * writer(void *arg) {
	int i = *((int *) arg);
	while(TRUE) {               
		 think_up_data(i);        // penso no que escrever - região não crítica
		 
                 pthread_mutex_lock(&lock_bd); //bloqueio acesso ao recurso compartilhado (base de dados) por outros escritores - não tem nenhum impacto/sincronização nos leitores
                      write_data_base(i);      // escrevo na base de dados
	         pthread_mutex_unlock(&lock_bd); //desfaço o bloqueio do recurso compartilhado
        }
        pthread_exit(0);
}

void read_data_base(int i) {
	printf("Leitor %d está lendo os dados! Número de leitores: %d\n", i,num_leitores);
	sleep(rand() % 5);
}

void use_data_read(int i) {
	printf("Leitor %d está usando os dados lidos! Número de leitores: %d\n", i,num_leitores);
	sleep(rand() % 5);
}

void think_up_data(int i) {
	printf("Escritor %d está pensando no que escrever!\n", i);
	sleep(rand() % 5);
}

void write_data_base(int i) {
	printf("Escritor %d está escrevendo os dados! Número de leitores: %d\n", i,num_leitores);
	sleep( rand() % 5 + 15);
}
