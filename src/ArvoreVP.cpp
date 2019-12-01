#include <iostream>
#include "ArvoreVP.h"
#include "NoVP.h"
#include <bits/stdc++.h>
using namespace std;

ArvoreVP::ArvoreVP()
{
    this->raiz = NULL;
    comparacoesIns=0;
    trocasIns=0;
}

ArvoreVP::~ArvoreVP()
{
    //dtor
}


void ArvoreVP::auxEmOrdem(NoVP *raiz)
{
    //int userId1 = raiz->getUserId();
    //int movieId1 = raiz->getMovieId();
    if(raiz == NULL)
    {
        return;
    }
    auxEmOrdem(raiz->esquerda);
    cout << raiz->getGameId() << ", ";
    auxEmOrdem(raiz->direita);
}

NoVP* ArvoreVP::AVPInserir(NoVP *noRaiz, NoVP *pt)
{
    if(noRaiz==NULL)
    {
        return pt;
    }
    string user1 = noRaiz->getUser();
    int gameId1 = noRaiz->getGameId();
    string user2 = noRaiz->getUser();
    int gameId2 = noRaiz->getGameId();

    if(pt->getGameId()<noRaiz->getGameId())
    {
        noRaiz->esquerda=AVPInserir(noRaiz->esquerda, pt);
        noRaiz->esquerda->pai=noRaiz;
    }
    else if(pt->getGameId() > noRaiz->getGameId())
    {
        noRaiz->direita = AVPInserir(noRaiz->direita, pt);
        noRaiz->direita->pai=noRaiz;
    }
    return noRaiz;
}

void ArvoreVP::auxNivelOrdem(NoVP *raiz)
{
    if(raiz==NULL)
    {
        return;
    }
    std::queue<NoVP *> q;
    q.push(raiz);
    while(!q.empty())
    {
        NoVP *temp = q.front();
        cout<<temp->getGameId()<<" ";
        q.pop();
        if(temp->esquerda!=NULL)
        {
            q.push(temp->esquerda);
        }
        if(temp->direita!=NULL)
        {
            q.push(temp->direita);
        }
    }
}

void ArvoreVP::rotacionaEsquerda(NoVP *&raiz,NoVP *&pt )
{
    NoVP *ptDireita = pt->direita;
    pt->direita = ptDireita->esquerda;
    if(pt->direita!=NULL)
    {

        pt->direita->pai = pt;
    }
    ptDireita->pai = pt->pai;

    if(pt->pai==NULL)
    {
        raiz=ptDireita;

    }
    else if(pt==pt->pai->esquerda)
    {
        pt->pai->esquerda= ptDireita;


    }
    else
    {
        pt->pai->direita=ptDireita;

    }
    ptDireita->esquerda=pt;
    pt->pai=ptDireita;

}

void ArvoreVP::rotacionaDireita(NoVP *&raiz,NoVP *&pt )
{
    NoVP *ptEsquerda = pt->esquerda;
    pt->esquerda = ptEsquerda->direita;
    if(pt->esquerda!=NULL)
    {

        pt->esquerda->pai = pt;
    }
    ptEsquerda->pai = pt->pai;

    if(pt->pai==NULL)
    {
        raiz=ptEsquerda;

    }
    else if(pt==pt->pai->esquerda)
    {
        pt->pai->esquerda= ptEsquerda;


    }
    else
    {
        pt->pai->direita=ptEsquerda;
    }
    ptEsquerda->direita=pt;
    pt->pai=ptEsquerda;

}

void ArvoreVP::correcao(NoVP *&raiz,NoVP *&pt)
{
    NoVP *paiPt=NULL;
    NoVP *avoPt=NULL;
    while((pt!=raiz)&&(pt->cor!=PRETO)&&(pt->pai->cor==VERMELHO))
    {
        paiPt=pt->pai;
        avoPt=pt->pai->pai;
        /**
         Caso 1 (pai de pt é filho esquerdo do avo)
         */
        if(paiPt==avoPt->esquerda)
        {
            NoVP *tioPt=avoPt->direita;
            /**
             Caso 1.1 (tio do pt tambem é vermelho, é só recolorir)
             */
            if((tioPt!=NULL)&&(tioPt->cor==VERMELHO))
            {
                avoPt->cor=VERMELHO;
                paiPt->cor=PRETO;
                tioPt->cor=PRETO;
                pt=avoPt;
            }
            else
            {
                /**
                Caso 1.2 (pt é filho direito do pai, é só fazer a rotação esquerda)
                */
                if(pt == paiPt->direita)
                {
                    rotacionaEsquerda(raiz,paiPt);
                    pt=paiPt;
                    paiPt=pt->pai;
                }
                /**
                Caso 1.3 (pt é filho esquerdo do pai, é só fazer a rotação direita)
                */
                rotacionaDireita(raiz,avoPt);
                swap(paiPt->cor,avoPt->cor);
                pt=paiPt;
            }
        }
        /**
         Caso 2 (pai de pt é filho esquerdo do avo)
         */
        else
        {
            NoVP *tioPt = avoPt->esquerda;
            /**
             Caso 2.1 (tio do pt tambem é vermelho, só precisa recolorir)
             */
            if((tioPt!=NULL)&&(tioPt->cor==VERMELHO))
            {
                avoPt->cor=VERMELHO;
                paiPt->cor=PRETO;
                tioPt->cor=PRETO;
                pt=avoPt;
            }
            /**
             Caso 2.2 (pt é filho esquerdo do pai, so precisar rotacionar direita)
             */
            else
            {
                if(pt==paiPt->esquerda)
                {
                    rotacionaDireita(raiz,paiPt);
                    pt=paiPt;
                    paiPt=pt->pai;
                }
                /**
                 Caso 2.3 (pt é filho direito do pai, so precisar rotacionar esquerda)
                 */
                rotacionaEsquerda(raiz,avoPt);
                swap(paiPt->cor, avoPt->cor);
                pt=paiPt;
            }
        }
    }
    raiz->cor=PRETO;
}

void ArvoreVP::Inserir(registro &registro)
{
    NoVP *pt = new NoVP(&registro);
    //pt = NULL;
    raiz = AVPInserir(raiz, pt);
    correcao(raiz, pt);
}

void ArvoreVP::emOrdem()
{
    auxEmOrdem(this->raiz);
}

void ArvoreVP::nivelOrdem()
{
    auxNivelOrdem(this->raiz);
}
void ArvoreVP::bucaNo(int id, string user)
{
    registro *reg = new registro();
    reg->setId(id);
    reg->setUser(user);
    NoVP *noRaiz = this->raiz;
    auxBuscaNo(noRaiz, reg);
}

NoVP* ArvoreVP::auxBuscaNo(NoVP *raiz, registro *reg)
{
    if(raiz == NULL || raiz->getGameId() == reg->getId())
    {
        return raiz;
    }
    if(raiz->getGameId() < reg->getId())
    {
        return auxBuscaNo(raiz->direita,reg);
    }
    return auxBuscaNo(raiz->esquerda, reg);
}

int ArvoreVP::getTrocasIns()
{
    return trocasIns;
}

int ArvoreVP::getComparacoesIns()
{
    return comparacoesIns;
}
