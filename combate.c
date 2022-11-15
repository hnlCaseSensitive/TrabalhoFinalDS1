#include "combate.h"

jogador* criaJogador(void){
    jogador* pj = (jogador*) malloc(sizeof(jogador));

    pj->hp = 100;
    pj->max_hp = 100;
    pj->xp = 0;
    pj->lvl = 1;
    strcpy(pj->name, "player 1");
    pj->stm = 50;
    pj->max_stm = 50;

    return pj;
}

void destroiLista(bag* b){
    while(b != NULL){
        bag* next = b->next;
        free(b);
        b = next;
    }
}

void destroiJogador(jogador* j){
    bag* temp = j->items;
    destroiLista(temp);
    free(j);
}