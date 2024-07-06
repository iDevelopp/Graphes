Bibliothèque C sur l'algorithmique des graphes.
https://langevin.univ-tln.fr/cours/graphe/graphe.html

ASTUCES: 
shellcheck
valgrind
indent -kr toto.c

make -n
grep -ri MAX_INT --include='*.c' ~


IMPLEMENTE: 
MAC: 
source setup_fish.sh
export GRAPHE=$(pwd)
echo $GRAPHE

FEDORA: 
source setup.sh

EN CAS DE PROBLEME : make clean dans lib puis make

sous fish ! 
set -x GRAPHE $(pwd)


