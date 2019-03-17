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
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
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
        //lecture des ids des deux extr�mit�s
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extr�mit� � la liste des voisins de l'autre (graphe non orient�)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second); // m_sommets.find(id))->second-> = sommet*
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orient�
    }
}
void graphe::afficher() const
{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"  ordre : "<<m_sommets.size()<<std::endl;

    for (std::unordered_map<std::string, Sommet*>::const_iterator it = m_sommets.begin(); it != m_sommets.end(); ++it) // parcours de la map
    {
        // m_sommets
        std::cout<<"  sommet :";
        it->second->afficherData(); // appel des m�thodes pour affiche les donn�es et les voisins de chaque id
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
        s0 = s.second;                              //Second vaut le pointeur sur la valeur
        cc = s0->rechercherCC();                    //cc prend la liste des ids de la composante connexe du sommet (on cherche un �l�ment gr�ce � son adresse

        for (const auto& c: cc)                     //Parcours de la liste des ids de la composante connexe du sommet
        {
            if (marquage.find(c)!=marquage.end())   //Ici on v�rifie que tous les sommets ont �t� marqu�s
            {
                same = false;                       //Si on trouve le sommet alors on marque false "Trouv�"
            }
            else                                    //Sinon
            {
                file.push(c);                       //On ajoute tout les ids des sommets non marques dans la file
                marquage.insert(c);
                same = true;
            }
        }

        if (same==true)
        {
            i++;
            std::cout<<"   cc"<<i<<std::endl;
            while (!file.empty())                   //Tant que la file n'est pas vide
            {
                std::cout<<"     "<<file.front();   //On affiche le premier �l�ment de la file
                file.pop();                         //Enl�ve les �l�ments de la file
            }
            std::cout<<std::endl;
        }
    }
    std::cout<<"nb cc :"<< i <<std::endl;

    return i;
}

int graphe::isEulerien() const
{
    int i=0;
    int nB_sommet_degPair=0;
    int nB_sommet_degImpair=0;
    int nB_sommet=0;
    int nB_chaine=0;
    int nB_cycle=0;
    bool same=true;
    const Sommet* s0;
    std::unordered_set<std::string>cc;
    std::unordered_set<std::string>marquage;
    std::queue<std::string> file;
    std::string chaine=" ";

    std::cout<<"composantes connexes :"<<std::endl;

    for (const auto& s: m_sommets)
    {
        s0 = s.second;                                      //Second vaut la valeur qui est un pointeur sur un sommet
        cc = s0->rechercherCC();                            //cc prend la liste des ids de la composante connexe du sommet (on cherche un �l�ment gr�ce � son adresse

        for (const auto& c: cc)                             //Parcours de la liste des ids de la composante connexe du sommet
        {
            if (marquage.find(c)!=marquage.end())           //Ici on v�rifie que tous les sommets ont �t� marqu�s
            {
                same = false;                               //Si on trouve le sommet alors on marque false "Trouv�"
            }
            else                                            //Sinon
            {
                file.push(c);                               //On ajoute tout les ids des sommets non marques dans la file
                marquage.insert(c);
                same = true;
            }
        }

        if (same==true)
        {
            i++;
            std::cout<<"   cc"<<i<<std::endl;
            //On r�initialise les valeurs pour chaque nouvelle composante connexe
            nB_sommet_degPair=0;
            nB_sommet_degImpair=0;
            nB_sommet=0;
            chaine=" ";

            //Parcours de la composante connexe
            while (!file.empty()) //Tant que la file n'est pas vide
            {
                Sommet*s1=(m_sommets.find(file.front()))->second;           //On prend le premier element de la file
                int degSommet=s1->getDegre();
                chaine=chaine+" "+file.front();

                if (degSommet>0)
                {
                    //Calcul du nbre de sommets pairs et impairs
                    if(degSommet%2==0)
                    {
                        ++nB_sommet_degPair;
                    }
                    else
                    {
                        ++nB_sommet_degImpair;
                    }
                }
                ++nB_sommet; //Compte le nombre de sommets par composante
                file.pop(); //Enl�ve les �l�ments de la file
            }

            //Analyse de la composante connexe : chaine, cycle ou rien
            if (nB_sommet>1)
            {
                if(nB_sommet_degImpair==0)
                {
                    ++nB_cycle; //Compte nombre de cycle
                    std::cout<<std::endl<<" Cycle eulerien present : "<<chaine<<std::endl;
                }
                else if ((nB_sommet_degImpair==0)||(nB_sommet_degImpair==2))
                {
                    ++nB_chaine; //Compte nombre de chaine
                    std::cout<<std::endl<<" Chaine eulerien presente : "<<chaine<<std::endl;
                }
                else
                    std::cout<<std::endl<<" Chaine non eulerienne "<<std::endl;
            }
            else
                std::cout<<std::endl<<" Sommet isole, rien d'eulerien "<<std::endl;
            std::cout<<std::endl;
        }
    }
    ///Sortie
    if(nB_cycle>0)
    {
        return 2;
    }
    if(nB_chaine>0)
    {
        return 1;
    }

    return 0;
}

int graphe::verifieId(std::string id) const
{
    if(m_sommets.find(id)!=m_sommets.end())     //Si la cl� existe
        return 1;
    else
        return 0;
}

graphe::~graphe()
{
    //dtor
}
