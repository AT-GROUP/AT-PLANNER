
#ifndef ATCore_DFDElement_h
#define ATCore_DFDElement_h

#include "../config.h"
#include "../ANamedObject.h"

#include <string>
#include <vector>

//class DFDConnection;
//class AWorkspaceScene;

/////////////////////// object layer ////////////////////////////////////

struct AT_CORE_API APoint
{
	int mX, mY;

	APoint(int _x = 0, int _y = 0)
		:mX(_x), mY(_y)
	{

	}

	void setX(const int new_x)
	{
		mX = new_x;
	}

	void setY(const int new_y)
	{
		mY = new_y;
	}

	int x() const
	{
		return mX;
	}

	int y() const
	{
		return mY;
	}
};

class AT_CORE_API DFDElement : public ANamedObject
{
public:
	//std::string mName;
	std::string mComment;

	enum class Type {Entity, Storage, Function, NFFunction};
	virtual Type type()=0;

	APoint Mouse_pos;

	DFDElement(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint())
		:ANamedObject(_name), mComment(comment), Mouse_pos(m_p)
	{
	}

/*	std::string GetName()
	{
		return mName;
	}

	void SetName(std::string name)
	{
		mName = name;
	}*/

	std::string GetComment()
	{
		return mComment;
	}

	void SetComment(std::string comm)
	{
		mComment = comm;
	}

	void SetPos(int x, int y)
	{
		Mouse_pos.setX(x);
		Mouse_pos.setY(y);
	}

	void GetPos()
	{
	}

	//virtual void serialize(xmlNode * xml_node) const;
	//virtual void deserialize(xmlNodePtr xml_ptr);

private:
	std::vector<DFDElement*> mChildren;
};


class AT_CORE_API DFDEntity : public DFDElement
{
public:
	DFDEntity(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type() override;

	/*virtual void serialize(xmlNode * xml_node) const
	{
		DFDElement::serialize(xml_node);
		//сериализация если элемент имеет аттрибуты отличные от DFDElement
	}*/

};


class AT_CORE_API DFDFunction : public DFDElement
{
public:
	DFDFunction(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type();
};


class AT_CORE_API DFDStorage : public DFDElement
{
public:
	DFDStorage(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type();
};


class AT_CORE_API DFDNFFunction : public DFDElement
{
public:
	DFDNFFunction(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type();
};
 
#endif
