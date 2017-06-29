#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _POP_
    #define _POP_
    #include "populacao.h"
#endif
#include "util.h"

/** DEC. FUNÇÕES **/
void ag(int clss);
/** MAIN **/
int main()
{
    srand( (unsigned)time(NULL) );
    srand(time(NULL));

    int i;

    for(i = 1 ; i <= 6;i++)
    {
        ag(i);
    }

}

void ag(int clss)
{
    clock_t inicio,fim;
    unsigned long int tempo;
    inicio = clock();

    int i,j,k;
    int pai1,pai2;
    Individuo *arquivo = iniciaPopulacao(TOTAL_INDIVIDUOS_ARQUIVO);
    Individuo *populacao = iniciaPopulacao(TAM_POPULACAO_TOTAL);

    carregaArquivo(arquivo);
    carregaPopulacao(populacao);

    for(i = 0;i<N_GERACOES;i++)
    {
        calculaAvaliacao(arquivo,populacao,clss); //Calcula avaliação
        quickSort(populacao,0,TAM_POPULACAO-1); //Ordena populacao
        calculafitnessAcumulado(populacao); //Calcula FA
        //exibeFitness(populacao);

        int indexFilhos = N_FILHOS;
        for(j=0;j<(N_FILHOS/2);j++) //Gera filhos
        {
            k = 0;
            do
            {
                pai1 = roleta(populacao); //Seleciona Pais
                pai2 = roleta(populacao);
                k++;
            }
            while(pai1 == pai2 && k < 10);

            //calculafitnessAcumulado(populacao); //Calcula FA
            //roletaSemRepeticao(populacao,&pai1,&pai2);

            crossOver(populacao,indexFilhos,indexFilhos+1,pai1,pai2);

            mutacao(populacao[indexFilhos].gen);
            mutacao(populacao[indexFilhos+1].gen);


            indexFilhos += 2;
        }

        SobeFilhos(populacao,TX_ELITISMO,TAM_POPULACAO-1,TAM_POPULACAO);

        //exibeDataMining(populacao,100,0);
        //calculaAvaliacao(arquivo,populacao,1); //Calcula avaliação
        //exibeFitness(populacao);
        //printf("\nFitness melhor: %f",populacao[0].fitness);
        //getchar();
    }


    calculaAvaliacao(arquivo,populacao,clss); //Calcula avaliação
    quickSort(populacao,0,TAM_POPULACAO-1); //Ordena populacao

    fim=clock();
    tempo=(fim-inicio)*1000/CLOCKS_PER_SEC;
    //Debug
    //exibeDataMining(populacao,100,0);
    exibeFitness(populacao);
    printf("\n[FITNESS TREINAMENTO]: %f",populacao[0].fitness);
    float fitnessTeste = calculaFitnessTeste(populacao[0].gen,arquivo,clss);

    exibeResultado(populacao[0].gen,fitnessTeste,populacao[0].fitness,clss,tempo);
    //Libera memoria:
    //liberaPopulacao(arquivo,TOTAL_INDIVIDUOS_ARQUIVO);
    //liberaPopulacao(populacao,TAM_POPULACAO_TOTAL);
    return 0;

}




