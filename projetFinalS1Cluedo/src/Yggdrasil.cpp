#include "Yggdrasil.h"
#include <fstream>

Yggdrasil::Yggdrasil() // z : vide ; x : plateau ;  0,1,2,... : asgard, alfheim, muspelheim, midgard,... (de gauche a droite et de haut en bas) ; b : bonus
{
    int alea1, alea2, compteur=0;
    std::vector<char> vec0{'z','z','z','z','z','z','z','z','x','4','z','z','z'};
    std::vector<char> vec1{'z','z','z','z','z','z','z','z','x','z','z','z','z'};
    std::vector<char> vec2{'z','z','z','z','z','z','z','z','x','z','x','x','5'};
    std::vector<char> vec3{'z','z','z','z','z','z','z','z','x','v','x','z','z'};
    std::vector<char> vec4{'z','z','z','0','z','1','x','3','x','x','z','z','z'};
    std::vector<char> vec5{'z','z','v','0','z','z','z','3','x','x','z','z','z'};
    std::vector<char> vec6{'z','x','x','0','x','x','x','3','x','x','z','z','z'};
    std::vector<char> vec7{'v','x','x','0','x','x','x','3','x','x','x','x','6'};
    std::vector<char> vec8{'z','x','x','0','x','x','x','3','x','x','z','z','z'};
    std::vector<char> vec9{'z','z','x','0','z','z','z','3','x','x','z','z','z'};
    std::vector<char> vec10{'z','z','z','0','z','2','x','3','z','x','z','z','z'};
    std::vector<char> vec11{'z','z','z','z','z','z','z','z','x','x','x','z','z'};
    std::vector<char> vec12{'z','z','z','z','z','z','z','z','x','z','v','x','7'};
    std::vector<char> vec13{'z','z','z','z','z','z','z','z','x','8','z','z','z'};

    m_tab.push_back(vec0);
    m_tab.push_back(vec1);
    m_tab.push_back(vec2);
    m_tab.push_back(vec3);
    m_tab.push_back(vec4);
    m_tab.push_back(vec5);
    m_tab.push_back(vec6);
    m_tab.push_back(vec7);
    m_tab.push_back(vec8);
    m_tab.push_back(vec9);
    m_tab.push_back(vec10);
    m_tab.push_back(vec11);
    m_tab.push_back(vec12);
    m_tab.push_back(vec13);

    do
    {
        alea1=rand()%14;
        alea2=rand()%13;
        if(m_tab[alea1][alea2]=='x')
        {
            m_tab[alea1][alea2]='b';
            compteur++;
        }
    }while(compteur<4);
}

Yggdrasil::~Yggdrasil()
{
    //dtor
}

void Yggdrasil::afficher(BITMAP* buffer, std::vector<Joueur*> liste, int joueur_en_cours, int type)
{
    BITMAP* fond=load_bitmap("images/paysage.bmp", NULL);
    BITMAP* ygg=load_bitmap("images/yggdrasil.bmp", NULL); // chargement image
    BITMAP* tmp=create_bitmap(SCREEN_W, SCREEN_H);
    std::vector<BITMAP*> icones;

    blit(fond, tmp, 0, 0, SCREEN_W - fond->w, 0, fond->w, fond->h);
    blit(ygg, tmp,0,0,0,0,ygg->w,ygg->h); // affichage arbre

    icones.push_back(load_bitmap("images/ThorPion.bmp", NULL));
    if(!icones[0]) allegro_message("ThorPion introuvable");
    icones.push_back(load_bitmap("images/OdinPion.bmp", NULL));
    if(!icones[1]) allegro_message("OdinPion introuvable");
    icones.push_back(load_bitmap("images/LokiPion.bmp", NULL));
    if(!icones[2]) allegro_message("Loki introuvable");
    icones.push_back(load_bitmap("images/JormunganderPion.bmp", NULL));
    if(!icones[3]) allegro_message("JormunganderPion introuvable");
    icones.push_back(load_bitmap("images/FreyaPion.bmp", NULL));
    if(!icones[4]) allegro_message("FreyaPion introuvable");
    icones.push_back(load_bitmap("images/FenrirPion.bmp", NULL));
    if(!icones[5]) allegro_message("FenrirPion introuvable");

    /// Affichage grille
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(m_tab[i][j]=='x')
            {
                circlefill(tmp, 45+i*30, 155+j*40, 5, makecol(48,186,65));
            }
            if(m_tab[i][j]=='b')
            {
                circlefill(tmp, 45+i*30, 155+j*40, 5, makecol(255,255,0));
            }

            if(m_tab[i][j]=='v')
            {
                circlefill(tmp, 45+i*30, 155+j*40, 5, makecol(255,0,0));
            }

            if((m_tab[i][j]>='0')&&(m_tab[i][j]<='8'))
            {
                circlefill(tmp, 45+i*30, 155+j*40, 5, makecol(10,15,239));
            }
        }
    }

    for(int i=0;i<liste.size();i++)
    {
        textprintf_ex(tmp,font,ygg->w + 15,SCREEN_H/15 + 120*i-10,makecol(200, 170, 16),-1,"%s", liste[i]->getpseudo().c_str());
        if(i==joueur_en_cours) liste[i]->afficher_main(tmp, ygg->w + 15 , SCREEN_H/15 + 120*i);
        else liste[i]->afficher_dosmain(tmp, ygg->w + 15 , SCREEN_H/15 + 120*i, -1);
        if(liste[i]->en_lice())
        {
            if((i==joueur_en_cours)&&(type==1)) circlefill(tmp, 45+(liste[i]->getx())*30, 155+(liste[i]->gety())*40, 5, makecol(255,0,0));
            else masked_blit(icones[i], tmp, 0,0,45+(liste[i]->getx())*30 - (icones[i]->w)/2,155+(liste[i]->gety())*40 - (icones[i]->h)/2, icones[i]->w, icones[i]->h);

        }
    }

    blit(tmp, buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    for(int i=0;i<icones.size();i++)destroy_bitmap(icones[i]);
    destroy_bitmap(ygg);
    destroy_bitmap(tmp);
    destroy_bitmap(fond);
}

void Yggdrasil::deplacement_joueur(int x, int y, bool &bool_chemin, bool &bool_salle,bool &bool_bifrost, std::vector<Joueur*> liste, int joueur_en_cours, int type, Pioche &jeu) // verifie la possibilité d'un déplacement d'un joueur, x et y recoivent les coordonnées du mouvement (ex : aller en haut -> x=0 et y=-1, à gauche -> x=-1 et y=0)
{
    int couleur;
    char carac;
    int choixTP;
    bool choix=false;
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);

    bool_chemin=false;
    if((liste[joueur_en_cours]->getx()+x >= 0)&&(liste[joueur_en_cours]->getx()+x <= 13)&&(liste[joueur_en_cours]->gety()+y >= 0)&&(liste[joueur_en_cours]->gety()+y <= 12))
    {
        if((m_tab[liste[joueur_en_cours]->getx()][liste[joueur_en_cours]->gety()])!=(m_tab[liste[joueur_en_cours]->getx()+x][liste[joueur_en_cours]->gety()+y])) // si la case d'arrivée n'est pas la même que celle de départ
        {
            if(m_tab[liste[joueur_en_cours]->getx()+x][liste[joueur_en_cours]->gety()+y]!='z') bool_chemin=true; // si la case d'arrivée n'est pas innacessible (caractère 'z' du plateau), le mouvement est validé
            if(m_tab[liste[joueur_en_cours]->getx()+x][liste[joueur_en_cours]->gety()+y]=='v') bool_bifrost = true;
            if((m_tab[liste[joueur_en_cours]->getx()+x][liste[joueur_en_cours]->gety()+y]>='0')&&(m_tab[liste[joueur_en_cours]->getx()+x][liste[joueur_en_cours]->gety()+y]<='8')) bool_salle=true; // si en plus la case d'arrivée est une salle, bool_salle prend true pour activer dans le sous-programme "tour_joueur" l'hypothèse et la fin du tour
        }
        else // si la case d'arrivée et de départ ont le même caractère, alors le déplacement est validé car salle1 -> salle1 est possible et n'active pas l'hypothèse
        {
            bool_chemin=true;
        }

        if(bool_chemin)

        {
            liste[joueur_en_cours]->setxy(liste[joueur_en_cours]->getx() + x,liste[joueur_en_cours]->gety()+ y);

            if (bool_bifrost)
                {
                    ///On appel le sous programme pour récupérer son choix
                    choixTP = Bifrost(screen,jeu,liste,joueur_en_cours);
                    std::cout << choixTP;
                    ///S'il veut se téléporter
                    if(choixTP ==1)
                    {
                        std::cout << std::endl << "x : " << liste[joueur_en_cours]->getx() << " y : " << liste[joueur_en_cours]->gety() << std::endl;
                        ///On analyse pour savoir il est a quel bout du bifrost et on le téléporte
                        if((liste[joueur_en_cours]->getx() == 3)&&(liste[joueur_en_cours]->gety() == 9)) liste[joueur_en_cours]->setxy(5,2);
                        else if((liste[joueur_en_cours]->getx() == 5)&&(liste[joueur_en_cours]->gety() == 2)) liste[joueur_en_cours]->setxy(3,9);
                        else if((liste[joueur_en_cours]->getx() == 7)&&(liste[joueur_en_cours]->gety() == 0)) liste[joueur_en_cours]->setxy(12,10);
                        else if((liste[joueur_en_cours]->getx() == 12)&&(liste[joueur_en_cours]->gety() == 10)) liste[joueur_en_cours]->setxy(7,0);
                    }
                    bool_bifrost = false;
                }

        }

        afficher(buffer, liste, joueur_en_cours, 0);
        for(int i=0;i<=SCREEN_W;i++) // affichage du plateau en "sous-brillance"
        {
            for(int j=0;j<=SCREEN_H;j++)
            {
                couleur=getpixel(buffer,i,j);
                putpixel(buffer,i,j,makecol(getr(couleur)/3, getg(couleur)/3, getb(couleur)/3));
            }
        }
        /// Gestion cases bonus
        if((m_tab[liste[joueur_en_cours]->getx()][liste[joueur_en_cours]->gety()]=='b')&&(type==0))
        {
            textprintf_ex(buffer, font, SCREEN_W/2 - 15*(SCREEN_W/130), SCREEN_H/2 - 15, makecol(200, 170, 16), -1, "Voulez-vous utiliser le bonus ?");
            textprintf_ex(buffer, font, SCREEN_W/2 -10*(SCREEN_W/130), SCREEN_H/2 + 15, makecol(200, 170, 16), -1, "OUI : O   |   NON : N");
            blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);

            while(!choix)
            {
                if(keypressed())
                {
                    carac=readkey();

                    if(key[KEY_O])
                    {
                        m_tab[liste[joueur_en_cours]->getx()][liste[joueur_en_cours]->gety()]='x';
                        bonus(liste, joueur_en_cours, jeu);
                        choix=true;
                    }
                    if(key[KEY_N])
                    {
                        choix=true;
                    }
                }
            }
        }
    }

    destroy_bitmap(buffer);
}

void Yggdrasil::verif_accusation( bool &bool_victoire, Pioche& jeu, std::vector<Joueur*> liste, int joueur_en_cours, bool &bool_choix_accusation)
{
    int choix=0, couleur;
    BITMAP* tmp=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* couche1=create_bitmap(SCREEN_W, SCREEN_H); // decor (plateau,cartes joueurs, ...)

    /// Affichage plaeau sous_brillance
    afficher(couche1, liste, joueur_en_cours, 0);
    for(int i=0;i<SCREEN_W;i++) // affichage du plateau en "sous-brillance"
    {
        for(int j=0;j<SCREEN_H;j++)
        {
            couleur=getpixel(couche1,i,j);
            putpixel(couche1,i,j,makecol(getr(couleur)/3, getg(couleur)/3, getb(couleur)/3));
        }
    }
    blit(couche1, tmp, 0,0,0,0, SCREEN_W, SCREEN_H);

    /// Demande de verification
    textprintf_ex(tmp, font, SCREEN_W/2 -18*(SCREEN_W/130), SCREEN_H/2 - 15, makecol(200, 170, 16), -1, "Etes-vous certain de vouloir accuser ?");
    textprintf_ex(tmp, font, SCREEN_W/2 -10*(SCREEN_W/130), SCREEN_H/2 + 15, makecol(200, 170, 16), -1, "OUI : O   |   NON : N");

    blit(tmp, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    while(choix==0)
    {
        if(key[KEY_O]) choix=1;
        if(key[KEY_N]) choix=2;
    }

    if(choix==1)
    {
        accusation(screen, bool_victoire, jeu, couche1);
        bool_choix_accusation=true;
    }

    destroy_bitmap(tmp);
    destroy_bitmap(couche1);
}

void Yggdrasil::accusation(BITMAP* buffer, bool &bool_victoire, Pioche& jeu,BITMAP* couche1)
{
    int curseur_x=1, curseur_y=1;
    char carac;
    BITMAP* tmp=create_bitmap(SCREEN_W, SCREEN_H);
    std::vector<std::string> hyp; // l'hypothese formulee par le joueur est un vector de 3 string pour simplifier, ces string prendront le nom de la carte choisie, il suffit ensuite de commparer ces string au nom des cartes de la solution dans la classe pioche

    /// Affichage des cartes Lieu
    // choix carte lieu
    while(!key[KEY_ENTER])
    {
        // affichage selection
        clear_bitmap(tmp);
        blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
        jeu.afficher(tmp, 1);
        switch(curseur_y)
        {
        case 1:
            rect(tmp, (curseur_x*SCREEN_W/4)-34, (2*(SCREEN_H/6))-50, (curseur_x*(SCREEN_W/4))+34, (2*(SCREEN_H/6))+50, makecol(0,0,255));
            break;

        case 2:
            rect(tmp, ((SCREEN_W/4)*curseur_x)-34, (SCREEN_H/2)-50, ((SCREEN_W/4)*curseur_x)+34, (SCREEN_H/2)+50, makecol(0,0,255));
            break;

        case 3:
            rect(tmp, ((SCREEN_W/4)*curseur_x)-34, (4*(SCREEN_H/6))-50, ((SCREEN_W/4)*curseur_x)+34, (4*(SCREEN_H/6))+50, makecol(0,0,255));
            break;

        default:
            break;
        }
        blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

        // gestion curseur
        if(keypressed())
        {
            carac=readkey();

            // gestion curseur
            if(key[KEY_UP])
            {
                if(curseur_y==1) curseur_y=3;
                else curseur_y--;
            }
            if(key[KEY_DOWN])
            {
                if(curseur_y==3) curseur_y=1;
                else curseur_y++;
            }
            if(key[KEY_RIGHT])
            {
                if(curseur_x==3) curseur_x=1;
                else curseur_x++;
            }
            if(key[KEY_LEFT])
            {
                if(curseur_x==1) curseur_x=3;
                else curseur_x--;
            }
        }
    }
    switch(curseur_y)
    {
    case 1 :
        hyp.push_back(jeu.getnom_complet(curseur_x-1));
        break;

    case 2:
        hyp.push_back(jeu.getnom_complet(curseur_x+2));
        break;

    case 3:
        hyp.push_back(jeu.getnom_complet(curseur_x+5));
        break;

    default :
        break;
    }

    // choix carte arme
    curseur_x=1;
    curseur_y=1;
    rest(300);
    while(!key[KEY_ENTER])
    {
        // affichage selection
        clear_bitmap(tmp);
        blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
        jeu.afficher(tmp, 2);
        rect(tmp, (SCREEN_W/4)*curseur_x-34, curseur_y*(2*(SCREEN_H/6))-50, (SCREEN_W/4)*curseur_x+34, curseur_y*(2*(SCREEN_H/6))+50, makecol(0,0,255));
        blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

        // gestion curseur
        if(keypressed())
        {
            carac=readkey();

            // gestion curseur
            if(key[KEY_UP])
            {
                if(curseur_y==1) curseur_y=2;
                else curseur_y--;
            }
            if(key[KEY_DOWN])
            {
                if(curseur_y==2) curseur_y=1;
                else curseur_y++;
            }
            if(key[KEY_RIGHT])
            {
                if(curseur_x==3) curseur_x=1;
                else curseur_x++;
            }
            if(key[KEY_LEFT])
            {
                if(curseur_x==1) curseur_x=3;
                else curseur_x--;
            }
        }
    }
    switch(curseur_y)
    {
    case 1 :
        hyp.push_back(jeu.getnom_complet(9+curseur_x-1));
        break;

    case 2:
        hyp.push_back(jeu.getnom_complet(9+curseur_x+2));
        break;

    default :
        break;
    }

    // choix carte perso
    rest(300);
    while(!key[KEY_ENTER])
    {
        // affichage selection
        clear_bitmap(tmp);
        blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
        jeu.afficher(tmp, 3);
        rect(tmp, (SCREEN_W/4)*curseur_x-34, curseur_y*(2*(SCREEN_H/6))-50, (SCREEN_W/4)*curseur_x+34, curseur_y*(2*(SCREEN_H/6))+50, makecol(0,0,255));
        blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

        if(keypressed())
        {
            carac=readkey();

            // gestion curseur
            if(key[KEY_UP])
            {
                if(curseur_y==1) curseur_y=2;
                else curseur_y--;
            }
            if(key[KEY_DOWN])
            {
                if(curseur_y==2) curseur_y=1;
                else curseur_y++;
            }
            if(key[KEY_RIGHT])
            {
                if(curseur_x==3) curseur_x=1;
                else curseur_x++;
            }
            if(key[KEY_LEFT])
            {
                if(curseur_x==1) curseur_x=3;
                else curseur_x--;
            }
        }
    }
    switch(curseur_y)
    {
    case 1 :
        hyp.push_back(jeu.getnom_complet(15+curseur_x-1));
        break;

    case 2:
        hyp.push_back(jeu.getnom_complet(15+curseur_x+2));
        break;

    default :
        break;
    }

    bool_victoire=jeu.verif_hypothese(hyp);
    if(!bool_victoire) // 2 actions en une : 1 - affectation de bool_vitoire | 2 : si le joueur n'a pas deviné la bonne réponse, on affiche le message d'erreur
    {
        clear_bitmap(tmp);
        blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
        textprintf_ex(tmp, font, SCREEN_W/2 - 3*(SCREEN_W/130), SCREEN_H/2 - 20, makecol(255,0,0), -1, "FAUX !");
        textprintf_ex(tmp, font, SCREEN_W/2 - 8*(SCREEN_W/130), SCREEN_H/2, makecol(255,0,0), -1, "VOUS ETES ELIMINE");
        blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
        rest(2000);
    }
    destroy_bitmap(tmp);
}

void Yggdrasil::hypothese(BITMAP* buffer, Pioche& jeu, std::vector<Joueur*> liste, int joueur_en_cours)
{
    int couleur, curseur_x=1, curseur_y=1;
    char carac;
    BITMAP* tmp=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* couche1=create_bitmap(SCREEN_W, SCREEN_H); // decor (plateau,cartes joueurs, ...)
    std::vector<std::string> hyp; // l'hypothese formulee par le joueur est un vector de 3 string pour simplifier, ces string prendront le nom de la carte choisie, il suffit ensuite de commparer ces string au nom des cartes de la solution dans la classe pioche
    std::vector<std::string> messages_erreur; // vecteur de phrases d'erreur (si une carte de l'hypothese est contestée par joueur)
    std::string string_tmp;

    /// Affichage plaeau sous_brillance
    afficher(couche1, liste, joueur_en_cours, 0);
    for(int i=0;i<=SCREEN_W;i++) // affichage du plateau en "sous-brillance"
    {
        for(int j=0;j<=SCREEN_H;j++)
        {
            couleur=getpixel(couche1,i,j);
            putpixel(couche1,i,j,makecol(getr(couleur)/3, getg(couleur)/3, getb(couleur)/3));
        }
    }

    /// Affichage des cartes Lieu
    // Carte lieu
    switch(m_tab[liste[joueur_en_cours]->getx()][liste[joueur_en_cours]->gety()])
    {
    case '0':
        hyp.push_back("Asgard");
        break;

    case '1':
        hyp.push_back("Alfheim");
        break;

    case '2':
        hyp.push_back("Muspelheim");
        break;

    case '3':
        hyp.push_back("Midgard");
        break;

    case '4':
        hyp.push_back("Vanaheim");
        break;

    case '5':
        hyp.push_back("Jotunheim");
        break;

    case '6':
        hyp.push_back("Niflheim");
        break;

    case '7':
        hyp.push_back("Helheim");
        break;

    case '8':
        hyp.push_back("Svartalfheim");
        break;

    default:
        break;
    }


    // choix carte arme
    curseur_x=1;
    curseur_y=1;
    rest(300);
    while(!key[KEY_ENTER])
    {
        // affichage selection
        clear_bitmap(tmp);
        blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
        jeu.afficher(tmp, 2);
        rect(tmp, (SCREEN_W/4)*curseur_x-34, curseur_y*(2*(SCREEN_H/6))-50, (SCREEN_W/4)*curseur_x+34, curseur_y*(2*(SCREEN_H/6))+50, makecol(0,0,255));
        blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

        if(keypressed())
        {
            carac=readkey();

            // gestion curseur
            if(key[KEY_UP])
            {
                if(curseur_y==1) curseur_y=2;
                else curseur_y--;
            }
            if(key[KEY_DOWN])
            {
                if(curseur_y==2) curseur_y=1;
                else curseur_y++;
            }
            if(key[KEY_RIGHT])
            {
                if(curseur_x==3) curseur_x=1;
                else curseur_x++;
            }
            if(key[KEY_LEFT])
            {
                if(curseur_x==1) curseur_x=3;
                else curseur_x--;
            }
        }
    }
    switch(curseur_y)
    {
    case 1 :
        hyp.push_back(jeu.getnom_complet(9+curseur_x-1));
        break;

    case 2:
        hyp.push_back(jeu.getnom_complet(9+curseur_x+2));
        break;

    default :
        break;
    }

    // choix carte perso
    rest(300);
    while(!key[KEY_ENTER])
    {
        // affichage selection
        clear_bitmap(tmp);
        blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
        jeu.afficher(tmp, 3);
        rect(tmp, (SCREEN_W/4)*curseur_x-34, curseur_y*(2*(SCREEN_H/6))-50, (SCREEN_W/4)*curseur_x+34, curseur_y*(2*(SCREEN_H/6))+50, makecol(0,0,255));
        blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

        if(keypressed())
        {
            carac=readkey();

            // gestion curseur
            if(key[KEY_UP])
            {
                if(curseur_y==1) curseur_y=2;
                else curseur_y--;
            }
            if(key[KEY_DOWN])
            {
                if(curseur_y==2) curseur_y=1;
                else curseur_y++;
            }
            if(key[KEY_RIGHT])
            {
                if(curseur_x==3) curseur_x=1;
                else curseur_x++;
            }
            if(key[KEY_LEFT])
            {
                if(curseur_x==1) curseur_x=3;
                else curseur_x--;
            }
        }
    }
    switch(curseur_y)
    {
    case 1 :
        hyp.push_back(jeu.getnom_complet(15+curseur_x-1));
        break;

    case 2:
        hyp.push_back(jeu.getnom_complet(15+curseur_x+2));
        break;

    default :
        break;
    }

    // contester
    curseur_x=1;
    for(int i=0;i<liste.size();i++)
    {
        if((i!=joueur_en_cours)&&(liste[i]->en_lice()))
        {
            clear_bitmap(tmp);
            blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
            textprintf_ex(tmp,font,(SCREEN_W/2)-(15*SCREEN_W/130),(SCREEN_H/2),makecol(200, 170, 16),-1,"Le joueur %d peut-il contester ?", i+1);
            blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
            rest(1250);
            while(!key[KEY_ENTER])
            {
                clear_bitmap(tmp);
                blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
                textprintf_ex(tmp,font,(SCREEN_W/2)-(15*SCREEN_W/130),(SCREEN_H/4),makecol(200, 170, 16),-1,"Le joueur %d peut-il contester ?", i+1);
                textprintf_ex(tmp,font,(SCREEN_W/2)-((23+(hyp[0].size()+hyp[1].size()+hyp[2].size())/2)*SCREEN_W/130),3*(SCREEN_H/4),makecol(200, 170, 16),-1,"Hypothese : %s va declancher le Ragnarok a %s avec %s", hyp[2].c_str(), hyp[0].c_str(), hyp[1].c_str());
                liste[i]->afficher_main(tmp, SCREEN_W/2 - (liste[i]->getnbrcartes())/2*(75), SCREEN_H/2 - 50);
                rect(tmp, SCREEN_W/2 - (liste[i]->getnbrcartes())/2*(75) + 75*(curseur_x-1), SCREEN_H/2 - 50, SCREEN_W/2 - (liste[i]->getnbrcartes())/2*(75) + 75*(curseur_x-1) + 69, SCREEN_H/2 + 50, makecol(0,0,255));
                blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

                if(keypressed())
                {
                    carac=readkey();

                    if(key[KEY_RIGHT])
                    {
                        if(curseur_x==(liste[i]->getnbrcartes())) curseur_x=1;
                        else curseur_x++;
                    }
                    if(key[KEY_LEFT])
                    {
                        if(curseur_x==1) curseur_x= (liste[i]->getnbrcartes()) ;
                        else curseur_x--;
                    }
                }
            }

            // validation contestation
            for(int j=0;j<3;j++)
            {
                if(hyp[j]==liste[i]->getnomcarte(curseur_x-1))
                {
                    string_tmp = liste[i]->getpseudo() + " conteste la carte " + hyp[j] ;
                    messages_erreur.push_back(string_tmp);
                }
            }
        }
    }

    // affichage resultat des constestations
    clear_bitmap(tmp);
    blit(couche1, tmp,0,0,0,0,SCREEN_W, SCREEN_H);
    textprintf_ex(tmp,font,(SCREEN_W/2)-(14*SCREEN_W/130),(SCREEN_H/2) - 50,makecol(200, 170, 16),-1,"Retour au tour du joueur %d :", joueur_en_cours+1);
    for(int i=0;i<messages_erreur.size();i++) textprintf_ex(tmp,font,(SCREEN_W/2)-(((messages_erreur[i].size())/2)*SCREEN_W/130),(SCREEN_H/2) + 50 + 20*i,makecol(200, 170, 16),-1,"%s", messages_erreur[i].c_str());
    if ((messages_erreur.size())<1) textprintf_ex(tmp,font,(SCREEN_W/2)-(18*SCREEN_W/130),(SCREEN_H/2) + 80,makecol(200, 170, 16),-1,"Personne ne conteste votre hypothese");
    textprintf_ex(tmp, font, SCREEN_W/2 - 16*(SCREEN_W/130), 5*(SCREEN_H/6), makecol(200, 170, 16), -1, "APPUYEZ SUR ENTRER POUR CONTINUER");
    blit(tmp, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
    rest(250);
    while (!key[KEY_ENTER])
    {

    }
    destroy_bitmap(tmp);
    destroy_bitmap(couche1);
    std::cout << "HINNN" ;
}

void Yggdrasil::bonus(std::vector<Joueur*> liste, int joueur_en_cours, Pioche &jeu) // gere les cases bonus
{
    char carac;
    int alea, couleur, choix_joueur=1, choix_carte=0, indice=1;
    bool bool_chemin=false, bool_salle,bool_bifrost = false;
    std::vector<int> tab={0,0,0,0,1,1,1,1,1,2}; // tableau de int représentant les différents bonus possibles et leur probabilité
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* decor=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* couche1=create_bitmap(SCREEN_W, SCREEN_H);

    afficher(decor, liste, joueur_en_cours, 0);
    for(int i=0;i<=SCREEN_W;i++) // affichage du plateau en "sous-brillance"
    {
        for(int j=0;j<=SCREEN_H;j++)
        {
            couleur=getpixel(decor,i,j);
            putpixel(decor,i,j,makecol(getr(couleur)/3, getg(couleur)/3, getb(couleur)/3));
        }
    }
    blit(decor, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

    /// Effet loterie + tirage au sort du bonus
    for(int i=0;i<50;i++)
    {
        alea=rand()%3;
        textprintf_ex(buffer, font, SCREEN_W/2 - 8*(SCREEN_W/130), SCREEN_H/2 - 30, makecol(200, 170, 16), -1, "Votre bonus est :");
        if(alea!=0) textprintf_ex(buffer, font, SCREEN_W/2 - 12*(SCREEN_W/130), SCREEN_H/2, makecol(200, 170, 16), -1, "- Teleportation au choix");
        else textprintf_ex(buffer, font, SCREEN_W/2 - 12*(SCREEN_W/130), SCREEN_H/2, makecol(255, 0, 0), -1, "- Teleportation au choix");
        if(alea!=1) textprintf_ex(buffer, font, SCREEN_W/2 - 17*(SCREEN_W/130), SCREEN_H/2 +15, makecol(200, 170, 16), -1, "- Voir une carte d'une main adverse");
        else textprintf_ex(buffer, font, SCREEN_W/2 - 17*(SCREEN_W/130), SCREEN_H/2 +15, makecol(255, 0, 0), -1, "- Voir une carte d'une main adverse");
        if(alea!=2) textprintf_ex(buffer, font, SCREEN_W/2 - 15*(SCREEN_W/130), SCREEN_H/2 +30, makecol(200, 170, 16), -1, "- Voir une carte de la solution");
        else textprintf_ex(buffer, font, SCREEN_W/2 - 15*(SCREEN_W/130), SCREEN_H/2 + 30, makecol(255, 0, 0), -1, "- Voir une carte de la solution");
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        rest(35);
    }
    alea=rand()%(tab.size()); // tirage au sort du bonus
    textprintf_ex(buffer, font, SCREEN_W/2 - 8*(SCREEN_W/130), SCREEN_H/2 - 30, makecol(200, 170, 16), -1, "Votre bonus est :");
    if(tab[alea]!=0) textprintf_ex(buffer, font, SCREEN_W/2 - 12*(SCREEN_W/130), SCREEN_H/2, makecol(200, 170, 16), -1, "- Teleportation au choix");
    else textprintf_ex(buffer, font, SCREEN_W/2 - 12*(SCREEN_W/130), SCREEN_H/2, makecol(255, 0, 0), -1, "- Teleportation au choix");
    if(tab[alea]!=1) textprintf_ex(buffer, font, SCREEN_W/2 - 17*(SCREEN_W/130), SCREEN_H/2 +15, makecol(200, 170, 16), -1, "- Voir une carte d'une main adverse");
    else textprintf_ex(buffer, font, SCREEN_W/2 - 17*(SCREEN_W/130), SCREEN_H/2 +15, makecol(255, 0, 0), -1, "- Voir une carte d'une main adverse");
    if(tab[alea]!=2) textprintf_ex(buffer, font, SCREEN_W/2 - 15*(SCREEN_W/130), SCREEN_H/2 +30, makecol(200, 170, 16), -1, "- Voir une carte de la solution");
    else textprintf_ex(buffer, font, SCREEN_W/2 - 15*(SCREEN_W/130), SCREEN_H/2 + 30, makecol(255, 0, 0), -1, "- Voir une carte de la solution");
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    rest(1750);

    if(tab[alea]==0) // teleportation au choix
    {
        while(!key[KEY_ENTER])
        {
            afficher(screen, liste, joueur_en_cours, 1);

            if(keypressed())
            {
                carac=readkey();

                if(key[KEY_UP]) deplacement_joueur(0, -1, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 1, jeu);

                if(key[KEY_DOWN]) deplacement_joueur(0, 1, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 1, jeu);

                if(key[KEY_LEFT]) deplacement_joueur(-1, 0, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 1, jeu);

                if(key[KEY_RIGHT]) deplacement_joueur(1, 0, bool_chemin, bool_salle,bool_bifrost, liste, joueur_en_cours, 1, jeu);
            }
        }
    }

    if(tab[alea]==1) // voir une carte de la main d'un adversaire
    {
        blit(decor, couche1, 0,0,0,0,SCREEN_W, SCREEN_H);
        textprintf_ex(couche1, font, SCREEN_W/2 - 24*(SCREEN_W/135), SCREEN_H/4, makecol(200, 170, 16), -1, "De quel joueur voulez-vous decouvrir une carte ?");
        for(int i=0;i<liste.size();i++)
        {
            if(i!=joueur_en_cours)
            {
                textprintf_ex(couche1, font, SCREEN_W/2 - (liste[i]->getpseudo().size()/2)*(SCREEN_W/130), SCREEN_H/4 + indice*(SCREEN_H/6), makecol(200, 170, 16), -1, "%s", liste[i]->getpseudo().c_str());
                indice++;
            }
        }
        while(!key[KEY_ENTER]) // choix du joueur
        {
            blit(couche1,buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
            rect(buffer, SCREEN_W/2-(10*(SCREEN_W/90)),SCREEN_H/4 + choix_joueur*(SCREEN_H/6) - SCREEN_H/25, SCREEN_W/2+(10*(SCREEN_W/90)), SCREEN_H/4 + choix_joueur*(SCREEN_H/6) + SCREEN_H/24, makecol(200, 170, 16));
            blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);

            if(keypressed())
            {
                carac=readkey();

                if(key[KEY_DOWN])
                {
                    choix_joueur=(choix_joueur+1)%(liste.size());
                    if(choix_joueur==0) choix_joueur=1;
                }
                if(key[KEY_UP])
                {
                    if(choix_joueur==1) choix_joueur=(liste.size())-1;
                    else choix_joueur--;
                }
            }
        }
        rest(250);
        while(!key[KEY_ENTER]) // choix de la carte
        {
            clear_bitmap(buffer);
            blit(decor, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
            if((liste[choix_joueur-1]->getnbrcartes())<(liste[0]->getnbrcartes()))
            {
                liste[choix_joueur-1]->afficher_dosmain(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2) - 34, SCREEN_H/2 - 50, -1);
                rect(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2) - 34 + choix_carte*75,SCREEN_H/2 - 50, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2)+69 + choix_carte*75 - 34, SCREEN_H/2 + 50, makecol(0,0, 255));
            }
            else
            {
                liste[choix_joueur-1]->afficher_dosmain(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2), SCREEN_H/2 - 50, -1);
                rect(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2) + choix_carte*75,SCREEN_H/2 - 50, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2)+69+ choix_carte*75, SCREEN_H/2 + 50, makecol(0,0, 255));
            }
            blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);

            if(keypressed()) // gestion curseur
            {
                carac=readkey();

                if(key[KEY_LEFT])
                {
                    if(choix_carte==0) choix_carte=liste[choix_joueur-1]->getnbrcartes() -1;
                    else choix_carte--;
                }
                if(key[KEY_RIGHT]) choix_carte=(choix_carte+1)%(liste[choix_joueur-1]->getnbrcartes());
            }
        }
        clear_bitmap(buffer);
        blit(decor, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
        if((liste[choix_joueur-1]->getnbrcartes())<(liste[0]->getnbrcartes()))
        {
            liste[choix_joueur-1]->afficher_dosmain(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2) - 34, SCREEN_H/2 - 50, choix_carte);
            rect(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2) - 34 + choix_carte*75,SCREEN_H/2 - 50, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2)+69 + choix_carte*75 - 34, SCREEN_H/2 + 50, makecol(0,0, 255));
        }
        else
        {
            liste[choix_joueur-1]->afficher_dosmain(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2), SCREEN_H/2 - 50, choix_carte);
            rect(buffer, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2) + choix_carte*75,SCREEN_H/2 - 50, SCREEN_W/2 - 75*((liste[choix_joueur-1]->getnbrcartes())/2)+69+ choix_carte*75, SCREEN_H/2 + 50, makecol(0,0, 255));
        }
        textprintf_ex(buffer, font, SCREEN_W/2 - 16*(SCREEN_W/135), SCREEN_H/2 + 60, makecol(200, 170, 16), -1, "APPUYEZ SUR ENTRER POUR CONTINUER");
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        rest(500);
        while(!key[KEY_ENTER])
        {

        }
    }

    if(tab[alea]==2) // voir une carte de la solution
    {
        while(!key[KEY_ENTER]) // choix de la carte
        {
            clear_bitmap(buffer);
            blit(decor, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
            jeu.afficher_dosSolution(buffer, SCREEN_W/2 - 110, SCREEN_H/2 - 50, -1);
            rect(buffer, SCREEN_W/2 - 110 + choix_carte*75,SCREEN_H/2 - 50, SCREEN_W/2 - 110 + choix_carte*75 +69, SCREEN_H/2 + 50, makecol(0,0, 255));
            blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);

            if(keypressed()) // gestion curseur
            {
                carac=readkey();

                if(key[KEY_LEFT])
                {
                    if(choix_carte==0) choix_carte=2;
                    else choix_carte--;
                }
                if(key[KEY_RIGHT]) choix_carte=(choix_carte+1)%3;
            }
        }
        clear_bitmap(buffer);
        blit(decor, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
        jeu.afficher_dosSolution(buffer, SCREEN_W/2 - 110, SCREEN_H/2 - 50, choix_carte);
        rect(buffer, SCREEN_W/2 - 110 + choix_carte*75,SCREEN_H/2 - 50, SCREEN_W/2 - 110 + choix_carte*75 +69, SCREEN_H/2 + 50, makecol(0,0, 255));
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        textprintf_ex(buffer, font, SCREEN_W/2 - 16*(SCREEN_W/135), SCREEN_H/2 + 60, makecol(200, 170, 16), -1, "APPUYEZ SUR ENTRER POUR CONTINUER");
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        rest(500);
        while(!key[KEY_ENTER])
        {

        }
    }

    destroy_bitmap(buffer);
    destroy_bitmap(decor);
    destroy_bitmap(couche1);
}


void Yggdrasil::save_plateau()
{
    int i,j,taille1,taille2;
    std::ofstream mon_Flux("Fichier/Sauvegarde.txt",std::ios::app);

    taille1=m_tab.size();
    if(mon_Flux)
    {
        for(i=0;i<taille1;i++)
        {
            taille2=m_tab[i].size();
            for(j=0;j<taille2;j++)
            {
                mon_Flux<<m_tab[i][j]<<" ";
            }
            mon_Flux<<"\n";
        }

    }else
    {
        allegro_message("ERREUR PL: Impossible d'ouvrir le fichier");
    }
}

int Yggdrasil::Bifrost(BITMAP* buffer, Pioche &jeu, std::vector<Joueur*> liste, int joueur_en_cours)
{
    int choix=0, couleur;
    BITMAP* tmp=create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* couche1=create_bitmap(SCREEN_W, SCREEN_H); // decor (plateau,cartes joueurs, ...)

    /// Affichage plaeau sous_brillance
    afficher(couche1, liste, joueur_en_cours,1);
    for(int i=0;i<SCREEN_W;i++) // affichage du plateau en "sous-brillance"
    {
        for(int j=0;j<SCREEN_H;j++)
        {
            couleur=getpixel(couche1,i,j);
            putpixel(couche1,i,j,makecol(getr(couleur)/3, getg(couleur)/3, getb(couleur)/3));
        }
    }
    blit(couche1, tmp, 0,0,0,0, SCREEN_W, SCREEN_H);

    /// Demande de verification
    if (((liste[joueur_en_cours]->getx() == 3)&&(liste[joueur_en_cours]->gety() == 9))||((liste[joueur_en_cours]->getx() == 5)&&(liste[joueur_en_cours]->gety() == 2)))
    {
        textprintf_ex(tmp, font, SCREEN_W/2 -18*(SCREEN_W/130), SCREEN_H/2 - 15, makecol(200, 170, 16), -1, "Etes-vous certain de vouloir utiliser le Bifrost ?");
        textprintf_ex(tmp, font, SCREEN_W/2 -10*(SCREEN_W/130), SCREEN_H/2 + 15, makecol(200, 170, 16), -1, "OUI : O   |   NON : N");
    }

    else if(((liste[joueur_en_cours]->getx() == 7)&&(liste[joueur_en_cours]->gety() == 0))||((liste[joueur_en_cours]->getx() == 12)&&(liste[joueur_en_cours]->gety() == 10)))
    {
        textprintf_ex(tmp, font, SCREEN_W/2 -18*(SCREEN_W/130), SCREEN_H/2 - 15, makecol(200, 170, 16), -1, "Etes-vous certain de vouloir monter sur le dos de Hugin, le corbeau d'Odin ?");
        textprintf_ex(tmp, font, SCREEN_W/2 -10*(SCREEN_W/130), SCREEN_H/2 + 15, makecol(200, 170, 16), -1, "OUI : O   |   NON : N");
    }

    else
    {
        choix = 2;
    }

    blit(tmp, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    while(choix==0)
    {
        if(key[KEY_O]) choix=1;
        if(key[KEY_N]) choix=2;
    }


    destroy_bitmap(tmp);
    destroy_bitmap(couche1);

    return choix;
}

