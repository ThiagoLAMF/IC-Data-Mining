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

    /*for(i=0;i<34;i++)
    {
        populacao[0].gen[i].peso = 0;

    }
    populacao[0].gen[19].peso = 1.0;
    populacao[0].gen[19].operador = 3;
    populacao[0].gen[19].valor = 1;

    populacao[0].gen[30].peso = 1.0;
    populacao[0].gen[30].operador = 1;
    populacao[0].gen[30].valor = 0;

    populacao[0].gen[34].valor = 1;
    //exibeGenesPeso(populacao[0].gen);
    calculaAvaliacao(arquivo,populacao,1); //Calcula avaliação*/
    for(i = 0;i<N_GERACOES;i++)
    {
        calculaAvaliacao(arquivo,populacao,CLASSE); //Calcula avaliação
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


    calculaAvaliacao(arquivo,populacao,CLASSE); //Calcula avaliação
    quickSort(populacao,0,TAM_POPULACAO-1); //Ordena populacao

    //Debug
    //exibeDataMining(populacao,100,0);
    exibeFitness(populacao);
    exibeGenesPeso(populacao[0].gen);
    calculaFitnessTeste(populacao[0].gen,arquivo,CLASSE);
    //printf("\nFITNESS: %f",populacao[0].fitness);

    //Libera memoria:
    //liberaPopulacao(arquivo,TOTAL_INDIVIDUOS_ARQUIVO);
    //liberaPopulacao(populacao,TAM_POPULACAO_TOTAL);

    getchar();
    return 0;
}





