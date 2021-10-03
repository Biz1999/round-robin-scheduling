#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>
#include "../include/process.h"
#include "../include/roundrobin.h"

#define push(qtdNaFila, fila, processo) ((fila[qtdNaFila]) = (processo))

void pop (int qtdNaFila, Processo *fila){
	for (int i = 0; i < qtdNaFila; i++){
			fila[i] = fila[i + 1];
	}
}

int duracaoTotal(Processo* processos, int numeroDeProcessos){
	int total = 0;
	for( int i = 0; i < numeroDeProcessos; i++ ){
		total += processos[i].duration;
	}

	return total;
}

int chegadaProcesso(Processo* processos, int numeroDeProcessos, int tempo, Processo *fila, int qtdNaFila){
	for(int i = 0; i < numeroDeProcessos; i++){
		if (processos[i].arrival == tempo){
			push(qtdNaFila, fila, processos[i]);
			return qtdNaFila+1;
		}
	}

	return qtdNaFila;
}

void roundRobin(Processo* processos, int numeroDeProcessos, int quantum) {
		int tempo, qtdNaFila;
		Processo *fila;
		fila = malloc(numeroDeProcessos *sizeof(Processo));
		qtdNaFila = 0;

		tempo = duracaoTotal(processos, numeroDeProcessos);
		qtdNaFila = chegadaProcesso(processos, numeroDeProcessos, 0,fila, qtdNaFila);
		for (int i = 0; i < tempo; i++) {
			for (int j = 0; j < qtdNaFila; j++) {
				if( j==0 ){
					fila[j].time += 1;
					quantum -= 1;
				} else{
					fila[j].waitingTime += 1;
				}
			}
			//printf("Tempo %d - %d ", i, qtdNaFila);
			printf("%d = %d - %d - %d - %d - %d\n", i, fila[0].processNumber,fila[1].processNumber,fila[2].processNumber, fila[3].processNumber, fila[4].processNumber);
			printf("%d - quantidade na fila = %d\n", fila[0].time, qtdNaFila);
			if ((fila[0].duration - fila[0].time) == 0) {
				pop(qtdNaFila, fila);
				qtdNaFila -= 1;
				quantum = 4;
			}
			else if (quantum == 0){
				Processo processoAtual = fila[0];
				pop(qtdNaFila, fila);
				push(qtdNaFila-1, fila, processoAtual);
				quantum = 4;
			}else{
				for(int k=0; k<fila[0].qtdeIO; k++){
						if(atoi(fila[0].io[k]) == fila[0].time){
							Processo processoAtual = fila[0];
							pop(qtdNaFila, fila);
							push(qtdNaFila-1, fila, processoAtual);
							quantum = 4;
							break;
						}
				}
			}
			if (i != 0)
				qtdNaFila = chegadaProcesso(processos, numeroDeProcessos, i,fila, qtdNaFila);
		}
	// 	for(int i=0; i< numberOfProcess;i++) {
	// 	printf("Processo: %d\n", processos[i].processNumber);
	// 	printf("Qtde IO: %d \n", processos[i].qtdeIO);
	// 	for(int j=0; j< processos[i].qtdeIO; j++) {
	// 		printf("IO: %s\n", processos[i].io[j]);
	// 	}
	// }
}

