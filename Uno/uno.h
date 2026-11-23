#ifndef UNO_H
#define UNO_H

#include <stdbool.h>

typedef enum{ VERMELHO, AZUL, VERDE, AMARELO, PRETO} Cor;

typedef struct{
    Cor cor;
    int valor;
} Carta;
bool pode_jogar_carta(Carta carta, Carta topo, Cor cor_atual);

typedef struct{
    Carta dados[108];
    int topo;
} Pilha;
Pilha inicializar_pilha(int n);
void embaralhar_pilha(Pilha *p);
Carta pilha_topo(Pilha p);
int pilha_cheia(Pilha p);
int pilha_vazia(Pilha p);
int pilha_quantia(Pilha p);
void pilha_empilhar(Pilha *p, Carta c);
Carta pilha_desempilhar(Pilha *p);
void transferir_pilha(Pilha *p, Pilha *d);

typedef struct{
    Carta mao[108];
    int qtd;
}Mao;
Mao inicializar_mao(Pilha *p);
void mao_adicionar(Mao *m, Carta c);
Carta mao_remover(Mao *m, int indice);
int mao_quantia(Mao m);
Carta mao_ver_carta(Mao m, int indice);

typedef struct{
    int jogador;
    int sentido;
    Cor cor_jogo;
    Mao mao[4];
    Carta carta_atual;
    Pilha pilha[2];
    bool aguardando_cor;
}Jogo;
Jogo inicializar_jogo();
void jogar_carta(Jogo *j, int i);
void comprar_carta(Jogo *j);
void escolher_cor(Jogo *j, Cor nova_cor);
#endif