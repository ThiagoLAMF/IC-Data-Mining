#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "selecao.h"
//#include "defines.h"
//#include "crossover.h"
#ifndef _POP_
#define _POP_
#include "populacao.h"
#endif
#include "util.h"
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

    int i,j,k;
    int pai1,pai2;
    Individuo *arquivo = iniciaPopulacao(TOTAL_INDIVIDUOS_ARQUIVO);
    Individuo *populacao = iniciaPopulacao(TAM_POPULACAO_TOTAL);

    carregaArquivo(arquivo);
    carregaPopulacao(populacao);

    for(i = 0;i<N_GERACOES;i++)
    {
        calculaAvaliacao(arquivo,populacao,0); //Calcula avaliação
        quickSort(populacao,0,TAM_POPULACAO-1); //Ordena populacao
        calculafitnessAcumulado(populacao); //Calcula FA
        //exibeFitness(populacao);

        int indexFilhos = N_FILHOS;
        for(j=0;j<(N_FILHOS/2);j++) //Gera filhos
        {
            /*k = 0;
            do
            {
                pai1 = roleta(populacao); //Seleciona Pais
                pai2 = roleta(populacao);
                k++;
            }
            while(pai1 == pai2 && k < 10);
            */

            int *pais = roletaSemRepeticao(populacao);
            pai1 = pais[0];
            pai2 = pais[1];

            crossOver(populacao,indexFilhos,indexFilhos+1,pai1,pai2);

            mutacao(populacao[indexFilhos].gen);
            mutacao(populacao[indexFilhos+1].gen);


            indexFilhos += 2;
        }

    }

    //exibeDataMining(populacao,100,0);
    exibeFitness(populacao);
    //printf("%f",((float)(rand())/(float)(RAND_MAX))*0.2);
    getchar();
    return 0;
}





