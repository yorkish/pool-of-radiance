#pragma once
#include <string>
#include "Dice.h"

class RollOperation {

	public:
		RollOperation();
		RollOperation(std::string x, std::string y, char operateur);
		RollOperation(const RollOperation& object);

		bool isX_SpecialOperation();
		bool isX_OperationMAX();
		bool isX_OperationRES();
		bool isX_OperationBEST3();

		void setX(std::string x);
		void setY(std::string y);

		char getOperateur() const;
		void setOperateur(char operateur);
		void setOperateur(std::string operateur);

		int getNbreLancersX() const;
	    int getNbreLancersY() const;

	    int  getBonusTotal();
	    void setBonusPerDie(int bonusPerDie);

	    void addToY(int valeur);

	    Dice getDiceX() const;
	    Dice getDiceY() const;

		std::string getStringRep();

	    ~RollOperation();

	private:
		void setNbreLancers();
		void setDices();

		std::string x;
		std::string y;
		char operateur;

		size_t posD_x;
		size_t posD_y;

		int nbreLancersX;
		int nbreLancersY;

		int bonusPerDie;

		Dice diceX;
		Dice diceY;
};
