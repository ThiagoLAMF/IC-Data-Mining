#define TOTAL_INDIVIDUOS_ARQUIVO 258
#define TOTAL_TREINAMENTO 170
#define TOTAL_TESTE 88

#define CLASSE 3

#define TAM_POPULACAO 50
#define TAM_POPULACAO_TOTAL 100 // TAM_POPULACAO + Quantidade de filhos
#define TAM_INDIVIDUO 34

#define P_MUTACAO_POR_CAMPO 50 //Porcentagem mutacao por campo
#define N_GERACOES 50
#define N_FILHOS 50

#define TX_ELITISMO 1

#define myrand ((float)(rand())/(float)(RAND_MAX) ) //macro myrand: gera numeros float entre 0 e 1
#define DIFERENTE 0
#define IGUAL 1
#define MENOR 2
#define MAIORIGUAL 3

typedef struct gene
{
    float peso;
    int operador;//aleatorio
    int valor;
}Gene;
typedef struct individuo
{
    Gene *gen;
    float fitness;
    float fitnessAcumulado;
}Individuo;


int calculaAvaliacao(Individuo *ind, Individuo *aval, int Classe);
void exibeGenes(Gene *gen);
void exibeDataMining(Individuo *ind,int tam_pop,int exibeClasse);
Individuo* iniciaPopulacao(int tamPopulacao);
void carregaArquivo(Individuo *ind);
void carregaPopulacao(Individuo *aval);
void liberaPopulacao(Individuo* populacao,int tamPopulacao);
void crossOver(Individuo* aval,int indexFilho,int indexFilho2,int indexPai1,int indexPai2);
int torneioEstocastico(Individuo *aval);
int roleta(Individuo *aval);
void roletaSemRepeticao(Individuo *populacao,int *pai1,int *pai2);
int calculafitnessAcumulado(Individuo *aval);
void exibeFitness(Individuo *aval);
float calculaFitnessTeste(Gene *regra,Individuo *base, int Classe);
