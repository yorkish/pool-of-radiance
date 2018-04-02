#pragma once

#include "Texte.h"

class ListeTexte {
	public:
		ListeTexte(Renderer &renderer);

		bool init();
        void handleEvent( TInfoTouches& infTouches );
		void draw();
		void release();

		void addTexte(int id, int colonne, int ligne,
		              Couleur couleurTexte,
		              Couleur couleurPremiereLettre = Couleur::sameColor,
		              Couleur couleurDerniereLettre = Couleur::sameColor);

		void addTexte(std::string texte, int colonne, int ligne,
		              Couleur couleurTexte,
		              Couleur couleurPremiereLettre = Couleur::sameColor,
		              Couleur couleurDerniereLettre = Couleur::sameColor);

		bool isEmpty();
		void reset();

		~ListeTexte();

	private:
		std::string getTexte(int id);

		std::vector <Texte*> lstTexte;

        Renderer&   renderer;
		SDL_Texture* imageFont;
};

