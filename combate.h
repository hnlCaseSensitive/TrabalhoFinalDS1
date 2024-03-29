#ifndef _COMBATE_H_
#define _COMBATE_H_

#include "gameLogic.h"

typedef enum{
    HEALING = 0,
    DMG = 1,
    ITEM = 2,
    SPECIAL
}tipo;

typedef struct {
    char nome[30];
    float valor, cost;
    tipo self_type;
}skill;

typedef struct bag{
    skill info;
    struct bag* next;
} bag;

typedef struct {
    char nome[30];
    int mult, base_val;
} weap;

typedef struct {
    char name[30];
    float hp, stm, max_hp, max_stm;
    int lvl, xp;
    skill tecs[5];
    bag* items;
    weap arma;
} jogador;

typedef struct{
    char name[30];
    float hp, stm, max_hp, max_stm;
    int lvl;
    skill tec;
} Inimigo;

jogador* criaJogador(void);

void destroiLista(bag* b);

void destroiJogador(jogador* j);

Inimigo* criaInimigoRng(int lvl);

skill criaSkillRng(void);

void addRngItem(jogador* j);

void usage(skill curr, jogador* j, Inimigo* i);

void AIusage(Inimigo* i, jogador* j);

void turnPass(Inimigo* i, jogador* j);

weap criaWeapRng(void);

void itemUsage(bag* b, jogador* j, Inimigo* i);

//skill getSkillFromFile(void);

//Inimigo* getInimigoFromFile(void);

//weap getWeapFromFile(void);

#endif

