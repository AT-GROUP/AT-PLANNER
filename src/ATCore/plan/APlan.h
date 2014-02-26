
#ifndef ATPlanner_APlan_H
#define ATPlanner_APlan_H

#include "config.h"
#include "../ANamedObject.h"
#include <vector>

/*
Describes general task, linked with some EDFD element.
*/
class AT_CORE_API AGeneralTask : public ANamedObject
{
public:
	AGeneralTask(int dfd_element_id, std::string _name);
private:
	int mDFDElementId;
};

class AT_CORE_API APlan
{
public:
	void addTask(AGeneralTask * _task);
	const std::vector<AGeneralTask*> & tasks() const;
private:
	std::vector<AGeneralTask*> mTasks;
};


#endif