#include "../header.h"

Joueur::Joueur()
       :m_pseudo(" "), m_experience(0), m_etat(true),m_x(7),m_y(5)
{
    //std::cout<<"JOUEUR CONSTRUIT";
}

Joueur::Joueur(std::string nom,int experience)
       :m_pseudo(nom),m_experience(experience),m_etat(1),m_x(7),m_y(5)
{

}

Joueur::~Joueur()
{

}

void Joueur::setetat(bool etat)
{
    m_etat=etat;
}

void Joueur::setpseudo(std::string pseudo)
{
    m_pseudo=pseudo;
}

void Joueur::setmain(Carte* card)
{
    m_main.push_back(card);
}

void Joueur::setexperience(int xp)
{
    m_experience=xp;
}

std::string Joueur::getpseudo()
{
    return m_pseudo;
}

int Joueur::getexperience()
{
    return m_experience;
}

void Joueur::setxy(int x, int y)
{
    m_x=x;
    m_y=y;
}

int Joueur::getx()
{
    return m_x;
}

int Joueur::gety()
{
    return m_y;
}

void Joueur::creation_Compte()
{
    std::string message("Saisir nom: ");
    std::string tmp;
    tmp=clavier_allegro(message);
    m_pseudo=tmp;
    std::cout<<"gros teste lk\n";
}

int Joueur::niveau() // retourne 0,1,2 ou 3 selon la jauge d'xp
{
    int niv;
    /*
    if(m_experience< ??? )
    {
        niv=0;
    }
    else
    {
        if(m_experience< ??? )
        {
            niv=1;
        }
        else
        {
            if(m_experience< ??? )
            {
                niv=2;
            }
            else
            {
                if(m_experience< ??? )
                {
                    niv=3;
                }
            }
        }
    }
    */
    return niv;
}

void Joueur::afficher_main(BITMAP* buffer, int x, int y) // affichage allegro main
{
    int i=0;

    for(auto elem:m_main)
    {
        elem->afficher_faceCarte(x+i*75, y, buffer);
        i++;
    }
}

void Joueur::afficher_dosmain(BITMAP* buffer, int x, int y, int carte_revelee) // affichage allegro main
{
    int i=0;

    for(auto elem:m_main)
    {
        if(i==carte_revelee)elem->afficher_faceCarte(x+i*75, y, buffer);
        else elem->afficher_dosCarte(x+i*75, y, buffer);
        i++;
    }
}

void Joueur::afficher()
{
    for(auto elem:m_main)
    {
        elem->afficher_console();
    }
}

bool Joueur::en_lice() // retourne true si le joueur n'est pas encore éliminé
{
    return m_etat;
}

int Joueur::getnbrcartes()
{
    return m_main.size();
}

std::string Joueur::getnomcarte(int i)
{
    return m_main[i]->getnom();
}

void Joueur::afficher_console_test()
{
    int i,j;
    std::cout << "M_MAIN ------------------\n" ;
    for(auto elem:m_main)
    {
        std::cout << "addresse : " << elem << "  |  " ;
        elem->afficher_console();
        std::cout << "\n" ;
    }
    rest(3000);
}

void Joueur::save_joueur()
{
    int taille,i;
    std::ofstream mon_Flux("Fichier/Sauvegarde.txt",std::ios::app);

    taille=m_main.size();
    if(mon_Flux)
    {
        mon_Flux<<m_pseudo<<"\n";
        mon_Flux<<m_experience<<"\n";
        mon_Flux<<m_etat<<"\n";
        mon_Flux<<m_x<<"\n";
        mon_Flux<<m_y<<"\n";
        mon_Flux<<taille<<"\n";
        for(i=0;i<taille;i++)
        {
            m_main[i]->save_carte();
        }

    }else
    {
        allegro_message("ERREUR J: Impossible d'ouvrir le fichier");
    }
}
