#include "De.h"

///Constructeur du dé
De::De()
    :m_num(1)
{

}

///Destructeur du dé
De::~De()
{

}

///Setter du nombre du dé
void De::setNum(int num)
{
    m_num = num;
}

///Getter du nombre du dé
int De::getNum()
{
    return m_num;
}

int De::LancerDe()
{
    m_num=rand()%(6-1+1)+1;
    return m_num;
}
