#ifndef _COMBATE_H_
#define _COMBATE_H_

#include "gameLogic.h"

typedef enum{
    ACIDO = 0, // Dano extra contra humanos
    ELETRICO = 1, // Dano extra contra robos
    PERFURACAO = 2, // Dano extra contra insetos
    DESARMADO = 3 // Tipo de dano principalmente usado pra interacoes especiais
} TiposDano;

typedef enum{
    HUMANO = 0, // Leva mais dano de acido
    ROBO = 1, // Leva mais dano de eletricidade
    INSETO = 2 // Leva mais dano de perfura��o
} TiposInimigo;

typedef struct template_arma{
    int dano; // Dano da arma
    char desc[128]; // Descri��o da arma
    TiposDano tipoDano; // Tipo de dano que a arma da
} arma;

typedef struct Player{
   int vidaMaxima; // O maximo de vida que o jogador pode ter
   int vidaAtual; // A vida atual do jogador
   arma armaAtual;
   char itemEspecial[128]; // Item especial adiquirido no come�o do jogo, guardado em char para ser mais facil ler


} Player;


typedef struct Inimigo{
    int vida; // Vida do inimigo
    int dano; // Dano que o inimigo da
    TiposInimigo tipo; // Tipo do inimigo
    char nome[200];
    int chancePontoFraco; // Chance do inimigo expor seu ponto fraco (em %)
    TiposDano vulnerabilidade;
} Inimigo;

typedef struct statusCombate {
    char *textOutputJ;
    char *textOutputI; //renomear
    char *armaEquipada;
} Status;

Inimigo *sorteiaInimigo();

void combate(Player* player, Inimigo *inimigo);

void escolheArma(Player *player, int arma, Status *status);

void ataque(Player*, Inimigo*);

void turnoJogador(Player *player, Inimigo *inimigo, Status *status);

void turnoInimigo(Player *player, Inimigo *inimigo, Status *status);

void output(Status *status, char *text);

void initArma(Player *);

void selecionaItem(int input, Player*);

void criaJogador(Player*, Status*);
#endif

