#ifndef NUAGE_H
#define NUAGE_H
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

typedef struct{
  float x;
  float y;
}point;

typedef struct{
  point* pts;
  int nbp;
}nuage;

nuage CreerNuage(int n);
void AfficherNuage(nuage t);

#endif
