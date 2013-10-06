
#include "AScheme.h"

using namespace BlockScheme;

ASlot::ASlot(const char * slot_name, int io_type, ABlock * parent)
	:ANamedObject(slot_name), mType(0), m_pParent(parent)
{

}

const int ASlot::type() const
{
	return mType;
}

ALink::ALink(ASlot * start_slot, ASlot * end_slot)
	:m_pStartSlot(start_slot), m_pEndSlot(end_slot)
{

}

ABlock::ABlock(const char * block_name)
	:ANamedObject(block_name)
{

}

AScheme::AScheme()
{

}
