#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include <algorithm>
#include "sommet.h"

Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}

void Sommet::ajouterVoisin(const Sommet* voisin)
{
    m_voisins.push_back(voisin);
}

void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;

}

void Sommet::afficherVoisins() const
{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::unordered_set<std::string> marquage;
    std::queue<const Sommet*> file;

    marquage.insert(this->m_id);

    file.push(this);

    while (!file.empty())
    {
        const Sommet* S = file.front();

        file.pop();

        for(int x =0; x<S->m_voisins.size(); ++x)                       //On balaye les voisins du sommet S
        {
            if (marquage.find(S->m_voisins[x]->m_id)==marquage.end())   //Si le sommet n'est pas decouvert
            {
                file.push(S->m_voisins[x]);                             //Alors ajouts des voisins dans la file

                marquage.insert(S->m_voisins[x]->m_id);                 //On marque l'id du sommet voisin en l'inserant dans une unordered set

                l_pred.insert({S->m_voisins[x]->m_id, S->m_id});        //On isnert l'id du nouveau sommet et du sommet predecesseur
            }
        }
    }

    return l_pred;
}

std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const
{
    std::unordered_map<std::string,std::string> l_pred;

    std::unordered_set<std::string> marquage;
    std::stack<const Sommet*> pile;

    marquage.insert(this->m_id);

    pile.push(this);

    while (!pile.empty())
    {
        const Sommet* S = pile.top();

        pile.pop();

        for(int x =0; x<S->m_voisins.size(); ++x)                       //On balaye les voisins du sommet S
        {
            if (marquage.find(S->m_voisins[x]->m_id)==marquage.end())   //Si le sommet n'est pas decouvert
            {
                pile.push(S->m_voisins[x]);                             //Alors ajouts des voisins dans la pile

                marquage.insert(S->m_voisins[x]->m_id);                 //On marque l'id du sommet voisin en l'inserant dans une unordered set

                l_pred.insert({S->m_voisins[x]->m_id, S->m_id});        //On isnert l'id du nouveau sommet et du sommet predecesseur
            }
        }
    }

    return l_pred;
}

std::unordered_set<std::string> Sommet::rechercherCC() const
{
    std::unordered_set<std::string> cc;
    std::cout<<"rechercherCC a coder"<<std::endl;
    return cc;
}

Sommet::~Sommet()
{
    //dtor
}
/*
///Sous programme qui compare les coordonées Y  return true si a < b
bool Fonctinf(Environnement* a, Environnement* b)
{
    return (a->getCoords().getY()<b->getCoords().getY());
}

///Méthode de trie en utilisant la fonction std::sort de la bibliothque <algorithm>
///Trie par ordre croissant le vecteur m_objet du début à la fin
void Sommet::trier()
{
    std::sort(m_voisins.begin(), m_voisins.end(), Fonctinf);
}*/
