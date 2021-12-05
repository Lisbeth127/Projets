#include "Pioche.h"

Pioche::Pioche()
{
    //ctor
}

Pioche::~Pioche()
{
    //dtor

    for(int i=0;i<m_complet.size();i++)
    {
        delete(m_complet[i]);
    }
}

void Pioche::setsolution(Carte* solution)
{
    m_solution.push_back(solution);
}

void Pioche::setjeu_ordonne(Carte* card)
{
    m_jeu_ordonne.push_back(card);
}

std::string Pioche::getnom_complet(int i)
{
    return m_complet[i]->getnom();
}

void Pioche::initialiser()
{
    int alea, i, j;
    m_jeu_ordonne.push_back(new Lieu("Asgard", "images/asgard.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Helheim", "images/helheim.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Alfheim", "images/alfheim.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Niflheim", "images/niflheim.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Svartalfheim", "images/svartalfheim.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Muspelheim", "images/muspelheim.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Jotunheim", "images/jotunheim.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Vanaheim", "images/vanaheim.bmp"));
    m_jeu_ordonne.push_back(new Lieu("Midgard", "images/midgard.bmp"));
    m_jeu_ordonne.push_back(new Arme("Mjollnir", "images/mjollnir.bmp"));
    m_jeu_ordonne.push_back(new Arme("Valshamr", "images/valshamr.bmp"));
    m_jeu_ordonne.push_back(new Arme("Gungnir", "images/gungnir.bmp"));
    m_jeu_ordonne.push_back(new Arme("Gjallarhorn", "images/gjallarhorn.bmp"));
    m_jeu_ordonne.push_back(new Arme("Hofund", "images/hofund.bmp"));
    m_jeu_ordonne.push_back(new Arme("les Chaussures de Vidar", "images/chaussures_de_vidar.bmp"));
    m_jeu_ordonne.push_back(new Perso("Thor", "images/thor.bmp"));
    m_jeu_ordonne.push_back(new Perso("Odin", "images/odin.bmp"));
    m_jeu_ordonne.push_back(new Perso("Loki", "images/loki.bmp"));
    m_jeu_ordonne.push_back(new Perso("Jormungandr", "images/jormungandr.bmp"));
    m_jeu_ordonne.push_back(new Perso("Fenrir", "images/fenrir.bmp"));
    m_jeu_ordonne.push_back(new Perso("Freyja", "images/freya.bmp"));
    for(auto elem:m_jeu_ordonne)
    {
        m_complet.push_back(elem);
    }

    alea=rand()%(8+1);
    m_solution.push_back(m_jeu_ordonne[alea]);
    m_jeu_ordonne.erase(m_jeu_ordonne.begin()+alea);
    alea=rand()%(13-8+1)+8;
    m_solution.push_back(m_jeu_ordonne[alea]);
    m_jeu_ordonne.erase(m_jeu_ordonne.begin()+alea);
    alea=rand()%(18-13+1)+13;
    m_solution.push_back(m_jeu_ordonne[alea]);
    m_jeu_ordonne.erase(m_jeu_ordonne.begin()+alea);
}

void Pioche::distribuer(std::vector<Joueur*> player)
{
    int i=0,j=0,k=0;
    int tailleP;
    int tailleJ,alea;
    std::vector<int> tab;
    tailleJ=m_jeu_ordonne.size();
    for(i=0; i<tailleJ; i++)
    {
        tab.push_back(1);
    }
    tailleP=player.size();
    for(i=0; i<tailleJ; i++)
    {
        alea=rand()%(17+1);
        while(tab[alea]==0)
        {
            alea=rand()%(17+1);
        }
        tab[alea]=0;
        player[k]->setmain(m_jeu_ordonne[alea]);
        k++;
        if(k>=tailleP)
        {
            k=0;
        }
    }
}

void Pioche::afficher(BITMAP* buffer, int type) // affiche toutes les cartes du jeu -> type 1 : lieux ; 2 : armes ; 3 : personnages
{
    BITMAP* tmp=create_bitmap(SCREEN_W,SCREEN_H);
    int i;

    for(int i=0;i<SCREEN_W;i++) // Invisibilisation du fond
    {
        for(int j=0;j<SCREEN_H;j++)
        {
            putpixel(tmp,i,j,makecol(255,0,255));
        }
    }

    switch(type)
    {
    case 1:
        for(i=0;i<3;i++) m_complet[i]->afficher_faceCarte((SCREEN_W/4)*(i+1)-34, 2*(SCREEN_H/6)-50, tmp);
        for(i=3;i<6;i++) m_complet[i]->afficher_faceCarte((SCREEN_W/4)*((i%3)+1)-34, SCREEN_H/2-50, tmp);
        for(i=6;i<9;i++) m_complet[i]->afficher_faceCarte((SCREEN_W/4)*((i%3)+1)-34, 4*(SCREEN_H/6)-50, tmp);
        break;

    case 2:
        for(i=9;i<12;i++) m_complet[i]->afficher_faceCarte((SCREEN_W/4)*((i%3)+1)-34, 2*(SCREEN_H/6)-50, tmp);
        for(i=12;i<15;i++) m_complet[i]->afficher_faceCarte((SCREEN_W/4)*((i%3)+1)-34, 4*(SCREEN_H/6)-50, tmp);
        break;

    case 3:
        for(i=15;i<18;i++) m_complet[i]->afficher_faceCarte((SCREEN_W/4)*((i%3)+1)-34, 2*(SCREEN_H/6)-50, tmp);
        for(i=18;i<21;i++) m_complet[i]->afficher_faceCarte((SCREEN_W/4)*((i%3)+1)-34, 4*(SCREEN_H/6)-50, tmp);
        break;

    default:
        break;
    }

    masked_blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
    destroy_bitmap(tmp);
}

void Pioche::afficher_console_test()
{
    std::cout << "M_SOLUTION ------------------\n" ;
    for(auto elem:m_solution)
    {
        std::cout << "addresse : " << elem << "  |  " ;
        elem->afficher_console();
        std::cout << "\n" ;
    }
    std::cout<<"\n";
    std::cout << "M_JEU_ORDONNE ------------------\n" ;
    for(auto elem:m_jeu_ordonne)
    {
        std::cout << "addresse CARTE : " << elem << "  |  " ;
        elem->afficher_console();
        std::cout << "\n" ;
    }
    std::cout<<"\n";
    std::cout << "M_COMPLET ------------------\n" ;
    for(auto elem:m_complet)
    {
        std::cout << "addresse CARTE : " << elem << "  |  " ;
        elem->afficher_console();
        std::cout << "\n" ;
    }
}

bool Pioche::verif_hypothese(std::vector<std::string> hyp)
{
    return (((m_solution[0]->getnom())==hyp[0])&&((m_solution[1]->getnom())==hyp[1])&&((m_solution[2]->getnom())==hyp[2])) ;
}

void Pioche::afficher_dosSolution(BITMAP* buffer, int x, int y, int carte_revelee)
{
    int i=0;

    for(auto elem:m_solution)
    {
        if(i==carte_revelee)elem->afficher_faceCarte(x+i*75, y, buffer);
        else elem->afficher_dosCarte(x+i*75, y, buffer);
        i++;
    }
}

