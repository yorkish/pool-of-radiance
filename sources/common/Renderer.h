#ifndef POR_RENDERER_H
#define POR_RENDERER_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>

#include "Global.h"
#include "Raiicap.h"

class Renderer {
public:
	Renderer(raiicap<Renderer> const &);
	~Renderer();

	static Renderer& getInstance();
	bool initRenderer();

	SDL_Texture* loadImage(std::string filename, Uint8 cKeyR = 0, Uint8 cKeyG = 0, Uint8 cKeyB = 255);

	void fillRect(SDL_Rect* clip, Couleur couleur);

	void wipeScreen(Couleur couleur = Couleur::black);
	void applyTexture(int x, int y, SDL_Texture* texture, SDL_Rect& clip);
	void applyTextureColorMod(SDL_Texture* texture, Couleur color);

	void preRender();
	void postRender();

	void sleep(Uint32 frameTime);

	void toggleFullScreen();
private:

	SDL_Color mapColor(Couleur color);

	SDL_Renderer *renderer;
	SDL_Window *window;

	SDL_Surface *screen;
	SDL_Texture *texture;

	int fullScreen;
	int delay;	// in ms

	SDL_Rect src;
	SDL_Rect dst;
};

#endif // POR_RENDERER_H
