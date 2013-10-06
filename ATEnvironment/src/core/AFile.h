
#ifndef ATEnvironment_AFile_h
#define ATEnvironment_AFile_h

#include "../core/ANamedObject.h"
#include <vector>

#include <libxml/tree.h>
#include <libxml/parser.h>


class AFile : public ANamedObject
{
	/*
	Link to file to contain files in project.
	*/
public:
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
