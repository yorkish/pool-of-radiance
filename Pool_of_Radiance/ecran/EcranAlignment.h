#pragma once
#include <string>
#include <vector>
#include "Ecran.h"
#include "../texte/ListeTexte.h"
#include "EcranUtil.h"

class EcranAlignment: public Ecran, public EcranUtil
{
	public:
		EcranAlignment();

		bool init();
		void handleEvent( TInfoTouches& infTouches );
        void draw();
        void verifierMessages();
        void release();

		~EcranAlignment();

	private:
		void updateScreen();

		ListeTexte oListeTexte;
		std::vector<NodeAlignment> vctAlignment;
		int posCourante;

		int MAX_POS;
};

