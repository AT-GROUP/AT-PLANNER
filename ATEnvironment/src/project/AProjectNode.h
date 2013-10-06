
#ifndef ATEnvironment_USProjectNode_h
#define ATEnvironment_USProjectNode_h

#include "../core/ANamedObject.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <vector>

class AFile;

class AProjectNode : public ANamedObject
{
	friend class AQProjectTreeWidget;
public:
	enum {ProjectRoot, File, BuildingElement, Group, Count} Type;
	AProjectNode(const char * _name);
	virtual int type()=0;
	void addChild(AProjectNode * child);
	void removeChild(AProjectNode * child);
	//virtual xmlNode * serialize(xmlNode * parent_node, USBuilding * building);
	//virtual void deserialize(xmlNode * node, USBuilding * building);
private:
	std::vector<AProjectNode*> mChildren;
};

/*
Group is folder.
*/
class AGroupProjectNode : public AProjectNode
{
public:
	AGroupProjectNode(const char * name);
	virtual int type();
};

/*
Node for project.
*/
class ARootProjectNode : public AGroupProjectNode
{
public:
	ARootProjectNode(const char * project_name);
	virtual int type();
};

/*
Node for file.
*/

class AFileProjectNode : public AGroupProjectNode
{
public:
	AFileProjectNode(AFile * file = 0);
	virtual int type();
	//virtual xmlNode * serialize(xmlNode * parent_node, USBuilding * building);
	//virtual void deserialize(xmlNode * node, USBuilding * building);
	AFile * file();
private:
	AFile * m_pFile;
};


#endif