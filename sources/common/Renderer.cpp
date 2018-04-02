#include "Renderer.h"

#include <iostream>
#include "Fichier.h"
#include <jeayeson/jeayeson.hpp>

using std::string;
using std::cout;
using std::endl;

Renderer::Renderer(raiicap<Renderer> const &) :
		renderer(0), window(0), screen(0), texture(0), fullScreen(0), delay(0) {
	src = {0, 0, 0, 0};
	dst = {0, 0, 0, 0};
}

bool Renderer::initRenderer() {
	// Get init parameters from config file
	json_map config { json_file { "data/settings/renderer.json" } };

	std::string windowTitle(config["window"]["title"]);
	std::string windowIcon(config["window"]["icon"]);

	json_int screenWidth = json_int(config["screen"]["width"]);
	json_int screenHeight = json_int(config["screen"]["height"]);
	//json_int screenBPP = json_int( config["screen"]["bpp"] );
	json_int screenFPS = json_int(config["screen"]["fps"]);

	json_int workWidth = json_int(config["work"]["width"]);
	json_int workHeight = json_int(config["work"]["height"]);

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("Could not load SDL : %s\n", SDL_GetError());
		return false;
	}

	atexit(SDL_Quit);

	// Window Properties
	window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

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

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(renderer, workWidth, workHeight);

	// FPS
	delay = 1000.0f / screenFPS;

	return true;
}

SDL_Texture* Renderer::loadImage(string filename, Uint8 cKeyR, Uint8 cKeyG, Uint8 cKeyB) {
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	Uint32 colorkey;

	surface = IMG_Load(filename.c_str());

	if (surface != NULL) {
		colorkey = SDL_MapRGB(surface->format, cKeyR, cKeyG, cKeyB);
		SDL_SetColorKey(surface, SDL_TRUE, colorkey);

		texture = SDL_CreateTextureFromSurface(renderer, surface);

		cleanup(surface);
	}

	return texture;
}

void Renderer::fillRect(SDL_Rect* clip, Couleur couleur) {
	SDL_Color couleurRGB = mapColor(couleur);
	SDL_SetRenderDrawColor(renderer, couleurRGB.r, couleurRGB.g, couleurRGB.b, couleurRGB.a);
	SDL_RenderFillRect(renderer, clip);
}

void Renderer::wipeScreen(Couleur couleur) {
	SDL_Color couleurRGB = mapColor(couleur);
	SDL_SetRenderDrawColor(renderer, couleurRGB.r, couleurRGB.g, couleurRGB.b, couleurRGB.a);
	SDL_RenderClear(renderer);
}

void Renderer::applyTexture(int x, int y, SDL_Texture* texture, SDL_Rect& clip) {
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	offset.w = clip.w;
	offset.h = clip.h;

	if (SDL_RenderCopyEx(renderer, texture, &clip, &offset, 0, 0, SDL_FLIP_NONE) != 0) {
		cout << "applyTexture has failed!!!";
	}
}

void Renderer::applyTextureColorMod(SDL_Texture* texture, Couleur color) {
	SDL_Color couleurRGB;

	couleurRGB = mapColor(color);

	if (SDL_SetTextureColorMod(texture, couleurRGB.r, couleurRGB.g, couleurRGB.b) != 0) {
		cout << "applyTextureColorMod has failed!!!";
	}
}

void Renderer::sleep(Uint32 frameTime) {
	Uint32 msec = delay - frameTime;

	if (msec > 0) {
		SDL_Delay(msec);
	}
}

void Renderer::toggleFullScreen() {
//	fullScreen = (fullScreen ? 0 : SDL_WINDOW_FULLSCREEN);
//	fullScreen ? SDL_ShowCursor(SDL_DISABLE) : SDL_ShowCursor(SDL_ENABLE);
}

void Renderer::preRender() {
	SDL_RenderClear(renderer);
}

void Renderer::postRender() {
	SDL_RenderPresent(renderer);
}

SDL_Color Renderer::mapColor(Couleur color) {
	RgbaPixel pixel;

	pixel.pixelColor = static_cast<Uint32>(color);
	return SDL_Color { pixel.r, pixel.g, pixel.b, pixel.a };
}

Renderer::~Renderer() {
	cleanup(renderer, window);
}
