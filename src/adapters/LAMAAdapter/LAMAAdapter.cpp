
#include "LAMAAdapter.h"
#include <ATCore/edfd/EDFDDocument.h>
#include <direct.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <map>

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

void LAMAAdapter::buildGeneralizedPlan(const EDFDDocument * common_dfd)
{
	//Create temp directory
	_mkdir("temp");

	//Get domain file from KB
	string domain_file_path = "kb/LAMA/generalized_plan.pddl";
	CopyFileA(domain_file_path.c_str(), "temp/generalized_plan_domain.pddl", false);

	//====================Generate problem file==============================
	ofstream problem_file;
	problem_file.open("temp/generalized_plan_problem.pddl" , fstream::out);     

	//Head

	problem_file << " more lorem ipsum";

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

	//Initial state
	problem_file << "(:init\n";

	int conn_id = 0;
	for(auto conn : connections)
	{
		auto src_it = find(elements.begin(), elements.end(), conn->source().get()), dest_it = find(elements.begin(), elements.end(), conn->dest().get());
		int src_id = distance(elements.begin(), src_it), dest_id = distance(elements.begin(), dest_it);

		problem_file << "\t(connected-directional c" << conn_id << " e" << src_id << " e" << dest_id << ")\n";
		++conn_id;
	}
/*	(= (currentTS) 0.0)
	(= (total-sum) 0.0)

	(can-start-timer)
	
	(= (worker-task-count w2) 0)
	(= (worker-task-count w5) 0)
	(= (worker-task-count w8) 0)
	(= (worker-task-count w12) 0)
	
	(= (worker-power w2) 2.0)
	(= (worker-power w5) 2.0)
	(= (worker-power w8) 2.0)
	(= (worker-power w12) 2.0)
*/
	problem_file << ")\n";
	//Goals
/*
	(:goal
		(and
			(closed t1)
			(closed t2)
		)
	)
)
*/

	problem_file.close();

	//=====================Call planner to solve the problem=======================

	//Parser the file to get plan
}
