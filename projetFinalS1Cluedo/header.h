#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <allegro.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <fstream>


/// Prototypes classes
class Joueur;
class Carte;
class Lieu;
class Perso;
class Arme;

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
#include "Partie.h"

/// Prototype sous-programmes
void initialisation_allegro();
std::string clavier_allegro(std::string msg);
//int menu();
void message_allegro(std::string msg);
/*void nouvelle_partie();
void creation_Joueur(std::vector<Joueur*> &player);
void tour_joueur(std::vector<Joueur*> liste, int joueur_en_cours, Yggdrasil plateau, Pioche &jeu, bool &bool_victoire);
void afficher_partie(BITMAP* buffer, Yggdrasil plateau, std::vector<Joueur*> liste);*/

/*
SOURCES :

fonction string.c_str() : https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
*/

#endif // HEADER_H_INCLUDED
