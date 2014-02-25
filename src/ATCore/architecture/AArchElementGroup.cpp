
#include "AArchElementGroup.h"
#include "../edfd/DFDElement.h"

AArchElementGroup::AArchElementGroup(const std::shared_ptr<DFDElement> & element)
	:m_pDfdElement(element)
{

}

const std::string & AArchElementGroup::name() const
{
	return m_pDfdElement->name();
}

const std::set<std::shared_ptr<AArchElement>> & AArchElementGroup::children() const
{
	return mChildren;
}

void AArchElementGroup::addChild(const std::shared_ptr<AArchElement> & new_element)
{
	mChildren.insert(new_element);
	return;
}
