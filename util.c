#ifndef _POP_
#define _POP_
#include "populacao.h"
#endif



int partition(Individuo *geracao, int l, int r)
{
    Individuo t;
    int i = l-1;
    int j;
    float pivot = geracao[r].fitness;

    for(j = l;j<=r-1;j++)
    {
        if(geracao[j].fitness <= pivot)
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
    Ordena com quick sort os indiv�duos da popula��o de acordo com a avalia��o:
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