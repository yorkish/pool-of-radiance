#include "Fichier.h"

using namespace std;

Fichier::Fichier()
{}

bool Fichier::ouvrirFichier( string nomFichier, int mode )
{
	fermerFichier();
	
	if ( mode == LECTURE )
		unFichier.open( nomFichier.c_str(), ios::in );
	else
		unFichier.open( nomFichier.c_str(), ios::out );
	
	this->mode = mode;
	return unFichier.is_open();
}

bool Fichier::lireString( string &valeur )
{
	string uneLigne;
	
	if (!unFichier.is_open() && mode != LECTURE )
		return false;
	
	if (getline(unFichier, uneLigne))
	{
		valeur = uneLigne;

		return true;
	}
	else
		return false;
}

bool Fichier::ecrireString( string &valeur )
{
	if (!unFichier.is_open() && mode != ECRITURE )
		return false;
	
	unFichier << valeur;

	return !unFichier.fail();
}

bool Fichier::ecrireCaractere( char valeur )
{
	if (!unFichier.is_open() && mode != ECRITURE )
		return false;
	
	unFichier << valeur;

	return !unFichier.fail();
}

bool Fichier::lireEntier( int &valeur )
{
	if (!unFichier.is_open() && mode != LECTURE )
		return false;
	
	unFichier >> valeur;
	return !unFichier.fail();
}

bool Fichier::ecrireEntier( int valeur )
{
	if ( !unFichier.is_open() && mode != ECRITURE )
		return false;
	
	unFichier << valeur;
	return !unFichier.fail();
}

bool Fichier::lireTuile( int &ID )
{
	if (!unFichier.is_open() && mode != LECTURE )
		return false;
	
	unFichier >> ID;

	return !unFichier.fail();
}

void Fichier::fermerFichier()
{
	if (unFichier.is_open())
		unFichier.close();
}

Fichier::~Fichier()
{ fermerFichier(); }
