#include <stdio.h>
#include <stdint.h>
#include "graphe.h"
#include "init.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void minilire ( const char * src ){

    FILE *file = fopen(src, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int nbs, x, y;
    while ( 0 == fscanf(file, "nbs=%d", &nbs ) )
        fgetc( file );
    printf ("ordre=%d\n", nbs );
    // allocation
    while(! feof( file) ) {
        if ( fscanf(file, "%d%d", &x, &y ) > 1 )
            printf ("x=%d y=%d\n", x, y );
        else fgetc( file );
    }

    fclose(file);
}



void ajouterArete(graphe G, int i, int j) {
  // Verifie que G est un pointeur valide vers le graphe
  if (i < 0 || j < 0 || i >= G.nbs || j >= G.nbs) {
    fprintf(stderr, "Erreur : Sommets invalides ou graphe NULL.\n");
    exit(EXIT_FAILURE);
  }

  if (G.mat[i][j] == 0 && G.mat[j][i] == 0) {
    //l'arête n'existe pas encore, on l'ajoute
    G.mat[i][j] = 1;
    G.mat[j][i] = 1;
  } else {
    //Si l'arête existe déjà, erreur fichier
    fprintf(stderr, "Erreur fichier : L'arête entre les sommets %d et %d existe déjà.\n", i, j);
  }
}


graphe lireGraphe(const char *nom) {
  FILE* source;
  source = fopen(nom, "r");
  if (source == NULL) {
    printf("lireGraphe() dans graphe.c erreur");
    printf("problème nom fichier à lire");
    perror(nom);
    exit(1);
  }
  graphe res; // Initialisez res à NULL pour éviter des problèmes de libération mémoire
  int n; // Déclaration de 'n' pour la taille du Graphe
  int i, j; // Déclaration de 'i' et 'j' pour sscanf

  char buffer[1024];
  while (fgets(buffer, 1024, source)) {
    switch (buffer[0]) {
      case 'n':
        if (sscanf(buffer, "nbs=%d", &n) == 1) { // sscanf pour la taille du graphe 'n'
          res = initgraphe(n);
        }
        break;
      case '#': break;
      default:
        if (sscanf(buffer, "%d %d", &i, &j) == 2) { // sscanf pour récuperer 'i' et 'j'
          // Ajoutez une arête au graphe 'res'
          ajouterArete(res, i, j);
        }
        break;
    }
  }
  fclose(source);
  return res;
}


void dessiner(graphe G, const char *nom){


  //ÉCRITURE DES POINTS DANS UN FICHIER
  FILE *dst = fopen(nom, "w");
  if (dst == NULL) {
    perror("dessiner() dans graphe.c -> erreur");
    perror("Impossible d'écrire le fichier DOT");
    exit(1);
  }
//digraph pour doubler les arcs, ici c'est des aretes donc juste graph
  fprintf(dst, "graph {\n"); // equivalent à fputs

  for (int i = 0; i < G.nbs; i++) {
    for (int j = i+1; j < G.nbs; j++) {
      if (G.mat[i][j]) {
        fprintf(dst, "%d -- %d ;\n", i, j);
      }
    }
  }

  fprintf(dst, "}\n");
  fclose(dst);

  //CONVERSION EN IMAGES

  char commande[100];
  snprintf(commande, sizeof(commande), "dot -Tpng %s -o graphe.png", nom);
  int result = system(commande);

  if (result == 0) {
      printf("La conversion en PNG a réussi.\n");
      system("open graphe.png"); // Sur macOS
      // system("xdg-open graphe.png"); // Sur Linux
  } else {
      printf("dessiner() dans graphe.c -> erreur");
      printf("La conversion en PNG a échoué.\n");
  }

}


void dessinerMaison() {


  FILE *dst = fopen("maison.dot", "w");
  if (dst == NULL) {
    perror("dessinerMaison() dans graphe.c -> erreur");
    perror("Impossible d'ouvrir le fichier DOT");
    exit(1);
  }

  fprintf(dst, "graph Maison {\n"); // equivalent à fputs

  //Carré pour le corps de la maison
  fprintf(dst, "a -- b -- c -- d -- a;\n");
  // Toit en forme de triangle
  fprintf(dst, "a -- e -- b;\n");
  fprintf(dst, "b -- f -- c;\n");
  fprintf(dst, "c -- g -- d;\n");
  // Porte
  fprintf(dst, "e -- h [label=\"Porte\"];}\n");
  fclose(dst);

  int result = system("dot -Tpng maison.dot -o maison.png");

  if (result == 0) {
      printf("La conversion en PNG a réussi.\n");
      //system("open maison.png"); // Sur macOS
      system("xdg-open graphe.png"); // Sur Linux
  } else {
      printf("dessinerMaison() dans graphe.c -> erreur");
      printf("La conversion en PNG a échoué.\n");
      exit(1);
  }
}


void freeGraphe(graphe G) {
  int i;
  liste aux;
  for (i = 0; i < G.nbs; i++) {
    free(G.mat[i]);
  }
  free(G.mat);

  for (i = 0; i < G.nbs; i++) {
    aux = G.adj[i];
    while (aux) {
      liste suivant = aux->suiv;
      free(aux);
      aux = suivant;
    }
  }
  free(G.adj);
}

graphe randGraphe(int n, float p) {
  srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
  int s = p * RAND_MAX;
  graphe g = initgraphe(n);
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (rand() <= s) {
        g.mat[i][j] = g.mat[j][i] = 1;
      }
    }
  }
  return g;
}

void afficherGraphe(graphe *g) {
    int i, j;
    for (i = 0; i < g->nbs; i++) {
        for (j = 0; j < g->nbs; j++) {
            printf("%d ", g->mat[i][j]);
        }
        printf("\n");
    }
}

int degre(int s, graphe *G) {
    // Vérifier si le sommet est valide
    if (s < 0 || s >= G->nbs) {
        fprintf(stderr, "fonction degre() dans graphe.c\n");
        fprintf(stderr, "Sommet invalide : %d\n", s);
        exit(1);
    }

    int degre = 0; // Initialisation du degré à zéro


    for (int i = 0; i < G->nbs; i++) {
        if (G->mat[s][i]) { // Parcours de la ligne correspondant au sommet s dans la matrice d'adjacence
            degre++; //compte le nombre de connexion
        }
    }

    return degre;
}




/*

Fonction qui construit un hypercube de dimension m

Rappel, ordre := 2^m eq 1<<m, S={0,1,2,3,...,2^m-1}
Deg(G) = m


Exemple: 
Pour G(3), on a:

110   ----------  111
     /|       /|
    / |      / |
010 ---------| | 011
    | |------|-|  
    | /100   | / 101
    |/       |/
    L--------|
000           001


 000 ^ 001


           000
          /\  \    
         /  \  \    
      100  010  001  
       /\    \        
      /  \    \        
    110   101  011   
    / 
   / 
  111


*/


int hammingweight(int i){
  int cpt=0, p;
  while (i!=0){
    p=i&1;
    if(p==1){
      cpt++;
    }
    i=i>>1;
  }
  return cpt;
}


graphe hypercube (int m){
  int nbSommet = 1<<m;
  graphe hcp = initgraphe(nbSommet);
  int i,j;
  for(i=0; i< hcp.nbs; i++){
    for(j=0; j< hcp.nbs; j++){
        if(hammingweight(i^j)==1){
          ajouterArete(hcp,i,j);
        }
    }
  }

  return hcp;
}


graphe complement(graphe* g){
  // Créer un nouveau graphe avec le même nombre de sommet que g.
  // i) même sommet
  // ii) Les arêtes ij de G ne sont pas une arête du complément et réciproquement.
  
  graphe compl = initgraphe(g->nbs);
  int i,j;
  for(i=0; i < g->nbs; i++){
    for(j=0; j < g->nbs; j++){
      if(g->mat[i][j]==0){
        ajouterArete(compl, i, j);
      }
    }
  }

  return compl;
}




// Retourne le nbr de k coloration de g
int coloration(int k, graphe g){
  int res=0;
  // Allocation tableau de couleur
  char* f=calloc(g.nbs, sizeof(int));
  // Fonction recursive qui retourne le nbr de k colorations dans res
  compte(0, &g, k, f, &res);
  free(f);
  return res;
}

void compte(int s, graphe* g, int k, char f[], int* cpt){

  int mark[k];

  // Condition d'arret, fin de recurisivité
  if(s==g->nbs){ 
    *cpt = *cpt+1;
    return; // Toutes les colorations sont attribués, fin
  }

  int i;

  // Init le tableau de marquage à 0: toutes les couleurs sont disponibles
  for(i=0;i<k;i++) mark[i]=0;

  // Pour tous les sommets plus petit que le sommet actuel
  for(int t=0;t<s;t++)
    if(g->mat[s][t]) // si s adjacent à t, déjà coloré
      mark[f[t]]=1; // on marque l'arrete
  
  // Explore les colorations possibles
  for(i=0; i<k; i++){
    if(mark[i]==0){ // si la couleur n'est pas utilisé
      f[s]=i; // on l'attribut au sommet
      compte(s+1,g,k,f,cpt); // continuer sur les sommets suivants
    }
  }


}


/*
Remarque :
    -  Le critère d'arret risque de ne pas fonctionner si le graphe n'est pas connexe, 
       il faut anticiper !
    -  Si ma fonction qui doit choisir un point s'arrete à un pt qui n'est pas définit, 
       cela veut dire qu'il n'était pas connecté !
*/



// Cherche le chemin le plus court entre a et b dans un graphe pondéré
void DIJKSTRA(int a, int b, graphe g){
  /*
    est[] := ensemble pour stocker les estimations de nos distances d'un départ à une arrivé
    visit[] := ensemble qui repère les sommets qui ont deja été marqué
    res[] := ensemble pour stocker notre 
  */
  
	int est[g.nbs], visit[g.nbs], res[g.nbs];
  int s, cpt=0;
	
  // Init les tableaux
  for(s=0;s<g.nbs;s++){
    est[s] = INT64_MAX; // Init la distance comme étant maximum.
    res[s] = -1;  
    visit[s] = 0; // non visité
  }
	est[a]=0; // AKA dist du sommet A vers lui même  

	/* 
    On regarde tous les points.
    Tous ceux qui n'ont pas été sélectionné, 
    on cherche la bonne estimation, et si on trouve un minimum
    on le marque et le met à jour.
  */
	while(cpt<g.nbs){
		s = choisir(est, visit, g); // Choisi le point qui minimise le chemin
		miseajour(s, est, res, g, visit);  
		cpt=cpt+1;
	}
	
  //On affiche le bon chemin
	for(s=b; s>=0; s=res[s])
    printf('%d',s);
	
}

//Choisi le pt qui minimise parmi ceux qui n'ont pas été choisi
int choisir(int est[], int v[], graphe g){
	int score = INT64_MAX, res = -1, s;

  /*
    On parcours tous les sommets.
    Si s n'a pas été marqué et que son estimation est plus faible que le score.
    Alors s devient le minimum et on met à jour le score.
  */
  
	for(s=0; s < g.nbs; s++){
		if(!v[s]<0 && score > est[s]){
			score = est[s];
      res=s;	
		}	
	}
  return s; // On retourne le point qui qui minimise le chemin
}


void miseajour(int s, int est[], int res[], graphe g, int v[]){
	int t;
  // Parcours tous les sommets 
	for( t=0; t<g.nbs; t++){
    // Si t n'a pas été visité, que s et t sont adjacent par une arete...
		if(!v[t] && g.mat[s][t] && est[t] >= est[s] + g.mat[s][t]){
			est[t]=est[s]+g.wt[s][t];                                       //mij du cout pr le chemin vers t en passant par s 
			res[t]=s;                                                      // On marque ce nv chemin optimal
		}
		v[s]=1;                                                         // On marque le sommet désormais visité
	}
}