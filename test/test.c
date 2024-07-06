#include <stdio.h>
#include "init.h"
#include "graphe.h"

//dot -Tpng graphe.dot -o graphe.png

int main(){
    //int argc, char* argv[]
    //graphe g;
    //g = lireGraphe(argv[1]);
/*

    const char *nom = "/Users/ivan/Documents/L3/I51_TAG/TP/TP1/projet/data/maison.txt";
    minilire(nom);
    graphe G = lireGraphe(nom);
    dessiner(G, "graphe.dot");
    freeGraphe(G);

    dessinerMaison();
*/


/*

    int n = 5;     // Nombre de sommets
    float p = 0.2; // Probabilité de création d'une arête

    graphe g = randGraphe(n, p);

    afficherGraphe(&g);
    dessiner(g, "graphe.dot"); //export sous "graphe.dot"

*/
    const char *nom = "/home/iv/TAG/data/maison.txt";
    graphe m = lireGraphe(nom);
    int s=2;
    int degreM = degre(s, &m);
    printf("s:=%d, deg(s):=%d\n", s, degreM);
    afficherGraphe(&m);
//    freeGraphe(g);
    freeGraphe(m);


    return 0;
}
