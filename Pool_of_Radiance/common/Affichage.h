#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>

#include "Global.h"

class Affichage
{
  public:
		static Affichage& getInstance();
		bool initRenderer();

		SDL_Texture* loadImage( std::string filename, Uint8 cKeyR, Uint8 cKeyG, Uint8 cKeyB );
		SDL_Surface* loadImageAsSurface(std::string filename, Uint8 cKeyR, Uint8 cKeyG, Uint8 cKeyB);

		void fillRect(SDL_Rect* clip, Couleur couleur);
		void fillRect(SDL_Surface* surface, SDL_Rect* clip, Couleur couleur);

		void wipeScreen(Couleur couleur = cNOIR);
		SDL_Surface* copySurface(SDL_Surface* source);
		SDL_Surface* swapColor(SDL_Surface* surface, Couleur oldColor, Couleur newColor);

		void applySurface( int x, int y, SDL_Surface* source, SDL_Rect& clip );
		void drawPixel( int x, int y, Uint8 R, Uint8 G, Uint8 B );
		void preRender();
		void postRender();

		void introduireDelai( Uint32 msec );

		void toggleFullScreen();
  private:
		Affichage();

		SDL_Surface* loadImage( std::string filename );
		SDL_Color mapColor(Couleur color);
		void setColorKey(SDL_Surface* surface, Couleur couleur);

		~Affichage();

		static Affichage* singleton;

		SDL_Renderer *renderer;
		SDL_Window *window;

		SDL_Surface *screen;

		SDL_Rect src;
		SDL_Rect dst;

		int fullScreen;

		std::string strCaption;
		std::string strIcone;
};
