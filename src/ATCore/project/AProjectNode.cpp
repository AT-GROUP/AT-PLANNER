#include "AProjectNode.h"
#include "../ADocument.h"
#include "../utils/helpers.h"

using namespace std;

AProjectNode::AProjectNode(const std::string & _name)
	:ANamedObject(_name)
{

}

void AProjectNode::addChild(AProjectNode * child)
{
	mChildren.push_back(child);
}

void AProjectNode::removeChild(AProjectNode * child)
{
	auto i = std::find(mChildren.begin(), mChildren.end(), child);
	if(i != mChildren.end())
	{
		mChildren.erase(i);
	}
}

std::vector<AProjectNode*> & AProjectNode::getChild()
{
	return mChildren;
}

AProjectNode* AProjectNode::getChild(int _i)
{
	try {
		return mChildren.at(_i);
	}
	catch (std::out_of_range &) {
		return NULL;

	};

}

void AProjectNode::serialize(xmlNode * xml_node) const
{
	xmlNewProp(xml_node, BAD_CAST "type" , BAD_CAST to_string(static_cast<int>(type())).c_str());
	xmlNewProp(xml_node, BAD_CAST "name" , BAD_CAST name().c_str());

	//xmlNodeSetContent(xml_node, BAD_CAST "");

	for(auto c : mChildren)
	{
		xmlNodePtr child_node = xmlNewChild(xml_node, NULL, BAD_CAST "node", BAD_CAST "");		
		c->serialize(child_node);
	}
}


AError AProjectNode::deserialize(xmlNodePtr xml_ptr)
{
	//Name
	auto cname = xml_prop(xml_ptr, "name");
	setName(string(cname));

	xml_for_each_child(xml_ptr, child)
	{
		AProjectNode * new_node = AProjectNode::createAndDeserialize(child);
		addChild(new_node);
	}

	return AError();
}


AProjectNode * AProjectNode::createAndDeserialize(xmlNode * xml_node)
{
	auto prop = xml_prop(xml_node, "type");
	int node_type = atoi(xml_prop(xml_node, "type"));

	AProjectNode * new_node = nullptr;
	switch(static_cast<AProjectNode::Type>(node_type))
	{
	case AProjectNode::Type::Group:
		{
			new_node = new AGroupProjectNode("group");
			break;
		}
	case AProjectNode::Type::File:
		{
			new_node = new ADocumentProjectNode();
			break;
		}
	default:
		break;
	};

	new_node->deserialize(xml_node);
	return new_node;
}

//================AGroupProjectNode=====================
AGroupProjectNode::AGroupProjectNode(const std::string & _name)
	:AProjectNode(_name), mExpanded(true)
{

}

AProjectNode::Type AGroupProjectNode::type() const
{
	return AProjectNode::Type::Group;
}

void AGroupProjectNode::setExpanded(bool expanded)
{
	mExpanded = expanded;
}

bool AGroupProjectNode::expanded() const
{
	return mExpanded;
}

void AGroupProjectNode::serialize(xmlNode * xml_node) const
{
	AProjectNode::serialize(xml_node);

	xmlNewProp(xml_node, BAD_CAST "expanded" , BAD_CAST to_string(static_cast<int>(mExpanded)).c_str());
}

AError AGroupProjectNode::deserialize(xmlNodePtr xml_ptr)
{
	auto res = AProjectNode::deserialize(xml_ptr);

	auto exp_prop = xml_prop(xml_ptr, "expanded");
	if(exp_prop)
	{
		mExpanded = atoi(exp_prop);
	}

	return res;
}

//==============ARootProjectNode=================
ARootProjectNode::ARootProjectNode(const std::string & project_name)
	:AGroupProjectNode(project_name)
{

}

AProjectNode::Type ARootProjectNode::type() const
{
	return AProjectNode::Type::ProjectRoot;
}

//==============AFileProjectNodede=================
ADocumentProjectNode::ADocumentProjectNode(ADocument * _file)
	:AGroupProjectNode("unnamed"), m_pFile(0)
{
	if(_file)
	{
		setName(_file->fileName());
		m_pFile = _file;
	}

}

AProjectNode::Type ADocumentProjectNode::type() const
{
	return AProjectNode::Type::File;
}

void ADocumentProjectNode::serialize(xmlNode * parent_node) const
{
	AGroupProjectNode::serialize(parent_node);

	if(m_pFile)
		m_pFile->save();
}
/*
AError ADocumentProjectNode::deserialize(xmlNode * node)
{
	auto res = AGroupProjectNode::deserialize(node);


	AProjectNode::deserialize(node, building);

	int file_index = atoi(xml_node_attr_data(node, "file_index"));

	USFile * file = building->fileContainer()->mFiles[file_index];
	m_pFile = file;
	setName(file->name().c_str());

	return res;
}*/

ADocument * ADocumentProjectNode::file()
{
	return m_pFile;
}

void ADocumentProjectNode::serialize(xmlNode* xml_node)
{
	
}
