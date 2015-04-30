#include "Affichage.h"
#include <iostream>
#include "Fichier.h"

using std::string;
using std::cout;
using std::endl;

// Initialisation du singleton à NULL
Affichage* Affichage::singleton = 0;

Affichage::Affichage() :
		fullScreen(0)
{

	Fichier oFic;

	renderer = 0;
	window = 0;
	screen = 0;

	src.w = SCREEN_WIDTH;
	src.h = SCREEN_HEIGHT;
	src.y = 0;
	src.x = 0;
	dst.x = 0;
	dst.y = 0;

	// Read window properties
	if (!oFic.ouvrirFichier(FILE_WINDOW_SETTING))
		printf("Could not open '%s'", FILE_WINDOW_SETTING.c_str());

	oFic.lireString(strCaption);
	oFic.lireString(strIcone);
	oFic.fermerFichier();
}

Affichage& Affichage::getInstance()
{
	if (singleton == 0)
		singleton = new Affichage();

	return *singleton;
}

bool Affichage::initRenderer()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Could not load SDL : %s\n", SDL_GetError());
		return false;
	}

	atexit(SDL_Quit);

	// Window Properties
	window = SDL_CreateWindow(strCaption.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	screen = SDL_CreateRGBSurface(0, TRAVAIL_WIDTH, TRAVAIL_HEIGHT, SCREEN_BPP, 0x00FF0000, 0x0000FF00, 0x000000FF,
			0xFF000000);

	renderer = SDL_CreateRenderer(window, -1, 0);

	// Icon
	SDL_Surface* icon = SDL_LoadBMP(strIcone.c_str());
	SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGB(icon->format, 0, 0, 0));
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	// Cursor
	SDL_ShowCursor(SDL_ENABLE);

	// Set logical 640x480
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (renderer != 0)
		return true;
	else
	{
		printf("Can't init window: %s\n", SDL_GetError());
		return false;
	}
}

SDL_Surface* Affichage::loadImage(string filename)
{
	return IMG_Load(filename.c_str());
}

SDL_Texture* Affichage::loadImage(string filename, Uint8 cKeyR, Uint8 cKeyG, Uint8 cKeyB)
{
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	Uint32 colorkey;

	surface = loadImage(filename);

	if (surface != NULL)
	{

		colorkey = SDL_MapRGB(surface->format, cKeyR, cKeyG, cKeyB);
		SDL_SetColorKey(surface, SDL_TRUE, colorkey);

		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);
	}

	return texture;
}

SDL_Surface* Affichage::loadImageAsSurface(string filename, Uint8 cKeyR, Uint8 cKeyG, Uint8 cKeyB)
{
	SDL_Surface* surface = NULL;
	SDL_Surface* optimizedSurface = NULL;
	Uint32 colorkey;

	surface = loadImage(filename);

	if (surface != NULL)
	{
		colorkey = SDL_MapRGB(surface->format, cKeyR, cKeyG, cKeyB);
		SDL_SetColorKey(surface, SDL_TRUE, colorkey);

		optimizedSurface = SDL_ConvertSurface(surface, screen->format, 0);

		SDL_FreeSurface(surface);
	}

	return optimizedSurface;
}

void Affichage::fillRect(SDL_Rect* clip, Couleur couleur)
{
	SDL_Color couleurRGB = mapColor(couleur);
	SDL_SetRenderDrawColor(renderer, couleurRGB.r, couleurRGB.g, couleurRGB.b, couleurRGB.a);
	SDL_RenderFillRect(renderer, clip);
}

void Affichage::fillRect(SDL_Surface* surface, SDL_Rect* clip, Couleur couleur)
{
	SDL_Color couleurRGB = mapColor(couleur);
	Uint32 fillColor = SDL_MapRGB(surface->format, couleurRGB.r, couleurRGB.g, couleurRGB.b);

	SDL_FillRect(surface, clip, fillColor);
}

void Affichage::wipeScreen(Couleur couleur)
{
	SDL_Color couleurRGB = mapColor(couleur);
	SDL_SetRenderDrawColor(renderer, couleurRGB.r, couleurRGB.g, couleurRGB.b, couleurRGB.a);
	SDL_RenderClear(renderer);
}

SDL_Surface* Affichage::copySurface(SDL_Surface* surface)
{
	SDL_Surface* newSurface = NULL;

	if (surface != NULL)
	{
		newSurface = SDL_ConvertSurface(surface, screen->format, 0);

		if (newSurface != NULL)
			SDL_BlitSurface(surface, NULL, newSurface, NULL);
	}

	return newSurface;
}

SDL_Surface* Affichage::swapColor(SDL_Surface* surface, Couleur oldColor, Couleur newColor)
{
	SDL_Surface* newSurface = NULL;

	if (surface == NULL)
		return newSurface;

	//On crée une nouvelle surface que l'on remplie de la nouvelle couleur
	newSurface = copySurface(surface);
	fillRect(newSurface, NULL, newColor);

	//On change le clé de transparence = la vieille couleur
	setColorKey(surface, oldColor);

	//On applique la surface source sur la nouvelle surface
	//Ce qui donnera changera l'ancienne couleur par la nouvelle
	SDL_BlitSurface(surface, NULL, newSurface, NULL);

	//On applique la clé de transparence sur la nouvelle surface (noir)
	setColorKey(newSurface, cNOIR);

	SDL_FreeSurface(surface);

	return newSurface;
}

void Affichage::setColorKey(SDL_Surface* surface, Couleur couleur)
{
	SDL_Color couleurRGB;
	Uint32 colorKey;

	couleurRGB = mapColor(couleur);
	colorKey = SDL_MapRGB(surface->format, couleurRGB.r, couleurRGB.g, couleurRGB.b);
	SDL_SetColorKey(surface, SDL_TRUE, colorKey);
}

void Affichage::applySurface(int x, int y, SDL_Surface* source, SDL_Rect& clip)
{
	/*SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	//On blit la surface
	SDL_BlitSurface(source, &clip, surfaceTravail, &offset);*/
}

/*void Affichage::drawPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B) {
 Uint32 color = SDL_MapRGB(surfaceTravail->format, R, G, B);

 switch(surfaceTravail->format->BytesPerPixel) {
 case 1: // Assuming 8-bpp
 {
 Uint8 *bufp;
 bufp = (Uint8 *) surfaceTravail->pixels + y * surfaceTravail->pitch + x;
 *bufp = color;
 }
 break;

 case 2: // Probably 15-bpp or 16-bpp
 {
 Uint16 *bufp;
 bufp = (Uint16 *) surfaceTravail->pixels + y * surfaceTravail->pitch
 / 2 + x;
 *bufp = color;
 }
 break;

 case 3: // Slow 24-bpp mode, usually not used
 {
 Uint8 *bufp;
 bufp = (Uint8 *) surfaceTravail->pixels + y * surfaceTravail->pitch + x
 * 3;
 if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
 bufp[0] = color;
 bufp[1] = color >> 8;
 bufp[2] = color >> 16;
 } else {
 bufp[2] = color;
 bufp[1] = color >> 8;
 bufp[0] = color >> 16;
 }
 }
 break;

 case 4: // Probably 32-bpp
 {
 Uint32 *bufp;
 bufp = (Uint32 *) surfaceTravail->pixels + y * surfaceTravail->pitch
 / 4 + x;
 *bufp = color;
 }
 break;
 }
 }*/

void Affichage::introduireDelai(Uint32 msec)
{
	SDL_Delay(msec);
}

void Affichage::toggleFullScreen()
{
	/*	fullScreen = (fullScreen ? 0 : SDL_WINDOW_FULLSCREEN);

	 fullScreen ? SDL_ShowCursor(SDL_DISABLE) : SDL_ShowCursor(SDL_ENABLE);
	 */
}

void Affichage::preRender()
{
	SDL_RenderClear(renderer);
}

void Affichage::postRender()
{
	SDL_RenderPresent(renderer);
}

SDL_Color Affichage::mapColor(Couleur color)
{

	switch (color)
	{
	case cNOIR:
		return COUL_NOIR;
	case cBLEU:
		return COUL_BLEU;
	case cVERT:
		return COUL_VERT;
	case cCYAN:
		return COUL_CYAN;
	case cROUGE:
		return COUL_ROUGE;
	case cMAGENTA:
		return COUL_MAGENTA;
	case cBRUN:
		return COUL_BRUN;
	case cGRIS_CLAIR:
		return COUL_GRIS_CLAIR;
	case cGRIS_FONCE:
		return COUL_GRIS_FONCE;
	case cBLEU_CLAIR:
		return COUL_BLEU_CLAIR;
	case cVERT_CLAIR:
		return COUL_VERT_CLAIR;
	case cCYAN_CLAIR:
		return COUL_CYAN_CLAIR;
	case cROUGE_CLAIR:
		return COUL_ROUGE_CLAIR;
	case cMAGENTA_CLAIR:
		return COUL_MAGENTA_CLAIR;
	case cJAUNE:
		return COUL_JAUNE;
	case cBLANC:
		return COUL_BLANC;

	case cMEME_COULEUR:
	default:
		return COUL_BLANC;
	}
}

Affichage::~Affichage()
{
	if (singleton != 0)
		delete singleton;

	//Destroy window
	if (renderer != 0)
		SDL_DestroyRenderer(renderer);

	if (window != 0)
		SDL_DestroyWindow(window);

	singleton = 0;
	window = 0;
	renderer = 0;
}
