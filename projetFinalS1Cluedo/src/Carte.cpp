#include "Carte.h"
#include <fstream>

///Constructeur par défaut
Carte::Carte(Carte const& copy)
{
    m_nom=copy.m_nom;
    m_faceCarte=copy.m_faceCarte;
    m_dosCarte=copy.m_dosCarte;
}

Carte::Carte(std::string nom, std::string fichier) // dans ce constructeur, on utilise la fonction c_str() de string car elle permet de transformer un string en const char*, type de données que requiert la fonction load_bitmap()
      :m_nom(nom), m_faceCarte(load_bitmap(fichier.c_str(), NULL)), m_dosCarte(load_bitmap("images/dosCarte.bmp", NULL))
{
    if(!m_faceCarte)
    {
        fichier+=" n'a pas ete trouve !";
        allegro_message(fichier.c_str());
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    if(!m_dosCarte)
    {
        allegro_message("dosCarte.bmp n'a pas ete trouve !");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

///Destructeur
Carte::~Carte()
{
    destroy_bitmap(m_faceCarte);
    destroy_bitmap(m_dosCarte);
}

std::string Carte::getnom()
{
    return m_nom;
}
void Carte::afficher_console()
{
    std::cout<< "NOM : " <<m_nom<<std::endl;
}

void Carte::afficher_faceCarte(int x, int y, BITMAP* buffer)
{
    std::cout << "MANU CA BEUG LA BORDEL |||  m_dosCarte : " << this->m_dosCarte << "  |||  m_faceCarte : " << this->m_faceCarte << " |||  m_nom : " << &(this->m_nom) << "\n" ;
    blit(m_faceCarte, buffer, 0,0,x,y, m_faceCarte->w, m_faceCarte->h);
}

void Carte::afficher_dosCarte(int x, int y, BITMAP* buffer)
{
    blit(m_dosCarte, buffer, 0,0,x,y, m_dosCarte->w, m_dosCarte->h);
}

void Carte::save_carte()
{
    std::ofstream mon_Flux("Fichier/Sauvegarde.txt",std::ios::app);
    if(mon_Flux)
    {
        mon_Flux<<m_nom<<"\n";

    }else
    {
        allegro_message("ERREUR C: Impossible d'ouvrir le fichier");
    }
}

