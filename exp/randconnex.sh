#!/bin/bash

if [ $# -lt 2 ]; then
    echo "parametre '?'"
    exit
fi
nmax=$1
rep=$2
for((n=1; n<nmax; n++))
  do
    ./expdisjoint.out -n $n -r $rep
  done > randconnexe.dat
gnuplot randconnexe.plt
