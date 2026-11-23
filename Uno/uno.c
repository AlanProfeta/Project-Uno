#include "uno.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Pilha inicializar_pilha(int n){
    if (n==0){
        Pilha p;
        p.topo = -1;
        for(int i = 0; i<5;i++){
            if(i<4){
                for(int j = 0; j<=12;j++){
                    if(j == 0){
                        Carta c = {i, j};
                        pilha_empilhar(&p, c);
                    }else{
                    Carta c = {i, j};
                        pilha_empilhar(&p, c);
                        pilha_empilhar(&p, c);
                    }
                } 
            }
            else{
                for(int j = 13; j<15; j++){
                    Carta c = {i, j};
                    pilha_empilhar(&p, c);
                    pilha_empilhar(&p, c);
                    pilha_empilhar(&p, c);
                    pilha_empilhar(&p, c);
                }
            }  
        }
        return p;
    }
    else if(n==1){
        Pilha p;
        p.topo = -1;
        return p;
    }
    else{  
        printf("Parametro de inicialiar pilha invalido");
        exit(EXIT_FAILURE);
    }
}
Carta pilha_topo(Pilha p){
    return p.dados[p.topo];
}
int pilha_cheia(Pilha p){
    if(p.topo == 107){
        return 1;
    }else{
        return 0;
    }
}
int pilha_vazia(Pilha p){
    if(p.topo == -1){
        return 1;
    }else{
        return 0;
    }
}
int pilha_quantia(Pilha p){
    return p.topo+1;
}
void pilha_empilhar(Pilha *p, Carta c){
    if(pilha_cheia(*p)){
        return;
    }
    p->topo++;
    p->dados[p->topo] = c;
}
Carta pilha_desempilhar(Pilha *p){
    if(pilha_vazia(*p)){
        Carta invalida = {-1,-1};
        return invalida;
    }
    Carta c = p->dados[p->topo];
    p->topo--;
    return c;
}
void transferir_pilha(Pilha *p, Pilha *d){
    if(pilha_vazia(*d)){
        return;
    }
    Carta c = pilha_desempilhar(d);
    while(!pilha_vazia(*d)){
        Carta descarte = pilha_desempilhar(d);
        pilha_empilhar(p, descarte);
    }
    embaralhar_pilha(p);
    pilha_empilhar(d, c);
}
void embaralhar_pilha(Pilha *p){
    for(int i = p->topo; i>0; i--){
        int j= rand() % (i+1);
        Carta aux = p->dados[j];
        p->dados[j] = p->dados[i];
        p->dados[i]=aux;
    }
}


Mao inicializar_mao(Pilha *p){
    Mao m;
    m.qtd =0;
    for(int i=0; i<7; i++){
        mao_adicionar(&m, pilha_desempilhar(p));
    }
    return m;
}
void mao_adicionar(Mao *m, Carta c){
    m->mao[m->qtd] = c;
    m->qtd++;
}
Carta mao_remover(Mao *m, int indice){
    Carta c = m->mao[indice];
    m->mao[indice] = m->mao[m->qtd-1];
    m->qtd--;
    return c;
}
int mao_quantia(Mao m){
    return m.qtd;
}
Carta mao_ver_carta(Mao m, int indice){
    return m.mao[indice];
}


Jogo inicializar_jogo(){
    Jogo j;
    srand(time(NULL));
    j.pilha[0] = inicializar_pilha(0);
    j.pilha[1] = inicializar_pilha(1);
    embaralhar_pilha(&j.pilha[0]);
    pilha_empilhar(&j.pilha[1], pilha_desempilhar(&j.pilha[0]));
    j.jogador=0;
    j.sentido=1;
    while(pilha_topo(j.pilha[1]).cor == PRETO){
        j.pilha[0] = inicializar_pilha(0);
        j.pilha[1] = inicializar_pilha(1);
        embaralhar_pilha(&j.pilha[0]);
        pilha_empilhar(&j.pilha[1], pilha_desempilhar(&j.pilha[0]));
    }
    j.carta_atual = pilha_topo(j.pilha[1]);
    j.mao[0] = inicializar_mao(&j.pilha[0]);
    j.mao[1] = inicializar_mao(&j.pilha[0]);
    j.mao[2] = inicializar_mao(&j.pilha[0]);
    j.mao[3] = inicializar_mao(&j.pilha[0]);
    j.cor_jogo = j.carta_atual.cor;
    j.aguardando_cor = false;
    return j;
}
void jogar_carta(Jogo *j, int i) {
    if (j->aguardando_cor) return;
    if (i < 0 || i >= mao_quantia(j->mao[j->jogador])) return;
    if (!pode_jogar_carta(mao_ver_carta(j->mao[j->jogador], i), j->carta_atual, j->cor_jogo)) return;

    pilha_empilhar(&j->pilha[1], mao_remover(&j->mao[j->jogador], i));
    j->carta_atual = pilha_topo(j->pilha[1]);
    if (j->carta_atual.cor == PRETO) {
        j->aguardando_cor = true;
        return;
    }
    j->cor_jogo = j->carta_atual.cor;
    if (j->carta_atual.valor == 10) {
        j->jogador = (j->jogador + (2 * j->sentido) + 8) % 4;
    } else if (j->carta_atual.valor == 11) {
        j->sentido *= -1;
        j->jogador = (j->jogador + j->sentido + 4) % 4;
    } else if (j->carta_atual.valor == 12) {
        j->jogador = (j->jogador + j->sentido + 4) % 4;
        for (int k = 0; k < 2; k++) {
            if (pilha_vazia(j->pilha[0])) transferir_pilha(&j->pilha[0], &j->pilha[1]);
            mao_adicionar(&j->mao[j->jogador], pilha_desempilhar(&j->pilha[0]));
        }
        j->jogador = (j->jogador + j->sentido + 4) % 4;
    } else {
        j->jogador = (j->jogador + j->sentido + 4) % 4;
    }
}

void escolher_cor(Jogo *j, Cor nova_cor) {
    if (!j->aguardando_cor || nova_cor == PRETO) return;

    j->cor_jogo = nova_cor;
    j->aguardando_cor = false;

    if (j->carta_atual.valor == 14) { 
        j->jogador = (j->jogador + j->sentido + 4) % 4;
        for (int k = 0; k < 4; k++) {
            if (pilha_vazia(j->pilha[0])) transferir_pilha(&j->pilha[0], &j->pilha[1]);
            mao_adicionar(&j->mao[j->jogador], pilha_desempilhar(&j->pilha[0]));
        }
        j->jogador = (j->jogador + j->sentido + 4) % 4;
    } else { 
        j->jogador = (j->jogador + j->sentido + 4) % 4;
    }
}
void comprar_carta(Jogo *j){
    if(pilha_vazia(j->pilha[0])){
        transferir_pilha(&j->pilha[0], &j->pilha[1]);
    }
    mao_adicionar(&j->mao[j->jogador%4], pilha_desempilhar(&j->pilha[0]));
    j->jogador = (j->jogador+j->sentido+4)%4;
}

bool pode_jogar_carta(Carta carta, Carta topo, Cor cor_atual){
    if(carta.cor == cor_atual || carta.valor == topo.valor || carta.cor==PRETO){
        return true;
    }else{
        return false;
    }
}