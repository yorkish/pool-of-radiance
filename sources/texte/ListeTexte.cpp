#include "ListeTexte.h"

using namespace std;

ListeTexte::ListeTexte(Renderer &renderer): renderer(renderer), imageFont(0)
{}

bool ListeTexte::init()
{
	imageFont = renderer.loadImage("assets/font.png", 0, 0, 0);

	return (imageFont != 0);
}

void ListeTexte::handleEvent( TInfoTouches& infTouches )
{}

void ListeTexte::draw()
{
	int size = lstTexte.size();
	for(int i = 0; i < size; i++)
		lstTexte[i]->draw();
}

void ListeTexte::addTexte(string texte, int colonne, int ligne, Couleur couleurTexte, Couleur couleurPremiereLettre, Couleur couleurDerniereLettre)
{
	Texte* unTexte = new Texte(renderer, imageFont);
	//_gblMemory.push_back(InfoAlloc('A',__FILE__, __LINE__));

	unTexte->setPosition(colonne*8, ligne*8);
	unTexte->setCouleurs(couleurTexte, couleurPremiereLettre, couleurDerniereLettre);
	unTexte->setTexte(texte);

	lstTexte.push_back( unTexte );
}

void ListeTexte::addTexte(int id, int colonne, int ligne, Couleur couleurTexte, Couleur couleurPremiereLettre, Couleur couleurDerniereLettre)
{
	addTexte( getTexte(id), colonne, ligne, couleurTexte, couleurPremiereLettre, couleurDerniereLettre);
}

string ListeTexte::getTexte(int id)
{
	string texte;

	switch (id)
	{
		case 0 : texte = "loading...please wait" ; break;
		default: texte = "Indice inconnu"        ; break;
	}

	return texte;
}

bool ListeTexte::isEmpty()
{
	return lstTexte.size() == 0;
}

void ListeTexte::reset()
{
	int size = lstTexte.size();
	for(int i = 0; i < size; i++)
		delete lstTexte[i];

	lstTexte.clear();
}

void ListeTexte::release() {}

ListeTexte::~ListeTexte()
{
	reset();
}
