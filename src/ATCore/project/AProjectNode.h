
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
	enum class Type  {ProjectRoot, File, BuildingElement, Group, Count} ;
	AProjectNode(const char * _name);
	virtual Type type()=0;
	void addChild(AProjectNode * child);
	void removeChild(AProjectNode * child);
	std::vector<AProjectNode*> & getChild();
	/*std::vector<AProjectNode*> getChild(int _i);
	std::vector<AProjectNode*> getChild(int _i,int _j);
	std::vector<AProjectNode*> getChild(int _i,int _j, int _k);*/
	AProjectNode* getChild(int _i);
	//virtual xmlNode * serialize(xmlNode * parent_node, USBuilding * building);
	//virtual void deserialize(xmlNode * node, USBuilding * building);
	virtual void serialize(xmlNode * xml_node) const;
	virtual void deserialize(xmlNodePtr xml_ptr);

	static AProjectNode * createAndDeserialize(xmlNode * project_node);
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
	virtual AProjectNode::Type type();
};

/*
Node for project.
*/
class ARootProjectNode : public AGroupProjectNode
{
public:
	ARootProjectNode(const char * project_name);
	virtual AProjectNode::Type type();
};

/*
Node for file.
*/

class AFileProjectNode : public AGroupProjectNode
{
public:	
	AFileProjectNode(AFile * file = 0);
	virtual AProjectNode::Type type();
	//virtual xmlNode * serialize(xmlNode * parent_node, USBuilding * building);			
	//virtual void deserialize(xmlNode * node, USBuilding * building);
	AFile * file();
	virtual void serialize (xmlNode* xml_node);
private:
	AFile * m_pFile;
};
				

#endif