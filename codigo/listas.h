#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipos abstratos de dados (TAD's)

struct casa {
	int id;
	int numero;
	float consumo;
	char nome[61];
	struct casa *prox;
};

struct rua {
	int id;
	char nome[61];
	struct rua *prox;
	struct casa *primeiro, *ultimo;
};

struct bairro {
	int id;
	char nome[61];
	struct bairro *prox;
	struct rua *primeiro, *ultimo;
};

typedef struct casa Casa;
typedef struct rua Rua;
typedef struct bairro Bairro;

//Funções Administrativas
void incluir_na_cidade(Bairro** cidade, int id_bairro, char nome[]);
void incluir_no_bairro(Bairro* cidade, int id_bairro, int id_rua, char nome[]);
void eliminar_do_bairro(Bairro* cidade, int id_bairro, int id_rua);
void incluir_na_rua(Bairro* cidade, int id_bairro, int id_rua, int id_casa, int numero_casa, char nome_consumidor[]);
void eliminar_da_rua(Bairro* cidade, int id_bairro, int id_rua, int id_casa);

//Funções Operacionais
void consumir(Bairro* cidade, int id_bairro, int id_rua, int id_casa, float consumo);
void medir_consumo_casa(Bairro* cidade, int id_bairro, int id_rua, int id_casa);
void medir_consumo_rua(Bairro* cidade, int id_bairro, int id_rua);
void medir_consumo_bairro(Bairro* cidade, int id_bairro);
void medir_consumo_cidade(Bairro* cidade);

//Funções Auxiliares
Bairro* encontra_bairro(Bairro* cidade, int id_bairro);
Rua* encontra_rua(Bairro* cidade, int id_rua);
Casa* encontra_casa(Rua* bairro, int id_casa);
void deletarCidade(Bairro* cidade);

