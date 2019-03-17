#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(std::string,double,double);
        /// méthode qui ajoute les voisins d'un sommet
        void ajouterVoisin(const Sommet*);
        /// méthode qui affiche les données d'un sommet (id et position)
        void afficherData() const;
        /// méthode qui ajffiche les voisins d'un sommet
        void afficherVoisins() const;
        ///méthode de parcours en largeur du graphe à partir du sommet
        ///renvoie les prédécesseurs sous forme d'une map (clé=id du sommet,valeur=id de son prédécesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///méthode de parcours en profondeur du graphe à partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///méthode qui recherche la composante connexe du sommet
        ///renvoie la liste des ids des sommets de la composante
        std::unordered_set<std::string> rechercherCC() const;
        /// méthode qui renvoie le degré d'un sommet
        int getDegre () const;

        ~Sommet();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
