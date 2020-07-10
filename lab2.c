/* Programa: Lab 2
   Autor: Felipe Baz Mitsuishi
   Versao: 1.0 - 19/09/2019
*/
// ##################### Bibliotecas Externas ##############################
#include <stdio.h>
// ########################## TAD X.h ######################################
struct info
{
    int valor;
    int proximo;
};
typedef struct info tipoinfo;
struct ListaEE
{
    int tamanhoLista;
    int primeiro;
    int ultimo;
    //0 = ocupado; 1 = livre
    int posLivre[10];
    tipoinfo elemento[10];
};
typedef struct ListaEE tipolistaEE;

int proxPosLivre(tipolistaEE *listaAux)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        if (listaAux->posLivre[i] == 1)
        {
            return i;
        }
    }
    return -1;
}

void inicializalistaEE(tipolistaEE *listaAux)
{
    int i;
    listaAux->tamanhoLista = 0;
    listaAux->primeiro = -1;
    listaAux->ultimo = -1;
    for (i = 0; i < 10; i++)
    {
        listaAux->elemento[i].valor = 0;
        listaAux->elemento[i].proximo = -1;
        listaAux->posLivre[i] = 1;
    }
}

void insere(tipolistaEE *listaAux, int element)
{
    int posicao;
    posicao = proxPosLivre(listaAux);
    if (posicao != -1)
    {
        if (listaAux->tamanhoLista == 0)
        {
            listaAux->primeiro = posicao;
        }
        else
        {
            listaAux->elemento[listaAux->ultimo].proximo = posicao;
        }
        listaAux->elemento[posicao].valor = element;
        listaAux->elemento[posicao].proximo = -1;
        listaAux->tamanhoLista++;
        listaAux->posLivre[posicao] = 0;
    }
}

int listaCheia(tipolistaEE *listaAux)
{
    if (listaAux->tamanhoLista < 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ###################### Funcoes e Procedimentos do programa ##############
int buscaLista(tipolistaEE *listaAux, int element)
{
    int i;
    for (i = 0; i <= 10; i++)
    {
        if (listaAux->elemento[i].valor == element)
        {
            return i;
        }
    }
    return -1;
}

void insereElementoinicioEE(tipolistaEE *listaAux, int element)
{
    int pos, AntigoPrimeiro;
    if (listaAux->tamanhoLista == 0)
    {
        pos = proxPosLivre(listaAux);
        insere(listaAux, element);
        listaAux->ultimo = pos;
        listaAux->primeiro = pos;
    }
    else
    {
        AntigoPrimeiro = listaAux->primeiro;
        pos = proxPosLivre(listaAux);
        insere(listaAux, element);
        listaAux->elemento[pos].proximo = AntigoPrimeiro;
        listaAux->primeiro = pos;
        listaAux->elemento[listaAux->ultimo].proximo = -1;
    }
}

void insereElementoMeioEE(tipolistaEE *listaAux, int element, int posInicio, int posFim)
{
    int posicao;
    insere(listaAux, element);
    posicao = buscaLista(listaAux, element);
    listaAux->elemento[posInicio].proximo = posicao;
    listaAux->elemento[posicao].proximo = posFim;
    if (posFim == listaAux->ultimo)
    {
        listaAux->elemento[posFim].proximo = -1;
    }
}

void insereElementoEndEE(tipolistaEE *listaAux, int element)
{
    int ultimoAntigo, posUltimoAtual;
    ultimoAntigo = listaAux->ultimo;
    insere(listaAux, element);
    posUltimoAtual = buscaLista(listaAux, element);
    listaAux->elemento[ultimoAntigo].proximo = posUltimoAtual;
    listaAux->ultimo = posUltimoAtual;
    listaAux->elemento[posUltimoAtual].proximo = -1;
}

void removeElementoPrimeiro(tipolistaEE *listaAux)
{
    int posElemento, posSeguinte;
    posElemento = listaAux->primeiro;
    posSeguinte = listaAux->elemento[posElemento].proximo;
    listaAux->elemento[posElemento].valor = 0;
    listaAux->elemento[posElemento].proximo = -1;
    listaAux->tamanhoLista--;
    listaAux->primeiro = posSeguinte;
    listaAux->posLivre[posElemento] = 1;
}

void removeElementoMid(tipolistaEE *listaAux, int posicao)
{
    int Anterior, Sucessor, pos, resp = 0;
    pos = listaAux->primeiro;
    while (resp != -999)
    {
        if (listaAux->elemento[pos].proximo == posicao)
        {
            Anterior = pos;
            resp = -999;
        }
        pos = listaAux->elemento[pos].proximo;
    }
    Sucessor = listaAux->elemento[posicao].proximo;
    listaAux->elemento[Anterior].proximo = Sucessor;
    listaAux->tamanhoLista--;
}

void removeElementoUltimo(tipolistaEE *listaAux, int posicao)
{
    int anterior, resp = 0;
    anterior = listaAux->primeiro;

    while (resp != -999)
    {
        if (listaAux->elemento[anterior].proximo == posicao)
        {
            listaAux->elemento[posicao].valor = 0;
            listaAux->elemento[anterior].proximo = -1;
            listaAux->posLivre[posicao] = 1;
            listaAux->ultimo = anterior;
            listaAux->tamanhoLista--;
            resp = -999;
        }
        anterior = listaAux->elemento[anterior].proximo;
    }
}
void removeEE(tipolistaEE *listaAux, int pos)
{
    if (pos == listaAux->primeiro)
    {
        removeElementoPrimeiro(listaAux);
    }
    else if (pos == listaAux->ultimo)
    {
        removeElementoUltimo(listaAux, pos);
    }
    else
    {
        removeElementoMid(listaAux, pos);
    }
}

void organizalista(tipolistaEE *listaAux, int element)
{
    int anterior, proximo, i, resposta = 0;
    if (listaAux->primeiro == -1)
    {
        insereElementoinicioEE(listaAux, element);
    }
    else
    {
        for (i = 0; i < listaAux->tamanhoLista; i++)
        {
            if (element > listaAux->elemento[listaAux->ultimo].valor)
            {
                insereElementoEndEE(listaAux, element);
                resposta = -999;
            }
            else if (element < listaAux->elemento[listaAux->primeiro].valor)
            {
                insereElementoinicioEE(listaAux, element);
                resposta = -999;
            }
            else
            {
                proximo = listaAux->elemento[listaAux->primeiro].proximo;
                anterior = listaAux->primeiro;
                while (resposta != -999)
                {
                    if (listaAux->elemento[proximo].valor > element)
                    {
                        if (listaAux->elemento[anterior].valor < element)
                        {
                            insereElementoMeioEE(listaAux, element, anterior, proximo);
                            resposta = -999;
                            break;
                        }
                    }
                    proximo = listaAux->elemento[proximo].proximo;
                    anterior = listaAux->elemento[anterior].proximo;
                }
            }
        }
    }
}

void printLista(tipolistaEE *listaAux)
{
    int pos, resposta = 0;
    listaAux->elemento[listaAux->ultimo].proximo = -1;
    pos = listaAux->primeiro;
    if(listaAux->tamanhoLista == 0)
    {
        printf("\n");
    }else{
        while (resposta != -999)
        {
            if(listaAux->elemento[pos].proximo == -1)
            {
                printf("%d\n", listaAux->elemento[pos].valor);
                resposta = -999;
            }else
            {
                printf("%d ", listaAux->elemento[pos].valor);
                pos = listaAux->elemento[pos].proximo;
            }
        }
    }
}

int AnotaAno(int element)
{
    int divisao;
    divisao = (element) / 10000;
    return divisao;
}
// ############################ Principal ###################################

int main()
{
    int moviments, escolha, Carteira, i, divisao, Resp, pos, anos = 2012, Ano[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    tipolistaEE myList;
    inicializalistaEE(&myList);
    scanf("%d", &moviments);
    for (i = 0; i < moviments; i++)
    {
        scanf("%d %d", &escolha, &Carteira);
        if (escolha == 1)
        {
            Resp = listaCheia(&myList);
            if (Resp == 0)
            {
                printf("Dia cheio\n");
                printLista(&myList);
            }
            else
            {
                organizalista(&myList, Carteira);
                printLista(&myList);
                divisao = AnotaAno(Carteira);
                switch (divisao)
                {
                case 1:
                    Ano[0]++;
                    break;
                case 2:
                    Ano[1]++;
                    break;
                case 3:
                    Ano[2]++;
                    break;
                case 4:
                    Ano[3]++;
                    break;
                case 5:
                    Ano[4]++;
                    break;
                case 6:
                    Ano[5]++;
                    break;
                case 7:
                    Ano[6]++;
                    break;
                case 8:
                    Ano[7]++;
                    break;
                }
            }
        }
        else if (escolha == 2)
        {
            Resp = buscaLista(&myList, Carteira);
            if (Resp == -1)
            {
                printf("Não foi reservado\n");
                printLista(&myList);
            }
            else
            {
                pos = buscaLista(&myList, Carteira);
                if (pos == -1)
                {
                    printf("Não foi reservado\n");
                    printLista(&myList);
                }
                else
                {
                    removeEE(&myList, pos);
                    printLista(&myList);
                }
            }
        }
    }
    for (i = 0; i < 8; i++)
    {
        printf("%d: %d\n", anos + i, Ano[i]);
    }
    return 0;
}