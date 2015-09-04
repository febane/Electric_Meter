/**
 * @package     Electricity
 * 
 * More info in documentation
 *
 * @author      Fernando Barbosa Neto   
 * @author      Jeferson de Oliveira Batista   
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

FILE *saida;

int main(int argc, char *argv[]) {
	
	if(argc != 2) {
		printf("Informe um arquivo de entrada!\n\n");
		return 1;
	}
	
	saida = fopen("saida.txt", "w");
	if(saida == NULL) {
		printf("Erro ao acessar saida.txt\n");
		return 2;
	}
	
	Bairro* cidade = NULL;
	
	// Inicializa os bairros
	incluir_na_cidade(&cidade, 13, "Bairro 13");
	incluir_na_cidade(&cidade, 17, "Bairro 17");
	incluir_na_cidade(&cidade, 15, "Bairro 15");
	incluir_na_cidade(&cidade, 14, "Bairro 14");
	incluir_na_cidade(&cidade, 27, "Bairro 27");
	incluir_na_cidade(&cidade, 31, "Bairro 31");
	incluir_na_cidade(&cidade, 19, "Bairro 19");
	incluir_na_cidade(&cidade, 28, "Bairro 28");
	incluir_na_cidade(&cidade, 21, "Bairro 21");
	
	// Lê o arquivo de entra e executa seus comandos
	ler_arquivo(cidade, argv[1]);
	
	// Libera a memória alocada
	deletarCidade(cidade);
	fclose(saida);
	return 0;
}


