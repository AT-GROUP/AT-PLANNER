
#ifndef ATCore_AProjectNode_h
#define ATCore_AProjectNode_h

#include "../ANamedObject.h"
#include "../AError.h"
#include "../ADocument.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <vector>

class ADocumentProjectNode;

class AT_CORE_API AProjectNode : public ANamedObject
{
	friend class AQProjectTreeWidget;
public:
	enum class Type  {ProjectRoot, File, BuildingElement, Group, Count} ;
	AProjectNode(const std::string & _name);
	virtual Type type() const=0;
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
	virtual AError deserialize(xmlNodePtr xml_ptr);

	static AProjectNode * createAndDeserialize(xmlNode * project_node);

	virtual void getDocumentNodesWithExtension(std::vector<const ADocumentProjectNode*> & docs, const std::string & ext) const;

	ADocumentProjectNode* findDocumentNode(const std::string & doc_name);
	std::vector<AProjectNode*> & children();
private:
	std::vector<AProjectNode*> mChildren;
};

/*
Group is folder.
*/
class AT_CORE_API AGroupProjectNode : public AProjectNode
{
public:
	AGroupProjectNode(const std::string & name);
	virtual AProjectNode::Type type() const;
	void setExpanded(bool expanded);
	bool expanded() const;
	virtual void serialize(xmlNode * xml_node) const override;
	virtual AError deserialize(xmlNodePtr xml_ptr) override;
	void removeDocumentsWithExtension(const std::string & ext);
private:
	bool mExpanded;
};

/*
Node for project.
*/
class AT_CORE_API ARootProjectNode : public AGroupProjectNode
{
public:
	ARootProjectNode(const std::string & project_name);
	virtual AProjectNode::Type type() const;
};

/*
Node for file.
*/

class AT_CORE_API ADocumentProjectNode : public AGroupProjectNode
{
public:	
	ADocumentProjectNode(ADocument * file = 0);
	virtual AProjectNode::Type type() const;
	virtual void serialize(xmlNode * parent_node) const override;
	//virtual AError deserialize(xmlNodePtr xml_ptr) override;
	const ADocument * file() const;
	virtual void serialize (xmlNode* xml_node);
	virtual void getDocumentNodesWithExtension(std::vector<const ADocumentProjectNode*> & docs, const std::string & ext) const;

	//Returns suffix from node name
	std::string extension() const;
private:
	ADocument * m_pFile;
};
				

#endif