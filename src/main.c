#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_util.h"
#include "object.h"
#include "geometry.h"
#include "tree.h"

int main(int argc, char *argv[]) {
	BinaryTree objectTree;

	char *baseDir = NULL;
	char *entryFileName = NULL;
	char *queryFileName = NULL;
	char *outputDir = NULL;
	char *outputSVGFileName = NULL;
	char *outputQrySVGFileName = NULL;
	char *outputTXTFileName = NULL;

	FILE *entryFile = NULL;
	FILE *queryFile = NULL;
	FILE *outputSVGFile = NULL;
	FILE *outputQrySVGFile = NULL;
	FILE *outputTXTFile = NULL;

	// Processamento dos argumentos passados ao programa
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
			if(entryFileName != NULL) {
				free(entryFileName);
			}
			entryFileName = malloc((strlen(argv[i]) + 1) * sizeof(char));
			strcpy(entryFileName, argv[i]);
		} else if(strcmp("-q", argv[i]) == 0) {
			if(++i >= argc) {
				printf("O argumento '-q' requer o nome de um arquivo!\n");
				return 1;
			}
			if(queryFileName != NULL) {
				free(queryFileName);
			}
			queryFileName = malloc((strlen(argv[i]) + 1) * sizeof(char));
			strcpy(queryFileName, argv[i]);
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

	// Verificação se os argumentos obrigatórios foram passados
	if(entryFileName == NULL) {
		printf("O argumento '-f' é obrigatório!\n");
		return 1;
	}
	if(outputDir == NULL) {
		printf("O argumento '-o' é obrigatório!\n");
		return 1;
	}

	outputSVGFileName = malloc((strlen(entryFileName) + 4) * sizeof(char));
	strcpy(outputSVGFileName, entryFileName);
	changeExtension(outputSVGFileName, "svg");

	// Abertura dos arquivos padrão
	entryFile = openFile(baseDir, entryFileName, "r");
	if(entryFile == NULL) {
		return 1;
	}
	outputSVGFile = openFile(outputDir, outputSVGFileName, "w");
	if(outputSVGFile == NULL) {
		return 1;
	}
	// Abertura dos arquivos referentes à consulta
	if(queryFileName != NULL) {
		outputTXTFileName = malloc((strlen(entryFileName) + 4) * sizeof(char));
		outputQrySVGFileName = malloc((strlen(entryFileName) + 4) * sizeof(char));
		char noExtName[32];
		strcpy(noExtName, queryFileName);
		removeExtension(noExtName);
		strcpy(outputTXTFileName, entryFileName);
		removeExtension(outputTXTFileName);
		strcpy(outputQrySVGFileName, outputTXTFileName);
		sprintf(outputTXTFileName, "%s-%s.txt", outputTXTFileName, noExtName);
		sprintf(outputQrySVGFileName, "%s-%s.svg", outputQrySVGFileName, noExtName);

		outputTXTFile = openFile(outputDir, outputTXTFileName, "w");
		if(outputTXTFile == NULL)
			return 1;

		outputQrySVGFile = openFile(outputDir, outputQrySVGFileName, "w");
		if(outputQrySVGFile == NULL)
			return 1;

		queryFile = openFile(baseDir, queryFileName, "r");
		if(queryFile == NULL)
			return 1;

		free(outputTXTFileName);
		free(outputQrySVGFileName);
		free(queryFileName);
	}

	if(baseDir != NULL)
		free(baseDir);
	free(outputSVGFileName);
	free(entryFileName);

	if(!processGeometry(entryFile, outputSVGFile, outputQrySVGFile, &objectTree))
		return 1;

	if(!processQuery(queryFile, outputQrySVGFile, outputTXTFile, &objectTree))
		return 1;
	
	fclose(entryFile);
	fclose(outputSVGFile);
	if(queryFile != NULL) {
		fclose(queryFile);
		fclose(outputSVGFile);
		fclose(outputTXTFile);
	}
}