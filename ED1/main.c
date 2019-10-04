#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "Funcoes.h"


int main(void)
{

    lista_Jogadores *list;
    Lista_de_Cartas *Pesca;
    Lista_de_Cartas *Descarte;

    lst_cria(&list);
    lst_criaCarta(&Pesca);
    lst_criaCarta(&Descarte);

    Cria_Baralho(&Pesca);

    int jog = 0;
    int players = -1;
    bool sair = false;
    bool inverte = false;

    while(2 > jog || jog > 8){
        printf("\nDigite um número total de jogadores, válido de 2 a 8: ");
        scanf(" %d", &jog);
    }
    while(0 > players || players > jog){
        printf("\nDigite o número de jogadores controlados pessoalmente, validos de 0 a %d: ", jog);
        scanf(" %d", &players);
    }

    int j = 0;
    printf("\n");
    for(int i = 0; i < jog; i++){
        char nominho[20];
        if(j >= jog - players)
            printf("Digite o nome do jogador: ");
        else
            printf("Digite o nome do computador: ");
        scanf("%s", nominho);
        lst_insereDupla(&list, nominho);
        lst_criaMao(&list);
        j++;
    }
    lst_conecta(&list);

    lista_Jogadores *l = list;
    for(int i = 0; i < players; i++){
        l->Jogador.CPU = 0;  
        l = l->prox;
    }
    
    Embaralha(&Pesca, BARALHOS*PORBARALHO);

    lst_entrega_primeira_rodada(&Pesca, &Descarte, &list, jog);    

    l = list;
    while(sair == false){
        Imprime_mao(l, Pesca, Descarte);
        Jogo_rodando(&sair, &l, &Descarte, &inverte, &Pesca);
        if(inverte == true)
            l = l->ant;
        else
            l = l->prox;
    }

    if(inverte == true)
        l = l->prox;
    else
        l = l->ant;
        
    system("clear || cls");
    printf("\n\n----------------------------------------------------------\n\n");
    printf("\n\nParabens, o jogador %s venceu o jogo!\n\n", l->Jogador.nome);
    printf("\n\n----------------------------------------------------------\n\n");

    Pega_carta_de_volta(&Pesca, &Descarte, &list, jog);

    lst_libera(&Pesca);
    lst_liberaDupla(&list);

    return 0;
}

