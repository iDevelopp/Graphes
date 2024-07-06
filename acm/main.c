#include "acm.h"
#include "nuage.h"

int main(int argc, char** argv){  
  if (argc<2){
    printf("La taille du nuage doit être passé en paramètre !\n");
    exit(1);
  }
  int n = atoi(argv[1]);
  
  nuage N = CreerNuage(n);
  AfficherNuage(N);
  graphe K = Kruskal(N);
  dessinerACM(K, N, "nom_du_fichier.dot");

  free(N.pts);
  freeGraphe(K);

  return 0;
}
