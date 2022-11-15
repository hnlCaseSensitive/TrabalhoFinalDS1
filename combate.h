#ifndef _COMBATE_H_
#define _COMBATE_H_

#include "gameLogic.h"

typedef enum{
    HEAL = 0,
    DMG = 1,
    ITEM = 2,
    SPECIAL
}tipo;

typedef enum{
    WATER = 0,
    FIRE = 1,
    METAL = 2,
    EARTH = 3,
    WOOD = 4,
    YIN = 5,
    YANG = 6
}elements;

typedef struct {
    char nome[30];
    float valor, cost;
    tipo self_type;
    elements self_element;
}skill;

typedef struct {
    char name[30];
    float hp, stm, max_hp, max_stm;
    int lvl, xp;
    skill tecs[5];
    bag* items;
} jogador;

typedef struct{
    skill info;
    bag* next;
} bag;

typedef enum {
    CROOK = 0,
    MAFIA_BOSS = 1,
    KING = 2,
    CEO_OF_EVIL
} enemy_type;

typedef struct{
    char name[30];
    float hp, stm, max_hp, max_stm;
    int lvl;
    skill* tecs;
    enemy_type self_type;
    elements self_element;
} Inimigo;

jogador* criaJogador(void);

void destroiLista(bag* b);

void destroiJogador(jogador* j);

#endif

