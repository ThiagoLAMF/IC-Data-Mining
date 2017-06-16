#define TOTAL_INDIVIDUOS 358
#define TAM_INDIVIDUO 34


#define DIFERENTE 1
#define IGUAL 2
#define MENOR 3
#define MAIORIGUAL 4
#define myrand ((float)(rand())/(float)(RAND_MAX) ) //macro myrand: gera numeros float entre 0 e 1

struct gene
{
    float peso;
    int operador;//aleatorio
    int valor;
};

typedef struct gene Gene;

struct individuo
{
    Gene *gen;
};

typedef struct individuo Individuo;

int calculaAvaliacao(Individuo *ind, Individuo *aval, int Classe);
void exibeGenes(Gene *gen);
void exibeDataMining(Individuo *ind,int tam_pop,int exibeClasse);
Individuo* iniciaPopulacao(int tamPopulacao);
void carregaPopulacao(Individuo *ind);
void carregaPopulacao2(Individuo *aval);
void crossOver(Individuo* ind);