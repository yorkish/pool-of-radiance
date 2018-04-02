#pragma once

#include <stack>
#include <vector>
#include "common/Global.h"
#include "queue/PileMessage.h"
#include "etat/EtatJeu.h"
#include "character/Character.h"
#include "SaveGameManager.h"
#include "common/Renderer.h"

class Jeu {
public:
	Jeu(Renderer &renderer);

	bool init();
	void handleEvent(TInfoTouches& infTouches);
	void move();
	void verifierMessages();
	void draw();

	bool exitRequested();

	~Jeu();

private:
	EtatJeu* getEtatCourant();
	void pushEtat(EtatJeu* etat);
	void popEtat();
	void popPushEtat(EtatJeu* etat);

	Renderer &renderer;

	GameState typeEtat;
	PileMessage& oPileMessage;
	SaveGameManager saveGameManager;

	std::stack<EtatJeu*> Etats;
	std::vector<Character*> lstCharacter;
};
