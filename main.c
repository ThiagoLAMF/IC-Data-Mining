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

    int i,j,k;
    int pai1,pai2;
    Individuo *arquivo = iniciaPopulacao(TOTAL_INDIVIDUOS_ARQUIVO);
    Individuo *populacao = iniciaPopulacao(TAM_POPULACAO_TOTAL);

    carregaArquivo(arquivo);
    carregaPopulacao(populacao);

    for(i = 0;i<N_GERACOES;i++)
    {
        calculaAvaliacao(arquivo,populacao,0); //Calcula avaliação dos 50 indiduos na população
        calculafitnessAcumulado(populacao);

        int indexFilhos = N_FILHOS;
        for(j=0;j<(N_FILHOS/2);j++) //Gera filhos
        {
            //roletaSemRepeticao(&populacao); //
            k = 0;
            do
            {
                pai1 = roleta(populacao); //Seleciona Pais
                pai2 = roleta(populacao);
                k++;
            }
            while(pai1 == pai2 && k < 10);

            crossOver(populacao,indexFilhos,indexFilhos+1,pai1,pai2);

            mutacao(populacao[indexFilhos].gen);
            mutacao(populacao[indexFilhos+1].gen);

            printf("PAI1: %d | PAI2: %d",pai1,pai2);
            getchar();
            indexFilhos += 2;
        }

    }

    exibeDataMining(populacao,100,0);

    //printf("%f",((float)(rand())/(float)(RAND_MAX))*0.2);
    getchar();
    return 0;
}





