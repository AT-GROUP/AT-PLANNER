
#include "APlan.h"

AGeneralTask::AGeneralTask(int dfd_element_id, std::string _name)
	:ANamedObject(_name), mDFDElementId(dfd_element_id)
{

}


void APlan::addTask(AGeneralTask * _task)
{
	mTasks.push_back(_task);
}

const std::vector<AGeneralTask*> & APlan::tasks() const
{
	return mTasks;
}
