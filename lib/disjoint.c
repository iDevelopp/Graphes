#include "disjoint.h"


// Fonction pour créer un singleton
ed singleton(int n){
  ed res= malloc(sizeof(emred));
	res->num=n;
	res->rep=res; // Chaque singleton est son propre représentant
return res;
}

// Fonction pour trouver le représentant d'un ensemble
ed repres(ed e){
	while(e->rep!=e)
		e=e->rep;
	return e;
}

// Fonction pour réunir deux ensembles (représentants)
void reunion(ed x, ed y){
	// x et y sont des représentants d'ensembles à fusionner
	//x et y sont des rep #
	y->rep=x; // Le représentant de y devient x
}

int nbcomposante(graphe g){
	ed t[g.nbs], ri, rj;
	int s;
	for(s=0; s<g.nbs; s++)        // n
			t[s] = singleton(s);
	int p = g.nbs;
	int i,j;
	for (i=0; i<g.nbs; i++)
		for(j=0; j<g.nbs; j++)
			if(g.mat[i][j]){
				ri=repres(t[i]);
				rj=repres(t[j]);
        if (ri!=rj){
          reunion(ri,rj);
          p=p-1;
        }
			}
	return p;
}
