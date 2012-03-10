#pragma once
#include <string>
#include "tinyxml.h"

class TinyXMLHelper {
	public:
		TinyXMLHelper();

		TiXmlNode*  findChildNodeById(TiXmlNode* node, std::string nomAttribut, int value);
		TiXmlNode*  findChildNodeById(TiXmlNode* node, std::string nomNode, std::string nomAttribut, int value);
		TiXmlNode*  findChildNodeById(TiXmlNode* node, std::string nomNode, std::string nomAttribut, std::string value);
		std::string getTextValue(TiXmlNode* node);
		int         getTextValueInt(TiXmlNode* node);
		int         getAttributeIntValue(TiXmlNode* node, std::string nomAttribut);
		std::string getAttributeValue(TiXmlNode* node, std::string nomAttribut);

		~TinyXMLHelper();
};

