
#include "AStartArchitectureGenerator.h"
#include <ATCore/edfd/EDFDDocument.h>
#include <ATCore/architecture/AArchElementGroup.h>
#include <ATCore/architecture/AArchitectureDocument.h>
#include <ATCore/architecture/AArchElement.h>
#include <memory>

using namespace std;

AStartArchitectureGenerator::AStartArchitectureGenerator()
{

}

void AStartArchitectureGenerator::generate(EDFDDocument * detailed_edfd, AArchitectureDocument * arch_doc)
{
	for(auto dfd_el : detailed_edfd->elements())
	{
		if(dfd_el->type() == DFDElement::Type::Function)
		{
			shared_ptr<AArchElementGroup> new_group(new AArchElementGroup(dfd_el));

			arch_doc->addGroup(new_group);
		}
		else if(dfd_el->type() == DFDElement::Type::Storage)
		{
			shared_ptr<AArchElementGroup> storage_group(new AArchElementGroup(dfd_el));

			shared_ptr<AArchInfoElement> storage(new AArchInfoElement("Database"));
			storage_group->addChild(storage);

			shared_ptr<AArchFuncElement> driver(new AArchFuncElement("Driver"));
			storage_group->addChild(driver);

			arch_doc->addGroup(storage_group);
		}
		//AArchFuncElement
	}
}
