#include "acm.h"
#include<math.h>

float dist(point A, point B);
void trierTableauAretes(arete* a, int n);
void dessinerACM(graphe G, nuage t, const char *nom);

//void dessinerAC_N(graphe G, nuage N);


/*On va creer un nuage d'aretes  et les tirer par poids croissant.
  Ces aretes vont former E, une partie de l’ensemble des aretes
  d’un arbre couvrant minimal Y.
  S'il existe une xy une arete traversante (coupe du graphe respectant E)
  nous allons nous servir de la structure d'ensemble disjoint
  pour créer le graphe couvrant minimum (ACM).
  */

  /*Le graphe va servir à positionner les arêtes,
  et le nuage à positionner les points à des endroits
  géographiques précis.*/



graphe Kruskal(nuage N){

  int n=N.nbp;

  //-> faire un tableau d'arêtes
  arete* a=calloc(n*(n-1)/2, sizeof(arete));
  int k=0;
  for(int i=0; i<n-1; i++){
    for(int j=i+1; j<n; j++){
      a[k].i = i;
      a[k].j = j;
      a[k].w = dist(N.pts[i], N.pts[j]);
      k++;
    }
  }

  trierTableauAretes(a, n*(n-1)/2);

  graphe acm = initgraphe(n);
  // Init  d'une structure d'ensemble disjoint sur les n sommets
  ed* data = (ed*)malloc(n * sizeof(ed));
  // On réalise un tableau de points representant vers eux-même (singleton)
  for (int i=0; i<n; i++)
      data[i] = singleton(i);

  /* Les aretes de l’arbre sont decouvertes de proche en proche.
     Les aretes sont parcourues par poids croissant. */
  
  int p=N.nbp;
  k=0;
  while(p>1){ 
    //-> tester l'arête k 
    ed r = repres(data[a[k].i]);
    ed s = repres(data[a[k].j]);
    if (r!=s){
      /* Dans cet ordre, si une arete xy reliant deux classes distinctes
      est ajoutee a l’arbre couvrant.
      Pour que l'ajout de cette arrete ne forme pas de cycle
      dans l'ACM, reunion précède l'ajout. */
      ajouterArete(acm, r->num, s->num);
      reunion(r, s);
      p--;
    }
    k++;
  }
  free(data);
  return acm;
}




//calcul la distance euclidienne entre deux coordonnées de points
float dist(point A, point B){
  float r = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
  return r;
}



void trierTableauAretes(arete* a, int n){
  //-> Trier le tableau d'arêtes
  for(int i=0; i<n-1; i++){
    int idx = i;
    for(int j=i+1; j<n; j++){
      //compare les poids des aretes
      if(a[idx].w > a[j].w)
        idx = j;
    }//fin boucle for
    //si minimum, echange
    if(idx != i){
      arete tmp = a[i];
      a[i] = a[idx];
      a[idx] = tmp;
    }
  }//fin du tri selection
}




void dessinerACM(graphe G, nuage t, const char *nom){
  FILE *dst = fopen(nom, "w");
  if (dst == NULL) {
    perror("dessinerACM() dans acm.c -> erreur");
    perror("Impossible d'écrire le fichier DOT");
    exit(1);
  }

  //ÉCRITURE DES POINTS DU NUAGE
  fprintf(dst, "graph  { \n node [shape=circle];\n");
  for(int i=0; i<t.nbp; i++){
    printf("node %d [pos=\"%f,%f\"];\n", i+1, t.pts[i].x, t.pts[i].y);
  }

  //DESSINER LES ARETES DU GRAPHE
  for (int i = 0; i < G.nbs; i++) {
    for (int j = i+1; j < G.nbs; j++) {
      if (G.mat[i][j]) {
        fprintf(dst, " %d -- %d \n", i, j);
      }
    }
  }

  fprintf(dst, "}\n");
  fclose(dst);


  //CONVERSION EN IMAGES
  char commande[100];
  snprintf(commande, sizeof(commande), "dot -Tpng -Kfdp  %s -o graphe.png", nom);
  int result = system(commande);

  if (result == 0) {
      printf("La conversion en PNG a réussi.\n");
      //system("open graphe.png"); // Sur macOS
      system("xdg-open graphe.png"); // Sur Linux
  } else {
      printf("dessiner() dans graphe.c -> erreur");
      printf("La conversion en PNG a échoué.\n");
  }

}