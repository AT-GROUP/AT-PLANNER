
#ifndef ATCore_AArchElementFactory_h
#define ATCore_AArchElementFactory_h

#include "../config.h"
#include "APIKInterface.h"
#include "../AError.h"
#include "AArchElement.h"
#include <vector>
#include <memory>

class _xmlNode;

class AT_CORE_API AArchElementFactory
{
public:
	AArchElementFactory();
	AError loadPIKDefinitions();
	AError deserialize(_xmlNode * doc_node);

	const std::vector<APIKInterfaceInf> & infPIKs() const;
	const std::vector<APIKInterfaceFunc> & funcPIKs() const;

	AArchElement * createArchPIKInstance(AArchElement::Type type, const std::string & interface_name);
	//Overloading with type autodetection
	AArchElement * createArchPIKInstance(const std::string & interface_name);
private:
	std::vector<APIKInterfaceInf> mInfoInteraces;
	std::vector<APIKInterfaceFunc> mFuncInteraces;
};

#endif
