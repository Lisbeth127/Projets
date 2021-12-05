#ifndef ARME_H_INCLUDED
#define ARME_H_INCLUDED

#include "Carte.h"

class Arme : public Carte
{
private :
    ///Attributs


public :
    ///Constructeurs
    Arme(std::string nom, std::string fichier);
    ~Arme();
};


#endif // ARME_H_INCLUDED
