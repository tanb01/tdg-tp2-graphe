
/*****************************************************
**   Programmeurs : CADOT Léonie et TAN Benjamin    **
**                  17 MARS 2019                    **
*****************************************************/

///Ce TP a ete realise dans le but de decouvrir la Theorie des graphes

#include <iostream>
#include "graphe.h"
#include <unordered_map>
#include <unordered_set>

int main()
{
    std::string idsommet= "1";

    graphe g{"graphe_2.txt"};
    g.afficher();

    std::cout<<"Saisir un sommet pour appliquer BFS et DFS: ";
    std::cin>>idsommet;

    //Blindage
    while(g.verifieId(idsommet)!=1)
    {
        std::cout<<"Veuillez resaisir un sommet pour appliquer BFS et DFS: ";
        std::cin>>idsommet;
    }

    g.afficherBFS(idsommet); //Appel méthode pour afficher le BFS
    g.afficherDFS(idsommet); //Appel méthode pour afficher le DFS
    int ncc=g.rechercher_afficherToutesCC(); //Appel méthode pour rechercher et afficher toutes les comosantes connexes

    int resultat=g.isEulerien(); //Appel méthode qui nous dit si présence d'un cycle, d'une chaine ou rien d'eulérien
    if (resultat==0)
    {
        std::cout<<"Le graphe n'admet rien d'eulerien"<<std::endl;
    }
    else if (resultat==1)
    {
        std::cout<<"Le graphe admet une chaine eulerienne"<<std::endl;
    }
    else
    {
        std::cout<<"Le graphe admet un cycle eulerien"<<std::endl;
    }
    return 0;
}
