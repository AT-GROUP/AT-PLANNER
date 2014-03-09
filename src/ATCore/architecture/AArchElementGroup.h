

#ifndef ATCore_AArchElementGroup_h
#define ATCore_AArchElementGroup_h

#include "../config.h"
#include "../utils/geometry.h"
//#include "AArchElement.h"
#include <string>
#include <set>
#include <memory>
#include <vector>
#include <map>

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

	void serialize(_xmlNode * group_node, std::vector<AArchElement*> & els) const;
	void deserialize(_xmlNode * group_node, std::map<int, AArchElement*> & elements);

	static AArchElementGroup * createAndDeserialize(_xmlNode * group_node, std::map<int, AArchElement*> & elements);

	const DFDElement * dfdElement() const;

	const APoint & pos() const;
	void setPos(const APoint & new_pos);

	bool removeElement(AArchElement * element);

	std::shared_ptr<AArchElement> findElementWithInterface(const std::string & interface_name) const;
private:
	std::shared_ptr<DFDElement> m_pDfdElement;
	std::set<std::shared_ptr<AArchElement>> mChildren;
	APoint mPos;
};

#endif
