#pragma once

class Timer
{
	public:
		Timer();

		//Les différentes actions du timer
		void start();
		void stop();
		void pause();
		void unpause();

		//Récupère le nombre de milliseconds depuis que le timer a été lancé
		//ou récupère le nombre de milliseconds depuis que le timer a été mis en pause
		int get_ticks();

		bool isStarted();
		bool isPaused();

		~Timer();

	private:

		int startTicks; //Le temps quand le timer est lancé

		int pausedTicks; //Le temps enregistré quand le Timer a été mit en pause

		//Le status du Timer
		bool bPaused;
		bool bStarted;
};
