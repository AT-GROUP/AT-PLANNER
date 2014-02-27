

#ifndef ATPlanner_AStartArchitectureGenerator_h
#define ATPlanner_AStartArchitectureGenerator_h

#include "config.h"

class EDFDDocument;
class AArchitectureDocument;
class AArchElementFactory;

class AT_PLANNER_API AStartArchitectureGenerator
{
public:
	AStartArchitectureGenerator();
	void generate(AArchElementFactory * arch_factory, EDFDDocument * detailed_edfd, AArchitectureDocument * arch_doc);
};

#endif
