#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

#include <iostream>
#include <vector>
#include <allegro.h>

///Classe carte
class Carte
{
private :
    ///Attributs
    std::string m_nom;
    BITMAP* m_faceCarte;
    BITMAP* m_dosCarte;

public :
    ///Constructeurs et destructeurs
    Carte(Carte const& copy);
    Carte(std::string nom, std::string fichier);
    virtual ~Carte();

    ///Accesseurs (il faut des setteurs pour que la méthode initialiser de la class pioche puisse creer les 21 cartes du jeu)
    std::string getnom();
    void afficher_console();
    void afficher_faceCarte(int x, int y, BITMAP* buffer);
    void afficher_dosCarte(int x, int y, BITMAP* buffer);
    void save_carte();
};

#endif // CARTES_H_INCLUDED
