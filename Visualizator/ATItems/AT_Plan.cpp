#include <ATItems/AT_Plan.h>


std::vector<AT_PlanItem*>& AT_Plan::getItems()
    {
        return m_Items;
    }
const std::string& AT_Plan::getPlanName()
    {
        return planName;
    }
void AT_Plan::generatePlan(char* path)
    {
        int dur;
        int start;
        std::string name;
        this->planName = "New_Plan1";
        PlannerIteraction m_Planner(path);
        std::string plan(m_Planner.getPlan());
        while(!plan.empty())
            {
                start = atoi(plan.substr(0,plan.find(":")).c_str());
                name = plan.substr(plan.find("(",0)+1,plan.find(")",0)-plan.find("(",0)-1);
                dur =  atoi(plan.substr(plan.find("[")+1,plan.find("]")-plan.find("[")-1).c_str());
                m_Items.push_back(new AT_PlanItem(name,dur,start));
                plan.erase(0,plan.find("\n")+1);
            }
    }
