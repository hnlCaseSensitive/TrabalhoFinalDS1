#include "gameLogic.h"
#include <string.h>
#include <unistd.h>

Inimigo* sorteiaInimigo(){
    Inimigo *aux = (Inimigo*) malloc(sizeof(Inimigo));
    // Sortei um numero de 1 a 100
    int sorteio = 0;

    srand(time(NULL));

    sorteio = rand() % 100;

    printf ("sorteio: %i", sorteio);
    // E seleciona um inimigo baseado no numero sorteado
    if (sorteio >= 75){
        aux->dano = 10;
        aux->vida = 100;
        aux->tipo = INSETO;
        strcpy(aux->nome, "inseto generico");
        aux->chancePontoFraco = 35;
        aux->vulnerabilidade = PERFURACAO;
    }
    else if (sorteio > 50){
        aux->dano = 10;
        aux->vida = 100;
        aux->tipo = ROBO;
        strcpy(aux->nome, "robo generico");
        aux->chancePontoFraco = 35;
        aux->vulnerabilidade = ELETRICO;
    }
    else {
        aux->dano = 10;
        aux->vida = 100;
        aux->tipo = HUMANO;
        strcpy(aux->nome, "humano generico");
        aux->chancePontoFraco = 35;
        aux->vulnerabilidade = ACIDO;
    }
    
    //printf("Vida:%d\n", aux->vida);
    return aux;
}

void escolheArma(Player *player, int escolha, Status *status)
{
    player->armaAtual.tipoDano = escolha;

    switch(escolha)
    {
        case ACIDO:
        {
            status->armaEquipada = "Acido";
        } break;
        case ELETRICO:
        {
            status->armaEquipada = "Eletrico";
        } break;
        case PERFURACAO:
        {
            status->armaEquipada = "Perfuracao";
        } break;
        case DESARMADO:
        {
            status->armaEquipada = "Desarmado";
        } break;
    }

}

//inicializa armas do jogador
void initArma(Player *player)
{
    int sorteio = 0;
    player->armaAtual.dano = 0;
        switch (player->armaAtual.dano)
    {
        case ACIDO:
            sorteio = (rand() % (30 - 5 + 1)) + 10;
            player->armaAtual.dano = 5 + sorteio;
            break;
        case ELETRICO:
            sorteio = (rand() % (30 - 5 + 1)) + 10;
            player->armaAtual.dano = 5 + sorteio;
            break;
        case PERFURACAO:
            sorteio = (rand() % (30 - 5 + 1)) + 10;
            player->armaAtual.dano = 5 + sorteio;
            break;
        case DESARMADO:
            sorteio = (rand() % (5 + 1));
            player->armaAtual.dano = 1 + sorteio;
    }
}
// //int num = (rand() % (upper - lower + 1)) + lower;

void turnoJogador(Player *player, Inimigo *inimigo, Status *status)
{
    initArma(player); //tirar daqui dps

    printf("Turno jogador\n");
    if (inimigo->vulnerabilidade==player->armaAtual.tipoDano) {
        inimigo->vida -= (player->armaAtual.dano + 15);
        //output(status, "Jogador fez dano a mais");
        status->textOutputJ = "jogador fez dano a mais";
        //return status;
        //printf("Status->texoutput:%s\n", status->textOutput);
        //return "Jogador fez de dano";
    }
    else {
        inimigo->vida -= player->armaAtual.dano;
        status->textOutputJ = "jogador fez dano";
        //printf("Status->texoutput:%s\n", status->textOutput);
        //return status;
    }
        //status->textOutput = "jogador nfez nada";
}

void turnoInimigo(Player *player, Inimigo *inimigo, Status *status)
{
    int sorteio = 0;
    int danoAdd = 0; // dano especial
    switch (inimigo->tipo)
    {
        case HUMANO: // leva mais dano de acido, chances de roubar arma do jogador
            printf("inimigo humano\n");
            srand(time(NULL));
            sorteio = rand() % 50;
            if (sorteio==45) {
                printf("Arma do jogador roubada!\n");
                escolheArma(player,DESARMADO,status);
            }
            // fazer chances de errar ataque
            player->vidaAtual -= inimigo->dano;
            break;
        case ROBO: // leva mais dano de eletricidade
            printf("inimigo robo\n");
            break;
        case INSETO: // perfurado
            printf("inimigo inseto\n");
            srand(time(NULL));
            sorteio = rand() % 50;
            if (sorteio%2==0) {
                printf("mordida de inseto!+ 1 dano\n");
                danoAdd += 1;
            }
            break;

    }
    printf("inimigo atacou!\n");
    player->vidaAtual -= inimigo->dano + danoAdd;
    printf("vida do jogador:%d\n", player->vidaAtual);
    status->textOutputI = "inimigo atacou";
}

