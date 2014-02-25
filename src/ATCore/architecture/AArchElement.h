
#ifndef ATCore_AArchElement_h
#define ATCore_AArchElement_h

#include "../config.h"
#include "../AError.h"
#include "../utils/geometry.h"
#include "../ANamedObject.h"
#include <vector>

struct _xmlNode;

class AT_CORE_API AArchElement : public ANamedObject
{
public:
	enum class Type {Functional, Informational};

	AArchElement(const std::string & _name = "");
	virtual Type type() const = 0;
	static AArchElement * createAndDeserialize(_xmlNode * element_node);
	
	virtual void serialize(_xmlNode * element_node) const;
	virtual AError deserialize(_xmlNode * element_node);

	const APoint & pos() const;
	void setPos(const APoint & new_pos);
private:
	APoint mPos;
};

/*
Describes interface for operational PIK for
usage in architecture maket.
*/
struct AT_CORE_API APIKInterface
{
	struct Slot
	{
		enum class Type {Info, Func};

		Slot(const std::string & _name)
			:name(_name)
		{

		}

		std::string name, acceptable_type;
	};

	std::vector<Slot> inputs, outputs;
};

/*
Describes PIK config.
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

/*
Operational element, that can do something. In ZOM it
is called "operational PIK".
*/

class AT_CORE_API AArchFuncElement : public AArchElement
{
public:
	AArchFuncElement(const std::string & _name = "");

	virtual Type type() const override;
	bool hasConfig() const;

	const APIKInterface & interfaceDeclaration() const;
private:
	APIKInterface mInterface;
	APIKConfig mConfig;
};

/*
Any informational element like KB, DB, or any
script/programm code.
*/
class AT_CORE_API AArchInfoElement : public AArchElement
{
public:
	AArchInfoElement(const std::string & _name = "");
	virtual Type type() const override;
};

#endif
