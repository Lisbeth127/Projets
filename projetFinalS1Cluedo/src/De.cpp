#include "De.h"

///Constructeur du d�
De::De()
    :m_num(1)
{

}

///Destructeur du d�
De::~De()
{

}

///Setter du nombre du d�
void De::setNum(int num)
{
    m_num = num;
}

///Getter du nombre du d�
int De::getNum()
{
    return m_num;
}

int De::LancerDe()
{
    m_num=rand()%(6-1+1)+1;
    return m_num;
}
