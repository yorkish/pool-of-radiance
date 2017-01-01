#pragma once

class Timer
{
	public:
		Timer();

		//Les diff�rentes actions du timer
		void start();
		void stop();
		void pause();
		void unpause();

		//R�cup�re le nombre de milliseconds depuis que le timer a �t� lanc�
		//ou r�cup�re le nombre de milliseconds depuis que le timer a �t� mis en pause
		int get_ticks();

		bool isStarted();
		bool isPaused();

		~Timer();

	private:

		int startTicks; //Le temps quand le timer est lanc�

		int pausedTicks; //Le temps enregistr� quand le Timer a �t� mit en pause

		//Le status du Timer
		bool bPaused;
		bool bStarted;
};
