#include <iostream>
#include "graphe.h"
#include <unordered_map>
#include <unordered_set>

/*
--> liste des sommets est stockee dans une unordered_map*/
//std::map<std::string, std::string> somMap;
//std::map<std::string, std::string>:: iterator it;

//somMap.insert(std::make_pair());

int main()
{
    std::string idsommet= "1";

    graphe g{"graphe_1.txt"};
    g.afficher();

    std::cout<<"Saisir un sommet pour appliquer BFS et DFS: ";//il faut bliner
    std::cin>>idsommet;

    g.afficherBFS(idsommet);
    g.afficherDFS(idsommet);
    int ncc=g.rechercher_afficherToutesCC();
    std::cout<<"le graphe est-il eulerien ? a coder ..."<<std::endl<<std::endl;
    return 0;
}
