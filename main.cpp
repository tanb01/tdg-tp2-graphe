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
    graphe g{"graphe_1.txt"};
    g.afficher();
    g.afficherBFS("1");
    g.afficherDFS("1");
    int ncc=g.rechercher_afficherToutesCC();
    std::cout<<"le graphe est-il eulerien ? a coder ..."<<std::endl<<std::endl;
    return 0;
}
