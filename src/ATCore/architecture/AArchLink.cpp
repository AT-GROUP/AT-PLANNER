
#include "AArchLink.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>

using namespace std;

AArchLink::AArchLink(AArchElement * _source, AArchElement * dest, const std::string slot_name)
	:m_pSource(_source), m_pDest(dest), mSlotName(slot_name)
{

}

AArchElement * AArchLink::destination()
{
	return m_pDest;
}

AArchElement * AArchLink::source()
{
	return m_pSource;
}

const std::string & AArchLink::slotName() const
{
	return mSlotName;
}

void AArchLink::serialize(_xmlNode * link_node, const std::vector<AArchElement*> & els) const
{
	int src_index = std::distance(els.begin(), find(els.begin(), els.end(), m_pSource)),
		dst_index = std::distance(els.begin(), find(els.begin(), els.end(), m_pDest));

	xmlNewProp(link_node, BAD_CAST "src_id" , BAD_CAST to_string(src_index).c_str());
	xmlNewProp(link_node, BAD_CAST "dest_id" , BAD_CAST to_string(dst_index).c_str());

	xmlNewProp(link_node, BAD_CAST "slot_name" , BAD_CAST mSlotName.c_str());
}

void AArchLink::deserialize(_xmlNode * link_node, const std::map<int, AArchElement*> & elements)
{
	int src_id = atoi(xml_prop(link_node, "src_id")), dst_id = atoi(xml_prop(link_node, "dest_id"));
	
	m_pSource = elements.find(src_id)->second;
	m_pDest = elements.find(dst_id)->second;

	mSlotName = string(xml_prop(link_node, "slot_name"));
}
