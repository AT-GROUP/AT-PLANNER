#include <Planners/Planner_Utils_CPT3.h>

PlannerIteraction::PlannerIteraction(std::string path)
{
    const char* temp_plan_filename = "/home/zexir/projects/AT-Planner-Adaper/Adapter/CPT3/output";
    system("/home/zexir/projects/AT-Planner-Adaper/Adapter/CPT3/plan.sh");
    strncpy(this->plan_filename, temp_plan_filename, 100);
}

PlannerIteraction::~PlannerIteraction()
{
}
std::string PlannerIteraction::getPlan()
{
    //std::cout << "Path to plan: " << this->plan_filename << "\n";
    std::ifstream myfile ((const char*)this->plan_filename);
    char outputLine[5000] = "";
    if (myfile.is_open())
    {
        std::string line;
        char commentSymbol[] = ";";
        while (getline(myfile,line))
        {
            if (strncmp(line.c_str(),commentSymbol,1)!=0)
            {
                strcat(outputLine,(const char*)strcat((char*)line.c_str(),"\n"));
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file"; //ToDo: всплывающее окно об ошибке
    std::string output(outputLine);
    return output;
}
