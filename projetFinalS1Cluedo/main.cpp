#include "header.h"

int main()
{
    srand(time(NULL));
    initialisation_allegro();
    Partie game;
    int choix=0;
    bool musique = true;
    std::vector<std::string>msgs_choix;

    msgs_choix.push_back("Nouvelle partie");
    msgs_choix.push_back("Reprendre un partie");
    msgs_choix.push_back("Quitter");

    SAMPLE* musiqueMenu = load_sample("son/musiqueMenu.wav");
    if (!musiqueMenu)
    {
        allegro_message("Pas pu trouver le son Razmo !");
    }

    play_sample(musiqueMenu,100,100,1000,1);

    while(choix!=3)
    {
        if(key[KEY_G]&&(musique))
        {
            play_sample(musiqueMenu,100,100,1000,1);
            musique = false;
        }

        if (key[KEY_H]&&(!musique))
        {
            stop_sample(musiqueMenu);
            musique = true;
        }

        //choix=menu();
        choix=game.choix_allegro(0,true,"Veillez faire votre choix",msgs_choix);

        switch(choix)
        {
        case 1:
            /// NOUVELLE PARTIE

            destroy_sample(musiqueMenu);
            rest(300);
            game.nouvelle_partie();
            break;

        case 2:

            destroy_sample(musiqueMenu);
            ///  REPRENDRE PARTIE
            break;

        default:

            destroy_sample(musiqueMenu);
            break;
        }
    }
    return 0;
}END_OF_MAIN();
