
#ifndef ATCore_DFDElement_h
#define ATCore_DFDElement_h

#include "../config.h"
#include "../ANamedObject.h"
#include "../utils/geometry.h"

#include <string>
#include <vector>
#include <memory>


/////////////////////// object layer ////////////////////////////////////

class EDFDDocument;
class _xmlNode;

class AT_CORE_API DFDElement : public ANamedObject
{
public:
	//std::string mName;
	std::string mComment;

	enum class Type {Entity, Storage, Function, NFFunction};
	virtual Type type() const=0;

	APoint Mouse_pos;

	DFDElement(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());

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

	APoint GetPos()
	{
		return Mouse_pos;
	}

	bool isDetalized() const;

	void serialize(_xmlNode * element_node) const;
	virtual AError deserialize(_xmlNode * element_node);

	static DFDElement * createAndDeserialize(_xmlNode * element_node);

private:
	std::vector<DFDElement*> mChildren;

public:
	struct
	{
		bool used;
		std::string document_name;
		std::shared_ptr<EDFDDocument> document;
	} mDetalization;
};


class AT_CORE_API DFDEntity : public DFDElement
{
public:
	DFDEntity(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type() const override;
};


class AT_CORE_API DFDFunction : public DFDElement
{
public:
	DFDFunction(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type() const;
};


class AT_CORE_API DFDStorage : public DFDElement
{
public:
	DFDStorage(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type() const;
};


class AT_CORE_API DFDNFFunction : public DFDElement
{
public:
	DFDNFFunction(const std::string & _name = "", const std::string & comment = "", const APoint & m_p = APoint());
	virtual Type type() const;
};
 
#endif
