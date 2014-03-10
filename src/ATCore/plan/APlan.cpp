
#include "APlan.h"

AGeneralTask::AGeneralTask(int dfd_element_id, std::string _name)
	:ANamedObject(_name), mDFDElementId(dfd_element_id)
{

}

int AGeneralTask::dfdElementId() const
{
	return mDFDElementId;
}

void AGeneralTask::addSubTask(ASubTask * sub_task)
{
	mSubTasks.push_back(sub_task);
}

//================ASubTask=====================
ASubTask::ASubTask(AGeneralTask * parent_task, std::string _name)
	:ANamedObject(_name), m_pParent(parent_task)
{

}

AGeneralTask * ASubTask::parent() const
{
	return m_pParent;
}

//================APlan======================
void APlan::addTask(AGeneralTask * _task)
{
	mTasks.push_back(_task);
}

const std::vector<AGeneralTask*> & APlan::tasks() const
{
	return mTasks;
}

std::vector<AGeneralTask*> & APlan::tasks()
{
	return mTasks;
}

const std::vector<DisplayTaskGroup> & APlan::displayGroups() const
{
	return mDisplayGroups;
}

void APlan::addDisplayGroup(const DisplayTaskGroup & dg)
{
	mDisplayGroups.push_back(dg);
}
