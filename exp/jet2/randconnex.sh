#!/bin/bash

if [ $# -lt 2 ]; then
    echo "parametre manquant"
    exit
fi
nmax=$1
pas=$2
for((n=1; n<nmax; n+=pas))
  do
    ./expdisjoint.out $n 10
  done > randconnexe.dat
gnuplot randconnexe.plt
