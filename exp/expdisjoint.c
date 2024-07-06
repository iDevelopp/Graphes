#include <stdio.h>
#include "init.h"
#include "graphe.h"
#include "disjoint.h"
#include <unistd.h>


int doit(int n){
  disjoint *table=calloc(n, sizeof(disjoint));
  int i;
  //srandom(time(NULL));
  for(i=0;i<n;i++)
    table[i]=singleton(i);
  int m=0, p=n;
  while(p>1){
    int x=random()%n;
    int y=random()%n;
    m=m+1;
    disjoint rx=repres(table[x]);
    disjoint ry=repres(table[y]);
    if (rx != ry){
      reunion(rx, ry); p=p-1;
    }
  }
  //printf("%d %d \n", n,m);
  for(i=0;i<n;i++) free(table[i]);
  free(table);
  return m;
}

int main(int argc, char* argv[]){

  int n, r;
  int opt; //va stocker l'option
  //getopt(argc, argv,"n:r:h") renvoie la prochaine option dans argv et stocke le charactère dans opt
  while((opt = getopt(argc, argv,"n:r:h"))!=-1){
    switch (opt){
      case 'n':
        n = atoi(optarg);//argument converti et stocké
        break;
      case 'r':
        r = atoi(optarg);
        break;
      case 'h':
        printf("Expérience numérique: Nombre d’arêtes et connexité. On évalue les cances pour un graphe d'ordre n d'être connexe en considérant uniquement le nombre de ces arêtes.");
        exit(0);
      //h est une option sans argument car reference à help
    }
  }

  int i;
  float mu=0;
  for(i=0;i<r;i++)
      mu+=doit(n);
  mu=mu/r;
  printf("%d %.2f\n",n,mu);

  return 0;
}
