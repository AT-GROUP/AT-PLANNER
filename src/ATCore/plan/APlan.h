
#ifndef ATPlanner_APlan_H
#define ATPlanner_APlan_H

#include "config.h"
#include "../ANamedObject.h"
#include "../edfd/DFDElement.h"
#include <vector>

class ASubTask;

/*
Describes general task, linked with some EDFD element.
*/

class AT_CORE_API AGeneralTask : public ANamedObject
{
public:
	AGeneralTask(int dfd_element_id, DFDElement::Type dfd_type, std::string _name);
	int dfdElementId() const;
	void addSubTask(ASubTask * sub_task);
	const DFDElement::Type dfdType() const;
private:
	int mDFDElementId;
	DFDElement::Type mDfdType;
	std::vector<ASubTask*> mSubTasks;
};

class AT_CORE_API ASubTask : public ANamedObject
{
public:
	ASubTask(AGeneralTask * parent_task, std::string _name);
	AGeneralTask * parent() const;
	void setExecutionString(const std::string & execution_string);
	const std::string & executionString() const;

	bool done() const;
private:
	AGeneralTask * m_pParent;
	std::string mExecutionString;
	bool mDone;
};

struct DisplayTaskGroup
{
	AGeneralTask * general_task;
	std::vector<ASubTask*> sub_tasks;
};

class AT_CORE_API APlan
{
public:
	void addTask(AGeneralTask * _task);
	const std::vector<AGeneralTask*> & tasks() const;
	std::vector<AGeneralTask*> & tasks();
	const std::vector<DisplayTaskGroup> & displayGroups() const;
	void addDisplayGroup(const DisplayTaskGroup & dg);
private:
	std::vector<AGeneralTask*> mTasks;
	std::vector<DisplayTaskGroup> mDisplayGroups;
};


#endif
