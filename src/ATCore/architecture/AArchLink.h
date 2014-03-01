
#ifndef ATCore_AArchLink_h
#define ATCore_AArchLink_h

#include "../config.h"
#include <string>
#include <vector>
#include <map>

class AArchElement;
struct _xmlNode;

class AT_CORE_API AArchLink
{
public:
	AArchLink(AArchElement * source = nullptr, AArchElement * dest = nullptr, const std::string slot_name = "");
	AArchElement * destination();
	AArchElement * source();
	const std::string & slotName() const;
	void serialize(_xmlNode * link_node, const std::vector<AArchElement*> & els) const;
	void deserialize(_xmlNode * link_node, const std::map<int, AArchElement*> & elements);
private:
	AArchElement * m_pSource, *m_pDest;
	std::string mSlotName;
};


#endif
