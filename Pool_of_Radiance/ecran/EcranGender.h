#pragma once
#include <string>
#include <vector>
#include "Ecran.h"
#include "../texte/ListeTexte.h"
#include "EcranUtil.h"

class EcranGender: public Ecran, public EcranUtil
{
	public:
		EcranGender();

		bool init();
		void handleEvent( TInfoTouches& infTouches );
        void draw();
        void verifierMessages();
        void release();

		~EcranGender();

	private:
		void updateScreen();

		ListeTexte oListeTexte;
		std::vector<NodeGender> vctGender;
		int posCourante;

		int MAX_POS;
};

