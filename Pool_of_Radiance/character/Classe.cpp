#include "Classe.h"
#include <iostream>
#include <vector>
#include "../common/Donnees.h"
#include "../roll/Roll.h"

using std::cout;
using std::vector;

Classe::Classe(): THAC0(10), level(1)
{}

Class_e Classe::getClasse() { return classe; }

void Classe::setClasse(Race_e race, Class_e classe)
{
	this->classe = classe;
	this->race   = race;

	//On génère la table THAC
	generateTHAC();
}

void Classe::generateTHAC()
{
	int i, x, THAC;
	THAC_GenerationTable table = Donnees::getInstance().getTHACInfo(classe, level);

	if (table.THAC == table.baseTHAC.value) {

		//On doit utiliser l'offset afin de bien générer la table
		int repeatsStart = THAC0 + table.baseTHAC.offset;

		for(i = 0, x = repeatsStart; i  < table.baseTHAC.repeats; i++, x--)
			THAC_Table[x] = table.baseTHAC.value;

		// jusqu'au THAC(-10)
		THAC = THAC_Table[x+1];
		while (x >= 0)
			THAC_Table[x--] = ++THAC;

		// jusqu'au THAC(+10)
		generateTHAC_R(THAC_Table[repeatsStart], repeatsStart + 1);

	} else {
		// jusqu'au THAC(-10)
		THAC = table.THAC;
		x = THAC0;
		while (x >= 0) {
			if (THAC == table.baseTHAC.value) {
				for(i = 0; i  < table.baseTHAC.repeats; i++, x--) {
					if (x < 0) break;
					THAC_Table[x] = table.baseTHAC.value;
				}
			}
			if (x < 0) break;
			THAC_Table[x--] = THAC++;

		}

		// jusqu'au THAC(+10)
		generateTHAC_R(table.THAC, THAC0 + 1);
	}
}

void Classe::generateTHAC_R(int THAC, int pos)
{
	while (pos < 21)
		THAC_Table[pos++] = --THAC;
}

Roll Classe::getRollStartingAge()
{
	return Roll( Donnees::getInstance().getStartingAge(race, classe) );
}

Roll Classe::getRollStartingGold()
{
	return Roll( Donnees::getInstance().getStartingGold(classe) );
}

Roll Classe::rollHitPoints(int bonusPerDie)
{
	return Roll( Donnees::getInstance().getHpRoll(classe, level, bonusPerDie) );
}

Condition Classe::getConditionPercentage()
{
	return Donnees::getInstance().getConditionPercentage(classe);
}

int Classe::getLevel()
{
	return level;
}

int Classe::getTHAC0(int bonus)
{
	//Un bonus positif déplace l'indice vers la droite (meilleures chances)
	//Un bonus négatif déplace l'indice vers la gauche du tableau (moins bonnes chances)
	return THAC_Table[THAC0 + bonus];
}

Classe::~Classe() {}
