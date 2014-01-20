#ifndef ATPLANITEM_H
#define ATPLANITEM_H

#include <iostream>

class AT_PlanItem
{
    private:
        std::string name;
        int duration;
        int startTime;
    public:
        AT_PlanItem(std::string c_name,int c_duration,int c_startTime);
        const std::string& getName();
        const int& getDuration();
        const int& getStartTime();
};

#endif // ATPLANITEM_H
