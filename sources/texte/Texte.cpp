#include <string>
#include <cstring>
#include <list>
#include <SDL2/SDL.h>
#include <iostream>
#include "Texte.h"

using namespace std;

Texte::Texte(Renderer &renderer, SDL_Texture* imageFont) : renderer(renderer), idTexte(-1), tabTexte(0),
										tabTexteMax(-1), couleurPremiereLettre(Couleur::white), couleurTexte(Couleur::white),
										couleurDerniereLettre(Couleur::white),posX(0), posY(0)
{
	this->imageFont = imageFont;
}

void Texte::draw()
{
	int posLettreX, posLettreY;

	posLettreX = posX ; posLettreY = posY;

	for (int i = 0; i < tabTexteMax; i++)
	{
		drawLettre(i, tabTexte[i], posLettreX, posLettreY);
		posLettreX += 8;
	}
}

void Texte::drawLettre(int pos, char lettre, int x, int y)
{
	SDL_Rect src;

	switch (lettre)
	{
		case 'a': case 'A': src.x = 0 ; src.y = 0 ; break;
		case 'b': case 'B': src.x = 1 ; src.y = 0 ; break;
		case 'c': case 'C': src.x = 2 ; src.y = 0 ; break;
		case 'd': case 'D': src.x = 3 ; src.y = 0 ; break;
		case 'e': case 'E': src.x = 4 ; src.y = 0 ; break;
		case 'f': case 'F': src.x = 5 ; src.y = 0 ; break;
		case 'g': case 'G': src.x = 6 ; src.y = 0 ; break;
		case 'h': case 'H': src.x = 7 ; src.y = 0 ; break;
		case 'i': case 'I': src.x = 0 ; src.y = 1 ; break;
		case 'j': case 'J': src.x = 1 ; src.y = 1 ; break;
		case 'k': case 'K': src.x = 2 ; src.y = 1 ; break;
		case 'l': case 'L': src.x = 3 ; src.y = 1 ; break;
		case 'm': case 'M': src.x = 4 ; src.y = 1 ; break;
		case 'n': case 'N': src.x = 5 ; src.y = 1 ; break;
		case 'o': case 'O': src.x = 6 ; src.y = 1 ; break;
		case 'p': case 'P': src.x = 7 ; src.y = 1 ; break;
		case 'q': case 'Q': src.x = 0 ; src.y = 2 ; break;
		case 'r': case 'R': src.x = 1 ; src.y = 2 ; break;
		case 's': case 'S': src.x = 2 ; src.y = 2 ; break;
		case 't': case 'T': src.x = 3 ; src.y = 2 ; break;
		case 'u': case 'U': src.x = 4 ; src.y = 2 ; break;
		case 'v': case 'V': src.x = 5 ; src.y = 2 ; break;
		case 'w': case 'W': src.x = 6 ; src.y = 2 ; break;
		case 'x': case 'X': src.x = 7 ; src.y = 2 ; break;
		case 'y': case 'Y': src.x = 0 ; src.y = 3 ; break;
		case 'z': case 'Z': src.x = 1 ; src.y = 3 ; break;

		case '0'  : src.x = 2 ; src.y = 3 ; break;
		case '1'  : src.x = 3 ; src.y = 3 ; break;
		case '2'  : src.x = 4 ; src.y = 3 ; break;
		case '3'  : src.x = 5 ; src.y = 3 ; break;
		case '4'  : src.x = 6 ; src.y = 3 ; break;
		case '5'  : src.x = 7 ; src.y = 3 ; break;

		case '6'  : src.x = 0 ; src.y = 4 ; break;
		case '7'  : src.x = 1 ; src.y = 4 ; break;
		case '8'  : src.x = 2 ; src.y = 4 ; break;
		case '9'  : src.x = 3 ; src.y = 4 ; break;
		case '!'  : src.x = 4 ; src.y = 4 ; break;
		case '"'  : src.x = 5 ; src.y = 4 ; break;
		case '#'  : src.x = 6 ; src.y = 4 ; break;
		case '&'  : src.x = 7 ; src.y = 4 ; break;

		case '\'' : src.x = 0 ; src.y = 5 ; break;
		case '('  : src.x = 1 ; src.y = 5 ; break;
		case ')'  : src.x = 2 ; src.y = 5 ; break;
		case '*'  : src.x = 3 ; src.y = 5 ; break;
		case '+'  : src.x = 4 ; src.y = 5 ; break;
		case ','  : src.x = 5 ; src.y = 5 ; break;
		case '-'  : src.x = 6 ; src.y = 5 ; break;
		case '.'  : src.x = 7 ; src.y = 5 ; break;

		case '/'  : src.x = 0 ; src.y = 6 ; break;
		case ':'  : src.x = 1 ; src.y = 6 ; break;
		case ';'  : src.x = 2 ; src.y = 6 ; break;
		case '<'  : src.x = 3 ; src.y = 6 ; break;
		case '>'  : src.x = 4 ; src.y = 6 ; break;
		case '='  : src.x = 5 ; src.y = 6 ; break;
		case '?'  : src.x = 6 ; src.y = 6 ; break;
		case '@'  : src.x = 7 ; src.y = 6 ; break;

		case ' '  : src.x = 0 ; src.y = 7 ; break;

		default : break;
	}

	src.h  = 8 ; src.w  = 8;
	src.x *= 8 ; src.y *= 8;

	if (pos == 0)
	{
		renderer.applyTextureColorMod(imageFont, couleurPremiereLettre);
		renderer.applyTexture(x, y, imageFont, src);
	}
	else if (pos == tabTexteMax -1)
	{
		renderer.applyTextureColorMod(imageFont, couleurDerniereLettre);
		renderer.applyTexture(x, y, imageFont, src);
	}
	else
	{
		renderer.applyTextureColorMod(imageFont, couleurTexte);
		renderer.applyTexture(x, y, imageFont, src);
	}
}

void Texte::setTexte(string texte)
{
	//On va travailler avec des char pour rendre l'algo plus simple
	tabTexteMax = texte.length();

	tabTexte = new char [texte.size()+1];
	std::copy(texte.begin(), texte.end(), tabTexte);
	tabTexte[texte.size()] = '\0';
}

void Texte::setPosition(int x, int y)
{
	posX = x; posY = y;
}

void Texte::setCouleurs(Couleur couleurTexte, Couleur couleurPremiereLettre, Couleur CouleurDerniereLettre)
{
	this->couleurTexte = couleurTexte;

	if (couleurPremiereLettre == Couleur::sameColor)
		this->couleurPremiereLettre = couleurTexte;
	else
		this->couleurPremiereLettre = couleurPremiereLettre;

	if (CouleurDerniereLettre == Couleur::sameColor)
		this->couleurDerniereLettre = couleurTexte;
	else
		this->couleurDerniereLettre = CouleurDerniereLettre;
}

Texte::~Texte()
{
	delete[] tabTexte;
	//_gblMemory.push_back(InfoAlloc('R',__FILE__, __LINE__));
}
