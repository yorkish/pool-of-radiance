#include "XalanCHelper.h"
#include <vector>
#include <stdlib.h>
#include "../common/Util.h"

#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xalanc/XalanDOM/XalanNamedNodeMap.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XPath/XObject.hpp>

using std::string;
using std::vector;
using std::stringstream;

XALAN_USING_XALAN(XalanSourceTreeDOMSupport)
XALAN_USING_XALAN(XalanDocumentPrefixResolver)
XALAN_USING_XALAN(XalanNode);
XALAN_USING_XALAN(XalanDOMString)
XALAN_USING_XALAN(NodeRefList);
XALAN_USING_XALAN(XalanNamedNodeMap);
XALAN_USING_XALAN(CharVectorType)
XALAN_USING_XALAN(XPathEvaluator)
XALAN_USING_XALAN(XObjectPtr)

XalanSourceTreeDOMSupport* XalanCHelper::theDOMSupport = 0;
XalanNode* XalanCHelper::root = 0;
XalanDocumentPrefixResolver* XalanCHelper::thePrefixResolver = 0;

XalanCHelper::XalanCHelper() {}

string XalanCHelper::getTextValue(XalanNode* node)
{
//	if (node != 0)
//		return node->ToElement()->GetText();
//	else
		return "";
}

int XalanCHelper::getTextValueInt(XalanNode* node)
{
//	string text = getTextValue(node);

//	if  (text.length() != 0) {
//		int value;

//		if (sscanf (text.c_str(), "%d", &value) == 1)
//			return value;
//	}

	return 0;
}

NodeRefList& XalanCHelper::selectNodeList(NodeRefList& nodeList, string& xpath) {
	XPathEvaluator evaluator;
	return evaluator.selectNodeList(nodeList, *theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);
}

NodeRefList& XalanCHelper::selectNodeList(NodeRefList& nodeList, const char* xpath) {
	string strXpath(xpath);
	return XalanCHelper::selectNodeList(nodeList, strXpath);
}

XalanNode* XalanCHelper::selectSingleNode(string& xpath) {
	XPathEvaluator evaluator;
	return evaluator.selectSingleNode(*theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);
}

XalanNode* XalanCHelper::selectSingleNode(stringstream& xpath) {
	string strXpath(xpath.str());
	return XalanCHelper::selectSingleNode(strXpath);
}

XalanNode* XalanCHelper::selectSingleNode(const char* xpath) {
	string strXpath(xpath);
	return XalanCHelper::selectSingleNode(strXpath);
}

string XalanCHelper::getStrResult(const char* xpath) {
	string strXpath(xpath);
	return XalanCHelper::getStrResult(strXpath);
}

string XalanCHelper::getStrResult(stringstream& xpath) {
	string strXpath(xpath.str());
	return XalanCHelper::getStrResult(strXpath);
}

string XalanCHelper::getStrResult(string& xpath) {
	XPathEvaluator evaluator;
	XObjectPtr theResult;

	theResult = evaluator.evaluate(*theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);

	return XalanCHelper::toStdString(theResult->str());

}

int XalanCHelper::getIntResult(string& xpath) {
	XPathEvaluator evaluator;
	XObjectPtr theResult;

	theResult = evaluator.evaluate(*theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);

	return XalanCHelper::toInt(theResult->str());
}

int XalanCHelper::getIntResult(const char* xpath) {
	string strXpath(xpath);
	return XalanCHelper::getIntResult(strXpath);
}

string XalanCHelper::getAttributeValue(XalanNode* node, const char* attribute)
{
	string result;
	XalanNode* attributeNode;
	XalanDOMString xalanString;

	if (node == 0)
		return "";

	try {
		const XalanNamedNodeMap* mapAttributes = node->getAttributes();
		attributeNode = mapAttributes->getNamedItem(XalanCHelper::toDOMString(attribute));
		xalanString = attributeNode->getNodeValue();
		result = XalanCHelper::toStdString(xalanString);
	} catch (...) {
		result = "";
	}

	return result;
}

int XalanCHelper::getAttributeIntValue(XalanNode* node, const char* attribute)
{
	string strResult;

	strResult = XalanCHelper::getAttributeValue(node, attribute);

	if (strResult.empty())
		return 0;

	return atoi(strResult.c_str());
}

string XalanCHelper::toStdString(XalanDOMString& theString)
{
	CharVectorType vctChar;
	string res;

	theString.transcode(vctChar);
	for( int i=0; vctChar[i] !='\0'; i++)
		res += vctChar[i];

	return res;
}

string XalanCHelper::toStdString(const XalanDOMString& theString)
{
	CharVectorType vctChar;
	string res;

	theString.transcode(vctChar);
	for( int i=0; vctChar[i] !='\0'; i++)
		res += vctChar[i];

	return res;
}

int XalanCHelper::toInt(const XalanDOMString& theString) {
	if (theString.empty())
		return 0;

	string temp(XalanCHelper::toStdString(theString));

	return atoi(temp.c_str());
}

XalanDOMString XalanCHelper::toDOMString(stringstream& ss) {
	return XalanDOMString(ss.str().c_str());
}

XalanDOMString XalanCHelper::toDOMString(string& string) {
	return XalanDOMString(string.c_str());
}

XalanDOMString XalanCHelper::toDOMString(const char* string) {
	return XalanDOMString(string);
}

void XalanCHelper::setWorkingObjects(xalanc_1_10::XalanSourceTreeDOMSupport*	theDOMSupport,
									 xalanc_1_10::XalanNode* 					root,
									 xalanc_1_10::XalanDocumentPrefixResolver*	thePrefixResolver) {

	XalanCHelper::theDOMSupport = theDOMSupport;
	XalanCHelper::root = root;
	XalanCHelper::thePrefixResolver = thePrefixResolver;
}

XalanCHelper::~XalanCHelper() {}
