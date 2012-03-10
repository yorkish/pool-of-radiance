#pragma once

#include "Texte.h"

class ListeTexte {
	public:
		ListeTexte();

		bool init();
        void handleEvent( TInfoTouches& infTouches );
		void draw();
		void release();

		void addTexte(int id, int colonne, int ligne,
		              Couleur couleurTexte,
		              Couleur couleurPremiereLettre = cMEME_COULEUR,
		              Couleur couleurDerniereLettre = cMEME_COULEUR);

		void addTexte(std::string texte, int colonne, int ligne,
		              Couleur couleurTexte,
		              Couleur couleurPremiereLettre = cMEME_COULEUR,
		              Couleur couleurDerniereLettre = cMEME_COULEUR);

		bool isEmpty();
		void reset();

		~ListeTexte();

	private:
		std::string getTexte(int id);

		std::vector <Texte*> lstTexte;

        Affichage&   oAffichage;
		SDL_Surface* imageFont;
};

