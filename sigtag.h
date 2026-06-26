#ifndef SIGTAG_H
#define SIGTAG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* DEFINIÇÕES GERAIS */
#define MAX_NOME       100
#define MAX_LOCAL      100
#define MAX_MINERAL    50
#define MAX_NOS_GRAFO  20
#define MAX_AMOSTRAS   200
#define NUM_OPCOES     13

/* ESTRUTURA: AMOSTRA GEOLÓGICA */
typedef struct {
    int    codigo;
    char   nome[MAX_NOME];
    char   local_extracao[MAX_LOCAL];
    char   mineral[MAX_MINERAL];
    float  teor;          /* teor mineral em % */
    int    prioridade;    /* 1=alta, 2=media, 3=baixa */
    char   data[12];      /* DD/MM/AAAA */
} Amostra;

/* BST — ÁRVORE BINÁRIA DE BUSCA */
typedef struct NoBST {
    Amostra        amostra;
    struct NoBST  *esq;
    struct NoBST  *dir;
} NoBST;

/* AVL — ÁRVORE AVL */
typedef struct NoAVL {
    Amostra        amostra;
    struct NoAVL  *esq;
    struct NoAVL  *dir;
    int            altura;
} NoAVL;

/* GRAFO — REDE LOGÍSTICA */
typedef enum { EXTRACAO, LABORATORIO, EXPORTACAO } TipoPonto;

typedef struct {
    int       id;
    char      nome[MAX_NOME];
    TipoPonto tipo;
} Ponto;

typedef struct {
    int origem;
    int destino;
    int peso;   /* distância em km */
} Aresta;

typedef struct {
    Ponto  pontos[MAX_NOS_GRAFO];
    int    adj[MAX_NOS_GRAFO][MAX_NOS_GRAFO]; /* -1 = sem ligação */
    int    num_pontos;
    int    num_arestas;
} Grafo;

/* SISTEMA DE MENU ADAPTATIVO */
typedef struct {
    int  id;
    char descricao[MAX_NOME];
    int  usos;
} OpcaoMenu;

typedef struct {
    OpcaoMenu opcoes[NUM_OPCOES];
} MenuAdaptativo;

/* ESTADO GLOBAL DO SISTEMA */
typedef struct {
    NoBST        *raiz_bst;
    NoAVL        *raiz_avl;
    Grafo         grafo;
    MenuAdaptativo menu;
    Amostra       lista[MAX_AMOSTRAS];  /* lista plana p/ ordenação */
    int           total_amostras;
    long long     comp_bst;   /* contadores de desempenho */
    long long     comp_avl;
    long long     comp_bubble;
    long long     comp_selection;
    long long     trocas_bubble;
    long long     trocas_selection;
} Sistema;

/* PROTÓTIPOS — BST */
NoBST* bst_inserir(NoBST *raiz, Amostra a, long long *comp);
NoBST* bst_buscar(NoBST *raiz, int codigo, long long *comp);
NoBST* bst_remover(NoBST *raiz, int codigo, long long *comp);
void   bst_emordem(NoBST *raiz, Amostra *out, int *idx);
void   bst_destruir(NoBST *raiz);

/* PROTÓTIPOS — AVL */
NoAVL* avl_inserir(NoAVL *raiz, Amostra a, long long *comp);
NoAVL* avl_buscar(NoAVL *raiz, int codigo, long long *comp);
NoAVL* avl_remover(NoAVL *raiz, int codigo, long long *comp);
void   avl_emordem(NoAVL *raiz, Amostra *out, int *idx);
void   avl_destruir(NoAVL *raiz);
int    avl_altura(NoAVL *no);

/* PROTÓTIPOS — ORDENAÇÃO */
void bubble_sort_teor(Amostra *arr, int n, long long *comp, long long *trocas);
void selection_sort_prioridade(Amostra *arr, int n, long long *comp, long long *trocas);

/* PROTÓTIPOS — GRAFO */
void grafo_init(Grafo *g);
int  grafo_add_ponto(Grafo *g, const char *nome, TipoPonto tipo);
void grafo_add_aresta(Grafo *g, int orig, int dest, int peso);
void grafo_dijkstra(Grafo *g, int origem, int destino, int *caminho, int *tam_caminho, int *distancia);
void grafo_imprimir(Grafo *g);

/* PROTÓTIPOS — MENU */
void menu_init(MenuAdaptativo *m);
void menu_registar_uso(MenuAdaptativo *m, int id);
void menu_ordenar(MenuAdaptativo *m);
void menu_exibir(MenuAdaptativo *m);

/* PROTÓTIPOS — SISTEMA */
void sistema_init(Sistema *s);
void sistema_popular_demo(Sistema *s);
void sistema_executar(Sistema *s);
void sistema_inserir_amostra(Sistema *s);
void sistema_buscar_amostra(Sistema *s);
void sistema_remover_amostra(Sistema *s);
void sistema_listar_inorder(Sistema *s);
void sistema_ordenar_bubble(Sistema *s);
void sistema_ordenar_selection(Sistema *s);
void sistema_comparar_arvores(Sistema *s);
void sistema_comparar_ordenacao(Sistema *s);
void sistema_add_ponto_grafo(Sistema *s);
void sistema_calcular_rota(Sistema *s);
void sistema_sugerir_estrutura(Sistema *s);
void sistema_ver_estatisticas(Sistema *s);

/* PROTÓTIPOS — FICHEIROS */
int  ficheiro_ler_amostras(const char *caminho, Amostra *arr, int max);
void ficheiro_ler_grafo(const char *caminho, Grafo *g);
void ficheiro_escrever_relatorio(const char *caminho, Sistema *s);

/* UTILITÁRIOS */
void limpar_tela(void);
void pausar(void);
void imprimir_separador(const char *titulo);
void imprimir_amostra(const Amostra *a);
int  ler_inteiro(const char *prompt, int min, int max);
float ler_float(const char *prompt, float min, float max);
void ler_string(const char *prompt, char *dest, int tam);

#endif /* SIGTAG_H */
