#ifndef DISJOINT_H
#define DISJOINT_H

#include "graphe.h"
// Définition de la structure ed
typedef struct ed{
	int num; // Champ pour stocker le numéro
	struct ed* rep; // Champ pour stocker le représentant de l'ensemble
}emred, *ed, *disjoint;

ed singleton(int n);
ed repres(ed e);
void reunion(ed x, ed y);
int nbcomposante(graphe g);

#endif
