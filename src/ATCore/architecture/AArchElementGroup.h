

#ifndef ATCore_AArchElementGroup_h
#define ATCore_AArchElementGroup_h

#include "../config.h"
//#include "AArchElement.h"
#include <string>
#include <set>
#include <memory>

class DFDElement;
class AArchElement;

class AT_CORE_API AArchElementGroup
{
public:
	AArchElementGroup(const std::shared_ptr<DFDElement> & element);
	const std::string & name() const;

	const std::set<std::shared_ptr<AArchElement>> & children() const;
	void addChild(const std::shared_ptr<AArchElement> & new_element);
private:
	std::shared_ptr<DFDElement> m_pDfdElement;
	std::set<std::shared_ptr<AArchElement>> mChildren;
};

#endif
