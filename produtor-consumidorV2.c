/*
ALUNO:	JOSE IVINES MATOS SILVA
PROFESSOR: kYLER COSTA GORGONIO
DISCIPLINA: SISTEMAS EM TEMPO REAL
PERIODO: 2023.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TAM_BUFFER 10


//VARIÁVEIS GLOBAIS
int buffer[TAM_BUFFER];
int pocicao_inicio = 0; 
int posicao_fim = 0; 
int produto,count;//ITEM PRODUZIDO, CONTADOR.

sem_t sem_vazio; 
sem_t sem_cheio;

pthread_mutex_t mutex; // CRIANDO ACESSO A SEÇÃO CRITICA POR EXCLUSÃO MÚTUA- APENAS UMA THREAD OU PROCESSO TEM ACESSO POR VEZ

void *maquina_produtora(void *maq_produtora){
    while(1){
        produto = rand() % 100; //PRODUZ UM NÚMERO ALEATÓRIO ENTRE 0 E 99
        sem_wait(&sem_vazio); //O SEMAFORO EM ESPERA RECEBE UM ESPAÇO DE MEMÓRIA VAZIO(PARA DECREMENTAR ATÉ CHEGAR EM 0)
        pthread_mutex_lock(&mutex);
      
        buffer[pocicao_inicio] = produto;

        pocicao_inicio = (pocicao_inicio + 1) % TAM_BUFFER;// PULA PARA A PROXIMA POSIÇÃO [EX: (0 + 160)/10 =60 ] 
      
        printf("UMA  MAQUINA  PRODUZIU:  %d\n", produto);
        printf("(%d) posicoes do BFF consumidas \n", pocicao_inicio);
        printf("(%d) posicoes do BFF liberadas\n", posicao_fim);
      
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_cheio); //INCREMENTA O SEMAFORO,OUTRA THREAD/PROCESSO PODE ENTRAR EM WAIT(ESPERA) PARA REALIZAR O BLOQUEIO DO DO BUFFER(pthread_mutex_lock)
    }
		    pthread_exit(NULL);//THREAD É FINALIZADA
}


void *maquina_consumidora(void *maq_consumidora) {

    while(1){
        sem_wait(&sem_cheio); //ESPERA SER PRODUZIDO PARA PODER CONSUMIR((TEM UM ITEM NO BUFFER? SIM(LIBERA ACESSO), NÃO(ESPERA)
        pthread_mutex_lock(&mutex); //BLOQUEIA O ACESSO AO BUFFER
        produto = buffer[posicao_fim];// O PROCCESSO É RETIRAR OS ITENS QUE FORAM CIRADOS PRIMEIRO
        posicao_fim = (posicao_fim + 1) % TAM_BUFFER;//INCREMENTA A POSIÇÃO

        printf("UMA  MAQUINA  CONCLUIO  O  PRODUTO:  (%d)\n", produto);
        printf("(%d) posicoes do BFF consumidas \n", pocicao_inicio);
        printf("(%d) posicoes do BFF liberadas\n", posicao_fim);
        pthread_mutex_unlock(&mutex); //LIBERAR O ACESSO AO BUFFER
        sem_post(&sem_vazio); // SEMAFORO É INCREMENTADO PARA LIBERAR O PROXIMO PROCESSO,
        sleep(1); 
    }
   pthread_exit(NULL);//THREAD É F /INALIZADA
}

int main() {
	int i;
  //declarando var do tipo pthread
  pthread_t produzir;
  pthread_t comsumir;

  sem_init(&sem_vazio, 0, TAM_BUFFER);//INICIALIZA UM SEMAFORO PARA INDICAR QUANTO HÁ ESPAÇOS VAZIOS NO BUFFER(INICIALMENTE TODOS ESTÃO VAZIOS)
  sem_init(&sem_cheio, 0, 0);//INICIALIZA OUTRO SEMAFORO PARA INDICAR QUANDO O BUFFER ESTRÁ CHEIO(INICIALMENTE TEM ZERO ESPAÇOES CHEIOS)
  pthread_mutex_init(&mutex, NULL);//BLOQUEIA ACESSO A SEÇÃO CRÍTICA
  
	pthread_create(&produzir, NULL, maquina_produtora,NULL);
	
	pthread_create(&comsumir, NULL, maquina_consumidora,NULL);
	  
	pthread_join(produzir, NULL);
	
	pthread_join(comsumir, NULL);

	
//DESTROID SEMAFOROS
    sem_destroy(&sem_vazio);
    sem_destroy(&sem_cheio);
    pthread_mutex_destroy(&mutex);

    return 0;
}