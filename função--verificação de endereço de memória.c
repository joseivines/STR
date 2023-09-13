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
	
	printf("O Buffer tem10 posicoes\n\n\n");
	while(count<10)
	{
		printf("\nBuffer posicao %d, tem endereco %d\n", count +1, &Buffer[count]);
		count++;
	}
	

	return 0;
}


