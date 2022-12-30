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

Inimigo* criaInimigoRng(int lvl){
    char name[30];

    Inimigo* rando = (Inimigo*)malloc(sizeof(Inimigo));

    for(int i = 0; i < 29; i++){
        name[i] = floor(rand() * 26) + 97;
    }
    name[29] = '\0';

    strcpy(rando->name, name);
    rando->lvl = lvl;
    rando->max_hp = lvl * 100;
    rando->hp = rando->max_hp;
    rando->max_stm = lvl * 500 * rand();
    rando->tec = criaSkillRng();

    return rando;

}

skill criaSkillRng(void){
    skill tec;
    tec.cost = floor(rand() * 10);
    tec.valor = floor(rand() * 100);
    strcpy(tec.nome, "skill rng");
    tec.self_type = DMG;

    return tec;
}

void usage(int selected, jogador* j, Inimigo* i){
    skill curr = j->tecs[selected];

    if(j->stm < curr.cost){
        return;
    }

    if(curr.self_type == HEAL){
        j->hp += curr.valor;
        if(j->hp > j->max_hp){
            j->hp = j->max_hp;
        }
    }else{
        i->hp -= curr.valor;
    }
    j->stm -= curr.cost;
}

void turnPass(Inimigo* i, jogador* j){
    i->stm += i->max_stm / 10;
    j->stm += j->max_stm / 10;
}

void AIusage(Inimigo* i, jogador* j){
    if(i->stm < i->tec.cost){
        return;
    }

    j->hp -= i->tec.valor;
    i->stm -= i->tec.cost;
}
