#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>
#include "../include/process.h"
#include "../include/roundrobin.h"

#define push(qtdNaFila, fila, processo) ((fila[qtdNaFila]) = (processo))

void pop (int qtdNaFila, Processo *fila){
	for (int i = 0; i < qtdNaFila-1; i++){
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
					fila[j].duration -= 1;
					quantum -= 1;
				} else{
					fila[j].waitingTime += 1;
				}
			}
			//printf("Tempo %d - %d ", i, qtdNaFila);
			printf("%d = %d - %d - %d - %d - %d\n", i, fila[0].processNumber,fila[1].processNumber,fila[2].processNumber, fila[3].processNumber, fila[4].processNumber);
			if (quantum == 0){
				printf("entrei no quantum\n");
				Processo processoAtual = fila[0];
				pop(qtdNaFila, fila);
				push(qtdNaFila-1, fila, processoAtual);
				quantum = 4;
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
