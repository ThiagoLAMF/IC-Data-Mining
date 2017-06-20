#ifndef _POP_
#define _POP_
#include "populacao.h"
#endif


/**
    Sobe os filhos na matriz
    posFilho = posição do primeiro filho
    posIni = índice da posição inicial de inserção
**/
void SobeFilhos(Individuo *geracao,int posIni,int qtdFilhos,int posFilho)
{
    int i;

    for(i=0;i<qtdFilhos;i++)
    {
        geracao[posIni] = geracao[posFilho];
        posFilho++;
        posIni++;
    }
}

int partition(Individuo *geracao, int l, int r)
{
    Individuo t;
    int i = l-1;
    int j;
    float pivot = geracao[r].fitness;

    for(j = l;j<=r-1;j++)
    {
        if(geracao[j].fitness >= pivot)
        {
            i++;
            t = geracao[i];
            geracao[i] = geracao[j];
            geracao[j] = t;
        }
    }

    t = geracao[i+1];
    geracao[i+1] = geracao[r];
    geracao[r] = t;

    return i+1;
}

/**
    Ordena com quick sort os indivíduos da população de acordo com a avaliação:
**/
void quickSort(Individuo *geracao, int l, int r)
{
   int j;

   if( l < r )
   {
        j = partition( geracao, l, r);// divide and conquer
        quickSort( geracao, l, j-1);
        quickSort( geracao, j+1, r);
   }

}


 void exibeGenesPeso(Gene *gen)
{
    int j;
    printf("\n-----------REGRA:----------\n");
    char *operador;
    char operadores[4][3] = {"!=\0","=\0","< \0",">=\0"};
    char atributos[34][50] = {
        "erythema \0",
        "scaling \0",
        "definite borders \0",
        "itching \0",
        "koebner phenomenon \0",
        "polygonal papules\0",
        "follicular papules \0",
        "oral mucosal involvement \0",
        "knee and elbow involvement \0",
        "scalp involvement \0",
        "family history, (0 or 1) \0",
        "melanin incontinence \0",
        "eosinophils in the infiltrate \0",
        "PNL infiltrate \0",
        "fibrosis of the papillary dermis \0",
        "exocytosis \0",
        "acanthosis \0",
        "hyperkeratosis \0",
        "parakeratosis\0",
        "clubbing of the rete ridges \0",
        "elongation of the rete ridges \0",
        "thinning of the suprapapillary epidermis \0",
        "spongiform pustule \0",
        "munro microabcess \0",
        "focal hypergranulosis \0",
        "disappearance of the granular layer \0",
        "vacuolisation and damage of basal layer \0",
        "spongiosis \0",
        "saw-tooth appearance of retes \0",
        "follicular horn plug \0",
        "perifollicular parakeratosis \0",
        "inflammatory monoluclear inflitrate \0",
        "band-like infiltrate\0",
        "Age\0"
    };

    for(j=0; j<TAM_INDIVIDUO; j++)
    {
        if(gen[j].peso > 0.7)
        {
            printf("%s %s %d and\n",atributos[j],operadores[gen[j].operador],gen[j].valor);
        }
    }
}

