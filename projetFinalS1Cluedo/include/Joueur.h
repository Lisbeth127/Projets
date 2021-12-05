#ifndef JOUEUR_H
#define JOUEUR_H

/// VOIR COMMENT SUPPRIMER CES INCLUDES -> FONT DOUBLON AVEC CEUX DU HEADER.H !!!!!!!!!!!!!!!
#include <iostream>
#include "Carte.h"

class Joueur
{
    public:
        Joueur();
        Joueur(std::string nom,int experience);
        ~Joueur();

        /// Accesseurs | (pour pouvoir reprendre une partie en cours il faut des setteurs)
        void setpseudo(std::string pseudo);
        void setmain(Carte* card); // push_back d'un seul pointeur de carte
        void setexperience(int xp);
        void setxy(int x, int y);
        void setetat(bool etat);
        std::string getpseudo();
        int getexperience();
        int getx();
        int gety();
        std::string getnomcarte(int i);

        /// Méthodes
        void creation_Compte();
        int niveau(); // retourne 0,1,2 ou 3 selon la jauge d'xp
        void afficher_main(BITMAP* buffer, int x, int y); // affichage allegro main
        void afficher_dosmain(BITMAP* buffer, int x, int y, int carte_revelee);
        void afficher();
        bool en_lice(); // retourne true si le joueur n'est pas encore éliminé
        int getnbrcartes(); // retourne le nombre de cartes du joueur pour l'affichage lors de l'hypothese
        void afficher_console_test();
        void save_joueur();

    protected:

    private:
        std::string m_pseudo;
        std::vector<Carte*> m_main; // On utilise un vecteur de pointeurs pour pouvoir utiliser le plymorphisme
        int m_experience; // jauge d'experience selon les points de fin de partie accumulés
        bool m_etat;
        int m_x;
        int m_y; // position dans le plateau
};

#endif // JOUEUR_H
