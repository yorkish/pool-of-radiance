#include "Timer.h"
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

Timer::Timer() : startTicks(0), pausedTicks(0), bPaused(false), bStarted(false)
{}

void Timer::start()
{
	//On démarre le timer
	bStarted = true;
	//On enlève la pause du timer
	bPaused = false;
	//On récupère le temps courant
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	//On stoppe le timer
	bStarted = false;
	//On enlève la pause
	bPaused = false;
}

int Timer::get_ticks()
{
	//Si le timer est en marche
	if( bStarted )
	{
		//Si le timer est en pause
		if( bPaused )
			//On retourne le nombre de ticks quand le timer a été mis en pause
			return pausedTicks;
		else
			//On retourne le temps courant moins le temps quand il a démarré
			return SDL_GetTicks() - startTicks;
	}

	return 0;
}

void Timer::pause()
{
	//Si le timer est en marche et pas encore en pause
	if( bStarted && !bPaused )
	{
		bPaused = true;

		//On calcul le pausedTicks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	//Si le timer est en pause
	if( bPaused )
	{
		bPaused = false;

		//On remet à zero le startTicks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Remise à zero du pausedTicks
		pausedTicks = 0;
	}
}

bool Timer::isStarted()
{
	return bStarted;
}

bool Timer::isPaused()
{
	return bPaused;
}

Timer::~Timer()
{}
