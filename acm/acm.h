#ifndef ACM_H
#define ACM_H
#include "nuage.h"
#include "init.h"
#include "graphe.h"
#include "disjoint.h"


typedef struct{
  int i,j;
  float w;
}arete;

float dist(point A, point B);
void dessinerACM(graphe G, nuage t, const char *nom);
graphe Kruskal(nuage N);


#endif
