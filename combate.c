#include "combate.h"
#include "gameLogic.h"
#include <math.h>

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
/*
void destroiLista(bag* b){
    while(b != NULL){
        bag* next = b->next;
        free(b);
        b = next;
    }
}

*/
void destroiJogador(jogador* j){
    //bag* temp = j->items;
    //destroiLista(temp);
    free(j);
}

Inimigo* criaInimigoRng(){
    char name[30];

    Inimigo* rando = (Inimigo*)malloc(sizeof(Inimigo));

    for(int i = 0; i < 29; i++){
        name[i] = floor(rand() * 26) + 97;
    }
    name[29] = '\0';

    strcpy(rando->name, name);
    rando->lvl = floor(rand() * 11);
    rando->max_hp = (rando->lvl) * 100;
    rando->hp = rando->max_hp;
    rando->self_element = floor(rand() * 7);
    rando->max_stm = (rando->lvl) * 500 * rand();
    rando->tecs = criaSkillRng();
    rando->self_type = CROOK;

    return rando;

}

skill* criaSkillRng(void){
    skill* tec = (skill*)malloc(sizeof(skill));

    tec->cost = floor(rand() * 10);
    tec->self_element = DMG;
    tec->valor = floor(rand() * 100);
    strcpy(tec->nome, "skill rng");
    tec->self_type = DMG;

    return tec;
}

