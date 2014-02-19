
#include "EDFDDocument.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>
#include <algorithm>
#include <sstream>

using namespace std;

EDFDDocument::EDFDDocument()
{

}

ADocument::Type EDFDDocument::type() const
{
	return ADocument::Type::EDFD;
}

void EDFDDocument::addElement(const std::shared_ptr<DFDElement> & new_element)
{
	mElements.push_back(new_element);
}

void EDFDDocument::addConnection(const std::shared_ptr<DFDConnection> & new_connection)
{
	mConnections.push_back(new_connection);
}

void EDFDDocument::serialize(_xmlNode * document_node) const
{
	int i = 1;
	xmlNodePtr doc_node1 = xmlNewChild(document_node, NULL, BAD_CAST "Elements", BAD_CAST "");
	for(auto e : mElements)
	{
		xmlNodePtr child_node = xmlNewChild(doc_node1, NULL, BAD_CAST "elem", BAD_CAST "");

		stringstream n_str1;
		n_str1 << i;
		string s1(n_str1.str());
		xmlNewProp (child_node, BAD_CAST "id" , BAD_CAST s1.c_str());

		xmlNewProp (child_node, BAD_CAST "name" , BAD_CAST e->name().c_str());

		stringstream n_str2;
		n_str2 << e->Mouse_pos.x();
		string s2(n_str2.str());
		xmlNewProp (child_node, BAD_CAST "xPos" , BAD_CAST s2.c_str());

		stringstream n_str3;
		n_str3 << e->Mouse_pos.y();
		string s3(n_str3.str());
		xmlNewProp (child_node, BAD_CAST "yPos" , BAD_CAST s3.c_str());
		
		if (e->type() == DFDElement::Type::Entity)
			xmlNewProp (child_node, BAD_CAST "type" , BAD_CAST "Entity");
		if (e->type() == DFDElement::Type::Function)
			xmlNewProp (child_node, BAD_CAST "type" , BAD_CAST "Function");
		if (e->type() == DFDElement::Type::Storage)
			xmlNewProp (child_node, BAD_CAST "type" , BAD_CAST "Storage");
		if (e->type() == DFDElement::Type::NFFunction)
			xmlNewProp (child_node, BAD_CAST "type" , BAD_CAST "NFFunction");
		i++;
	}

	xmlNodePtr doc_node2 = xmlNewChild(document_node, NULL, BAD_CAST "Connections", BAD_CAST "");

	for(auto c : mConnections)
	{
		int i_c = 1;
		xmlNodePtr child_node = xmlNewChild(doc_node2, NULL, BAD_CAST "con", BAD_CAST "");
		xmlNewProp (child_node, BAD_CAST "name" , BAD_CAST c->name().c_str());
		for (auto e_c : mElements)
		{
			if (e_c->name() == c->source())
			{
				stringstream n_str4;
				n_str4 << i_c;
				string s4(n_str4.str());
				xmlNewProp (child_node, BAD_CAST "Source" , BAD_CAST s4.c_str());
			}
			if (e_c->name() == c->dest())
			{
				stringstream n_str5;
				n_str5 << i_c;
				string s5(n_str5.str());
				xmlNewProp (child_node, BAD_CAST "Dest" , BAD_CAST s5.c_str());
			}
			i_c++;
		}
	}
}

AError EDFDDocument::deserialize(_xmlNode * document_node)
{
	shared_ptr<DFDElement> new_el(nullptr);
	xmlNode *cur = child_for_path(document_node, "Elements");
	xml_for_each_child(cur, child)
	{
		const char *_id = xml_prop(child, "id");
		const char *_name = xml_prop(child, "name");
		const char *_xPos = xml_prop(child, "xPos");
		const char *_yPos = xml_prop(child, "yPos");
		APoint ap(atoi(_xPos), atoi(_yPos));
		const char *_type = xml_prop(child, "type");
		if (_type == "Entity")
			new_el.reset(new DFDEntity(_name, _name, ap));
	}
	//xmlNode * cur = child_for_path(document_node, "Elements");
	return AError();
}

bool EDFDDocument::isDetalized() const
{
	for(auto e : mElements)
	{
		if(e->isDetalized())
			return true;
	}

	return false;
}

void EDFDDocument::buildDetalizationLinks(vector<shared_ptr<EDFDDocument>> & edfd_docs)
{
	for(auto e : mElements)
	{
		if(e->isDetalized())
		{
			//e->buildDetalizationLink(edfd_docs);
			
			auto doc_it = find_if(edfd_docs.begin(), edfd_docs.end(), [=](const shared_ptr<EDFDDocument> & doc){ return doc->fileName() == e->mDetalization.document_name;});
	
			if(doc_it != edfd_docs.end())
				e->mDetalization.document = *doc_it;

			edfd_docs.erase(doc_it);
		}
	}

}
