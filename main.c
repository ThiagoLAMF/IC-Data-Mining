#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "util.h"
//#include "selecao.h"
//#include "defines.h"
//#include "crossover.h"
#include "populacao.h"
/*
1 - git pull (Pegar os arquivos do servidor)
2 - git status (Verifica Conflitos)
3 - git add .
4 - git commit -m "Mensagem"
5 - git push
*/
/** DEC. FUNÇÕES **/
/** MAIN **/
int main()
{
    srand( (unsigned)time(NULL) );
    srand(time(NULL));

    int i,j;

    Individuo *ind = iniciaPopulacao(TOTAL_INDIVIDUOS);
    Individuo *aval = iniciaPopulacao(100);

    carregaPopulacao2(aval);
    carregaPopulacao(ind);


    calculaAvaliacao(ind,aval,0);
    printf("Avaliacao: %f",aval[0].fitness);

    //crossOver(aval,50);

    //exibeDataMining(aval,52,0);
    getchar();
    return 0;
}





