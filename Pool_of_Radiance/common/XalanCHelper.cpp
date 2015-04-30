#include "XalanCHelper.h"
#include <iostream>
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
using std::cout;
using std::endl;

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

NodeRefList& XalanCHelper::selectNodeList(NodeRefList& nodeList, stringstream& xpath) {
	string strXpath(xpath.str());
	return XalanCHelper::selectNodeList(nodeList, strXpath);
}

NodeRefList& XalanCHelper::selectNodeList(NodeRefList& nodeList, string xpath) {
	XPathEvaluator evaluator;
	return evaluator.selectNodeList(nodeList, *theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);
}

XalanNode* XalanCHelper::selectSingleNode(string xpath) {
	XPathEvaluator evaluator;
	return evaluator.selectSingleNode(*theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);
}

XalanNode* XalanCHelper::selectSingleNode(stringstream& xpath) {
	string strXpath(xpath.str());
	return XalanCHelper::selectSingleNode(strXpath);
}

string XalanCHelper::getStrResult(stringstream& xpath) {
	string strXpath(xpath.str());
	return XalanCHelper::getStrResult(strXpath);
}

string XalanCHelper::getStrResult(string xpath) {
	XPathEvaluator evaluator;
	XObjectPtr theResult;

	theResult = evaluator.evaluate(*theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);
	cout << "* *" << endl;
	cout << xpath << endl;
	cout << theResult->str() << endl;
	cout << "* *" << endl;
	return XalanCHelper::toStdString(theResult->str());

}

int XalanCHelper::getIntResult(stringstream& xpath) {
	string strXpath(xpath.str());
	return XalanCHelper::getIntResult(strXpath);
}

int XalanCHelper::getIntResult(string xpath) {
	XPathEvaluator evaluator;
	XObjectPtr theResult;

	theResult = evaluator.evaluate(*theDOMSupport, root, XalanCHelper::toDOMString(xpath).c_str(), *thePrefixResolver);

	return XalanCHelper::toInt(theResult->str());
}

string XalanCHelper::getAttributeValue(XalanNode* node, const char* attribute)
{
	string result = "";
	XalanNode* attributeNode;
	XalanDOMString xalanString;

	if (node == 0)
		return result;

	const XalanNamedNodeMap* mapAttributes = node->getAttributes();

	if (mapAttributes != 0) {
		attributeNode = mapAttributes->getNamedItem(XalanCHelper::toDOMString(attribute));

		if (attributeNode != 0) {
			xalanString = attributeNode->getNodeValue();
			result = XalanCHelper::toStdString(xalanString);
		}
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

XalanDOMString XalanCHelper::toDOMString(string string) {
	return XalanDOMString(string.c_str());
}

XalanNode* XalanCHelper::NextSibling(XalanNode* node) {
	XalanNode* newNode = node->getNextSibling();

	while (newNode->getNodeType() != XalanNode::ELEMENT_NODE)
		newNode = newNode->getNextSibling();

	return newNode;
}

XalanNode* XalanCHelper::FirstChild(XalanNode* node) {
	XalanNode* newNode = node->getFirstChild();
	return XalanCHelper::NextSibling(newNode);
}

void XalanCHelper::setWorkingObjects(xalanc_1_11::XalanSourceTreeDOMSupport*	theDOMSupport,
									 xalanc_1_11::XalanNode* 					root,
									 xalanc_1_11::XalanDocumentPrefixResolver*	thePrefixResolver) {

	XalanCHelper::theDOMSupport = theDOMSupport;
	XalanCHelper::root = root;
	XalanCHelper::thePrefixResolver = thePrefixResolver;
}

XalanCHelper::~XalanCHelper() {}
