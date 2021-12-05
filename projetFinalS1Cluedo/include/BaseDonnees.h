#ifndef BASEDONNEES_H
#define BASEDONNEES_H

#include <iostream>
#include <map>
#include "Joueur.h"

class BaseDonnees
{
    public:
        BaseDonnees();
        ~BaseDonnees();

        /// Méthodes
        void nouveau_compte(Joueur *player); // a utiliser lors de la creation d'un nouveau compte
        bool connexion(Joueur &player);
        void sauvegarde();
        void affichage();

    protected:

    private:
        std::map<std::string,Joueur*> m_base; // /// l'attribut m_pseudo de la classe Joueur jouera le role d'identifiant et le string de mot de passe
};
void message_allegro(std::string msg);

#endif // BASEDONNEES_H
