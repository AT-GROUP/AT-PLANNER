
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

void build_element_pair_links(AArchitectureDocument * arch_doc, DFDElement * el1, AArchElementGroup * gr1, DFDElement * el2, AArchElementGroup * gr2)
{
	if((el1->type() == DFDElement::Type::NFFunction) && (el2->type() == DFDElement::Type::Storage))
	{
		auto db_driver = gr2->findElementWithInterface("DBDriver");
		auto dialoger = gr1->findElementWithInterface("ATDialoger");

		arch_doc->createLink(db_driver.get(), dialoger.get(), "DB Driver");
	}
	else if((el1->type() == DFDElement::Type::Function) && (el2->type() == DFDElement::Type::Storage))
	{
		auto db_driver = gr2->findElementWithInterface("DBDriver");
		auto simp_op = gr1->findElementWithInterface("SimpleOperation");

		arch_doc->createLink(db_driver.get(), simp_op.get(), "DB Driver");
	}
}

void AStartArchitectureGenerator::generate(AArchElementFactory * arch_factory, EDFDDocument * detailed_edfd, AArchitectureDocument * arch_doc)
{
	const int g_width = ceil(sqrt(detailed_edfd->elements().size()));
	int current_x(0), current_y(0);

	const float space_step = 300.0f;

	//======================Create fragments based on DFD elements======================
	map<DFDElement*, AArchElementGroup*> groups_index;

	for(auto dfd_el : detailed_edfd->elements())
	{
		AArchElementGroup * new_gr(nullptr);

		if(dfd_el->type() == DFDElement::Type::Function)
		{
			new_gr = new AArchElementGroup(dfd_el);
			
			shared_ptr<AArchInfoElement> simp_op(static_cast<AArchInfoElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Functional, "SimpleOperation")));

			new_gr->addChild(simp_op);
		}
		else if(dfd_el->type() == DFDElement::Type::Storage)
		{
			new_gr = new AArchElementGroup(dfd_el);

			shared_ptr<AArchInfoElement> storage(static_cast<AArchInfoElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Informational, "DataBase")));
			shared_ptr<AArchFuncElement> driver(static_cast<AArchFuncElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Functional, "DBDriver")));

			if(storage && driver)
			{
				storage->setPos(-60, -60);
				driver->setPos(60, 60);

				new_gr->addChild(storage);
				new_gr->addChild(driver);

				arch_doc->createLink(storage.get(), driver.get(), "DataBase");
			}
		}
		else if(dfd_el->type() == DFDElement::Type::NFFunction)
		{
			new_gr = new AArchElementGroup(dfd_el);


			shared_ptr<AArchInfoElement> dialoger(static_cast<AArchInfoElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Functional, "ATDialoger")));
			shared_ptr<AArchFuncElement> explainer(static_cast<AArchFuncElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Functional, "ATExplainer")));
			shared_ptr<AArchInfoElement> solver(static_cast<AArchInfoElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Functional, "ATSolver")));

			shared_ptr<AArchInfoElement> dialog_scenario(static_cast<AArchInfoElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Informational, "ATDialogScenario")));
			shared_ptr<AArchInfoElement> kb(static_cast<AArchInfoElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Informational, "ATKnowledgeBase")));
			shared_ptr<AArchInfoElement> exp(static_cast<AArchInfoElement*>(arch_factory->createArchPIKInstance(AArchElement::Type::Informational, "ATExplanations")));
			

			if(dialoger && explainer && solver && dialog_scenario && kb && exp)
			{
				new_gr->addChild(dialoger);
				dialoger->setPos(0, 0);

				new_gr->addChild(explainer);
				explainer->setPos(-150, 90);

				new_gr->addChild(exp);
				exp->setPos(-210, 140);

				new_gr->addChild(solver);
				solver->setPos(-150, -10);

				new_gr->addChild(dialog_scenario);
				dialog_scenario->setPos(-150, -60);

				new_gr->addChild(kb);
				kb->setPos(-240, 10);

				arch_doc->createLink(solver.get(), dialoger.get(), "Solver");
				arch_doc->createLink(kb.get(), solver.get(), "Knowledge Base");
				arch_doc->createLink(dialog_scenario.get(), dialoger.get(), "Dialog Scenario");
				arch_doc->createLink(explainer.get(), dialoger.get(), "Explainer");
				arch_doc->createLink(exp.get(), explainer.get(), "Explanations");
			}
		}

		if(new_gr && (new_gr->children().size() > 0))
		{
			arch_doc->addGroup(shared_ptr<AArchElementGroup>(new_gr));

			groups_index.insert(pair<DFDElement*, AArchElementGroup*>(dfd_el.get(), new_gr));

			new_gr->setPos(APoint(current_x * space_step, current_y * space_step));

			++current_x;
			if(current_x == g_width)
			{
				++current_y;
				current_x = 0;
			}
		}
	}

	//=========================Build links between them========================
	for(auto l : detailed_edfd->connections())
	{
		DFDElement * el1 = l->source().get(), *el2 = l->dest().get();
		AArchElementGroup * gr1 = groups_index[el1],
						*gr2 = groups_index[el2];

		if(gr1 && gr2)
		{
			build_element_pair_links(arch_doc, el1, gr1, el2, gr2);
			build_element_pair_links(arch_doc, el2, gr2, el1, gr1);
		}
	}
}
