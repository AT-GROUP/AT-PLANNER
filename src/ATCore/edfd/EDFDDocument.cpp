
#include "EDFDDocument.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////

bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

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

void EDFDDocument::deleteElement(const std::shared_ptr<DFDElement> & element)
{
	int el = find(mElements.begin(), mElements.end(), element) - mElements.begin();
	if (el <mElements.size())
		mElements.erase(mElements.begin() + el);
}

void EDFDDocument::deleteConnection(const std::shared_ptr<DFDConnection> & connection)
{
	//mConnections.push_back(new_connection);
}

void EDFDDocument::serialize(_xmlNode * document_node) const
{
	int i = 1;
	xmlNodePtr doc_node1 = xmlNewChild(document_node, NULL, BAD_CAST "Elements", BAD_CAST "");
	for(auto e : mElements)
	{
		xmlNodePtr child_node = xmlNewChild(doc_node1, NULL, BAD_CAST "elem", BAD_CAST "");
		e->setId(i);
		e->serialize(child_node);
		i++;
	}

	xmlNodePtr doc_node2 = xmlNewChild(document_node, NULL, BAD_CAST "Connections", BAD_CAST "");

	for(auto c : mConnections)
	{
		int i_c = 1;
		xmlNodePtr child_node = xmlNewChild(doc_node2, NULL, BAD_CAST "con", BAD_CAST "");
		xmlNewProp (child_node, BAD_CAST "name" , BAD_CAST c->name().c_str());
		xmlNewProp(child_node, BAD_CAST "std?" , BAD_CAST BoolToString(c->std()));
		if (c->std())
		{
			xmlNewProp (child_node, BAD_CAST "source-to-dest_data" , BAD_CAST c->std_d().c_str());
		}
		xmlNewProp(child_node, BAD_CAST "dts?" , BAD_CAST BoolToString(c->dts()));
		if(c->dts())
		{
			xmlNewProp (child_node, BAD_CAST "dest-to-source_data" , BAD_CAST c->dts_d().c_str());
		}
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
		
		shared_ptr<DFDElement> new_el(DFDElement::createAndDeserialize(child));


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

		
		bool std = to_bool(xml_prop(conn_node, "std?"));
		bool dts = to_bool(xml_prop(conn_node, "dts?"));

		shared_ptr<DFDConnection> conn(new DFDConnection(_cname, src_elem, dest_elem, std, dts)); ////////////////////////////!!!!!!!!!

		if (std) 
			conn->setSTD_data(xml_prop(conn_node, "source-to-dest_data"));
		if (dts)
			conn->setDTS_data(xml_prop(conn_node, "dest-to-source_data"));

		mConnections.push_back(conn);
	}

	/* old des
	xml_for_each_child(conn_nodes, conn_node)
	{
		const char *_cname = xml_prop(conn_node, "name");

		//Get linked element indices
		int source_id = atoi(xml_prop(conn_node, "source_id")), dest_id = atoi(xml_prop(conn_node, "dest_id"));
		
		//Get links to real elements
		shared_ptr<DFDElement> src_elem = element_dictionary[source_id], dest_elem = element_dictionary[dest_id];

		shared_ptr<DFDConnection> conn(new DFDConnection(_cname, src_elem, dest_elem, true, false)); ////////////////////////////!!!!!!!!!

		mConnections.push_back(conn);
	}
	*/

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

bool EDFDDocument::isDetalizedWith(const std::shared_ptr<EDFDDocument> & detail_doc) const
{
	for(auto e : mElements)
	{
		if(e->isDetalized())
		{
			if(e->mDetalization.document == detail_doc)
				return true;
		}
	}

	return false;
}

AError EDFDDocument::buildDetalizationLinks(vector<shared_ptr<EDFDDocument>> & edfd_docs)
{
	for(auto e : mElements)
	{
		if(e->isDetalized())
		{
			//e->buildDetalizationLink(edfd_docs);
			
			auto doc_it = find_if(edfd_docs.begin(), edfd_docs.end(), [=](const shared_ptr<EDFDDocument> & doc){ return doc->fileName() == e->mDetalization.document_name;});
	
			if(doc_it != edfd_docs.end())
			{
				e->mDetalization.document = *doc_it;
				//edfd_docs.erase(doc_it);
			}
			else
			{
				return AError(AT_ERROR_PROJECT_DATA, "Detalization diagramm document for \"" + e->name() + "\" object in \"" + fileName() + "\" document not found.");
			}
			
		}
	}

	return AError();

}

void EDFDDocument::mergeWith(const std::shared_ptr<EDFDDocument> & detail_doc)
{
	//Find element, which is detalized with this document

	auto detailed_el = std::find_if(mElements.begin(), mElements.end(), [=](const std::shared_ptr<DFDElement> & el){return el->isDetalized() && el->mDetalization.document == detail_doc;});

	if(detailed_el != mElements.end())
	{
		//Get all links connected with the element in source document

		vector<shared_ptr<DFDConnection>> connected_links;
		for(auto l : mConnections)
		{
			if(l->connectedTo(*detailed_el))
			{
				connected_links.push_back(l);
			}
		}

		//Replace element with elements from detail doc
		mElements.erase(detailed_el);
		mElements.insert(mElements.end(), detail_doc->mElements.begin(), detail_doc->mElements.end());

		//Get connected to Ext links, other add to current docs
		vector<shared_ptr<DFDConnection>> ext_links;
		for(auto l : detail_doc->mConnections)
		{
			//If link is connected to Ext
			if(false)
			{
				ext_links.push_back(l);
			}
			else
				mConnections.push_back(l);
		}
		

		//Synchronize links
		//!!!!!
		for(auto l : connected_links)
			mConnections.erase(std::find(mConnections.begin(), mConnections.end(), l));

		//Merge elements with similar names
		for(int i = 0; i < mElements.size(); ++i)
		{
			for(int j = i+1; j < mElements.size(); ++j)
			{
				if(mElements[i]->isSameAs(mElements[j].get()))
				{
					mergeElements(i, j);
				}
			}
		}
	}
	else
	{
		AError::criticalErrorOccured(AError(AT_ERROR_UNKNOWN, "Failed to merge EDFD documents."));
	}
}

void EDFDDocument::mergeElements(int index1, int index2)
{
	//Relink connections
	for(auto c : mConnections)
	{
		if(c->connectedTo(mElements[index2]))
			c->relinkTo(mElements[index2], mElements[index1]);
	}

	//Remove 2nd element
	mElements.erase(mElements.begin() + index2);
}
