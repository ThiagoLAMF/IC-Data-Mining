#define TOTAL_INDIVIDUOS_ARQUIVO 358

#define TAM_POPULACAO 50
#define TAM_POPULACAO_TOTAL 100 // TAM_POPULACAO + Quantidade de filhos
#define TAM_INDIVIDUO 34

#define P_MUTACAO_POR_CAMPO 30 //Porcentagem mutacao por campo
#define N_GERACOES 2
#define N_FILHOS 50

#define myrand ((float)(rand())/(float)(RAND_MAX) ) //macro myrand: gera numeros float entre 0 e 1
#define DIFERENTE 0
#define IGUAL 1
#define MENOR 2
#define MAIORIGUAL 3



typedef struct gene Gene;

struct gene
{
    float peso;
    int operador;//aleatorio
    int valor;
};
struct individuo
{
    Gene *gen;
    float fitness;
    float fitnessAcumulado;
};

typedef struct individuo Individuo;

int calculaAvaliacao(Individuo *ind, Individuo *aval, int Classe);
void exibeGenes(Gene *gen);
void exibeDataMining(Individuo *ind,int tam_pop,int exibeClasse);
Individuo* iniciaPopulacao(int tamPopulacao);
void carregaArquivo(Individuo *ind);
void carregaPopulacao(Individuo *aval);
void crossOver(Individuo* aval,int indexFilho,int indexFilho2,int indexPai1,int indexPai2);
int torneioEstocastico(Individuo *aval);
int roleta(Individuo *aval);
int* roletaSemRepeticao(Individuo *aval);
int calculafitnessAcumulado(Individuo *aval);
void exibeFitness(Individuo *aval);
