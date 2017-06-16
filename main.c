#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "util.h"
//#include "selecao.h"
//#include "defines.h"
//#include "crossover.h"
#include "populacao.h"

/** DEC. FUNÇÕES **/
/** MAIN **/
int main()
{
    srand( (unsigned)time(NULL) );
    srand(time(NULL));


    int i,j;

    Individuo *ind = iniciaPopulacao(TOTAL_INDIVIDUOS);
    Individuo *aval = iniciaPopulacao(50);

    carregaPopulacao2(aval);
    exibeDataMining(aval,50,0);
    getchar();
    carregaPopulacao(ind);
    //exibeDataMining(ind);
    //getchar();
    calculaAvaliacao(ind,aval,0);

    return 0;
}




