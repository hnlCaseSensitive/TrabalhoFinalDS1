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

    pj->arma = criaWeapRng();

    for(int i = 0; i < 5; i++){
        pj->tecs[i] = criaSkillRng();
    }

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
        name[i] = floor(rand() % 26) + 97;
    }
    name[29] = '\0';

    strcpy(rando->name, name);
    rando->lvl = lvl;
    rando->max_hp = lvl * 100.0;
    rando->hp = rando->max_hp;
    rando->max_stm = rand() % (lvl * 50);
    rando->tec = criaSkillRng();
    if(rando->tec.self_type == HEAL){
        rando->tec.self_type = DMG;
        rando->tec.valor *= -1;
    }

    return rando;

}

skill criaSkillRng(void){
    skill tec;
    tec.cost = floor(rand() % 10);
    tec.valor = floor(rand() % 60) - 39;
    strcpy(tec.nome, "skill rng");

    if(tec.valor > 0){
        tec.self_type = HEAL;
    }else{
        tec.self_type = DMG;
    }

    return tec;
}

void usage(skill curr, jogador* j, Inimigo* i){
    if(curr.self_type == ITEM){
        if(curr.valor > 0){
            curr.self_type = HEAL;
        }else{
            curr.self_type = DMG;
        }
    }else{
        curr.cost *= j->arma.mult;
        curr.valor *= j->arma.mult;
    }

    if(j->stm < curr.cost){
        return;
    }

    if(curr.self_type == HEAL){
        j->hp += curr.valor;
        if(j->hp > j->max_hp){
            j->hp = j->max_hp;
        }
    }else{
        i->hp += curr.valor;
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

    j->hp += i->tec.valor;
    i->stm -= i->tec.cost;
}

weap criaWeapRng(void){
    weap wep;

    for(int i = 0; i < 29; i++){
        wep.nome[i] = floor(rand() % 26) + 97;
    }

    wep.base_val = (rand() % 25) + 9;
    wep.mult = (rand() % 3) + 1;

    return wep;
}

void itemUsage(bag* b, jogador* j, Inimigo* i){
    bag* aux = j->items;
    if(j->items == b){
        j->items = b->next;
    }else{
        while(aux->next != b && aux->next != NULL){
            aux = aux->next;
        }
        aux->next = b->next;
    }

    b->info.cost = 0;
    usage(b->info, j, i);

    free(b);
}

void addRngItem(jogador* j){
    bag* item = (bag*)malloc(sizeof(bag));

    item->info = criaSkillRng();
    item->info.cost = 0;

    item->next = j->items;
    j->items = item;

}
