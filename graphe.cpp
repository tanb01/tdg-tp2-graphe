#include <fstream>
#include <iostream>
#include <queue>
#include "graphe.h"

graphe::graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
    }
}
void graphe::afficher() const
{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"  ordre : "<<m_sommets.size()<<std::endl;
    /*
    for(auto i : m_sommets)
    {
        std::cout<<i.first;
    }*/

    for (std::unordered_map<std::string, Sommet*>::const_iterator it = m_sommets.begin(); it != m_sommets.end(); ++it)
    {
        std::cout<<"  sommet :";
        it->second->afficherData();
        it->second->afficherVoisins();
        std::cout<<std::endl;
    }
}

void graphe::parcoursBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}

void graphe::afficherBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}

void graphe::parcoursDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}

void graphe::afficherDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}

int graphe::rechercher_afficherToutesCC() const
{
    int i=0;
    bool same=true;
    const Sommet* s0;
    std::unordered_set<std::string>cc;
    std::unordered_set<std::string>marquage;
    std::queue<std::string> file;

    std::cout<<"composantes connexes :"<<std::endl;

    for (const auto& s: m_sommets)
    {
        s0 = s.second;
        cc = s0->rechercherCC();

        for (const auto& c: cc)
        {
            if (marquage.find(c)!=marquage.end())
            {
                same = false;
            }
            else
            {
                file.push(c);
                marquage.insert(c);
                same = true;
            }
        }

        if (same==true)
        {
            i++;
            std::cout<<"   cc"<<i<<std::endl;
            while (!file.empty())
            {
                std::cout<<"     "<<file.front();
                file.pop();
            }
            std::cout<<std::endl;
        }
    }

    std::cout<<"nb cc :"<< i <<std::endl;

    return i;
}

graphe::~graphe()
{
    //dtor
}
