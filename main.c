#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>
#include "include/process.h"

int main()
{
	int i;
	char *str;
	char *temp;

	str = malloc(100 * sizeof(char));

	i = 1;
	while(fgets(str, 100, stdin)){
		temp = strtok(str, ";");

		printf("Linha %d\n", i);
		while(temp){
			printf("%s ", temp);
			temp = strtok(NULL, ";");
		}
		printf("\n");
		i++;
	}

	free(str);
	// int controlProcess = 0;
	// int controlIO = 0;

	// Processo* pid;

	// FILE *arq;
	// char Linha[100];
	// char *result_archive;

	// arq = fopen("input.txt", "rt");

	// if (arq == NULL)
	// {
	// 	printf("Problemas na abertura do arquivo\n");
	// 	return 1;
	// }

	// while (!feof(arq))
  // 	{

	// 	int lenString = 1;
	// 	result_archive = fgets(Linha, 100, arq); 
	// 	char** result = malloc(sizeof(char**));

	// 	char *temp = strtok(Linha, ";");

	// 	if(temp != 0) {
	// 		result[0] = temp;
	// 	}

	// 	while( (temp = strtok(0, ";")) != 0) {
	// 		result = realloc(result, (lenString + 1) * sizeof(char**));
	// 		result[lenString++] = temp;
	// 	}


	// 	if(controlProcess == 0) {
	// 	 	pid = malloc(sizeof(Processo) * (controlProcess + 1));
	// 	} else {
	// 		pid = realloc(pid, sizeof(Processo) * (controlProcess + 1));
	// 	}


	// 	pid[controlProcess].processNumber = atoi(result[0]);
	// 	pid[controlProcess].duration = atoi(result[1]);
	// 	pid[controlProcess].arrival = atoi(result[2]);
		
	// 	char *tempIO = strtok(result[3], ",");



	// 	pid[controlProcess].io  = malloc(sizeof(char**));


	// 	if(tempIO == 0 ) {
	// 		pid[controlProcess].io[0] = 0;
	// 		pid[controlProcess].qtdeIO = 0;
	// 	} else {
	// 		pid[controlProcess].io[0] = tempIO;
	// 		pid[controlProcess].qtdeIO = 1;
	// 	}

	// 	while( (tempIO = strtok(0, ",")) != 0) {
	// 		pid[controlProcess].io = realloc(pid[controlProcess].io, (pid[controlProcess].qtdeIO + 1) * sizeof(char**));
	// 		pid[controlProcess].io[pid[controlProcess].qtdeIO++] = tempIO;
	// 	}

	// 	controlProcess++;


	// 	free(result);
	// 	free(temp);

  // 	}


	// for(int i=0; i< controlProcess;i++) {
	// 	printf("%d\n", pid[i].io[0]);
	// }

	// //free(pid);

	// fclose(arq);

	return 0;

}