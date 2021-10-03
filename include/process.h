#ifndef PROCESS_H_
#define PROCESS_H_

typedef struct {
	int processNumber;
	int duration;
	int time;
	int arrival;
	int waitingTime;
	char textoIO[100];
	int *io;
	int qtdeIO;
} Processo;

#endif