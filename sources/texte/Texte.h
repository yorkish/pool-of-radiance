#pragma once

#include <list>
#include "../common/Renderer.h"

class Texte 
{
    public :

        Texte(Renderer &renderer, SDL_Texture* imageFont);
		void draw();
		static void release();

		void setPosition(int x, int y);
		void setCouleurs(Couleur couleurTexte, Couleur couleurPremiereLettre, Couleur CouleurDerniereLettre);
		void setTexte(std::string texte = "");

		~Texte();

	private :

        void drawLettre(int pos, char lettre, int x, int y);

        Renderer& renderer;

		int     idTexte;
	    char*   tabTexte;
		int     tabTexteMax;
		Couleur couleurPremiereLettre;
		Couleur couleurTexte;
		Couleur couleurDerniereLettre;

		int posX;
        int posY;

        SDL_Texture* imageFont;
};
