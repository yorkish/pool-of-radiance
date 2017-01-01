#pragma once
#include <string>
#include <sstream>
#include <xalanc/XalanSourceTree/XalanSourceTreeDOMSupport.hpp>
#include <xalanc/DOMSupport/XalanDocumentPrefixResolver.hpp>
#include <xalanc/XalanDOM/XalanNode.hpp>
#include <xalanc/XalanDOM/XalanDOMString.hpp>
#include <xalanc/XPath/NodeRefList.hpp>

class XalanCHelper {
	public:
		XalanCHelper();

		static int         getAttributeIntValue(xalanc_1_11::XalanNode* node, const char* nomAttribut);
		static std::string getAttributeValue(xalanc_1_11::XalanNode* node, const char* nomAttribut);

		static std::string toStdString(const xalanc_1_11::XalanDOMString& theString);
		static std::string toStdString(xalanc_1_11::XalanDOMString& theString);

		static int toInt(const xalanc_1_11::XalanDOMString& theString);

		static xalanc_1_11::XalanDOMString toDOMString(std::stringstream& ss);
		static xalanc_1_11::XalanDOMString toDOMString(std::string string);

		static xalanc_1_11::NodeRefList& selectNodeList(xalanc_1_11::NodeRefList& nodeList, std::stringstream& xpath);
		static xalanc_1_11::NodeRefList& selectNodeList(xalanc_1_11::NodeRefList& nodeList, std::string xpath);

		static xalanc_1_11::XalanNode* selectSingleNode(std::stringstream& xpath);
		static xalanc_1_11::XalanNode* selectSingleNode(std::string xpath);

		static std::string getStrResult(std::stringstream& xpath);
		static std::string getStrResult(std::string xpath);

		static int getIntResult(std::stringstream& xpath);
		static int getIntResult(std::string xpath);

		static xalanc_1_11::XalanNode* NextSibling(xalanc_1_11::XalanNode* node);
		static xalanc_1_11::XalanNode* FirstChild(xalanc_1_11::XalanNode* node);

		static void setWorkingObjects(xalanc_1_11::XalanSourceTreeDOMSupport*	theDOMSupport,
									  xalanc_1_11::XalanNode* 					root,
									  xalanc_1_11::XalanDocumentPrefixResolver*	thePrefixResolver);

		~XalanCHelper();

	private:
		static xalanc_1_11::XalanSourceTreeDOMSupport*		theDOMSupport;
		static xalanc_1_11::XalanDocumentPrefixResolver*	thePrefixResolver;
		static xalanc_1_11::XalanNode* 						root;
};

