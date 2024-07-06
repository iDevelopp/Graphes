#!/bin/bash

# Obtient le chemin absolu du répertoire 'graphe'
export GRAPHE=$(pwd)

# Configure l'alias 'mkgraphe' dans le .bashrc
echo "alias mkgraphe=\"make -C $GRAPHE/lib\"" >> ~/.bashrc

# Charge le .bashrc pour activer les modifications
source ~/.bashrc

echo "Répertoire 'graphe' a été référencé dans bashrc avec succès."
#on execute ce fichier avec source dans le terminal, chmod +x aussi avant
