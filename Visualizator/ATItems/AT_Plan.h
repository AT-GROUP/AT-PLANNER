#ifndef AT_PLAN_H
#define AT_PLAN_H

#include <iostream>
#include <vector>

#include <ATItems/AT_PlanItem.h>
#include <Planners/Planner_Utils_CPT3.h>

class AT_Plan
{
    private:
        std::string planName;
        std::vector<AT_PlanItem *> m_Items;
    public:
        void generatePlan(char* path);
        std::vector<AT_PlanItem *> & getItems();
        const std::string & getPlanName();
};

#endif // AT_PLAN_H
