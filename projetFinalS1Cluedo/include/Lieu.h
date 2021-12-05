#ifndef LIEU_H_INCLUDED
#define LIEU_H_INCLUDED

///Librairies
#include <iostream>
#include "Carte.h"
//#include <allegro.h>

///Classe
class Lieu : public Carte
{
private :
    ///Attributs


public :
    ///Constructeurs
    Lieu(std::string nom, std::string fichier);
    ~Lieu();
};

#endif // LIEU_H_INCLUDED
