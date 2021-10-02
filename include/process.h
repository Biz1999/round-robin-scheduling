#ifndef PROCESS_H_
#define PROCESS_H_

typedef struct {
	int processNumber;
	int duration;
	int arrival;
	char *io;
	int qtdeIO;
} Processo;

#endif