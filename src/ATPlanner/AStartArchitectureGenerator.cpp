
#include "AStartArchitectureGenerator.h"
#include <ATCore/edfd/EDFDDocument.h>
#include <ATCore/architecture/AArchElementGroup.h>
#include <ATCore/architecture/AArchitectureDocument.h>
#include <ATCore/architecture/AArchElement.h>
#include <ATCore/architecture/AArchElementFactory.h>
#include <memory>

using namespace std;

AStartArchitectureGenerator::AStartArchitectureGenerator()
{

}

void AStartArchitectureGenerator::generate(AArchElementFactory * arch_factory, EDFDDocument * detailed_edfd, AArchitectureDocument * arch_doc)
{
	for(auto dfd_el : detailed_edfd->elements())
	{
		AArchElementGroup * new_gr(nullptr);

		if(dfd_el->type() == DFDElement::Type::Function)
		{
			new_gr = new AArchElementGroup(dfd_el);

			//arch_doc->addGroup(new_group);
		}
		else if(dfd_el->type() == DFDElement::Type::Storage)
		{
			new_gr = new AArchElementGroup(dfd_el);

			shared_ptr<AArchInfoElement> storage(new AArchInfoElement("Database"));
			new_gr->addChild(storage);

			shared_ptr<AArchFuncElement> driver(new AArchFuncElement("Driver"));
			new_gr->addChild(driver);
		}

		if(new_gr && (new_gr->children().size() > 0))
		{
			arch_doc->addGroup(shared_ptr<AArchElementGroup>(new_gr));
		}
	}
}
