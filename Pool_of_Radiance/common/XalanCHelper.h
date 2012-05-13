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

		std::string getTextValue(xalanc_1_10::XalanNode* node);
		int         getTextValueInt(xalanc_1_10::XalanNode* node);

		static int         getAttributeIntValue(xalanc_1_10::XalanNode* node, const char* nomAttribut);
		static std::string getAttributeValue(xalanc_1_10::XalanNode* node, const char* nomAttribut);

		static std::string toStdString(const xalanc_1_10::XalanDOMString& theString);
		static std::string toStdString(xalanc_1_10::XalanDOMString& theString);

		static int toInt(const xalanc_1_10::XalanDOMString& theString);

		static xalanc_1_10::XalanDOMString toDOMString(std::stringstream& ss);
		static xalanc_1_10::XalanDOMString toDOMString(std::string& string);
		static xalanc_1_10::XalanDOMString toDOMString(const char* string);

		static xalanc_1_10::NodeRefList& selectNodeList(xalanc_1_10::NodeRefList& nodeList, std::string& xpath);
		static xalanc_1_10::NodeRefList& selectNodeList(xalanc_1_10::NodeRefList& nodeList, const char* xpath);

		static xalanc_1_10::XalanNode* selectSingleNode(std::stringstream& ss);
		static xalanc_1_10::XalanNode* selectSingleNode(std::string& xpath);
		static xalanc_1_10::XalanNode* selectSingleNode(const char* xpath);

		static std::string getStrResult(std::stringstream& xpath);
		static std::string getStrResult(std::string& xpath);
		static std::string getStrResult(const char* xpath);

		static int getIntResult(std::string& xpath);
		static int getIntResult(const char* xpath);

		static void setWorkingObjects(xalanc_1_10::XalanSourceTreeDOMSupport*	theDOMSupport,
									  xalanc_1_10::XalanNode* 					root,
									  xalanc_1_10::XalanDocumentPrefixResolver*	thePrefixResolver);

		~XalanCHelper();

	private:
		static xalanc_1_10::XalanSourceTreeDOMSupport*		theDOMSupport;
		static xalanc_1_10::XalanDocumentPrefixResolver*	thePrefixResolver;
		static xalanc_1_10::XalanNode* 						root;
};

