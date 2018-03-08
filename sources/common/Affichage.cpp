#include "Affichage.h"
#include <iostream>
#include "Fichier.h"
#include <jeayeson/jeayeson.hpp>

using std::string;
using std::cout;
using std::endl;

// Initialisation du singleton à NULL
Affichage* Affichage::singleton = 0;

Affichage::Affichage()
		: fullScreen(0)
{
	renderer = 0;
	window = 0;
	screen = 0;
	sdlTexture = 0;

	src.w = 0;
	src.h = 0;
	src.y = 0;
	src.x = 0;
	dst.x = 0;
	dst.y = 0;

	delay = 0;
}

Affichage& Affichage::getInstance()
{
	if (singleton == 0) singleton = new Affichage();

	return *singleton;
}

bool Affichage::initRenderer()
{
	// Get init parameters from config file
	json_map config { json_file { "data/settings/renderer.json" } };

	std::string windowTitle( config["window"]["title"] );
	std::string windowIcon( config["window"]["icon"] );

	json_int screenWidth = json_int( config["screen"]["width"] );
	json_int screenHeight = json_int( config["screen"]["height"] );
	//json_int screenBPP = json_int( config["screen"]["bpp"] );
	json_int screenFPS = json_int( config["screen"]["fps"] );

	json_int workWidth = json_int( config["work"]["width"] );
	json_int workHeight = json_int( config["work"]["height"] );

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Could not load SDL : %s\n", SDL_GetError());
		return false;
	}

	atexit(SDL_Quit);

	// Window Properties
	window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (!window) {
		printf("Can't init window: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		printf("Can't init renderer: %s\n", SDL_GetError());
		return false;
	}

	// Icon
	SDL_Surface* icon = SDL_LoadBMP(windowIcon.c_str());
	SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGB(icon->format, 0, 0, 0));
	SDL_SetWindowIcon(window, icon);
	cleanup(icon);

	// Cursor
	SDL_ShowCursor(SDL_ENABLE);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, workWidth, workHeight);

	// FPS
	delay = 1000.0f / screenFPS;

	return true;
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

		cleanup(surface);
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

		cleanup(surface);

	} else {
		cout << "loading of file (" << filename << ") has failed!!!";
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

void Affichage::applyTexture(int x, int y, SDL_Texture* texture, SDL_Rect& clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	offset.w = clip.w;
	offset.h = clip.h;

	if (SDL_RenderCopyEx(renderer, texture, &clip, &offset, 0, 0, SDL_FLIP_NONE) != 0) {
		cout << "applyTexture has failed!!!";
	}
}

void Affichage::applyTextureColorMod(SDL_Texture* texture, Couleur color) {
	SDL_Color couleurRGB;

	couleurRGB = mapColor(color);

	if (SDL_SetTextureColorMod(texture, couleurRGB.r, couleurRGB.g, couleurRGB.b) != 0) {
		cout << "applyTextureColorMod has failed!!!";
	}
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

	if (surface == NULL) return newSurface;

	SDL_SaveBMP(surface, "/home/ugo/font.bmp");

	newSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	fillRect(newSurface, NULL, newColor);

	setColorKey(surface, Couleur::cBLANC);
	setColorKey(newSurface, Couleur::cNOIR);

	SDL_BlitSurface(surface, NULL, newSurface, NULL);

	SDL_SaveBMP(surface, "/home/ugo/font.bmp");

	SDL_SaveBMP(newSurface, "/home/ugo/newfont.bmp");

	SDL_FreeSurface(surface);

	return newSurface;
}

void Affichage::setColorKey(SDL_Surface* surface, Couleur couleur)
{
	SDL_Color couleurRGB;
	Uint32 colorKey;

	couleurRGB = mapColor(couleur);
	colorKey = SDL_MapRGBA(surface->format, couleurRGB.r, couleurRGB.g, couleurRGB.b, couleurRGB.a);

	if (SDL_SetColorKey(surface, SDL_TRUE, colorKey) != 0) {
		cout << "setColorKey has failed!!!";
	}
}

void Affichage::applySurface(int x, int y, SDL_Surface* source, SDL_Rect& clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	//On blit la surface
	SDL_BlitSurface(source, &clip, screen, &offset);
}

void Affichage::introduireDelai(Uint32 frameTime)
{
	Uint32 msec = delay - frameTime;

	if (msec > 0)
	{
		SDL_Delay(msec);
	}
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
		case Couleur::cNOIR:
			return COUL_NOIR;
		case Couleur::cBLEU:
			return COUL_BLEU;
		case Couleur::cVERT:
			return COUL_VERT;
		case Couleur::cCYAN:
			return COUL_CYAN;
		case Couleur::cROUGE:
			return COUL_ROUGE;
		case Couleur::cMAGENTA:
			return COUL_MAGENTA;
		case Couleur::cBRUN:
			return COUL_BRUN;
		case Couleur::cGRIS_CLAIR:
			return COUL_GRIS_CLAIR;
		case Couleur::cGRIS_FONCE:
			return COUL_GRIS_FONCE;
		case Couleur::cBLEU_CLAIR:
			return COUL_BLEU_CLAIR;
		case Couleur::cVERT_CLAIR:
			return COUL_VERT_CLAIR;
		case Couleur::cCYAN_CLAIR:
			return COUL_CYAN_CLAIR;
		case Couleur::cROUGE_CLAIR:
			return COUL_ROUGE_CLAIR;
		case Couleur::cMAGENTA_CLAIR:
			return COUL_MAGENTA_CLAIR;
		case Couleur::cJAUNE:
			return COUL_JAUNE;
		case Couleur::cBLANC:
			return COUL_BLANC;

		case Couleur::cMEME_COULEUR:
		default:
			return COUL_BLANC;
	}
}

Affichage::~Affichage()
{
	if (singleton != 0) delete singleton;

	cleanup(renderer, window);
}
