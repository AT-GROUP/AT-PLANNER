
#include "EDFDDocument.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

///////////////////////////////////////////////////////////////////////////

EDFDDocument::EDFDDocument()
{

}

ADocument::Type EDFDDocument::type() const
{
	return ADocument::Type::EDFD;
}

std::vector<std::shared_ptr<DFDElement>> EDFDDocument::getElements() const
{
	return mElements;
}

const std::vector<std::shared_ptr<DFDElement>> & EDFDDocument::elements() const
{
	return mElements;
}

const std::vector<std::shared_ptr<DFDConnection>> & EDFDDocument::connections() const
{
	return mConnections;
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

		xmlNewProp (child_node, BAD_CAST "id" , BAD_CAST to_string(i).c_str());

		xmlNewProp (child_node, BAD_CAST "name" , BAD_CAST e->name().c_str());

		xmlNewProp (child_node, BAD_CAST "xPos" , BAD_CAST to_string(e->Mouse_pos.x()).c_str());

		xmlNewProp (child_node, BAD_CAST "yPos" , BAD_CAST to_string(e->Mouse_pos.y()).c_str());

		xmlNewProp(child_node, BAD_CAST "type" , BAD_CAST to_string(static_cast<int>(e->type())).c_str());

		xmlNewProp(child_node, BAD_CAST "detal" , BAD_CAST BoolToString(e->mDetalization.used));

		if (e->mDetalization.used)
		{
			xmlNewProp(child_node, BAD_CAST "detal_doc_name" , BAD_CAST e->mDetalization.document_name.c_str());
			//xmlNewProp(child_node, BAD_CAST "type" , BAD_CAST e->mDetalization.document);
		}

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
			if (e_c->name() == c->sourceName())
			{
				stringstream n_str4;
				n_str4 << i_c;
				string s4(n_str4.str());
				xmlNewProp (child_node, BAD_CAST "source_id" , BAD_CAST s4.c_str());
			}
			if (e_c->name() == c->destName())
			{
				stringstream n_str5;
				n_str5 << i_c;
				string s5(n_str5.str());
				xmlNewProp (child_node, BAD_CAST "dest_id" , BAD_CAST s5.c_str());
			}
			i_c++;
		}
	}
}

AError EDFDDocument::deserialize(_xmlNode * document_node)
{
	//Dictionary for elements
	map<int, shared_ptr<DFDElement>> element_dictionary;

	xmlNode *cur = child_for_path(document_node, "Elements");
	xml_for_each_child(cur, child)
	{
		int id = atoi(xml_prop(child, "id"));
		const char *_name = xml_prop(child, "name");
		const char *_xPos = xml_prop(child, "xPos");
		const char *_yPos = xml_prop(child, "yPos");
		APoint ap(atoi(_xPos), atoi(_yPos));
		auto _type = atoi(xml_prop(child, "type"));
		
		shared_ptr<DFDElement> new_el(nullptr);

		switch(static_cast<DFDElement::Type>(_type))
		{
		case DFDElement::Type::Entity:
			{
				new_el.reset(new DFDEntity(_name, _name, ap));
				break;
			}
		case DFDElement::Type::Function:
			{
				new_el.reset(new DFDFunction(_name, _name, ap));
				break;
			}
		case DFDElement::Type::Storage:
			{
				new_el.reset(new DFDStorage(_name, _name, ap));
				break;
			}
		case DFDElement::Type::NFFunction:
			{
				new_el.reset(new DFDNFFunction(_name, _name, ap));
				break;
			}
		default:
			break;
		}

		////////////////////////////////////////////////////
		bool det = to_bool(xml_prop(child, "detal"));
		new_el->mDetalization.used = det;
		if (det)
		{
			new_el->mDetalization.document_name = xml_prop(child, "detal_doc_name");
		}
		////////////////////////////////////////////////////

		mElements.push_back(new_el);

		element_dictionary[id] = new_el;
	}

	auto conn_nodes = child_for_path(document_node, "Connections");

	xml_for_each_child(conn_nodes, conn_node)
	{
		const char *_cname = xml_prop(conn_node, "name");
		//Get linked element indices
		int source_id = atoi(xml_prop(conn_node, "source_id")), dest_id = atoi(xml_prop(conn_node, "dest_id"));
		
		//Get links to real elements
		shared_ptr<DFDElement> src_elem = element_dictionary[source_id], dest_elem = element_dictionary[dest_id];

		shared_ptr<DFDConnection> conn(new DFDConnection(_cname, src_elem, dest_elem));

		mConnections.push_back(conn);
	}

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
