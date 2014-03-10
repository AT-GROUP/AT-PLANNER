
#include "LAMAAdapter.h"
#include <ATCore/edfd/EDFDDocument.h>
#include <ATCore/plan/APlan.h>
#include <ATCore/architecture/AArchitectureDocument.h>
#include <ATCore/architecture/AArchElement.h>
#include <ATCore/architecture/AArchLink.h>
#include <direct.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>

using namespace std;

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new LAMAAdapter();
}

const std::string LAMAAdapter::name()
{
	return "LAMA planner adapter";
}

const std::string LAMAAdapter::description()
{
	return "PDDL adapter for planner LAMA 2011";
}

APlan * LAMAAdapter::buildGeneralizedPlan(const EDFDDocument * common_dfd)
{
	//Create temp directory
	_mkdir("temp");

	//clear files
	bool res = DeleteFile(L"temp/plan.tfd.best");

	//Get domain file from KB
	string domain_file_path = "kb/TFD/generalized_plan.pddl";
	CopyFileA(domain_file_path.c_str(), "temp/generalized_plan_domain.pddl", false);

	//====================Generate problem file==============================
	ofstream problem_file;
	problem_file.open("temp/generalized_plan_problem.pddl" , fstream::out);     

	//Head

	problem_file << "(define (problem generalized-plan-building)\n"
				<<	"(:domain AT-generalized-plan-LAMA)\n\n"

	//=================================
	//Objects
	<< "(:objects\n";
	
	//Elements
	vector<DFDElement*> elements;
	map<DFDElement::Type, vector<DFDElement*>> typed_elements;

	for(auto & e : common_dfd->elements())
	{
		elements.push_back(e.get());
		typed_elements[e->type()].push_back(e.get());

	}

	for(auto eg : typed_elements)
	{
		problem_file << "\t";

		for(auto e : eg.second)
		{
			int element_index = distance(elements.begin(), find(elements.begin(), elements.end(), e));
			problem_file << "e" << element_index << " ";
		}

		problem_file << "- ";

		switch(eg.first)
		{
		case DFDElement::Type::Entity:
			problem_file << "entity";
			break;
		case DFDElement::Type::Function:
			problem_file << "operation";
			break;
		case DFDElement::Type::NFFunction:
			problem_file << "nf-operation";
			break;
		case DFDElement::Type::Storage:
			problem_file << "storage";
			break;
		}

		problem_file << "\n";
	}

	//Connections
	problem_file << "\t";
	vector<DFDConnection*> connections;
	for(auto & conn : common_dfd->connections())
	{
		connections.push_back(conn.get());
		problem_file << "c" << connections.size() - 1 << " ";
	}

	problem_file << "- link \n";

	problem_file <<	")\n";

	//==================================================
	//Initial state
	problem_file << "(:init\n";

	//Advanced typing
	/*for(auto eg : typed_elements)
	{
		problem_file << "\t";

		string type_pred;

		switch(eg.first)
		{
		case DFDElement::Type::Entity:
			type_pred = "is-entity";
			break;
		case DFDElement::Type::Function:
			type_pred = "is-operation";
			break;
		case DFDElement::Type::NFFunction:
			type_pred = "is-nf-operation";
			break;
		case DFDElement::Type::Storage:
			type_pred = "is-storage";
			break;
		}

		for(auto e : eg.second)
		{
			int element_index = distance(elements.begin(), find(elements.begin(), elements.end(), e));
			problem_file << "(" << type_pred << " e" << element_index << ") ";
		}

		problem_file << "\n";
	}*/

	problem_file << "\n";

	//Connections
	int conn_id = 0;
	for(auto conn : connections)
	{
		auto src_it = find(elements.begin(), elements.end(), conn->source().get()), dest_it = find(elements.begin(), elements.end(), conn->dest().get());
		int src_id = distance(elements.begin(), src_it), dest_id = distance(elements.begin(), dest_it);

		problem_file << "\t(connected-directional c" << conn_id << " e" << src_id << " e" << dest_id << ")\n";
		++conn_id;
	}

	//Base cost - 0 for all
	problem_file <<	"\n";
	for(int e1 = 0; e1 < elements.size(); ++e1)
	{
		problem_file <<	"\t";
		for(int e2 = 0; e2 < elements.size(); ++e2)
		{
			problem_file <<	"(= (sequence-cost e" << e1 << " e" << e2 << ") 0) ";
		}

		problem_file <<	"\n";
	}

	//Specify elements must be developed
	problem_file <<	"\n";
	problem_file <<	"\t";
	for(auto e : elements)
	{
		if(e->type() != DFDElement::Type::Entity)
		{
			int element_index = distance(elements.begin(), find(elements.begin(), elements.end(), e));
			problem_file <<	"(must-be-developed e" << element_index << ") ";
		}
	}

	problem_file <<	"\n";

	//Total cost
	problem_file << "(= (total-cost) 0)\n";

	problem_file << ")\n";
	
	

	//===================================
	//Goals
	problem_file <<	"(:goal\n";
	problem_file <<	"\t(and\n";
	problem_file << "\t\t(general-plan-build)\n";
	problem_file <<	"\t)\n";
	problem_file <<	")\n";
	

	//Metric
	problem_file <<	"(:metric minimize (total-cost))\n\n";

	problem_file <<	")\n";

	problem_file.close();


	//=====================Call planner to solve the problem=======================
	_chdir("temp");
	string python_cmd = "\"C:\\Program Files (x86)\\Python26\\python.exe\" ..\\planners\\tfd\\translate\\translate.py generalized_plan_domain.pddl generalized_plan_problem.pddl";
	system(python_cmd.c_str());
	system(" ..\\planners\\tfd\\preprocess.exe < output.sas");
	system(" ..\\planners\\tfd\\search.exe ay t 3 p plan.tfd < output");

	//===============================Parser the file to get plan====================
	//regex re("\\d+.(\\d+): \\(finish-element (.*)\\[.*\\]");

	ifstream plan_file;
	plan_file.open("plan.tfd.best", istream::in);

	vector<string> plan_actions;

	while(plan_file)
	{
		string line;
		getline(plan_file, line);

		if(line.find("finish-element") != string::npos)
		{
			plan_actions.push_back(line);
		}
	}
	

	plan_file.close();


	APlan * plan = new APlan();

	for(auto act : plan_actions)
	{
		size_t pos_start = act.find("finish-element ") + strlen("finish-element ") + 1, pos_end = act.find(")");
		string el_id = act.substr(pos_start, pos_end - pos_start - 1);
		int e_id = atoi(el_id.c_str());

		auto el = elements[e_id];


		AGeneralTask * gtask = new AGeneralTask(el->id(), el->type(), "Develop \"" + el->name() + "\"");
		plan->addTask(gtask);
	}

	//Clear all temp files
	_chdir("..");

	return plan;
}


APlan * LAMAAdapter::buildDetailPlan(APlan * plan, const AArchitectureDocument * arch_doc)
{
	//Create temp directory
	_mkdir("temp");

	//Get domain file from KB
	string domain_file_path = "kb/TFD/detail_plan.pddl";
	CopyFileA(domain_file_path.c_str(), "temp/detail_plan_domain.pddl", false);

	//Remove old files
	bool res = DeleteFile(L"temp/plan.tfd.best");

	//====================Generate problem file==============================
	ofstream problem_file;
	problem_file.open("temp/detail_plan_problem.pddl" , fstream::out);     

	//Head

	problem_file << "(define (problem detail-plan-building)\n"
				<<	"(:domain AT-detail-plan-LAMA)\n\n";


	//=================================
	//Objects
	problem_file << "(:objects\n";

	//Global tasks
	problem_file << "\t";
	for(int g = 0; g < plan->tasks().size(); ++g)
	{
		auto gtask = plan->tasks()[g];		
		problem_file << "gt" << g << " ";
	}
	
	problem_file << " - global-task\n";

	
	//Architecture instances
	vector<AArchElement*> arch_index;
	map<string, vector<AArchElement*>> arch_elements;
	vector<AArchElement*> configurable_elements;
	map<int, vector<AArchElement*>> task_assignation;
	for(auto gr : arch_doc->groups())
	{
		int dfd_el_id = gr->dfdElement()->id();

		for(auto e : gr->children())
		{
			task_assignation[dfd_el_id].push_back(e.get());
			arch_index.push_back(e.get());
			arch_elements[e->interfaceDeclaration().name()].push_back(e.get());
			
			if(e->type() == AArchElement::Type::Functional)
			{
				auto fe = static_cast<AArchFuncElement*>(e.get());
				if(fe->hasConfig())
				{
					configurable_elements.push_back(fe);
				}
			}
		}
	}

	for(auto gr : arch_elements)
	{
		problem_file << "\t";

		for(auto e : gr.second)
		{
			int e_index = std::distance(arch_index.begin(), std::find(arch_index.begin(), arch_index.end(), e));
			problem_file << "e" << e_index << " ";
		}
		
		problem_file << "- " << gr.first << "\n";
	}
	//gtask->dfdElementId();

	problem_file << ")\n";

	//==================================================
	//Initial state
	problem_file << "\n(:init\n";

	//Global task sequence
	problem_file << "\t";
	for(int g = 0; g < plan->tasks().size() - 1; ++g)
	{
		problem_file << "(is-after gt" << g << " gt" << g+1 << ") ";
	}
	problem_file << "\n";

	//Current task - first task
	problem_file << "\t(current-global-task gt0)\n";

	//Total-cost = 0
	problem_file << "\t(= (total-cost) 0)\n";

	//Configurations
	problem_file << "\n\t";
	for(auto ce : configurable_elements)
	{
		int e_index = std::distance(arch_index.begin(), std::find(arch_index.begin(), arch_index.end(), ce));
		problem_file << "(must-be-configured e" << e_index << ") ";
	}
	problem_file << "\n\n";

	//What is necessary to develop
	problem_file << "\t";
	for(int i = 0; i < arch_index.size(); ++i)
	{
		if(arch_index[i]->mustBeDeveloped())
		{
			int e_index = std::distance(arch_index.begin(), std::find(arch_index.begin(), arch_index.end(), arch_index[i]));
			problem_file << "(must-be-developed e" << e_index << ") ";
		}
	}
	problem_file << "\n\n";
	
	//Task assignations
	for(int g = 0; g < plan->tasks().size(); ++g)
	{
		auto task = plan->tasks()[g];

		int dfd_el_id = task->dfdElementId();
		
		problem_file << "\t";

		for(auto el : task_assignation[dfd_el_id])
		{
			int e_index = std::distance(arch_index.begin(), std::find(arch_index.begin(), arch_index.end(), el));
			problem_file << "(assigned-to-task e" << e_index << " gt" << g << ") ";
		}
		
		problem_file << "\n";
	}

	//Inputs
	problem_file << "\n\t";
	for(auto l : arch_doc->links())
	{
		int src_index = std::distance(arch_index.begin(), std::find(arch_index.begin(), arch_index.end(), l->source())), 
			dst_index = std::distance(arch_index.begin(), std::find(arch_index.begin(), arch_index.end(), l->destination()));

		problem_file << "(is-input-for e" << src_index << " e" << dst_index << ") ";
	}
	problem_file << "\n";

	problem_file << ")\n";

	//===================================
	//Goals
	problem_file <<	"\n(:goal\n";
	problem_file <<	"\t(project-finished)\n";
	problem_file <<	")\n";

	//============================
	//Metric
	problem_file <<	"\n(:metric minimize (total-cost))\n\n";

	problem_file <<	")\n";

	problem_file.close();

	//=====================Call planner to solve the problem=======================
	_chdir("temp");
	system("\"C:\\Program Files (x86)\\Python26\\python.exe\" ..\\planners\\tfd\\translate\\translate.py detail_plan_domain.pddl detail_plan_problem.pddl");
	system(" ..\\planners\\tfd\\preprocess.exe < output.sas");
	system(" ..\\planners\\tfd\\search.exe ay t 3 p plan.tfd < output");

	//====================Parse the plan===================
	ifstream plan_file;
	plan_file.open("plan.tfd.best", istream::in);

	vector<string> executable_actions;
	executable_actions.push_back("project-database");
	executable_actions.push_back("configure-pik");
	executable_actions.push_back("acquire-knowledges-kmpz");
	executable_actions.push_back("write-dialog-scenario");
	executable_actions.push_back("develop-simple-operation");

	vector<string> plan_actions;

	while(plan_file)
	{
		string line;
		getline(plan_file, line);

		for(auto ea : executable_actions)
		{
			if(line.find(ea) != string::npos)
			{
				plan_actions.push_back(line);
				break;
			}
		}
	}
	
	vector<ASubTask*> detail_sequence;

	for(auto act : plan_actions)
	{
		size_t pos_start = act.find("(");
		act = act.substr(pos_start + 1, act.length() - pos_start - 1);

		pos_start = act.find(' ');
		string act_name = act.substr(0, pos_start);

		act = act.substr(pos_start + 1, act.length() - pos_start - 1);
		
		pos_start = act.find(' ');
		string selement_id = act.substr(1, pos_start - 1);
		act = act.substr(pos_start + 1, act.length() - pos_start - 1);

		pos_start = act.find(')');
		string sglobal_task_id = act.substr(2, pos_start - 1);
		
		int element_index = atoi(selement_id.c_str()), 
			global_task_index = atoi(sglobal_task_id.c_str());

		AGeneralTask * gtask = plan->tasks()[global_task_index];
		AArchElement * el = arch_index[element_index];

		ASubTask * subTask = new ASubTask(gtask, act_name + ": " + el->name());
		
		string execution_string;
		
		if(act_name == "project-database")
		{
			execution_string = "exec-tpp project-database \"" + el->name() + "\"";
		}
		else if(act_name == "configure-pik")
		{
			execution_string = "configure \"" + el->name() + "\"";
		}
		
		subTask->setExecutionString(execution_string);

		gtask->addSubTask(subTask);

		detail_sequence.push_back(subTask);
	}

	plan_file.close();

	//Build correct display groups
	int start_index = 0;

	while(start_index < detail_sequence.size())
	{
		//find end_index
		int end_index = start_index;
		while((end_index < detail_sequence.size()) && (detail_sequence[start_index]->parent() == detail_sequence[end_index]->parent()))
			++end_index;

		DisplayTaskGroup dg;
		dg.general_task = detail_sequence[start_index]->parent();
		dg.sub_tasks.insert(dg.sub_tasks.end(), detail_sequence.begin() + start_index, detail_sequence.begin() + end_index);

		plan->addDisplayGroup(dg);

		start_index = end_index;
	}

 	return plan;
}
