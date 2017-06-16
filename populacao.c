#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "populacao.h"


int calculaAvaliacao(Individuo *ind, Individuo *aval, int Classe)
{
    int i,contadorC1 = 0,j,k,posMaiorFitness;
    float FP=0,TP=0,FN=0,TN=0; //TN: Diz que � negativo e � negativo
    float SE,SP;
    float fitness;
    float maiorFitness = 0;
    for(i=0; i<50; i++) //Percorre aleatorios
    {
        FP=0,TP=0,FN=0,TN=0;
        for(k = 0; k<TOTAL_INDIVIDUOS; k++) //percorre carregados do arquivo
        {
            int flagDiferente = 0;
            for(j = 0; j<TAM_INDIVIDUO; j++) //PErcorre os genes
            {
                if(aval[i].gen[j].peso > 0.7  )
                {
                    int operador = aval[i].gen[j].operador;
                    //DIFERENTE, IGUAL, MENORIGUAL, MAIORIGUAL
                    switch(operador)
                    {
                    case DIFERENTE:
                        if(aval[i].gen[j].valor == ind[k].gen[j].valor)
                        {
                            flagDiferente = 1;
                        }
                        break;
                    case IGUAL:
                        if(aval[i].gen[j].valor != ind[k].gen[j].valor)
                        {
                            flagDiferente = 1;
                        }
                        break;
                    case MENOR:
                        if(aval[i].gen[j].valor >= ind[k].gen[j].valor)
                        {
                            flagDiferente = 1;
                        }
                        break;
                    case MAIORIGUAL:
                        if(aval[i].gen[j].valor < ind[k].gen[j].valor)
                        {
                            flagDiferente = 1;
                        }
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
            //false negative (fn) - the rule predicts that the patient does not have a given disease but the patient does have it.

        }
        //printf("tp = %f FP = %f TN = %f FN = %f\n",TP, FP, TN, FN);

        SE = (TP +1)/(TP + FN +1);
        SP = (TN +1 )/(TN + FP +1);
        //printf("\n SE == %f", SE);
        //printf("\n SP == %f", SP);

        fitness = SE * SP;
        if (fitness > maiorFitness)
        {
            maiorFitness = fitness;
            posMaiorFitness = i;
        }
        //printf("\n Fitness == %f", fitness);
        aval[i].fitness = fitness;



        //getchar();
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



/*Individuo* iniciaPopulacao2()
{
    Individuo *ind = (Individuo*) malloc(sizeof(Individuo*)*50);

    int i;
    for(i=0; i<50; i++)
    {
        Gene *gen = (Gene*) malloc(sizeof(Gene)*TAM_INDIVIDUO);
        ind[i].gen = gen;
    }
    return ind;
}*/


void carregaPopulacao(Individuo *ind)
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
            //printf( "%s\n", ultimo_token );
            if (rand()%(2) < 1) //flag vai definir si o peso é negativo ou não
                ind[indexIndividuo].gen[index].peso = myrand;

            else
                ind[indexIndividuo].gen[index].peso = -myrand;
             // atribui valor aleatorio entre -1 e 1 no peso.
          //  printf("peso: %f",ind[indexIndividuo].gen[index].peso);
           // getchar();
            ind[indexIndividuo].gen[index].operador = rand()%(4);
//            printf("op: %d",ind[indexIndividuo].gen[index].operador);
//           getchar();
            ind[indexIndividuo].gen[index].valor = atoi(ultimo_token);

            ultimo_token = strtok( NULL, delimitador );
            index++;
        }
        indexIndividuo++;
    }
}


void carregaPopulacao2(Individuo *aval)
{
    int i=0,index = 0;
    int indexIndividuo = 0;

    for (i=0;i<50;i++)
    {
        index = 0;
        while( index != TAM_INDIVIDUO )
        {

            if (rand()%(2) < 1) //flag vai definir si o peso é negativo ou não
                aval[indexIndividuo].gen[index].peso = myrand;

            else
                aval[indexIndividuo].gen[index].peso = -myrand;

            aval[indexIndividuo].gen[index].operador = rand()%(4);

            if (index == 10)
                aval[indexIndividuo].gen[index].valor = rand()%(2);
            else if (index == 33)
                aval[indexIndividuo].gen[index].valor = rand()%(100);
            else
               aval[indexIndividuo].gen[index].valor = rand()%(4);


            index++;
        }
        indexIndividuo++;
    }
}



int mutacao(Gene *gen)
{
    // numero aleatorio que fara a troca
    int i,j,num1, num2,pos1,pos2;
    Gene aux;
    printf("\nantes a mutacao\n");

    exibeGenes(gen);
//    for(j=0; j<TAM_INDIVIDUO+1; j++)
//    {
//        printf("%d,",gen[j].valor);
//    }

    for(i=0; i<=10; i++)
    {
        do
        {
            num1 = rand()%(33);
            num2 = rand()%(33);
        }
        while (num1 == 10 && num2 == 10);

        //aux = gen[num1];
        gen[num1] = gen[num2];
        //gen[num2] = aux;
        printf("\npos1: %d, pos2: %d\n",num1,num2);
    }
    printf("\napos a mutacao\n");
    exibeGenes(gen);


}
/*
void crossOver(Individuo* aval,int index,Gene* Filho1,Gene* Filho2)
{

    //Cross over, seleciona 2 pais e gera 2 filhos.
    Gene *a,*b;
    a = (Gene*) malloc(sizeof(Gene)*TAM_INDIVIDUO);
    b = (Gene*) malloc(sizeof(Gene)*TAM_INDIVIDUO);
    int posA=0,posB=0;

    while (posA == posB)
    {
        posA = rand()%(50);
        posB = rand()%(50);
    }


    printf("\nposA = %d\n posB = %d\n",posA,posB);

    a = aval[posA].gen;
    b = aval[posB].gen;
    exibeGenes(a);
    exibeGenes(b);

    int pos1,pos2;

    do
    {
        pos1 = rand()%(TAM_INDIVIDUO);
        pos2 = rand()%(TAM_INDIVIDUO);
    }
    while(pos1==pos2);

    printf("\n pos1 = %d,\npos2 = %d",pos1,pos2);
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
    printf("\n menor = %d,maior = %d",menor,maior);

    //Gene* filho1 = (Gene*) malloc(sizeof(Gene)*TAM_INDIVIDUO);
    //Gene* filho2 = (Gene*) malloc(sizeof(Gene)*TAM_INDIVIDUO);
    Gene* filho1 = aval[index].gen;
    Gene* filho2 = aval[index+1].gen;

    //Gene* aux = (Gene*) malloc(sizeof(Gene)*TAM_INDIVIDUO);
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
    exibeGenes(filho1);
    exibeGenes(filho2);
    Filho1 = filho1;
    Filho2 = filho2;
//    aval[index++].gen = filho1;
//    aval[index++].gen = filho2;
//   // getchar();
}
*/
