#include "Partie.h"

Partie::Partie()
    :m_bool_victoire(false),m_tour(0)
{
    //ctor
}

Partie::~Partie()
{
    //dtor
}

void Partie::nouvelle_partie()
{
    /// Initialisations
    creation_Joueur();
    int choix=1,i=0;
    bool connect;
    bool musique = false;
    std::vector<std::string>msgs_choix;
    msgs_choix.push_back("OUI");
    msgs_choix.push_back("NON");
    SAMPLE* musiqueJeu = load_sample("son/musiqueJeu.wav");
    if(!musiqueJeu)
    {
        allegro_message("Y'a pas le son du jeu razmo !");
    }

    for(auto &elem:m_liste)
    {
        i++;
        choix=choix_allegro(i,false,"Joueur %d : Avez-vous un compte parmi nous?",msgs_choix);
        connect=false;

        while((connect==false)&&(choix==1))
        {
            if(choix==1)
            {
                connect=m_bases.connexion(*elem);
                if(connect==false)
                {
                    choix=choix_allegro(i,false,"ERREUR! Joueur %d avez-vous un compte parmi nous?",msgs_choix);
                }
            }
        }
        if(choix!=1)
        {
            m_bases.nouveau_compte(elem);

            m_bases.affichage();
        }
    }

    m_jeu.initialiser();
    m_jeu.distribuer(m_liste);

    play_sample(musiqueJeu,100,100,1000,1);

    /// Boucle de jeu
    while(!m_bool_victoire)
    {

        if(m_liste[m_tour]->en_lice()) tour_joueur(m_liste, m_tour, m_plateau, m_jeu, m_bool_victoire,musiqueJeu,musique);
        m_tour = (m_tour+1)%(m_liste.size());

    }

    destroy_sample(musiqueJeu);
    rest(100);
}

void Partie::creation_Joueur()
{
    std::vector<std::string>msgs_choix;
    int choix;
    msgs_choix.push_back("3 Joueurs");
    msgs_choix.push_back("4 Joueurs");
    msgs_choix.push_back("5 Joueurs");
    choix=choix_allegro(0,true,"Selectionner Le Nombre De Joueurs",msgs_choix);
    /*int couleur=makecol(200, 170, 16);
    int choix=1;
    char carac;
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* titre=load_bitmap("images/titre.bmp", NULL);
    BITMAP* fond=load_bitmap("images/ragnarok.bmp", NULL);

    while(!key[KEY_ENTER])
    {
        clear_bitmap(buffer);
        blit(fond, buffer, 0,0,0,0,fond->w, fond->h); // fond
        masked_blit(titre, buffer, 0,0,SCREEN_W/2-(titre->w)/2, SCREEN_H/9,titre->w, titre->h); // titre

        // options menu principal
        textprintf_ex(buffer,font,(SCREEN_W/2)-(18*SCREEN_W/135),(SCREEN_H/2),couleur,-1,"Veuillez Selectionner Le Nombre De Joueurs");
        textprintf_ex(buffer,font,(SCREEN_W/2)-(4*SCREEN_W/135),(SCREEN_H/2)+(SCREEN_H/10),couleur,-1,"3 Joueurs");
        textprintf_ex(buffer,font,(SCREEN_W/2)-(4*SCREEN_W/135),(SCREEN_H/2)+2*(SCREEN_H/10),couleur,-1,"4 Joueurs");
        textprintf_ex(buffer,font,(SCREEN_W/2)-(4*SCREEN_W/135),(SCREEN_H/2)+3*(SCREEN_H/10),couleur,-1,"5 Joueurs");
        rect(buffer, SCREEN_W/2-(10*(SCREEN_W/90)),(SCREEN_H/2)+choix*(SCREEN_H/10)-SCREEN_H/40, SCREEN_W/2+(10*(SCREEN_W/90)), (SCREEN_H/2)+choix*(SCREEN_H/10)+SCREEN_H/25, couleur);

        if(keypressed())
        {
            carac=readkey();

            if(key[KEY_DOWN])
            {
                choix=(choix+1)%4;
                if(choix==0) choix=1;
            }
            if(key[KEY_UP])
            {
                if(choix==1) choix=3;
                else choix--;
            }
        }

        blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H); // affichage à l'écran
    }*/
    for(int i=0; i<choix+2; i++)
    {
        m_liste.push_back(new Joueur);
        m_liste[i]->afficher();
    }

    /*destroy_bitmap(buffer);
    destroy_bitmap(titre);
    destroy_bitmap(fond);*/
}

void Partie::tour_joueur(std::vector<Joueur*> liste, int joueur_en_cours, Yggdrasil &plateau, Pioche &jeu, bool &bool_victoire,SAMPLE*musiqueJeu,bool &musique)
{
    int couleur, verif=0;
    char carac;
    bool bool_chemin=false , bool_salle=false, bool_choix_accusation=false, bool_bifrost = false;
    std::string string_tmp; /// PEUT ETRE MODIFIER LE NOM DE LA VARIABLE
    BITMAP* couche1=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* couche2=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* masque=create_bitmap(SCREEN_W, SCREEN_H);
    De dice;

    //////// TEST ///////////////
    /*
    jeu.afficher_console_test();
    for(int i=0;i<liste.size();i++)
    {
        std::cout << i << "\n";
        liste[i]->afficher_console_test();
    }*/
    //////// TEST ///////////////

    /// Affichage tirage du dé
    plateau.afficher(couche1, liste, joueur_en_cours, 0);
    for(int i=0;i<=SCREEN_W;i++) // affichage du plateau en "sous-brillance"
    {
        for(int j=0;j<=SCREEN_H;j++)
        {
            couleur=getpixel(couche1,i,j);
            putpixel(couche1,i,j,makecol(getr(couleur)/3, getg(couleur)/3, getb(couleur)/3));
        }
    }

    for(int i=0;i<SCREEN_W;i++) // création du bitmap "invisible" completement rose
    {
        for(int j=0;j<SCREEN_H;j++)
        {
            putpixel(masque,i,j,makecol(255, 0, 255));
        }
    }

    for(int i=0;i<30;i++) // affichage text dans une boucle qui modifie à chaque tour la valeur du dé pour donner l'effet roulette
    {
        clear_bitmap(couche2);

        blit(masque, couche2,0,0,0,0,SCREEN_W, SCREEN_H);
        string_tmp=liste[joueur_en_cours]->getpseudo();
        textprintf_ex(couche2,font,(SCREEN_W/2)-((3+(string_tmp.size())/2)*SCREEN_W/136),4*(SCREEN_H/9),makecol(200, 170, 16),-1,"Tour de %s", string_tmp.c_str());
        textprintf_ex(couche2,font,(SCREEN_W/2)-(6*SCREEN_W/135),4*(SCREEN_H/9)+(SCREEN_H/18),makecol(200, 170, 16),-1,"Tirage du De : %d",dice.LancerDe());
        blit(couche1, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        masked_blit(couche2, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(50);
    }
    rest(500);

   while(verif!=dice.getNum())
    {
        if(key[KEY_G]&&(musique))
        {
            play_sample(musiqueJeu,100,100,1000,1);
            musique = false;
        }

        if (key[KEY_H]&&(!musique))
        {
            stop_sample(musiqueJeu);
            musique = true;
        }


        plateau.afficher(screen, liste, joueur_en_cours, 0);
        textprintf_ex(screen, font, SCREEN_W/2, 20, makecol(255,0,0), -1, "%d", dice.getNum()-verif);



        /// Détéction et verification du déplacement
        if(keypressed())
        {
            carac=readkey();

            if(key[KEY_UP])
            {
                plateau.deplacement_joueur(0, -1, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 0, jeu);
                if(bool_chemin) verif++;
            }
            if(key[KEY_DOWN])
            {
                plateau.deplacement_joueur(0, 1, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 0, jeu);
                if(bool_chemin) verif++;
            }
            if(key[KEY_LEFT])
            {
                plateau.deplacement_joueur(-1, 0, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 0, jeu);
                if(bool_chemin) verif++;
            }
            if(key[KEY_RIGHT])
            {
                plateau.deplacement_joueur(1, 0, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 0, jeu);
                if(bool_chemin) verif++;
            }
            if(key[KEY_SPACE])
            {
                plateau.verif_accusation(bool_victoire, jeu, liste, joueur_en_cours, bool_choix_accusation);
            }
        }

        if(bool_choix_accusation)
        {
            verif=dice.getNum(); // fin de tour
            if(!bool_victoire) liste[joueur_en_cours]->setetat(false); // si le joueur se trompe dans son accusation, il est éliminé
        }
        if(bool_salle)
        {
            plateau.hypothese(screen, jeu, liste, joueur_en_cours);
            verif=dice.getNum(); // fin de tour
        }
    }

    destroy_bitmap(masque);
    destroy_bitmap(couche1);
    destroy_bitmap(couche2);
    std::cout << "ta gueule jean claude" ;
}

int Partie::choix_allegro(int i,bool b_titre,std::string msg,std::vector<std::string>msg_choix)
{
    int couleur=makecol(200, 170, 16);
    int choix=1;
    char carac;
    bool musique = true;
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* fond=load_bitmap("images/ragnarok.bmp", NULL);
    BITMAP* titre=load_bitmap("images/titre.bmp", NULL);

    /*if(b_titre==true)
    {
        BITMAP* titre=load_bitmap("images/titre.bmp", NULL);
    }*/
    //SAMPLE* musique=load_sample("son/menu.wav");
    rest(250);
    while(!key[KEY_ENTER])
    {
        clear_bitmap(buffer);
        blit(fond, buffer, 0,0,0,0,fond->w, fond->h); // fond

        if(b_titre==true)
        {
            masked_blit(titre, buffer, 0,0,SCREEN_W/2-(titre->w)/2, SCREEN_H/9,titre->w, titre->h); // titre
        }

        // options menu principal

        textprintf_ex(buffer,font,(SCREEN_W/2)-(((msg.size()/2)-2)*SCREEN_W/135),(SCREEN_H/2),couleur,-1,msg.c_str(),i);
        textprintf_ex(buffer,font,(SCREEN_W/2)-((msg_choix[0].size()/2)*SCREEN_W/135),(SCREEN_H/2)+(SCREEN_H/10),couleur,-1,msg_choix[0].c_str());
        textprintf_ex(buffer,font,(SCREEN_W/2)-((msg_choix[1].size()/2)*SCREEN_W/135),(SCREEN_H/2)+2*(SCREEN_H/10),couleur,-1,msg_choix[1].c_str());
        if(msg_choix.size()==3)
        {
            textprintf_ex(buffer,font,(SCREEN_W/2)-((msg_choix[2].size()/2)*SCREEN_W/135),(SCREEN_H/2)+3*(SCREEN_H/10),couleur,-1,msg_choix[2].c_str());
        }
        rect(buffer, SCREEN_W/2-(10*(SCREEN_W/90)),(SCREEN_H/2)+choix*(SCREEN_H/10)-SCREEN_H/40, SCREEN_W/2+(10*(SCREEN_W/90)), (SCREEN_H/2)+choix*(SCREEN_H/10)+SCREEN_H/25, couleur);

        //play_sample(musique, 255, 0, 2000, 0);

        if(keypressed())
        {
            carac=readkey();
            if(key[KEY_DOWN])
            {
                choix=(choix+1)%4;
                if(choix==0) choix=1;
            }
            if(key[KEY_UP])
            {
                if(choix==1) choix=3;
                else choix--;
            }
        }
        blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H); // affichage à l'écran
    }

    destroy_bitmap(fond);
    destroy_bitmap(titre);
    destroy_bitmap(buffer);

    return choix;
}

/*int Partie::identification(int i)
{
    int couleur=makecol(200, 170, 16);
    int choix=1;
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* fond=load_bitmap("images/ragnarok.bmp", NULL);

    rest(250);
    while(!key[KEY_ENTER])
    {
        clear_bitmap(buffer);
        blit(fond, buffer, 0,0,0,0,fond->w, fond->h); // fond

        // options menu principal
        textprintf_ex(buffer,font,(SCREEN_W/2)-(15*SCREEN_W/130),(SCREEN_H/2),couleur,-1,"Joueur %d : Avez-vous un compte parmi nous?",i);
        textprintf_ex(buffer,font,(SCREEN_W/2)-(4*SCREEN_W/130),(SCREEN_H/2)+(SCREEN_H/10),couleur,-1,"OUI");
        textprintf_ex(buffer,font,(SCREEN_W/2)-(4*SCREEN_W/130),(SCREEN_H/2)+2*(SCREEN_H/10),couleur,-1,"NON");
        rect(buffer, SCREEN_W/2-(10*(SCREEN_W/90)),(SCREEN_H/2)+choix*(SCREEN_H/10)-SCREEN_H/40, SCREEN_W/2+(10*(SCREEN_W/90)), (SCREEN_H/2)+choix*(SCREEN_H/10)+SCREEN_H/25, couleur);

        if(key[KEY_DOWN])
        {
            choix=(choix+1)%3;
            if(choix==0) choix=1;
            rest(250);
        }
        if(key[KEY_UP])
        {
            if(choix==1) choix=2;
            else choix--;
            rest(250);
        }

        blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H); // affichage à l'écran
    }
    std::cout<<"CHOIX "<<choix<<std::endl;
    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    return choix;
}*/

void Partie::save_partie()
{
    std::ofstream mon_Flux("Fichier/Sauvegarde.txt",std::ios::app);
    int tailleL,i;

    tailleL=m_liste.size();
    if(mon_Flux)
    {
        mon_Flux<<tailleL<<"\n";

    }else
    {
        allegro_message("ERREUR P: Impossible d'ouvrir le fichier");
    }
    for(i=0;i<tailleL;i++)
    {
        m_liste[i]->save_joueur();
    }
    m_plateau.save_plateau();
}
