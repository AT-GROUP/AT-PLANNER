
#ifndef ATCore_AArchElement_h
#define ATCore_AArchElement_h

#include "../config.h"
#include "../AError.h"
#include "../utils/geometry.h"
#include "../ANamedObject.h"
#include "APIKInterface.h"
#include <vector>

struct _xmlNode;
class AArchElementFactory;

class AT_CORE_API AArchElement : public ANamedObject
{
public:
	enum class Type {Functional, Informational};

	AArchElement(APIKInterface & _intf, const std::string & _name = "");
	virtual Type type() const = 0;
	static AArchElement * createAndDeserialize(_xmlNode * element_node, AArchElementFactory * arch_factory);
	
	virtual void serialize(_xmlNode * element_node) const;
	virtual AError deserialize(_xmlNode * element_node);

	const APoint & pos() const;
	void setPos(const APoint & new_pos);
	void setPos(const float x, const float y);

	APIKInterface::Slot & slot(const std::string & slot_name);
	const APIKInterface & interfaceDeclaration() const;
	virtual bool mustBeDeveloped() const = 0;
protected:
	APIKInterface & mInterface;
private:
	APoint mPos;
};

/*
Operational element, that can do something. In ZOM it
is called "operational PIK".
*/

struct AT_CORE_API APIKConfigInstance
{
	APIKConfigInstance(const APIKConfig & config)
		:mConfig(config)
	{

	}

	bool exists() const
	{
		return !mConfig.params.empty();
	}

	const std::vector<APIKConfig::Property> & params() const
	{
		return mConfig.params;
	}
private:
	const APIKConfig & mConfig;
};

class AT_CORE_API AArchFuncElement : public AArchElement
{
public:
	AArchFuncElement(APIKInterfaceFunc & intf, const std::string & _name = "");
	const APIKInterfaceFunc & archInterface() const;
	APIKInterfaceFunc & archInterface();

	virtual Type type() const override;
	bool hasConfig() const;
	const APIKConfigInstance & config() const;
	APIKConfigInstance & config();

	virtual bool mustBeDeveloped() const;
private:
	APIKConfigInstance mConfig;
};

/*
Any informational element like KB, DB, or any
script/programm code.
*/
class AT_CORE_API AArchInfoElement : public AArchElement
{
public:
	AArchInfoElement(APIKInterfaceInf & intf, const std::string & _name = "");
	virtual Type type() const override;

	virtual bool mustBeDeveloped() const
	{
		return true;
	}
};

#endif
