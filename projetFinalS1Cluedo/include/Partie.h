#ifndef PARTIE_H
#define PARTIE_H

#include <fstream>

/// Librairies classes
#include "Carte.h"
#include "Lieu.h"
#include "Perso.h"
#include "Arme.h"
#include "Joueur.h"
#include "Pioche.h"
#include "BaseDonnees.h"
#include "Yggdrasil.h"
#include "De.h"

class Partie
{
public:
    Partie();
    ~Partie();
    /*void initialisation_allegro();
    std::string clavier_allegro();
    int menu();*/
    void nouvelle_partie();
    void creation_Joueur();
    void tour_joueur(std::vector<Joueur*> liste, int joueur_en_cours, Yggdrasil &plateau, Pioche &jeu, bool &bool_victoire,SAMPLE*musiqueJeu,bool &musique);
    //int identification(int i);
    int choix_allegro(int i,bool b_titre,std::string msg,std::vector<std::string>msg_choix);
    void save_partie();

protected:

private:
    Yggdrasil m_plateau;
    Pioche m_jeu;
    std::vector<Joueur*> m_liste;
    bool m_bool_victoire;
    int m_tour;
    BaseDonnees m_bases;

};

#endif // PARTIE_H
