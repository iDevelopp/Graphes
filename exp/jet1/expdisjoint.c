#include <stdio.h>
#include "init.h"
#include "graphe.h"
#include "disjoint.h"


int main(int argc, char* argv[]){

  if(argv[1]==0){
    perror("expdisjoint.c, argv[1] manquant");
    return 1;
  };
  int n=atoi(argv[1]);


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
  printf("%d %d \n", n,m);
  for(i=0;i<n;i++) free(table[i]);
  free(table);
  return 0;
}
