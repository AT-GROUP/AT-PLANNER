
#ifndef ATCore_AArchElement_h
#define ATCore_AArchElement_h

#include "../config.h"
#include "../AError.h"
#include "../utils/geometry.h"
#include "../ANamedObject.h"
#include "APIKInterface.h"
#include <vector>

struct _xmlNode;

class AT_CORE_API AArchElement : public ANamedObject
{
public:
	enum class Type {Functional, Informational};

	AArchElement(APIKInterface & _intf, const std::string & _name = "");
	virtual Type type() const = 0;
	static AArchElement * createAndDeserialize(_xmlNode * element_node);
	
	virtual void serialize(_xmlNode * element_node) const;
	virtual AError deserialize(_xmlNode * element_node);

	const APoint & pos() const;
	void setPos(const APoint & new_pos);
protected:
	APIKInterface & mInterface;
private:
	APoint mPos;
};

/*
Operational element, that can do something. In ZOM it
is called "operational PIK".
*/

class AT_CORE_API AArchFuncElement : public AArchElement
{
public:
	AArchFuncElement(const std::string & _name = "");
	const APIKInterfaceFunc & archInterface() const;
	APIKInterfaceFunc & archInterface();

	virtual Type type() const override;
	bool hasConfig() const;
	const APIKConfig & config() const;
	APIKConfig & config();

	const APIKInterface & interfaceDeclaration() const;
private:
	
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
