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
    bool sair = false;
    bool inverte = false;

    while(2 > jog || jog > 8){
        printf("Digite um número de jogadores válido de 2 a 8: \n");
        scanf(" %d", &jog);
    }

    for(int i = 0; i < jog; i++){
        char nominho[20];
        if(i == jog - 1)
            printf("Digite o seu nome: \n");
        else
            printf("Digite o nome do jogador: \n");
        scanf("%s", nominho);
        lst_insereDupla(&list, nominho);
        lst_criaMao(&list);
    }
    lst_conecta(&list);
    list->Jogador.CPU = 0;
    
    Embaralha(&Pesca, BARALHOS*52);

    lst_entrega_primeira_rodada(&Pesca, &Descarte, &list, jog);    

    lista_Jogadores *l = list;
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

