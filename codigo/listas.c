#include "listas.h"

extern FILE* saida;

void incluir_na_cidade(Bairro **cidade, int id_bairro, char nome[]) {
	
	Bairro* novo = (Bairro*) malloc(sizeof(Bairro));
	
	novo->id = id_bairro;
	strcpy(novo->nome, nome);
	novo->prox = *cidade;
	novo->primeiro = novo->ultimo = NULL;
	*cidade = novo;
}

void incluir_no_bairro(Bairro* cidade, int id_bairro, int id_rua, char nome[]) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
			
	if(bairro == NULL || encontra_rua(bairro, id_rua) != NULL) {
		fprintf(saida,"ERRO: Rua nao incluida. Bairro id: %d Rua id: %d Rua nome: '%s'\n", id_bairro, id_rua, nome);
		return;
	}
	
	Rua* novo = (Rua*) malloc(sizeof(Rua));
	novo->id = id_rua;
	strcpy(novo->nome, nome);
	novo->prox = NULL;
	novo->primeiro = novo->ultimo = NULL;
	
	if(bairro->primeiro == NULL)
		bairro->primeiro = bairro->ultimo = novo;
	else {
		bairro->ultimo->prox = novo;
		bairro->ultimo = novo;
	}
	
	fprintf(saida,"Rua incluida com sucesso. Bairro id: %d Rua id:%d Rua nome '%s'\n", id_bairro, id_rua, nome);
}

void eliminar_do_bairro(Bairro* cidade, int id_bairro, int id_rua) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
	
	if(bairro == NULL) {
		fprintf(saida, "Bairro inexistente!\n");
		fprintf(saida, "ERRO: Rua nao removida. Bairro id: %d. Rua id: %d", id_bairro, id_rua);
		return;
	}
	
	Rua* ant = NULL;
	Rua* rua = bairro->primeiro;
	Casa* casa = NULL;
	
	while(rua != NULL && rua->id != id_rua) {
		ant = rua;
		rua = rua->prox;
	}

	if(rua == NULL) {
		fprintf(saida, "Bairro vazio ou rua com ID = %d não encontrada\n", id_rua);
		fprintf(saida, "ERRO: Rua nao removida. Bairro id: %d. Rua id: %d\n", id_bairro, id_rua);
		return;
	}
	
	if(rua == bairro->primeiro && rua == bairro->ultimo) {
		bairro->ultimo = NULL;
		bairro->primeiro = NULL;
		for(casa = rua->primeiro; casa != NULL; casa = rua->primeiro) {
			rua->primeiro = casa->prox;
			free(casa);
		}
		free(rua);
	}
	
	else if(rua == bairro->ultimo) {
		bairro->ultimo = ant;
		ant->prox = NULL;
		for(casa = rua->primeiro; casa != NULL; casa = rua->primeiro) {
			rua->primeiro = casa->prox;
			free(casa);
		}
		free(rua);
	}
	
	else if(rua == bairro->primeiro) {
		bairro->primeiro = rua->prox;
		for(casa = rua->primeiro; casa != NULL; casa = rua->primeiro) {
			rua->primeiro = casa->prox;
			free(casa);
		}
		free(rua);
	}
	
	else {
		ant->prox = rua->prox;
		for(casa = rua->primeiro; casa != NULL; casa = rua->primeiro) {
			rua->primeiro = casa->prox;
			free(casa);
		}
		free(rua);
	}
	fprintf(saida, "Rua removida com sucesso. Bairro id: %d Rua id: %d\n", id_bairro, id_rua);
}

void incluir_na_rua(Bairro* cidade, int id_bairro, int id_rua, int id_casa, int numero_casa, char nome_consumidor[]) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
	Rua* rua = encontra_rua(bairro, id_rua);
	
	if(rua == NULL || encontra_casa(rua, id_casa) != NULL) {
		fprintf(saida,"ERRO: Casa nao incluida. Bairro id: %d. Rua id: %d. Casa id: %d. Casa nr: %d. Consumidor nome: '%s'\n", 
		        id_bairro, id_rua, id_casa, numero_casa, nome_consumidor);
		return;
	}
	
	Casa* novo = (Casa*) malloc(sizeof(Casa));
	novo->id = id_casa;
	novo->numero = numero_casa;
	strcpy(novo->nome, nome_consumidor);
	novo->consumo = 0.0;
	novo->prox = NULL;
	
	if(rua->primeiro == NULL)
		rua->primeiro = rua->ultimo = novo;
	
	else {
		Casa* ant = NULL;
		Casa* casa = rua->primeiro;
	
		while(casa != NULL && novo->numero > casa->numero) {
			ant = casa;
			casa = casa->prox;
		}
		
		if(ant == NULL) {
			novo->prox = rua->primeiro;
			rua->primeiro = novo;
		}
		
		else {
			novo->prox = casa;
			ant->prox = novo;
			if(casa == NULL)
				rua->ultimo = novo;
		}
	}
	
	fprintf(saida,"Casa incluida com sucesso. Bairro id: %d. Rua id: %d. Casa id: %d. Casa nr: %d. Consumidor nome: '%s'\n", 
	        id_bairro, id_rua, id_casa, numero_casa, nome_consumidor);
}

void eliminar_da_rua(Bairro* cidade, int id_bairro, int id_rua, int id_casa) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
	Rua* rua = encontra_rua(bairro, id_rua);
	
	if(rua == NULL) {
		fprintf(saida,"Bairro ou rua inexistente!\n");
		fprintf(saida,"ERRO: Casa nao removida. Bairro id: %d. Rua id: %d. Casa id: %d\n", id_bairro, id_rua, id_casa);
		return;
	}
	
	Casa* ant = NULL;
	Casa* casa = rua->primeiro;
	
	while(casa != NULL && casa->id != id_casa) {
		ant = casa;
		casa = casa->prox;
	}

	if(casa == NULL) {
		fprintf(saida, "Rua vazia ou casa com ID = %d não encontrado", id_casa);
		fprintf(saida, "ERRO: Casa nao removida. Bairro id: %d. Rua id: %d. Casa id: %d\n", id_bairro, id_rua, id_casa);
		return;
	}
	
	if(casa == rua->primeiro && casa == rua->ultimo) {
		rua->ultimo = NULL;
		rua->primeiro = NULL;
		free(casa);
	}
	
	else if(casa == rua->ultimo) {
		rua->ultimo = ant;
		ant->prox = NULL;
		free(casa);
	}
	
	else if(casa == rua->primeiro) {
		rua->primeiro = casa->prox;
		free(casa);
	}
	
	else {
		ant->prox = casa->prox;
		free(casa);
	}
		
	fprintf(saida,"Casa removida com sucesso. Bairro id: %d Rua id: %d Casa id: %d\n", id_bairro, id_rua, id_casa);
}

void consumir(Bairro* cidade, int id_bairro, int id_rua, int id_casa, float consumo) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
	Rua* rua = encontra_rua(bairro, id_rua);
	Casa* casa = encontra_casa(rua, id_casa);
	
	if(casa == NULL) {
		fprintf(saida,"ERRO: Casa nao encontrada. Bairro id: %d; Rua id: %d; Casa id: %d\n", id_bairro, id_rua, id_casa);
		return;
	}
	
	casa->consumo += consumo;
}

void medir_consumo_casa(Bairro* cidade, int id_bairro, int id_rua, int id_casa) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
	Rua* rua = encontra_rua(bairro, id_rua);
	Casa* casa = encontra_casa(rua, id_casa);
	
	if(casa == NULL) {
		fprintf(saida,"ERRO: Casa nao encontrada. Bairro id: %d; Rua id: %d; Casa id: %d\n", id_bairro, id_rua, id_casa);
		return;
	}
	
	fprintf(saida,"Bairro id: %d; Nome do Bairro: %s; Rua id: %d; Nome da Rua: %s; Casa id: %d; Consumo total: %.2f kWh\n", 
	id_bairro, bairro->nome, id_rua, rua->nome, id_casa, casa->consumo);
}

void medir_consumo_rua(Bairro* cidade, int id_bairro, int id_rua) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
	Rua* rua = encontra_rua(bairro, id_rua);
	Casa* casa = NULL;
	
	float consumo = 0.0;
	int cont = 0;
		
	if(rua == NULL) {
		fprintf(saida,"ERRO: Rua nao encontrada. Bairro id: %d; Rua id: %d\n", id_bairro, id_rua);
		return;
	}
	
	for(casa = rua->primeiro; casa != NULL; casa = casa->prox) {
		consumo += casa->consumo;
		cont++;
	}
	
	fprintf(saida,"Bairro id: %d; Nome do Bairro: %s; Rua id: %d; Nome da Rua: %s; Numero de casas: %d; Consumo total: %.2f kWh\n", 
	id_bairro, bairro->nome, id_rua, rua->nome, cont, consumo);
}

void medir_consumo_bairro(Bairro* cidade, int id_bairro) {
	
	Bairro* bairro = encontra_bairro(cidade, id_bairro);
	Rua* rua = NULL;
	Casa* casa = NULL;
	
	float consumo = 0.0;
	int cont1 = 0;
	int cont2 = 0;
	
	if(bairro==NULL) {
		fprintf(saida,"ERRO: Bairro nao encontrado. Bairro id: %d", id_bairro);
		return;
	}
	
	for(rua = bairro->primeiro; rua != NULL; rua = rua->prox) {
		for(casa = rua->primeiro; casa != NULL; casa = casa->prox) {
			consumo += casa->consumo;
			cont1++;
		}
		cont2++;
	}
	
	fprintf(saida,"Bairro id: %d; Nome do Bairro: %s; Numero de ruas: %d; Numero de casas: %d; Consumo total: %.2f kWh\n", 
	        id_bairro, bairro->nome, cont2, cont1, consumo);
}

void medir_consumo_cidade(Bairro* cidade) {
	
	Bairro* bairro = NULL;
	Rua* rua = NULL;
	Casa* casa = NULL;
	
	float consumo = 0.0;
	int cont1 = 0;
	int cont2 = 0;
	int cont3 = 0;
	
	if(cidade==NULL) {
		fprintf(saida,"ERRO: Cidade vazia.");
		return;
	}
	
	for(bairro = cidade; bairro != NULL; bairro = bairro->prox) {
		for(rua = bairro->primeiro; rua != NULL; rua = rua->prox) {
			for(casa = rua->primeiro; casa != NULL; casa = casa->prox) {
				consumo += casa->consumo;
				cont1++;
			}
			cont2++;
		}
		cont3++;
	}
	
	fprintf(saida,"Numero de bairros: %d; Numero de ruas: %d; Numero de casas: %d; Consumo total: %.2f kWh\n", cont3, cont2, cont1, consumo);
}

Bairro* encontra_bairro(Bairro* cidade, int id_bairro) {
	
	Bairro* p;
	
	for(p = cidade; p != NULL; p = p->prox) {
		if(p->id == id_bairro)
			return p;
	}
	return NULL;
}

Rua* encontra_rua(Bairro* bairro, int id_rua) {
	
	if(bairro == NULL)
		return NULL;
	
	Rua* p;
	
	for(p = bairro->primeiro; p != NULL; p = p->prox) {
		if(p->id == id_rua)
			return p;
	}
	return NULL;
}

Casa* encontra_casa(Rua* rua, int id_casa) {

	if(rua == NULL)
		return NULL;
	
	Casa* p;
	
	for(p = rua->primeiro; p != NULL; p = p->prox) {
		if(p->id == id_casa)
			return p;
	}
	return NULL;
}

void deletarCidade(Bairro* cidade) {
	
	Bairro* bairro;
	Rua* rua;
	Casa* casa;
	
	for(bairro = cidade; bairro != NULL; bairro = cidade) {
		for(rua = bairro->primeiro; rua != NULL; rua = bairro->primeiro) {
			for(casa = rua->primeiro; casa != NULL; casa = rua->primeiro) {
				rua->primeiro = casa->prox;
				free(casa);
			}
			bairro->primeiro = rua->prox;
			free(rua);
		}
		cidade = bairro->prox;
		free(bairro);
	}
}


