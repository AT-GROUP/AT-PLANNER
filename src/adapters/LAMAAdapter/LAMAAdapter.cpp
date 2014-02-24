
#include "LAMAAdapter.h"
#include <ATCore/edfd/EDFDDocument.h>
#include <ATPlanner/APlan.h>
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
	system("\"C:\\Program Files\\Emscripten\\python\\2.7.5.3_64bit\\python\" ..\\planners\\tfd\\translate\\translate.py generalized_plan_domain.pddl generalized_plan_problem.pddl");
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

		AGeneralTask * gtask = new AGeneralTask(2, "Develop \"" + el->name() + "\"");
		plan->addTask(gtask);
	}

	//Clear all temp files
	_chdir("..");

	return plan;
}
