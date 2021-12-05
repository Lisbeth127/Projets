#ifndef YGGDRASIL_H
#define YGGDRASIL_H

#include <iostream>
#include <vector>
#include <allegro.h>
#include "Joueur.h"
#include "Pioche.h"

class Yggdrasil
{
    public:
        Yggdrasil();
        ~Yggdrasil();

        /// Méthodes
        void afficher(BITMAP* buffer, std::vector<Joueur*> liste, int joueur_en_cours, int type);
        void deplacement_joueur(int x, int y, bool &bool_chemin, bool &bool_salle, bool &bool_bifrost, std::vector<Joueur*> liste, int joueur_en_cours, int type, Pioche &jeu); // verifie la possibilité d'un déplacement d'un joueur, x et y recoivent les coordonnées du mouvement (ex : aller en haut -> x=0 et y=-1, à gauche -> x=-1 et y=0)
        void accusation(BITMAP* buffer, bool &bool_victoire, Pioche& jeu,BITMAP* couche1);
        void verif_accusation( bool &bool_victoire, Pioche& jeu, std::vector<Joueur*> liste, int joueur_en_cours, bool &bool_choix_accusation);
        void hypothese(BITMAP* buffer, Pioche& jeu, std::vector<Joueur*> liste, int joueur_en_cours);
        void bonus(std::vector<Joueur*> liste, int joueur_en_cours, Pioche &jeu);
        void save_plateau();
        int Bifrost(BITMAP* buffer, Pioche &jeu, std::vector<Joueur*> liste, int joueur_en_cours);

    private:
        std::vector<std::vector<char>> m_tab;
};

#endif // YGGDRASIL_H
