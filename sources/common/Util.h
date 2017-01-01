#pragma once
#include <vector>
#include <string>

class Util {
	public:
		Util();

		static std::vector<std::string> splitString(std::string chaine, char separator);
		static void  trim(std::string& chaine);
		static void  rightTrim(std::string& chaine);
		static void  leftTrim(std::string& chaine);
		static void  toUpperCase(std::string& chaine);
		static void  toLowerCase(std::string& chaine);
		static std::string toStr(int valeur, unsigned int largeur = 0, bool zero = false);

		~Util();

	private:
		static std::string intToString(int valeur, std::string format);
};

