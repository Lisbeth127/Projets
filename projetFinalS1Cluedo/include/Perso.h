#ifndef PERSO_H
#define PERSO_H

#include <iostream>
#include "Carte.h"

class Perso : public Carte
{
    public:
        Perso(std::string nom, std::string fichier);
        ~Perso();

    protected:

    private:
};

#endif // PERSO_H
