#ifndef _COMBATE_H_
#define _COMBATE_H_

typedef enum{
    ACIDO = 0, // Dano extra contra humanos
    ELETRICO = 1, // Dano extra contra robos
    PERFURACAO = 2, // Dano extra contra insetos
    DESARMADO = 3 // Tipo de dano principalmente usado pra interacoes especiais
} tiposDano;

typedef enum{
    HUMANO = 0, // Leva mais dano de acido
    ROBO = 1, // Leva mais dano de eletricidade
    INSETO = 2 // Leva mais dano de perfuração
} tiposInimigo;

typedef struct template_arma{
    int dano; // Dano da arma
    char desc[128]; // Descrição da arma
    tiposDano tipoDano; // Tipo de dano que a arma da
} arma;

typedef struct player_stats_combate{
   int vidaMaxima; // O maximo de vida que o jogador pode ter
   int vidaAtual; // A vida atual do jogador

    // NOTA: dependendo de como vamos estruturar o jogo, talvez uma das variáveis acima não será necessária

   arma arma[4]; // A ideia é que em combate, teremos quatro opções de armas
   char itemEspecial[128]; // Item especial adiquirido no começo do jogo, guardado em char para ser mais facil ler

   // ADICIONAR TRAITS TALVEZ? (talvez em outra struct? Isso separaria o jogador que faz o combate e q faz as interações em dois...)
} playerCombate;


typedef struct template_inimigo{
    int vida; // Vida do inimigo
    int dano; // Dano que o inimigo da
    tiposInimigo tipo; // Tipo do inimigo
    char nome[128];
    int chancePontoFraco; // Chance do inimigo expor seu ponto fraco (em %)
} inimigo;

inimigo sorteiaInimigo();

void combate(playerCombate* player, inimigo inimigo);

#endif

