#pragma once
#include <stack>
#include "EtatJeu.h"
#include "../ecran/Ecran.h"

class EtatMenu: public EtatJeu
{
	public:
		EtatMenu(Renderer &renderer);

		bool onEnter();
		void update( TInfoTouches& keysInfo );
        void render();
        void checkMessages();
        bool onExit();

    	virtual std::string getStateID() const {
    		return "MENU_STATE";
    	}

		~EtatMenu();

	private:
		Ecran* getMenuCourant();
		void pushMenu( Ecran* ecran );
		void popMenu();
		void popPushMenu( Ecran* ecran );

		std::stack< Ecran* > Ecrans;

};
