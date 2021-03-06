#pragma once
#include <string>
#include <vector>
#include "Ecran.h"
#include "../texte/ListeTexte.h"
#include "EcranUtil.h"

class EcranClasse: public Ecran, public EcranUtil
{
	public:
		EcranClasse();

		bool init();
		void handleEvent( TInfoTouches& infTouches );
        void draw();
        void verifierMessages();
        void release();

		~EcranClasse();

	private:
		void updateScreen();

		ListeTexte oListeTexte;
		std::vector<NodeClasse> vctClasse;
		int posCourante;

		int MAX_POS;
};

