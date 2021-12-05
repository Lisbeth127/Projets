#include "../header.h"

BaseDonnees::BaseDonnees()
{
    //ctor
    std::ifstream mon_Flux("Fichier/Registre.txt");
    std::string nom;
    std::string mdp,ligne;
    int experience,taille,i,j; // jauge d'experience selon les points de fin de partie accumulés
    if(mon_Flux)
    {
        while(std::getline(mon_Flux,ligne))
        {
            taille=ligne.size();
            j=0;
            for(i=0;i<taille;i++)
            {
                if((ligne[i]==' ')&&(j==0))
                {
                    j=i;
                }
            }
            mdp.assign(ligne,0,j);
            nom.assign(ligne.begin()+j+1,ligne.end()-2);
            experience=ligne[i-1]-48;
            /*std::cout<<"MDP:"<<mdp<<std::endl;
            std::cout<<"Nom:"<<nom<<std::endl;
            std::cout<<"Experience: "<<experience<<"\n\n";
            std::cout<<"J0: "<<j[0]<<std::endl;
            std::cout<<"J1: "<<j[1]<<std::endl;
            std::cout<<"I: "<<i<<std::endl;*/
            m_base.insert(std::pair<std::string,Joueur*>(mdp,new Joueur(nom,experience)));
        }
    }
    else
    {
        std::cout<<"ERREUR: Impossible d'ouvrir le fichier!"<<std::endl;
    }
}

BaseDonnees::~BaseDonnees()
{
    //dtor
}

bool BaseDonnees::connexion(Joueur &player)
{
    std::string mdp;
    std::string message("Saisir mot de passe");
    mdp=clavier_allegro(message);

    auto it=m_base.find(mdp);
    if(it!=m_base.end())
    {
        //allegro_message("MOT DE PASSE TROUVE!\nVOTRE NOM:%s",it->second->getpseudo().c_str());
        message_allegro("MOT DE PASSE TROUVE!");
        //std::cout<<"COUCOUUUUUUUU\n";
        player=*(it->second);
        //std::cout<<"NOM DU JOUEURG: "<<player.getpseudo()<<std::endl;
        return true;
    }
    else
    {
        //allegro_message("MOT DE PASSE INTROUVABLE!");
        //message_allegro("MOT DE PASSE INTROUVABLE!");
        std::cout<<"J AI PAS TROUVER MA GUEULE\n";
        return false;
    }

}

void BaseDonnees::nouveau_compte(Joueur *player)
{
    //Joueur* j_tmp=new Joueur;
    std::ofstream mon_Flux("Fichier/Registre.txt",std::ios::app);
    std::string mdp;
    std::string message("Saisir le mot de passe: ");

    //SAISIE DU NOM DU JOUEUR AUQUEL ON CREE UN COMPTE (FAIT PARTIE DE LA CLASSE POUR FAICLITER LA MODIFICATION DU PSEUDO)
    player->creation_Compte();
    //SAISIE DU MOT DE PASSE DE CE MEME JOUEUR
    mdp=clavier_allegro(message);
    //AJOUT DE CE NOUVEAU COMPTE DANS LA MAP QUI REPRESENTE LA BASE DE DONNEE
    m_base.insert(std::pair<std::string,Joueur*>(mdp,player));
    if(mon_Flux)
    {
        mon_Flux<<mdp<<" "<<player->getpseudo()<<" "<<player->getexperience()<<"\n";
    }
    else
    {
        std::cout<<"ERREUR: OUVERTURE IMPOSSIBLE\n";
    }

}

void BaseDonnees::sauvegarde()
{
    /*std::ofstream mon_Flux("Fichier/Registre.txt",std::ios::app);
    if(mon_Flux)
    {
        mon_Flux<<m_base.
    }*/
}

void BaseDonnees::affichage()
{
    std::cout<<"\n";
    for( auto elem:m_base)
    {
        std::cout<<elem.first;
        std::cout<<"=>";
        elem.second->afficher();
    }
}
