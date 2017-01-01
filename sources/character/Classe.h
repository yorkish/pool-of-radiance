#pragma once
#include "../common/Global.h"
#include "../roll/Roll.h"

class Classe {
	public:
		Classe();

		Class_e getClasse();
		void setClasse(Race_e race, Class_e classe);
		Condition getConditionPercentage();
		Roll getRollStartingAge();
		Roll getRollStartingGold();
		int  getLevel();
		int  getTHAC0(int bonus);
		Roll rollHitPoints(int bonusPerDie);
		~Classe();

	private:
		void generateTHAC();
		void generateTHAC_R(int THAC, int pos);
		void generateTHAC_L();

		const int THAC0;

		Race_e race;
		Class_e classe;

		int level;
		int THAC_Table[21]; //de -10 à 10
};

