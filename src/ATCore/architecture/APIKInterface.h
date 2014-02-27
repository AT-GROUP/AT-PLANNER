
#ifndef ATCore_APIKInterface_h
#define ATCore_APIKInterface_h

#include "../config.h"
#include "../AError.h"
#include <string>
#include <vector>

struct _xmlNode;

/*
Describes interface for operational PIK for
usage in architecture maket.
*/
class AT_CORE_API APIKInterface
{
public:
	enum class Type {Info, Func};

	struct Slot
	{
		

		Slot(const std::string & _name)
			:name(_name)
		{

		}

		std::string name, acceptable_type;
	};

	virtual AError deserialize(_xmlNode * doc_node) = 0;

	std::vector<Slot> inputs, outputs;
};

class AT_CORE_API APIKInterfaceInf : public APIKInterface
{
public:
	virtual AError deserialize(_xmlNode * doc_node);
};

/*
Describes Functional PIK config.
*/
struct AT_CORE_API APIKConfig
{
	struct Property
	{
		Property(const std::string & _name)
			:name(_name)
		{

		}

		std::string name;
	};

	std::vector<Property> params;
};

struct AT_CORE_API APIKInterfaceFunc : public APIKInterface
{
	virtual AError deserialize(_xmlNode * doc_node);

	APIKConfig config;
};


#endif
