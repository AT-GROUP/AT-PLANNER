
#ifndef ATCore_AFile_h
#define ATCore_AFile_h

#include "config.h"
#include "ANamedObject.h"
#include <vector>

#include <libxml/tree.h>
#include <libxml/parser.h>


class AT_CORE_API AFile : public ANamedObject
{
	/*
	Link to file to contain files in project.
	*/
public:
	enum class Type {ExtendedDFD, DialogScenario, KnowledgeBase, Unknown};

	AFile(const char * file_name = "unnamed.x");
	
	/*
	Returns size of file in bytes.
	*/
	/*size_t size();
	void serialize(xmlNode * file_section_node);
	void deserialize(xmlNode * file_node);*/

private:
};


#endif
