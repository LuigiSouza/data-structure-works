#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "Funcoes.h"


//------------------------------------------------------------------------------------------------------------------------


bool verifica_naipe(char primeia[20], char segunda[20]){

    int i = 0;

    while(primeia[i] != '\0'){
        if(primeia[i] != segunda[i])
            return false;

        i++;
    }
    if(segunda[i] != '\0')
        return false;

    return true;
}

int lst_tamanho(Lista_de_Cartas * inicio){

    Lista_de_Cartas *l = inicio;
    int i = 0;

    while( l != NULL )
    {
        l = l->prox;
        i++;
    }

    return i;
}

void ordena (Lista_de_Cartas ** Jogador_Mao){
    Lista_de_Cartas *j = *Jogador_Mao;

    (*Jogador_Mao) = (*Jogador_Mao)->prox;
    Lista_de_Cartas *q = (*Jogador_Mao);
    Lista_de_Cartas *p = (*Jogador_Mao);
    Lista_de_Cartas *ant = p;

    j->prox = NULL;

    while(p != NULL)
    {
        if(j->CartaAtual.valor < p->CartaAtual.valor)
            break;
        ant = p;
        p = p->prox;
    }
    if(p != ant){
        ant->prox = j;
        j->prox = p;
    }
    else{
        j->prox = (*Jogador_Mao);
        (*Jogador_Mao) = j;
    }

    return;
}


//------------------------------------------------------------------------------------------------------------------------


void lst_conecta(lista_Jogadores ** inicio){
    lista_Jogadores *l = *inicio;
    lista_Jogadores *j = *inicio;

    while(l->prox != NULL){
        l = l->prox;
    }

    l->prox = j;
    j->ant = l;

    *inicio = j;   
}

void lst_liberaDupla (lista_Jogadores** inicio)
{
lista_Jogadores* p = *inicio;
    do{
        lista_Jogadores* t = p->prox;
        free(p);
        p = t;
    } while( p != *inicio );
    *inicio = NULL;
}
void lst_libera (Lista_de_Cartas** inicio)
{
Lista_de_Cartas* p = *inicio;
    while( p != NULL )
    {
        Lista_de_Cartas* t = p->prox;
        free(p);
        p = t;
    }
    *inicio = NULL;
}

void lst_insereDupla (lista_Jogadores** inicio, char Name[20])
{
    lista_Jogadores* novo = (lista_Jogadores*) malloc(sizeof(lista_Jogadores));

    novo->Jogador.CPU = true;
    novo->Jogador.ganhando = false;
    strcpy(novo->Jogador.nome, Name);

    novo->prox = *inicio;
    novo->ant = NULL;
    
    if (*inicio != NULL)
        (*inicio)->ant = novo;
    *inicio = novo;
}

void lst_insere (Lista_de_Cartas** inicio, int i, char naip[10])
{
    Lista_de_Cartas* novo = (Lista_de_Cartas*) malloc(sizeof (Lista_de_Cartas));

    novo->CartaAtual.valor = i;
    strcpy(novo->CartaAtual.naipe,naip);

    novo->prox = *inicio;
    *inicio = novo;
}


void lst_cria (lista_Jogadores ** inicio)
{   
    *inicio = NULL;
}
void lst_criaCarta(Lista_de_Cartas ** inicio)
{
    *inicio = NULL;
}
void lst_criaMao(lista_Jogadores ** inicio)
{
    (*inicio)->Jogador.Mao = NULL;
}


//------------------------------------------------------------------------------------------------------------------------


char ConverteNaipe(int j, char *aux){

    if(j == 0){
        strcpy(aux, "Espadas");
        aux[7] = '\0';
    }
    else if(j == 1){
        strcpy(aux, "Copas");
        aux[5] = '\0';
    }
    else if(j == 2){
        strcpy(aux, "Ouro");
        aux[4] = '\0';
    }
    else if(j == 3){
        strcpy(aux, "Paus");
        aux[4] = '\0';
    }
    else{
        strcpy(aux, "ErroNaip");
        aux[7] = '\0';
    }
}

void Cria_Baralho(Lista_de_Cartas ** BaralhoTotal){
    char aux[10];

    for(int i = 0; i < BARALHOS; i++){
        for(int j = 0; j < NAIPES; j++){
            for(int z = 0; z < CARTAS; z++){
                ConverteNaipe(j, aux);
                lst_insere(BaralhoTotal, z + 1, aux);
            }
        }
    }
}

void Embaralha(Lista_de_Cartas ** Bolo, int num_de_cartas){
    srand(time(NULL));

    int aux;
    int auxant = -1;
    int j;

    Lista_de_Cartas *anterior;
    Lista_de_Cartas *proximo;
    Lista_de_Cartas *inicio;
    Lista_de_Cartas *final;
    Lista_de_Cartas *segundo;

    for(int i = 0; i < 400; i++){
        j = 0;

        inicio = *Bolo;
        proximo = *Bolo;

        segundo = inicio->prox;
        anterior = proximo;

        aux = rand()%num_de_cartas;

        while(aux == auxant){
            aux = rand()%num_de_cartas;
        }

        while(j < aux){
            anterior = proximo;
            proximo = proximo->prox;

            j++;
        }

        final = proximo->prox;
        
        anterior->prox = inicio;

        
        if(proximo == segundo)
            proximo->prox = inicio;
        else
            proximo->prox = segundo;

        inicio->prox = final;

        *Bolo = proximo;
        auxant = aux;
    }
}

bool Verifica_carta(Lista_de_Cartas * Descarte, Lista_de_Cartas * Jogada, int tam){

    if(Jogada->CartaAtual.valor == 8 && tam == 1)
        return false;
    if(Jogada->CartaAtual.valor == 8)
        return true;

    if(Jogada->CartaAtual.valor == Descarte->CartaAtual.valor)
        return true;
    else
        return verifica_naipe(Jogada->CartaAtual.naipe, Descarte->CartaAtual.naipe);
}


//------------------------------------------------------------------------------------------------------------------------


void Imprime_mao(lista_Jogadores * l, Lista_de_Cartas * Pesca, Lista_de_Cartas * Descarte){

    system("clear || cls");

    Lista_de_Cartas *rola = Pesca;
    printf("\nTamanho da Pesca: %4d\nCartas no Descarte: %2d\n\nCartas na Mao: %7d\n\n", lst_tamanho(Pesca), lst_tamanho(Descarte), lst_tamanho(l->Jogador.Mao));

    printf("Jogador  : %s\n", l->Jogador.nome);
    if(l->Jogador.CPU == true)
        printf("Controle : Computador\n");
    else
        printf("Controle : Jogador\n");
    printf("-----------------------\n");
    printf("\nCarta   0: Comprar uma nova carta\n\n");

    Lista_de_Cartas *q = l->Jogador.Mao;
    int pos = 1;
    while(q != NULL){
        printf("Carta %3d: %2d , %s\n",pos ,q->CartaAtual.valor, q->CartaAtual.naipe);
        q = q->prox;
        pos++;
    }
}

void lst_entrega_uma_carta(Lista_de_Cartas ** Inicio_bolo, Lista_de_Cartas ** Inicio_lista){
    Lista_de_Cartas *inicioMonte = *Inicio_bolo;
    Lista_de_Cartas *inicioMao = *Inicio_lista;

    Lista_de_Cartas *aux = inicioMao;
    inicioMao = inicioMonte;

    inicioMonte = inicioMonte->prox;
    
    inicioMao->prox = aux;

    *Inicio_lista = inicioMao;
    *Inicio_bolo = inicioMonte;
}

void Pega_carta_de_volta(Lista_de_Cartas ** Inicio_bolo, 
            Lista_de_Cartas ** Inicio_Descarte, lista_Jogadores ** Inicio_lista, int num)
{
    Lista_de_Cartas *posBolo = *Inicio_bolo;
    Lista_de_Cartas *descate_ini = *Inicio_Descarte;
    Lista_de_Cartas *lembra_primeira = *Inicio_Descarte;
    lista_Jogadores *posPlayer = *Inicio_lista;

    if(num == 0){
        descate_ini = descate_ini->prox;
        lembra_primeira->prox = NULL;
    }

    while(descate_ini != NULL){
        lst_entrega_uma_carta(&descate_ini, &posBolo);
    }


    for(int i = 0; i < num; i++){
        while(posPlayer->Jogador.Mao != NULL){
            lst_entrega_uma_carta(&posPlayer->Jogador.Mao, &posBolo);
        }
        posPlayer = posPlayer->prox;
    }

    *Inicio_bolo = posBolo;
    
    if(num == 0){
        *Inicio_Descarte = lembra_primeira;
        Embaralha(Inicio_bolo, lst_tamanho(*Inicio_bolo));
    }
}

void lst_entrega_primeira_rodada(Lista_de_Cartas ** Inicio_bolo, 
            Lista_de_Cartas ** Inicio_Descarte, lista_Jogadores ** Inicio_lista, int num)
{
    Lista_de_Cartas *posBolo = *Inicio_bolo;
    lista_Jogadores *posPlayer = *Inicio_lista;
    lista_Jogadores *inicio = *Inicio_lista;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < num; j++){
            lst_entrega_uma_carta(&posBolo, &posPlayer->Jogador.Mao);
            ordena(&posPlayer->Jogador.Mao);

            posPlayer = posPlayer->prox;
        }
    }
    lst_entrega_uma_carta(&posBolo, Inicio_Descarte);

    *Inicio_lista = inicio;
    *Inicio_bolo = posBolo;
}


//------------------------------------------------------------------------------------------------------------------------


Lista_de_Cartas * lst_acha_pos(Lista_de_Cartas * inicio, int i, Lista_de_Cartas ** ant){
    Lista_de_Cartas *aux = inicio;
    *ant = aux->prox;

    for(int j = 0; j < i; j++){
        *ant = aux;
        aux = aux->prox;
    }

    return aux;
}

void compra_carta(Lista_de_Cartas ** Monte_inicio, lista_Jogadores ** Jogador_atual){
    Lista_de_Cartas *aux = (*Jogador_atual)->Jogador.Mao;

    lst_entrega_uma_carta(Monte_inicio, &aux);
    ordena(&aux);    

    (*Jogador_atual)->Jogador.Mao = aux;

}

void compra_carta_aleatoria(bool Bot, lista_Jogadores ** Jogador_atual, 
        Lista_de_Cartas ** Monte_inicio, Lista_de_Cartas ** Descarte_inicio)
{

    srand(time(NULL));

    int carta = -1;

    Lista_de_Cartas *pos;
    Lista_de_Cartas *ant;

    if(Bot == false){
        while(carta < 0 || carta >= lst_tamanho((*Jogador_atual)->Jogador.Mao)){
            Imprime_mao(*Jogador_atual, *Monte_inicio, *Descarte_inicio);
            printf("\nO jogador anterior jogou um Rei (13), escolha uma carta para descartar: ");

            scanf(" %d", &carta);
            carta--;
        } 
        pos = lst_acha_pos((*Jogador_atual)->Jogador.Mao, carta, &ant);

        if(carta > 0)
            ant->prox = pos->prox;  
        else   
            (*Jogador_atual)->Jogador.Mao = ant;         
        
        lst_entrega_uma_carta(&pos, Descarte_inicio);

        if(lst_tamanho((*Jogador_atual)->Jogador.Mao) == 0)
            (*Jogador_atual)->Jogador.ganhando = true;
    }
    else{
        printf("\nO jogador anterior jogou um Rei (13), o próximo jogador descarta uma carta...");
        carta = rand()%lst_tamanho((*Jogador_atual)->Jogador.Mao);

        pos = lst_acha_pos((*Jogador_atual)->Jogador.Mao, carta, &ant);

        if(carta > 0)
            ant->prox = pos->prox;  
        else   
            (*Jogador_atual)->Jogador.Mao = ant;

        lst_entrega_uma_carta(&pos, Descarte_inicio);
    }
}

void carta_especial(int valor, bool * inverte, lista_Jogadores ** Jogador_atual, 
        Lista_de_Cartas ** Monte_inicio, Lista_de_Cartas ** Descarte_inicio)
{

    Lista_de_Cartas *aux;

    if(valor == 1){
        printf("O jogador jogou um As... A ordem dos jogadores foi invertida!\n");
        if(*inverte == true)
            *inverte = false;
        else  
            *inverte = true;
    }
    else if(valor == 11){
        printf("O jogador jogou um 'J'... O proximo jogador compra duas cartas!\n");
        if(*inverte == false)
            aux = (*Jogador_atual)->prox->Jogador.Mao;
        else
            aux = (*Jogador_atual)->ant->Jogador.Mao;


        if(lst_tamanho(*Monte_inicio) == 0)
            Pega_carta_de_volta(Monte_inicio, Descarte_inicio, Jogador_atual, 0);
        lst_entrega_uma_carta(Monte_inicio, &aux);
        ordena(&aux);

        if(lst_tamanho(*Monte_inicio) == 0)
            Pega_carta_de_volta(Monte_inicio, Descarte_inicio, Jogador_atual, 0);
        lst_entrega_uma_carta(Monte_inicio, &aux);
        ordena(&aux);

        if(*inverte == false){
            (*Jogador_atual)->prox->Jogador.ganhando = false;
            (*Jogador_atual)->prox->Jogador.Mao = aux;
        }
        else{
            (*Jogador_atual)->ant->Jogador.ganhando = false;
            (*Jogador_atual)->ant->Jogador.Mao = aux;
        }
    }
    else if(valor == 12){
        printf("O jogador jogou um 'Q'... O Jogador anterior compra duas cartas!\n");
        if(*inverte == false)
            aux = (*Jogador_atual)->ant->Jogador.Mao;
        else
            aux = (*Jogador_atual)->prox->Jogador.Mao;
            
        if(lst_tamanho(*Monte_inicio) == 0)
            Pega_carta_de_volta(Monte_inicio, Descarte_inicio, Jogador_atual, 0);
        lst_entrega_uma_carta(Monte_inicio, &aux);
        ordena(&aux);

        if(lst_tamanho(*Monte_inicio) == 0)
            Pega_carta_de_volta(Monte_inicio, Descarte_inicio, Jogador_atual, 0);
        lst_entrega_uma_carta(Monte_inicio, &aux);
        ordena(&aux);

        if(*inverte == false){
            (*Jogador_atual)->ant->Jogador.ganhando = false;
            (*Jogador_atual)->ant->Jogador.Mao = aux;
        }
        else{
            (*Jogador_atual)->prox->Jogador.ganhando = false;
            (*Jogador_atual)->prox->Jogador.Mao = aux;
        }

    }
    else if(valor == 13){

        lista_Jogadores *pos;

        if(*inverte == false)
            pos = (*Jogador_atual)->prox;
        else            
            pos = (*Jogador_atual)->ant;
    
        aux = pos->Jogador.Mao;
        
        if(lst_tamanho(*Monte_inicio) == 0)
            Pega_carta_de_volta(Monte_inicio, Descarte_inicio, Jogador_atual, 0);
        lst_entrega_uma_carta(Monte_inicio, &aux);

        if(*inverte == false){
            (*Jogador_atual)->prox->Jogador.ganhando = false;
            (*Jogador_atual)->prox->Jogador.Mao = aux;
            pos = (*Jogador_atual)->prox;
        }
        else{        
            (*Jogador_atual)->ant->Jogador.ganhando = false;
            (*Jogador_atual)->ant->Jogador.Mao = aux;
            pos = (*Jogador_atual)->ant;
        }

        compra_carta_aleatoria(pos->Jogador.CPU, &pos, Monte_inicio, Descarte_inicio);   
    }
}


//------------------------------------------------------------------------------------------------------------------------


void Jogo_rodando(bool *sair, lista_Jogadores ** Jogador_atual, 
        Lista_de_Cartas ** Descarte_inicio, bool *inverte, Lista_de_Cartas ** Monte_pesca)
{
    if((*Jogador_atual)->Jogador.ganhando == true){
        *sair = true;
        return;
    }


    if(lst_tamanho((*Jogador_atual)->Jogador.Mao) == 0){
        (*Jogador_atual)->Jogador.ganhando = true;
        
        return;
    }

    fflush(stdin);

    int carta = -2;

    bool valido = false;
    bool primeiro_ciclo = false;

    lista_Jogadores *aux = *Jogador_atual;
    Lista_de_Cartas *ant;
    Lista_de_Cartas *pos;

    lista_Jogadores *l = *Jogador_atual;


    if(aux->Jogador.CPU == 0){
        while(valido == false){
            carta = -2;
            printf("\nDescarte: %d , %s\n", (*Descarte_inicio)->CartaAtual.valor, (*Descarte_inicio)->CartaAtual.naipe);
            while(carta < -1 || carta >= lst_tamanho(aux->Jogador.Mao)){
                printf("\nDigite a carta desejada: ");
                scanf(" %d", &carta);
                carta--;
            }     

            if(carta == -1){
                pos = (*Jogador_atual)->Jogador.Mao;
                while(pos != NULL){
                    valido = Verifica_carta(*Descarte_inicio, pos, lst_tamanho(aux->Jogador.Mao));

                    if(valido == true){
                        printf("\nEh possivel jogar alguma carta...\n\n");
                        getchar();
                        getchar();
                        if(*inverte == false)
                            (*Jogador_atual) = (*Jogador_atual)->ant;
                        else
                            (*Jogador_atual) = (*Jogador_atual)->prox;

                        return;
                    }

                    pos = pos->prox;

                    primeiro_ciclo = true;
                }
                
                (*Jogador_atual)->Jogador.ganhando = false;         

                if(lst_tamanho(*Monte_pesca) == 0)
                    Pega_carta_de_volta(Monte_pesca, Descarte_inicio, Jogador_atual, 0);
                compra_carta(Monte_pesca, Jogador_atual);
                Imprime_mao(*Jogador_atual, *Monte_pesca, *Descarte_inicio);

                if(*inverte == false)
                    (*Jogador_atual) = (*Jogador_atual)->ant;
                else
                    (*Jogador_atual) = (*Jogador_atual)->prox;

                return;
            }

            pos = lst_acha_pos(aux->Jogador.Mao, carta, &ant);

            valido = Verifica_carta(*Descarte_inicio, pos, lst_tamanho(aux->Jogador.Mao));
        }   
        if(carta > 0)
            ant->prox = pos->prox;  
        else   
            (*Jogador_atual)->Jogador.Mao = ant;         
        
        lst_entrega_uma_carta(&pos, Descarte_inicio);

        if((*Descarte_inicio)->CartaAtual.valor > 10 || (*Descarte_inicio)->CartaAtual.valor == 1){
            carta_especial((*Descarte_inicio)->CartaAtual.valor, inverte, Jogador_atual, Monte_pesca, Descarte_inicio);
        }
    }
    else{
        printf("\nDescarte: %d , %s\n", (*Descarte_inicio)->CartaAtual.valor, (*Descarte_inicio)->CartaAtual.naipe);
        pos = aux->Jogador.Mao;

        carta = 0;

        while(pos != NULL){
            valido = Verifica_carta(*Descarte_inicio, pos, lst_tamanho(aux->Jogador.Mao));

            if(valido == true)
                break;

            pos = pos->prox;
            carta ++;

            primeiro_ciclo = true;
        }

        if(valido == true){
            printf("Carta Jogada: %d, %s\n", pos->CartaAtual.valor, pos->CartaAtual.naipe);

            pos = lst_acha_pos(aux->Jogador.Mao, carta, &ant);

            if(primeiro_ciclo == true)
                ant->prox = pos->prox;  
            else   
                (*Jogador_atual)->Jogador.Mao = ant;
                

            lst_entrega_uma_carta(&pos, Descarte_inicio);

            if((*Descarte_inicio)->CartaAtual.valor > 10 || (*Descarte_inicio)->CartaAtual.valor == 1){
                carta_especial((*Descarte_inicio)->CartaAtual.valor, inverte, Jogador_atual, Monte_pesca, Descarte_inicio);
            }

        }
        else
        {   
            if(lst_tamanho(*Monte_pesca) == 0)
                Pega_carta_de_volta(Monte_pesca, Descarte_inicio, Jogador_atual, 0);

            (*Jogador_atual)->Jogador.ganhando = false;         

            compra_carta(Monte_pesca, Jogador_atual);
            printf("O jogador compra outra carta...\n");
            getchar();

            if(*inverte == false)
                (*Jogador_atual) = (*Jogador_atual)->ant;
            else
                (*Jogador_atual) = (*Jogador_atual)->prox;

            return;            
        }

    }

    if(lst_tamanho((*Jogador_atual)->Jogador.Mao) == 0)
        (*Jogador_atual)->Jogador.ganhando = true;

    getchar();
}

