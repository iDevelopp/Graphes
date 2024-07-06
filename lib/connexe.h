#ifndef CONNEXE_H
#define CONNEXE_H

#include "graphe.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int nbConnexe(graphe G);
void PPrec(int s, graphe G, int v[]);
void PPr(int s, graphe G, int v[]);//par adj

graphe CCGC(int n);
uint64_t action( int*s, uint64_t x);

#endif
