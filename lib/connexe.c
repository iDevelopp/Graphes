#include "connexe.h"
#include <stdint.h>
#include <stdlib.h>

int nbConnexe(graphe G){
  int* visit=calloc(G.nbs, sizeof(int));
  int s;
  for( s=0;s<G.nbs;s++)
    visit[s]=0;
  int p=0;
  for( s=0;s<G.nbs;s++){
    if(visit[s]==0){
      PPrec(s,G,visit);
      p=p+1;
    }

  }
  free(visit);
  return p;
};



void PPrec(int s, graphe G, int v[]) {
  v[s]=1;
  for(int t=s+1; t<G.nbs;t++){
    if(G.mat[s][t] && +v[t] == 0 )
      PPr(t,G,v); // à vérifier
  }
};


void PPr(int s, graphe G, int v[]) {
    v[s] = 1;
    liste aux = G.adj[s];
    while (aux) {
        if (v[aux->num] == 0)
            PPrec(aux->num, G, v);
        aux = aux->suiv;
    }
} // par adj



/*

graphe CCGC(int n) {
  graphe res;
  int m = n * (n - 1) / 2;
  uint64_t nbg = ((uint64_t)1) << m; //nb de graphe
  //fabrication fondamental des tableaux tau et sigma
  int* t = tau(n); //précalcul
  int* sigmaT = sigma(n);
  char* visit = (char*)malloc(nbg); //nb de composantes connexes
  uint64_t p = 0;
  for (int g = 0; g < nbg; g++) {
    if (visit[g] == 0) {
      PP(g, sigmaT, t, visit); //parcours en profondeur
      p++;
    }
  }
  free(visit);
  free(t);
  free(sigmaT);
  return res; // Assurez-vous de retourner un objet graphe ici
}

*/
/*
PP(g, sigma, tau)
pile p <- vide
visit[s]<- 1
empiler(g)
tant que non vide(p):
  x<- depiler()
  y<- action(sigma, x);   | y<-action(tau,x)
  si visit[y] alors       | si visit[y] alors
      visit[y] <- 1       |     visit[y] <- 1
      empiler(y)          |     empiler(y)
//temps de calcul en fct de n : 2C{_n}{^2}(n) + 2*2^(2C{_n}{^2})
*/

uint64_t action( int*s, uint64_t x){
  uint64_t y=0;
  while(x){
    if (x&1)
      y|= ((uint64_t)1) << 1;
    x=x>>1;
  }
  return y;
}
/*
builtin function de gcc
*production d'un mot
* le plus petit bit allumé
*/
