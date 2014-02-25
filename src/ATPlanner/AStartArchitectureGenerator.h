

#ifndef ATPlanner_AStartArchitectureGenerator_h
#define ATPlanner_AStartArchitectureGenerator_h

#include "config.h"

class EDFDDocument;
class AArchitectureDocument;

class AT_PLANNER_API AStartArchitectureGenerator
{
public:
	AStartArchitectureGenerator();
	void generate(EDFDDocument * detailed_edfd, AArchitectureDocument * arch_doc);
};

#endif
