#include "graphe.h"
#include "init.h"

typedef unsigned char uchar;

graphe initgraphe(int n){
  graphe res;
  res.nbs=n;
  res.mat=calloc(n,sizeof(uchar*));
  int i;

  for(i=0;i<n;i++)
    res.mat[i]=calloc(n,sizeof(uchar));

  res.adj = calloc(n,sizeof(liste));
  return res;
}
