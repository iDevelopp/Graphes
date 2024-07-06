#include "nuage.h"

nuage CreerNuage(int n){

  srand(time(NULL));
  nuage r;
  r.nbp = n;
  r.pts = calloc(n, sizeof(point));

  for(int i=0; i<n; i++){
    r.pts[i].x = (float)rand()/(float)(100);
    r.pts[i].y = (float)rand()/(float)(100);
  }

  return r;
};

void AfficherNuage(nuage t){
  int n = t.nbp;
  for(int i=0; i<n; i++){
    printf("%f %f\n", t.pts[i].x, t.pts[i].y);
  }
};
