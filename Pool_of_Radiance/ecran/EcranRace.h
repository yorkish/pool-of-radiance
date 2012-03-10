#pragma once
#include <string>
#include <vector>
#include "Ecran.h"
#include "../texte/ListeTexte.h"
#include "EcranUtil.h"

class EcranRace: public Ecran, public EcranUtil
{
	public:
		EcranRace();

		bool init();
		void handleEvent( TInfoTouches& infTouches );
        void draw();
        void verifierMessages();
        void release();

		~EcranRace();

	private:
		void updateScreen();

		ListeTexte oListeTexte;
		std::vector<NodeRace> vctRace;
		int posCourante;

		int MAX_POS;
};

