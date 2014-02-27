
#ifndef ATCore_AArchElementFactory_h
#define ATCore_AArchElementFactory_h

#include "../config.h"
#include "APIKInterface.h"
#include "../AError.h"
#include <vector>

class _xmlNode;

class AT_CORE_API AArchElementFactory
{
public:
	AArchElementFactory();
	AError loadPIKDefinitions();
	AError deserialize(_xmlNode * doc_node);
private:
	std::vector<APIKInterfaceInf> mInfoInteraces;
	std::vector<APIKInterfaceFunc> mFuncInteraces;
};

#endif
