/*
ALUNO:	JOSE IVINES MATOS SILVA
PROFESSOR: kYLER COSTA GORGONIO
DISCIPLINA: SISTEMAS EM TEMPO REAL
PERIODO: 2023.1
*/

//função-> verificação de endereço de memória

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 10 // Tamanho do buffer

int main()
{
	int Buffer[TAM_BUFFER]; //buffer de tamalho 10 inicialmente vazio ou com lixo
	int count = 0;//contador
	int produto;
	int i;

	while(count<10)
	{
		i=rand();
		produto = i%100;//testar 10//100//1000
		printf("\nO resto da divisao de %d dividido por 100 e: %d \n", i,produto);
		count++;
	}
	

	return 0;
}


