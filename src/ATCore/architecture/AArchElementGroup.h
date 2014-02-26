

#ifndef ATCore_AArchElementGroup_h
#define ATCore_AArchElementGroup_h

#include "../config.h"
#include "../utils/geometry.h"
//#include "AArchElement.h"
#include <string>
#include <set>
#include <memory>

class DFDElement;
class AArchElement;
class _xmlNode;

class AT_CORE_API AArchElementGroup
{
public:
	AArchElementGroup(const std::shared_ptr<DFDElement> & element);
	const std::string & name() const;

	const std::set<std::shared_ptr<AArchElement>> & children() const;
	void addChild(const std::shared_ptr<AArchElement> & new_element);

	void serialize(_xmlNode * group_node) const;
	void deserialize(_xmlNode * group_node);

	static AArchElementGroup * createAndDeserialize(_xmlNode * group_node);

	const DFDElement * dfdElement() const;

	const APoint & pos() const;
	void setPos(const APoint & new_pos);
private:
	std::shared_ptr<DFDElement> m_pDfdElement;
	std::set<std::shared_ptr<AArchElement>> mChildren;
	APoint mPos;
};

#endif
