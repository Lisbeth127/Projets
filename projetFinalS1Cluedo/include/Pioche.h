#ifndef PIOCHE_H
#define PIOCHE_H

#include "Carte.h"
#include "Arme.h"
#include "Lieu.h"
#include "Perso.h"
#include "Joueur.h"
#include <vector>

class Pioche
{
    public:
        Pioche();
        ~Pioche();

        /// Accesseurs (setteurs pour reprendre une partie sauvegardée)
        void setsolution(Carte* solution);
        void setjeu_ordonne(Carte* card); // inutile de prévoir un setteur pour m_jeu_desordonne car lorsqu'on quitte une partie en cours en la sauvegardant, toutes les mains des joueurs ont été distribuées, cet attribut est donc inutile dans ce cas, en revanche m_jeu_ordonne est toujours utile pour l affichage de toutes le scartes du jeu
        std::string getnom_complet(int i);

        /// Méthodes
        void initialiser(); // initialiser m_jeu_desordonne, m_jeu_ordonne, m_solution
        void distribuer(std::vector<Joueur*>player);
        void hypothese();
        void afficher(BITMAP* buffer, int type);
        bool verif_hypothese(std::vector<std::string> hyp);
        void afficher_console_test();
        void afficher_dosSolution(BITMAP* buffer, int x, int y, int carte_revelee);

    private:
        std::vector<Carte*> m_jeu_ordonne; //jeu ordonné privé des cartes formant la solution, permettant ainsi de définir les cartes à mélanger
        std::vector<Carte*> m_solution; // les 3 cartes lieu, arme et dieu servant de solution
        std::vector<Carte*> m_complet;// paquet de Cartes servant a afficher à tout moment toutes les cartes du jeu et ne pas utiliser de dynamic_cast (si l'on souhaite n'afficher que les lieux par exemple on peut afficher seulement les 9 premiers indices)
};

#endif // PIOCHE_H
