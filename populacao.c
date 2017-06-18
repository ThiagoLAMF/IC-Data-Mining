#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _POP_
#define _POP_
#include "populacao.h"
#endif


int calculaAvaliacao(Individuo *ind, Individuo *aval, int Classe)
{
    int i,contadorC1 = 0,j,k,posMaiorFitness;
    float FP=0,TP=0,FN=0,TN=0; //TN: Diz que � negativo e � negativo
    float SE,SP;
    float fitness;
    float maiorFitness = 0;

    for(i=0; i<TAM_POPULACAO; i++) //Percorre aleatorios
    {
        FP=0,TP=0,FN=0,TN=0;
        for(k = 0; k<TOTAL_INDIVIDUOS_ARQUIVO; k++) //percorre carregados do arquivo
        {
            int flagDiferente = 0;
            for(j = 0; j<TAM_INDIVIDUO; j++) //PErcorre os genes
            {
                if(aval[i].gen[j].peso > 0.7  )
                {
                    int operador = aval[i].gen[j].operador;
                    switch(operador)
                    {
                        case DIFERENTE:
                            if(aval[i].gen[j].valor == ind[k].gen[j].valor)
                                flagDiferente = 1;
                            break;
                        case IGUAL:
                            if(aval[i].gen[j].valor != ind[k].gen[j].valor)
                                flagDiferente = 1;
                            break;
                        case MENOR:
                            if(aval[i].gen[j].valor >= ind[k].gen[j].valor)
                                flagDiferente = 1;
                            break;
                        case MAIORIGUAL:
                            if(aval[i].gen[j].valor < ind[k].gen[j].valor)
                                flagDiferente = 1;
                            break;
                    }
                    if(flagDiferente) break;
                }
            }
            if(Classe == ind[k].gen[34].valor && !flagDiferente) //Regra diz que paciente tem e ele realmente tem
            {
                TP++;
            }
            if(Classe == ind[k].gen[34].valor && flagDiferente)//Regra diz que paciente tem e paciente nao tem
            {
                FP++;
            }
            if(Classe != ind[k].gen[34].valor && !flagDiferente) //Regradiz que paciente nao tem e paciente realmente nao tem
            {
                TN++;
            }
            if(Classe != ind[k].gen[34].valor && flagDiferente) //Regra diz
            {
                FN++;
            }
        }

        SE = (TP +1)/(TP + FN +1);
        SP = (TN +1 )/(TN + FP +1);

        fitness = SE * SP;
        if (fitness > maiorFitness)
        {
            maiorFitness = fitness;
            posMaiorFitness = i;
        }
        aval[i].fitness = fitness;
    }
    return posMaiorFitness;
}


void exibeGenes(Gene *gen)
{
    int j;
    printf("\nExibe genes do individuo:\n");
    for(j=0; j<TAM_INDIVIDUO+1; j++)
    {
        printf("%d,",gen[j].valor);
    }
}

void exibeDataMining(Individuo *ind,int tamPopulacao,int exibeClasse)
{
    int tamIndividuo = TAM_INDIVIDUO;
    if(exibeClasse)  tamIndividuo = TAM_INDIVIDUO + 1;

    int i,j;
    printf("-----Individuos----\n");
    for(i=0; i<tamPopulacao; i++)
    {
        //printf("[%d]\t",i);
        for(j=0; j<tamIndividuo; j++)
        {
            printf("%d,",ind[i].gen[j].valor);
        }
        printf("\n");

    }
}


Individuo* iniciaPopulacao(int tamPopulacao)
{
    Individuo *ind = (Individuo*) malloc(sizeof(Individuo)*tamPopulacao);

    int i;
    for(i=0; i<tamPopulacao; i++)
    {
        Gene *gen = (Gene*) malloc(sizeof(Gene)*TAM_INDIVIDUO);
        ind[i].gen = gen;
    }
    return ind;
}

void carregaArquivo(Individuo *ind)
{
    char buffer[ 100 ];
    const char *delimitador = ",";
    char *ultimo_token;
    int index = 0;
    int indexIndividuo = 0;
    FILE *arq;

    //Abre arquivo para leitura e coloca na base de dados;
    arq = fopen("dermatology.data.txt","r");
    if (!arq)
    {
        printf("ERRO na abertura do arquivo");
        system("pause");
        exit(1);
    }


    while( fgets(buffer, 100, arq) != NULL ) //Pega linha do arquivo
    {

        index = 0;
        ultimo_token = strtok( buffer, delimitador ); //Pega cada elemento
        while( ultimo_token != NULL )
        {
            ind[indexIndividuo].gen[index].peso = 0;
            ind[indexIndividuo].gen[index].operador = -1;
            ind[indexIndividuo].gen[index].valor = atoi(ultimo_token);

            ultimo_token = strtok( NULL, delimitador );
            index++;
        }
        indexIndividuo++;
    }
}


void carregaPopulacao(Individuo *aval)
{
    int i=0,index = 0;
    int indexIndividuo = 0;

    for (i=0; i<50; i++)
    {
        index = 0;
        while( index != TAM_INDIVIDUO )
        {

            if (rand()%(2) < 1) //flag vai definir si o peso é negativo ou não
                aval[indexIndividuo].gen[index].peso = myrand;

            else
                aval[indexIndividuo].gen[index].peso = -myrand;

            aval[indexIndividuo].gen[index].operador = rand()%(4);

            if (index == 10) //Hist. Fam.
                aval[indexIndividuo].gen[index].valor = rand()%(2);
            else if (index == 33) //Idade
                aval[indexIndividuo].gen[index].valor = rand()%(100);
            else
                aval[indexIndividuo].gen[index].valor = rand()%(4);
            index++;
        }
        aval[indexIndividuo].fitness = 0;
        aval[indexIndividuo].fitnessAcumulado = 0;
        indexIndividuo++;
    }
}



int mutacao(Gene *gen)
{
    int total_genes = (int) (P_MUTACAO_POR_CAMPO * TAM_INDIVIDUO) / 100;

    // numero aleatorio que fara a troca
    int i,j,num1, num2,pos1,pos2;
    float pesoAux = 0;
    int operadorAux;
    int valorAux;

    //printf("\nantes a mutacao\n");
    //exibeGenes(gen);

    for(i=0; i<=total_genes; i++)
    {
        //TROCA PESO:
        do
        {
            num1 = rand()%(33);
            num2 = rand()%(33);
        }
        while (num1 == num2);
        pesoAux = gen[num1].peso;
        gen[num1].peso = gen[num2].peso;
        gen[num2].peso = pesoAux;

        //TROCA OPERADOR
        do
        {
            num1 = rand()%(33);
            num2 = rand()%(33);
        }
        while (num1 == num2);
        operadorAux = gen[num1].operador;
        gen[num1].operador = gen[num2].operador;
        gen[num2].operador = operadorAux;

        //TROCA VALOR
        do
        {
            num1 = rand()%(33);
            num2 = rand()%(33);
        }
        while (num1 == 10 && num2 == 10);
        valorAux = gen[num1].valor;
        gen[num1].valor = gen[num2].valor;
        gen[num2].valor = valorAux;

    }
    //printf("\napos a mutacao\n");
    //exibeGenes(gen);


}

void crossOver(Individuo* aval,int indexFilho,int indexFilho2,int indexPai1,int indexPai2)
{
    Gene *a,*b;
    a = aval[indexPai1].gen;
    b = aval[indexPai2].gen;
    //exibeGenes(a);
    //exibeGenes(b);

    int pos1,pos2;

    do
    {
        pos1 = rand()%(TAM_INDIVIDUO);
        pos2 = rand()%(TAM_INDIVIDUO);
    }
    while(pos1==pos2);

    //printf("\n pos1 = %d,\npos2 = %d",pos1,pos2);
    int menor =0, maior =0;
    if (pos1 < pos2)
    {
        menor = pos1;
        maior = pos2;
    }
    else
    {
        menor = pos2;
        maior = pos1;
    }
    //printf("\n menor = %d,maior = %d",menor,maior);

    Gene* filho1 = aval[indexFilho].gen;
    Gene* filho2 = aval[indexFilho2].gen;

    int g;
    for(g=0; g<TAM_INDIVIDUO+1; g++) // +1 para pegar a ultima coluna (classe)
    {
        if(g <= menor)
        {
            filho1[g] = a[g];
            filho2[g] = b[g];
        }
        else if( (g > menor) && (g <= maior))
        {
            filho1[g] = b[g];
            filho2[g] = a[g];
        }
        else if(g > maior )
        {
            filho1[g] = a[g];
            filho2[g] = b[g];
        }

    }
    //exibeGenes(filho1);
    //exibeGenes(filho2);
}

// ---------------SELEÇÃO------------------
int torneioEstocastico(Individuo *aval)
{
    printf("\n\ntorneio:");
    int posPai1, posPai2;

    posPai1 = roleta(aval);
    posPai2 = roleta(aval);

    if(posPai1 == posPai2);
    {
        printf("\nSegunda tentatica pai1\n");
        posPai1 = roleta(aval);
    }
    printf("\npos Pai 1 == %d\npos Pai 2 == %d\n",posPai1,posPai2);
    return 1; //

}

/**
    Retorna dois elementos da população.
**/
void roletaSemRepeticao(Individuo *populacao,int *pai1,int *pai2)
{
    // Não finalizado
    //int pais[2];
    int k = 0;
    do
    {
        *pai1 = roleta(populacao); //Seleciona Pais
        *pai2 = roleta(populacao);
        k++;
    }
    while(*pai1 == *pai2 && k < 10);

    if(*pai1 == *pai2)
    {
        //Se após 10 tentativas, ainda seleciona pais iguais, seta a frequencia acumulada do elemento para -1

        populacao[*pai1].fitnessAcumulado = -1;
        //é necessário calcular o fitness acumulado novamente
        calculafitnessAcumulado(populacao);
        *pai2 = roleta(populacao);
        populacao[*pai1].fitnessAcumulado = 0; //volta o fitness para o elemento ser escolhido novamente
        //printf("\n[SEM REPETICAO]: PAI1: %d | PAI2: %d",pai1,pai2);

    }
    //printf("\nPAI1: %d | PAI2: %d",*pai1,*pai2);
    //getchar();
}

/**
    Gira a roleta 3 vezes ignorando os elementos que tem fitnessAcumulado = -1
**/
int roleta(Individuo *aval)
{
    int i=0,j=0,k=0,posMaior;
    float maior=0.00,A=0.00, aptA = 0.00, B=0.00, aptB = 0.00, C=0.00, aptC =0.00,somatotal=0.00;
    Gene *a,*b;
    somatotal = aval[TAM_POPULACAO-1].fitnessAcumulado;

    while (A == B && A == C)
    {

        /*do{
            A =((float)(rand())/(float)(RAND_MAX))*1;
           // printf("\nTESTE A\n aptidoes random:\n somatotal %f \nA = %f",somatotal,A);
           // getchar();
        }while (A > somatotal);


        do{
            B =((float)(rand())/(float)(RAND_MAX))*1;
            //printf("\nTESTE B\n aptidoes random:\n somatotal %f \nB = %f",somatotal,B);
            //getchar();
        }while (B > somatotal);

        do{
            C =((float)(rand())/(float)(RAND_MAX))*1;
          //  printf("\nTESTE C\n aptidoes random:\n somatotal %f \nC = %f",somatotal,C);
            //getchar();
        }while (C > somatotal);*/

        A =((float)(rand())/(float)(RAND_MAX))*somatotal;
        B =((float)(rand())/(float)(RAND_MAX))*somatotal;
        C =((float)(rand())/(float)(RAND_MAX))*somatotal;

    }



    //printf("\nA: %f B: %f C:%f - %f",A,B,C,somatotal);

    while(aval[i].fitnessAcumulado <= A)
    {
        i++;

    }
    aptA = aval[i].fitness;
    //printf("\nA[i] = %d\n aptA: %f \n",i,aptA);

    while(aval[j].fitnessAcumulado <= B)
    {
        j++;

    }
    aptB = aval[j].fitness;
    //printf("\nB[j] = %d\n aptB: %f \n",j,aptB);

    while(aval[k].fitnessAcumulado <= C)
    {
        k++;

    }
    aptC = aval[k].fitness;
    //printf("\nC[k] = %d\n aptC: %f \n",k,aptC);

    if (aptA >= aptB && aptA >= aptC)
    {
        maior = aptA;
        posMaior = i;
    }
    else if(aptB >= aptA && aptB >= aptC)
    {
        maior = aptB;
        posMaior = j;
    }
    else if(aptC >= aptB && aptC >= aptB)
    {
        maior = aptC;
        posMaior = k;
    }
    return posMaior;

}

int calculafitnessAcumulado(Individuo *aval)
{
    int soma=0,i,antes=0;
    float fitnessAnterior = 0;
    for(i=0;i<50;i++)
    {
        if(aval[i].fitnessAcumulado != -1) //Usado para diminuir a seleção repetida na roleta
        {
            aval[i].fitnessAcumulado = aval[i].fitness + fitnessAnterior;
            fitnessAnterior = aval[i].fitnessAcumulado;
        }
        //printf("\n[FA] %f",aval[i].fitnessAcumulado);

    }

}

void exibeFitness(Individuo *aval)
{
    int i;
    printf("\nPRINT FITNESS\n");
    for(i=0;i<TAM_POPULACAO;i++)
    {
        printf("\n[%d]\t F: %.5f\tFA: %.5f",i,aval[i].fitness,aval[i].fitnessAcumulado);
    }
}
