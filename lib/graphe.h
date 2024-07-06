#ifndef GRAPHE_H
#define GRAPHE_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef unsigned char nchar;

typedef struct liste{
  int num;
  struct liste* suiv;
}enrlist, *liste;
//2 objets, 1 enregistrement sur une liste et une liste


typedef struct {
  int nbs; //ordre du graphe
  nchar** mat; //matrice adjacente
  liste* adj;
}graphe;


void minilire ( const char * src );
void ajouterArete(graphe G, int i, int j);
graphe lireGraphe(const char *nom);
void dessiner(graphe G, const char *nom);
void dessinerMaison();
void freeGraphe(graphe G);
graphe randGraphe(int n, float p);
void afficherGraphe(graphe *g);
int degre(int s, graphe *G);

int hammingweight(int i);
graphe hypercube (int m);

graphe complement(graphe* g);
int coloration(int k, graphe s);


void compte(int s, graphe* g, int k, char f[], int* cpt);
void DIJKSTRA(int a, int b, graphe g);
int choisir(int est[], int v[], graphe g);
void miseajour(int s, int est[], int res[], graphe g, int v[]);
//page 17, 22, 26, 31

#endif
