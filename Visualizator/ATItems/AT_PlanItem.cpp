#include <ATItems/AT_PlanItem.h>

AT_PlanItem::AT_PlanItem(std::string c_name,int c_duration,int c_startTime)
{
    this->name = c_name;
    this->duration = c_duration;
    this->startTime = c_startTime;
}
const std::string& AT_PlanItem::getName()
{
    return name;
}
const int& AT_PlanItem::getDuration()
{
    return duration;
}
const int& AT_PlanItem::getStartTime()
{
    return startTime;
}
