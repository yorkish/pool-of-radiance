#pragma once

#include <stack>
#include <vector>
#include "common/Global.h"
#include "queue/PileMessage.h"
#include "etat/EtatJeu.h"
#include "character/Character.h"
#include "SaveGameManager.h"

class Jeu
{
	public:
		Jeu();

		bool init();
		void handleEvent( TInfoTouches& infTouches );
		void move();
		void verifierMessages();
		void draw();

		bool exitRequested();

		~Jeu();

	private:
		EtatJeu* getEtatCourant();
		void pushEtat( EtatJeu* etat );
		void popEtat();
		void popPushEtat( EtatJeu* etat );

		GameState typeEtat;
		PileMessage& oPileMessage;
		SaveGameManager saveGameManager;

		std::stack< EtatJeu* > Etats;
		std::vector<Character*> lstCharacter;
};
