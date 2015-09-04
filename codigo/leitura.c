/**
 * @package     Electricity
 * 
 * More info in documentation
 *
 * @author      Fernando Barbosa Neto   
 * @author      Jeferson de Oliveira Batista   
 * 
 */

#include "leitura.h"

void ler_arquivo(Bairro* cidade, char arquivo[]) {
	FILE *entrada;
	
	entrada = fopen(arquivo, "r");
	
	if(entrada == NULL) {
		printf("Erro ao acessar %s\n", arquivo);
		return;
	}
	
	char unidade[7];
	char acao[9];
	int pi1, pi2, pi3, pi4; //piX = parametro int X
	char pc1[100]; //pcX = parametro char X
	float pf1; //pfX = parametro float X
	
	while(!feof(entrada)) {		
		fscanf(entrada, "%s %s", unidade, acao);
		
		if(!strcmp(unidade, "cidade")) {
		
            if(!strcmp(acao, "medir")) {
				fscanf(entrada, "\n");
				medir_consumo_cidade(cidade);
			}
			else {
				printf("\nComando inválido!\n");
				return;
			}
		}
		
		else if(!strcmp(unidade, "bairro")) {
			
			if(!strcmp(acao, "medir")) {
				fscanf(entrada, "%d \n", &pi1);
				medir_consumo_bairro(cidade, pi1);
		    }
		    	
		    else {
				printf("\nComando inválido!\n");
				return;
			}
		}
		
		else if(!strcmp(unidade, "rua")) {
			
			if(!strcmp(acao, "incluir")) {
				fscanf(entrada, "%d %d \"%[^\"]\"\n", &pi1, &pi2, pc1);
				incluir_no_bairro(cidade, pi1, pi2, pc1);
			}
			
			else if(!strcmp(acao, "eliminar")) {
				fscanf(entrada, "%d %d \n", &pi1, &pi2);
				eliminar_do_bairro(cidade, pi1, pi2);
			}
			
			else if(!strcmp(acao, "medir")) {
				fscanf(entrada, "%d %d \n", &pi1, &pi2);
				medir_consumo_rua(cidade, pi1, pi2);
			}
			
			else {
				printf("\nComando inválido!\n");
				return;
			}
		}
		
		else if(!strcmp(unidade, "casa")) {
		
			if(!strcmp(acao, "incluir")) {
				fscanf(entrada, "%d %d %d %d \"%[^\"]\"\n", &pi1, &pi2, &pi3, &pi4, pc1);
				incluir_na_rua(cidade, pi1, pi2, pi3, pi4, pc1);
			}
			
			else if(!strcmp(acao, "eliminar")) {
				fscanf(entrada, "%d %d %d \n", &pi1, &pi2, &pi3);
				eliminar_da_rua(cidade, pi1, pi2, pi3);
			}
			
			else if(!strcmp(acao, "consumir")) {
				fscanf(entrada, "%d %d %d %entrada \n", &pi1, &pi2, &pi3, &pf1);
				consumir(cidade, pi1, pi2, pi3, pf1);
			}
			
			else if(!strcmp(acao, "medir")) {
				fscanf(entrada, "%d %d %d \n", &pi1, &pi2, &pi3);
				medir_consumo_casa(cidade, pi1, pi2, pi3);
			}
			
			else {
				printf("\nComando inválido!\n");
				return;
			}
		}
		else {
			printf("\nComando inválido!\n");
			return;
		}
	}
	
	fclose(entrada);
}

