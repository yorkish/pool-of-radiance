#include "TinyXMLHelper.h"
#include <vector>
#include "../common/Util.h"

using std::string;
using std::vector;

TinyXMLHelper::TinyXMLHelper() {}

TiXmlNode* TinyXMLHelper::findChildNodeById(TiXmlNode* node, string nomNode, string nomAttribut, string value)
{
	if (node == 0)
		return 0;

	TiXmlNode* nodeCourante;
	string id;

	nodeCourante = node->FirstChild(nomNode);

	while (nodeCourante != 0)
	{
		id = getAttributeValue(nodeCourante, nomAttribut);

		if ( id.compare(value) == 0 )
			return nodeCourante;

		nodeCourante = nodeCourante->NextSibling(nomNode);
	}

	return 0;
}

TiXmlNode* TinyXMLHelper::findChildNodeById(TiXmlNode* node, string nomNode, string nomAttribut, int value)
{
	if (node == 0)
		return 0;

	TiXmlNode* nodeCourante;
	int id;

	nodeCourante = node->FirstChild(nomNode);

	while (nodeCourante != 0)
	{
		id = getAttributeIntValue(nodeCourante, nomAttribut);

		if ( id == value )
			return nodeCourante;

		nodeCourante = nodeCourante->NextSibling(nomNode);
	}

	return 0;
}

TiXmlNode* TinyXMLHelper::findChildNodeById(TiXmlNode* node, string nomAttribut, int value)
{
	if (node == 0)
		return 0;

	TiXmlNode* nodeCourante;
	string     strId;
	vector<string> vctId;
	vector<string>::iterator iter;

	nodeCourante = node->FirstChild();

	while (nodeCourante != 0)
	{
		strId = getAttributeValue(nodeCourante, nomAttribut);

		if (strId.length() != 0) {
			if (strId.find(';') != string::npos) {
				vctId = Util::splitString(strId, ';');

				for(iter = vctId.begin(); iter != vctId.end(); iter++) {
					if ( atoi( (*iter).c_str() ) == value )
						return nodeCourante;
				}

			} else
				if ( atoi(strId.c_str()) == value )
					return nodeCourante;
		}

		nodeCourante = nodeCourante->NextSibling();
	}

	return 0;
}

string TinyXMLHelper::getTextValue(TiXmlNode* node)
{
	if (node != 0)
		return node->ToElement()->GetText();
	else
		return "";
}

int TinyXMLHelper::getTextValueInt(TiXmlNode* node)
{
	string text = getTextValue(node);

	if  (text.length() != 0) {
		int value;

		if (sscanf (text.c_str(), "%d", &value) == 1)
			return value;
	}

	return 0;
}

int TinyXMLHelper::getAttributeIntValue(TiXmlNode* node, string nomAttribut)
{
	const int SUCCES = TIXML_SUCCESS;
	int valeur;
	int retour;

	retour = node->ToElement()->QueryIntAttribute(nomAttribut, &valeur);

	if (retour == SUCCES)
		return valeur;
	else
		return 0;
}

string TinyXMLHelper::getAttributeValue(TiXmlNode* node, string nomAttribut)
{
	const int SUCCES = TIXML_SUCCESS;
	string valeur;
	int retour;

	if (node == 0)
		return "";

	retour = node->ToElement()->QueryStringAttribute(nomAttribut.c_str(),&valeur);

	if (retour == SUCCES)
		return valeur;
	else
		return "";
}

TinyXMLHelper::~TinyXMLHelper() {}
