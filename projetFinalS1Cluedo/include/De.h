#ifndef DE_H
#define DE_H

///Librairies
#include <iostream>
#include <time.h>

///Classe
class De
{
private :
    int m_num;

public :
    De();
    ~De();

    ///Accesseurs
    void setNum(int num);
    int getNum();
    ///Methode
    int LancerDe();
};

#endif // DE_H
