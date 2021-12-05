#include "header.h"

void initialisation_allegro()
{
    allegro_init();
    set_color_depth(desktop_color_depth());

    //if((set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,0,0,0,0))!=0)
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,700,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    //show_mouse(screen);
}

std::string clavier_allegro(std::string msg)
{
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);
    std::string saisie;
    BITMAP* fond=load_bitmap("images/ragnarok.bmp",NULL);
    char carac;

    rest(500); // pour que le choix precedent (menu) n'interfere pas avec la saisie clavier

    while ((saisie.size()<2)||(!key[KEY_ENTER]))
    {
        /// Affichage dynamique
        clear_bitmap(buffer);
        blit(fond,buffer,0,0,0,0,fond->w,fond->h);
        textprintf_ex(buffer,font,(SCREEN_W/2)-((msg.size()/2)*SCREEN_W/135),(SCREEN_H/2),makecol(200, 170, 16),-1,msg.c_str());
        for(long unsigned int i=0;i<saisie.size();i++) // long unsigned int au lieu d'un int simplement pour éviter un warning à la compilation
        {
            textprintf_ex(buffer,font,(SCREEN_W/2)-6-(5*(saisie.size()+0.1/2))+9*i ,(SCREEN_H/2)+30,makecol(200, 170, 16),-1,"%c", saisie[i]);
        }
        blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        if(keypressed()) // Saisie
        {
            carac=readkey();
            if((key[KEY_Q])&&(saisie.size()<10))
            {
                saisie.push_back('A');
            }
            if((key[KEY_B])&&(saisie.size()<10))
            {
                saisie.push_back('B');
            }
            if((key[KEY_C])&&(saisie.size()<10))
            {
                saisie.push_back('C');
            }
            if((key[KEY_D])&&(saisie.size()<10))
            {
                saisie.push_back('D');
            }
            if((key[KEY_E])&&(saisie.size()<10))
            {
                saisie.push_back('E');
            }
            if((key[KEY_F])&&(saisie.size()<10))
            {
                saisie.push_back('F');
            }
            if((key[KEY_G])&&(saisie.size()<10))
            {
                saisie.push_back('G');
            }
            if((key[KEY_H])&&(saisie.size()<10))
            {
                saisie.push_back('H');
            }
            if((key[KEY_I])&&(saisie.size()<10))
            {
                saisie.push_back('I');
            }
            if((key[KEY_J])&&(saisie.size()<10))
            {
                saisie.push_back('J');
            }
            if((key[KEY_K])&&(saisie.size()<10))
            {
                saisie.push_back('K');
            }
            if((key[KEY_L])&&(saisie.size()<10))
            {
                saisie.push_back('L');
            }
            if((key[KEY_SEMICOLON])&&(saisie.size()<10))
            {
                saisie.push_back('M');
            }
            if((key[KEY_N])&&(saisie.size()<10))
            {
                saisie.push_back('N');
            }
            if((key[KEY_O])&&(saisie.size()<10))
            {
                saisie.push_back('O');
            }
            if((key[KEY_P])&&(saisie.size()<10))
            {
                saisie.push_back('P');
            }
            if((key[KEY_A])&&(saisie.size()<10))
            {
                saisie.push_back('Q');
            }
            if((key[KEY_R])&&(saisie.size()<10))
            {
                saisie.push_back('R');
            }
            if((key[KEY_S])&&(saisie.size()<10))
            {
                saisie.push_back('S');
            }
            if((key[KEY_T])&&(saisie.size()<10))
            {
                saisie.push_back('T');
            }
            if((key[KEY_U])&&(saisie.size()<10))
            {
                saisie.push_back('U');
            }
            if((key[KEY_V])&&(saisie.size()<10))
            {
                saisie.push_back('V');
            }
            if((key[KEY_Z])&&(saisie.size()<10))
            {
                saisie.push_back('W');
            }
            if((key[KEY_X])&&(saisie.size()<10))
            {
                saisie.push_back('X');
            }
            if((key[KEY_Y])&&(saisie.size()<10))
            {
                saisie.push_back('Y');
            }
            if((key[KEY_W])&&(saisie.size()<10))
            {
                saisie.push_back('Z');
            }
            if((key[KEY_BACKSPACE])&&(saisie.size()>0))
            {
                saisie.pop_back();
            }
        }
    }

    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    return saisie;
}

/*int menu()
{
    int couleur=makecol(200, 170, 16);
    int choix=0;
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* titre=load_bitmap("images/titre.bmp", NULL);
    BITMAP* fond=load_bitmap("images/ragnarok.bmp", NULL);
    //SAMPLE* musique=load_sample("son/menu.wav");

    while(!key[KEY_ENTER])
    {
        clear_bitmap(buffer);
        blit(fond, buffer, 0,0,0,0,fond->w, fond->h); // fond
        masked_blit(titre, buffer, 0,0,SCREEN_W/2-(titre->w)/2, SCREEN_H/9,titre->w, titre->h); // titre

        // options menu principal
        textprintf_ex(buffer,font,(SCREEN_W/2)-(7*SCREEN_W/130),(SCREEN_H/2),couleur,-1,"Nouvelle partie");
        textprintf_ex(buffer,font,(SCREEN_W/2)-(10*SCREEN_W/130),(SCREEN_H/2)+(SCREEN_H/10),couleur,-1,"Reprendre une partie");
        textprintf_ex(buffer,font,(SCREEN_W/2)-(3*SCREEN_W/130),(SCREEN_H/2)+2*(SCREEN_H/10),couleur,-1,"Quitter");
        rect(buffer, SCREEN_W/2-(10*(SCREEN_W/90)),(SCREEN_H/2)+choix*(SCREEN_H/10)-SCREEN_H/40, SCREEN_W/2+(10*(SCREEN_W/90)), (SCREEN_H/2)+choix*(SCREEN_H/10)+SCREEN_H/25, couleur);

        //play_sample(musique, 255, 0, 2000, 0);

        if(key[KEY_DOWN])
        {
            choix=(choix+1)%3;
            rest(250);
        }
        if(key[KEY_UP])
        {
            if(choix==0) choix=2;
            else choix--;
            rest(250);
        }

        blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H); // affichage à l'écran
    }

    destroy_bitmap(fond);
    destroy_bitmap(titre);
    destroy_bitmap(buffer);
    //destroy_sample(musique);

    return choix;
}*/

void message_allegro(std::string msg)
{
    int couleur=makecol(200, 170, 16);
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* fond=load_bitmap("images/ragnarok.bmp", NULL);
    //rest(250);
        clear_bitmap(screen);
        clear_bitmap(buffer);
        blit(fond, buffer, 0,0,0,0,fond->w, fond->h); // fond

        // options menu principal
        textprintf_ex(buffer,font,(SCREEN_W/2)-((msg.size()/2)*SCREEN_W/135),(SCREEN_H/2),couleur,-1,msg.c_str());
        blit(buffer, screen, 0,0,0,0,fond->w, fond->h);
        //if(readkey());
        rest(1000);

    destroy_bitmap(buffer);
    destroy_bitmap(fond);
}

/*void nouvelle_partie()
{
    /// Déclarations
    Yggdrasil plateau;
    Pioche jeu;
    std::vector<Joueur*> liste;
    std::string tmp;
    bool bool_victoire = false ;
    int tour = 0;

    /// Initialisations
    creation_Joueur(liste);
    jeu.initialiser();
    jeu.distribuer(liste);

    jeu.afficher_console_test();

    /// Boucle de jeu
    while(!bool_victoire)
    {
        if(liste[tour]->en_lice()) tour_joueur(liste,tour,plateau, jeu, bool_victoire);
        tour = (tour+1)%(liste.size());
    }
    rest(100);
}

void creation_Joueur(std::vector<Joueur*> &player)
{
    int couleur=makecol(200, 170, 16);
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
    }
    for(int i=0;i<choix+2;i++)
    {
        player.push_back(new Joueur);
        player[i]->afficher();
    }

    destroy_bitmap(buffer);
    destroy_bitmap(titre);
    destroy_bitmap(fond);
}

void tour_joueur(std::vector<Joueur*> liste, int joueur_en_cours, Yggdrasil plateau, Pioche &jeu, bool &bool_victoire)
{
    int couleur, verif=0;
    char carac;
    bool bool_chemin=false , bool_salle=false, bool_choix_accusation=false;
    std::string string_tmp; /// PEUT ETRE MODIFIER LE NOM DE LA VARIABLE
    BITMAP* couche1=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* couche2=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* masque=create_bitmap(SCREEN_W, SCREEN_H);
    De dice;

    //////// TEST ///////////////

    jeu.afficher_console_test();
    for(int i=0;i<liste.size();i++)
    {
        std::cout << i << "\n";
        liste[i]->afficher_console_test();
    }
    //////// TEST ///////////////

    /// Affichage tirage du dé
    plateau.afficher(couche1, liste, joueur_en_cours);
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
jeu.afficher_console_test();
   while(verif!=dice.getNum())
    {
        plateau.afficher(screen, liste, joueur_en_cours);

        /// Détéction et verification du déplacement
        if(keypressed())
        {
            carac=readkey();

            if(key[KEY_UP])
            {
                plateau.deplacement_joueur(liste[joueur_en_cours], 0, -1, bool_chemin, bool_salle);
                if(bool_chemin)
                {
                    liste[joueur_en_cours]->setxy(liste[joueur_en_cours]->getx(),liste[joueur_en_cours]->gety()-1);
                    bool_chemin=false;
                    verif++;
                }
            }
            if(key[KEY_DOWN])
            {
                plateau.deplacement_joueur(liste[joueur_en_cours], 0, 1, bool_chemin, bool_salle);
                if(bool_chemin)
                {
                    liste[joueur_en_cours]->setxy(liste[joueur_en_cours]->getx(),liste[joueur_en_cours]->gety()+1);
                    bool_chemin=false;
                    verif++;
                }
            }
            if(key[KEY_LEFT])
            {
                plateau.deplacement_joueur(liste[joueur_en_cours], -1, 0, bool_chemin, bool_salle);
                if(bool_chemin)
                {
                    liste[joueur_en_cours]->setxy(liste[joueur_en_cours]->getx()-1,liste[joueur_en_cours]->gety());
                    bool_chemin=false;
                    verif++;
                }
            }
            if(key[KEY_RIGHT])
            {
                plateau.deplacement_joueur(liste[joueur_en_cours], 1, 0, bool_chemin, bool_salle);
                if(bool_chemin)
                {
                    liste[joueur_en_cours]->setxy(liste[joueur_en_cours]->getx()+1,liste[joueur_en_cours]->gety());
                    bool_chemin=false;
                    verif++;
                }
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
}*/
