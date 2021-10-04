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
		int quantumOriginal = quantum;
		float totalDeEspera;
		Processo *fila;
		fila = malloc(numeroDeProcessos *sizeof(Processo));

		totalDeEspera = 0;
		qtdNaFila = 0;

		tempo = duracaoTotal(processos, numeroDeProcessos);
		qtdNaFila = chegadaProcesso(processos, numeroDeProcessos, 0,fila, qtdNaFila);
		for (int i = 0; i <= tempo; i++) {
			quantum -= 1;
			if ((fila[0].duration - fila[0].time) == 0) {
				for (int j = 0; j < numeroDeProcessos; j++){
					if (fila[0].processNumber == processos[j].processNumber){
						processos[j].waitingTime = fila[0].waitingTime;
					}
				}
				totalDeEspera+= fila[0].waitingTime;
				pop(qtdNaFila, fila);
				qtdNaFila -= 1;
				quantum = quantumOriginal;
			}
			else if (quantum == 0){
				Processo processoAtual = fila[0];
				pop(qtdNaFila, fila);
				push(qtdNaFila-1, fila, processoAtual);
				quantum = quantumOriginal;
			}else{
				for(int k=0; k<fila[0].qtdeIO; k++){
						if(atoi((char*)fila[0].io[k]) == fila[0].time){
							Processo processoAtual = fila[0];
							pop(qtdNaFila, fila);
							push(qtdNaFila-1, fila, processoAtual);
							quantum = quantumOriginal;
							break;
						}
				}
			}
			if (i != 0){
				qtdNaFila = chegadaProcesso(processos, numeroDeProcessos, i,fila, qtdNaFila);
			}

			for (int j = 0; j < qtdNaFila; j++) {
				if( j == 0 ) {
					fila[j].time += 1;
				}else {
					fila[j].waitingTime += 1;
				}
			}
		}

	printf("\nPID.\tDuracao\tChegada\tI/O\n");
	printf("-----------------------------\n");
		for(int i=0; i< numeroDeProcessos; i++){
			printf("P%d\t%d\t%d\t", 
			processos[i].processNumber, 
			processos[i].duration,
			processos[i].arrival
			);
			for(int j=0; j< processos[i].qtdeIO; j++){
				if (processos[i].qtdeIO-1 == j){
					printf("%s", processos[i].io[j]);
				}else{
					printf("%s, ", processos[i].io[j]);
				}
			}
			if (processos[i].qtdeIO == 0){
				printf("-\n");
			}
			else if (numeroDeProcessos-1 == i){
				printf("\n");
			}
			printf("-----------------------------\n");
		}

	printf("Tempos de Espera: \n");
	for(int i=0; i< numeroDeProcessos; i++){
			printf("P%d = %dms\n", processos[i].processNumber, processos[i].waitingTime);
		}
	
	float divisao = (totalDeEspera / numeroDeProcessos);
	printf("\nTempo de Espera Medio: %.2f\n", divisao);
}

