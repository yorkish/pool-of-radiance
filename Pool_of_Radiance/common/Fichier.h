#pragma once

#include <fstream>
#include <string>

static const int LECTURE = 2;
static const int ECRITURE = 4;

class Fichier
{
	public:
		Fichier();
		
		bool ouvrirFichier( std::string nomFichier, int mode=LECTURE );
		
		bool lireString( std::string &valeur );
		bool ecrireString( std::string &valeur );
		
		bool ecrireCaractere( char valeur );		
		
		bool lireEntier( int &valeur );
		bool ecrireEntier( int valeur );
		
		bool lireTuile( int &ID );

		void fermerFichier();
		
		~Fichier();

	private:
		std::fstream unFichier;
		int mode;

};
