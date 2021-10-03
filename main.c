#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>
#include "include/process.h"

int main()
{
	int controlProcess = 0;
	int controlIO = 0;

	Processo* pid;

	char *result_archive;
	char str[100];

	//Input do arquivo no nomento da compilação
	while (fgets(str, 100, stdin)) {

		int lenString = 1;
		char** result = malloc(4 * sizeof(char**));

		//printf("valor str: %s", str);
		//char linha = gets("%s", *str);

		char linha[100];

		strcpy(linha, str);

		char *temp = strtok(linha, ";");


		if(temp != 0) {
			result[0] = temp;
		}

		while( (temp = strtok(0, ";")) != 0) {
			//result = realloc(result, (lenString + 1) * sizeof(char**));
			result[lenString++] = temp;
		}


		if(controlProcess == 0) {
		 	pid = malloc(sizeof(Processo) * (controlProcess + 1));
		} else {
			pid = realloc(pid, sizeof(Processo) * (controlProcess + 1));
		}


		pid[controlProcess].processNumber = atoi(result[0]);
		pid[controlProcess].duration = atoi(result[1]);
		pid[controlProcess].arrival = atoi(result[2]);

		if(result[3]!= 0) {
			strcpy(pid[controlProcess].textoIO ,result[3]);
		} else {
			strcpy(pid[controlProcess].textoIO ,""); 
		}
		

		controlProcess++;


		free(result);
		free(temp);
		
		

  	}



	//CORREÇÃO DO CAMPO IO
	for(int i=0; i< controlProcess;i++) {
		
		if(pid[i].textoIO != "")
		{	
			char *tempIO = strtok(pid[i].textoIO , ",");



			pid[i].io  = malloc(sizeof(char**));


			if(tempIO == 0 ) {
				pid[i].io[0] = 0;
				pid[i].qtdeIO = 0;
			} else {
				pid[i].io[0] = tempIO;
				pid[i].qtdeIO = 1;
			}

			while( (tempIO = strtok(0, ",")) != 0) {
				
				pid[i].io = realloc(pid[i].io, (pid[i].qtdeIO + 1) * sizeof(char**));
				pid[i].io[pid[i].qtdeIO] = tempIO;
				pid[i].qtdeIO++;
			}


			free(tempIO);
		}

	}
	

	//FIM DO CAMPO IO	

	for(int i=0; i< controlProcess;i++) {
		printf("Processo: %d\n", pid[i].processNumber);

		printf("Qtde IO: %d \n", pid[i].qtdeIO);

		for(int j=0; j< pid[i].qtdeIO; j++) {
			printf("IO: %s\n", pid[i].io[j]);
		}

	}


	//REALIZAR ALGORITMO ROUND ROBIN




	//FIM DO ALGORITMO

	free(pid);


	return 0;

}