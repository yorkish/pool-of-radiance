#pragma once
#include <stack>
#include "EtatJeu.h"
#include "../ecran/Ecran.h"

class EtatMenu: public EtatJeu
{
	public:
		EtatMenu();

		bool init();
		void handleEvent( TInfoTouches& infTouches );
        void draw();
        void verifierMessages();
        void release();

		~EtatMenu();

	private:
		Ecran* getMenuCourant();
		void pushMenu( Ecran* ecran );
		void popMenu();
		void popPushMenu( Ecran* ecran );

		std::stack< Ecran* > Ecrans;

};
