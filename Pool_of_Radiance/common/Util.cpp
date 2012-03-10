#include "Util.h"
#include <stdio.h>

using std::vector;
using std::string;

Util::Util() {}

vector<string> Util::splitString(string chaine, char separator)
{
	vector<string> result;
	size_t pos =  0;
	size_t lastPos = 0;
	string temp;

	Util::trim(chaine);
	pos = chaine.find_first_of(separator);

	//15;20;3;4;5
	if (pos != string::npos) {
		while (pos != string::npos)
		{
			temp = chaine.substr(lastPos, pos - lastPos);
			Util::trim(temp);
			if (temp.length() != 0)
				result.push_back(temp);

			lastPos = ++pos;
			pos = chaine.find_first_of(separator, lastPos);
		}
		temp = chaine.substr(lastPos, chaine.length() - lastPos);
		Util::trim(temp);
		if (temp.length() != 0)
			result.push_back(temp);
	}
	else if (chaine.length() != 0)
		result.push_back(chaine);

	return result;
}

void Util::trim(std::string& chaine)
{
	Util::rightTrim(chaine);
	Util::leftTrim(chaine);
}

void Util::rightTrim(std::string& chaine)
{
	const string whitespaces (" \t\f\v\n\r");

	size_t pos = chaine.find_last_not_of(whitespaces);
	if (pos != string::npos)
		chaine.erase(pos+1);
}

void Util::leftTrim(string& chaine)
{
	const string whitespaces (" \t\f\v\n\r");

	size_t pos = chaine.find_first_not_of(whitespaces);
	if (pos != string::npos)
		chaine.erase(0, pos);
}


void Util::toUpperCase(string& chaine)
{
	for ( int i=0; chaine[i] != '\0'; i++)
		chaine[i] = toupper( chaine[i] );
}

void Util::toLowerCase(string & chaine)
{
	for ( int i=0; chaine[i] != '\0'; i++)
		chaine[i] = tolower( chaine[i] );
}

string Util::toStr(int valeur, unsigned int largeur, bool zero)
{
	string format = "%";

	if (zero)
		format.append("0");

	if (largeur != 0) {
		if (largeur > 10)
			format.append( Util::intToString(10, "%d") );
		else
			format.append( Util::intToString(largeur, "%d") );
	}

	format.append("d");

	return Util::intToString(valeur, format);
}

string Util::intToString(int valeur, string format)
{
	string retour;
	char*  temp;

	temp = new char[12 + 1]; // milliards

	snprintf(temp, 10, format.c_str(), valeur);
	retour = temp;

	delete[] temp;

	return retour;
}

Util::~Util() {}
