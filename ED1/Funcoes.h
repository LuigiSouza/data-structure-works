#ifndef __FUNCOES__
#define __FUNCOES__

#define BARALHOS 2
#define PORBARALHO 52
#define NAIPES 4
#define CARTAS 13

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "Funcoes.h"



struct carta_t{
    char naipe[10];
    int valor;
};
struct ListaDeCartas_t{
    struct carta_t CartaAtual;
    struct ListaDeCartas_t *prox;
};
typedef struct ListaDeCartas_t Lista_de_Cartas;


struct jogadores_t{
    char nome[20];
    bool CPU;
    bool ganhando;

    Lista_de_Cartas *Mao;
};
struct Lista_t{
    struct jogadores_t Jogador;
    struct Lista_t *ant;
    struct Lista_t *prox;
};
typedef struct Lista_t lista_Jogadores;



//------------------------------------------------------------------------------------------------------------------------



bool verifica_naipe(char primeia[20], char segunda[20]);

int lst_tamanho(Lista_de_Cartas * inicio);

void ordena (Lista_de_Cartas ** Jogador_Mao);


//------------------------------------------------------------------------------------------------------------------------


void lst_conecta(lista_Jogadores ** inicio);

void lst_liberaDupla (lista_Jogadores** inicio);

void lst_libera (Lista_de_Cartas** inicio);

void lst_insereDupla (lista_Jogadores** inicio, char Name[20]);

void lst_insere (Lista_de_Cartas** inicio, int i, char naip[10]);

void lst_cria (lista_Jogadores ** inicio);

void lst_criaCarta(Lista_de_Cartas ** inicio);

void lst_criaMao(lista_Jogadores ** inicio);


//------------------------------------------------------------------------------------------------------------------------


char ConverteNaipe(int j, char *aux);

void Cria_Baralho(Lista_de_Cartas ** BaralhoTotal);

void Embaralha(Lista_de_Cartas ** Bolo, int num_de_cartas);

bool Verifica_carta(Lista_de_Cartas * Descarte, Lista_de_Cartas * Jogada, int tam);


//------------------------------------------------------------------------------------------------------------------------


void Imprime_mao(lista_Jogadores * l, Lista_de_Cartas * Pesca, Lista_de_Cartas * Descarte);

void lst_entrega_uma_carta(Lista_de_Cartas ** Inicio_bolo, Lista_de_Cartas ** Inicio_lista);

void Pega_carta_de_volta(Lista_de_Cartas ** Inicio_bolo, 
            Lista_de_Cartas ** Inicio_Descarte, lista_Jogadores ** Inicio_lista, int num);

void lst_entrega_primeira_rodada(Lista_de_Cartas ** Inicio_bolo, 
            Lista_de_Cartas ** Inicio_Descarte, lista_Jogadores ** Inicio_lista, int num);


//------------------------------------------------------------------------------------------------------------------------


Lista_de_Cartas * lst_acha_pos(Lista_de_Cartas * inicio, int i, Lista_de_Cartas ** ant);

void compra_carta(Lista_de_Cartas ** Monte_inicio, lista_Jogadores ** Jogador_atual);

void compra_carta_aleatoria(bool Bot, lista_Jogadores ** Jogador_atual, 
        Lista_de_Cartas ** Monte_inicio, Lista_de_Cartas ** Descarte_inicio);

void carta_especial(int valor, bool * inverte, lista_Jogadores ** Jogador_atual, 
        Lista_de_Cartas ** Monte_inicio, Lista_de_Cartas ** Descarte_inicio);

//------------------------------------------------------------------------------------------------------------------------

void Jogo_rodando(bool *sair, lista_Jogadores ** Jogador_atual, 
        Lista_de_Cartas ** Descarte_inicio, bool *inverte, Lista_de_Cartas ** Monte_pesca);

#endif