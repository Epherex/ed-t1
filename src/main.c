#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_util.h"

double clamp(double valor, double a, double b) {
	double clampado = valor > b ? b : valor;
	clampado = valor < a ? a : valor;
	return clampado;
}

int main(int argc, char *argv[]) {
	char *baseDir = NULL;
	char *entryFilePath = NULL;
	char *queryFilePath = NULL;
	char *outputDir = NULL;

	FILE *entryFile = NULL;

	for(int i = 1; i < argc; i++) {
		if(strcmp("-e", argv[i]) == 0) {
			if(++i >= argc) {
				printf("O argumento '-e' requer um diretório!\n");
				return 1;
			}
			if(baseDir != NULL) {
				free(baseDir);
			}
			baseDir = malloc((strlen(argv[i]) + 1) * sizeof(char));
			strcpy(baseDir, argv[i]);
		} else if(strcmp("-f", argv[i]) == 0) {
			if(++i >= argc) {
				printf("O argumento '-f' requer o nome de um arquivo!\n");
				return 1;
			}
			if(entryFilePath != NULL) {
				free(entryFilePath);
			}
			entryFilePath = malloc((strlen(argv[i]) + 1) * sizeof(char));
			strcpy(entryFilePath, argv[i]);
		} else if(strcmp("-q", argv[i]) == 0) {
			if(++i >= argc) {
				printf("O argumento '-q' requer o nome de um arquivo!\n");
				return 1;
			}
			if(queryFilePath != NULL) {
				free(queryFilePath);
			}
			queryFilePath = malloc((strlen(argv[i]) + 1) * sizeof(char));
			strcpy(queryFilePath, argv[i]);
		} else if(strcmp("-o", argv[i]) == 0) {
			if(++i >= argc) {
				printf("O argumento '-o' requer um diretório!\n");
				return 1;
			}
			if(outputDir != NULL) {
				free(outputDir);
			}
			outputDir = malloc((strlen(argv[i]) + 1) * sizeof(char));
			strcpy(outputDir, argv[i]);
		} else {
			printf("Comando não reconhecido: '%s'\n", argv[i]);
			return 1;
		}
	}

	if(entryFilePath == NULL) {
		printf("O argumento '-f' é obrigatório!\n");
		return 1;
	}

	if(outputDir == NULL) {
		printf("O argumento '-o' é obrigatório!\n");
		return 1;
	}

	entryFile = openFile(baseDir, entryFilePath);

	printf("oi\n");

}