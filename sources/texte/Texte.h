#pragma once

#include <list>
#include "../common/Affichage.h"

class Texte 
{
    public :

        Texte(SDL_Surface* imageFont);
		void draw();
		static void release();

		void setPosition(int x, int y);
		void setCouleurs(Couleur couleurTexte, Couleur couleurPremiereLettre, Couleur CouleurDerniereLettre);
		void setTexte(std::string texte = "");

		~Texte();

	private :

        void drawLettre(int pos, char lettre, int x, int y);

		int     idTexte;
	    char*   tabTexte;
		int     tabTexteMax;
		Couleur couleurTexte;
		Couleur couleurPremiereLettre;
		Couleur couleurDerniereLettre;

		int posX;
        int posY;

        SDL_Surface* fontPremiereLettre;
        SDL_Surface* fontTexte;
        SDL_Surface* fontDerniereLettre;
        Affichage&  oAffichage;
};
