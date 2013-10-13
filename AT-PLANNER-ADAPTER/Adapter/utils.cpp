#include <utils.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <utils.h>
using namespace std;

PlannerIteraction::PlannerIteraction(char path[])
{
    // ToDo: где-то тут должен быть вызов планировщика и определение переменной filename: пути к составленному плану
    const char* temp_plan_filename = "/home/zexir/AT-PLANNER/AT-PLANNER-ADAPTER/Adapter/Planners/CPT3/output";
    strncpy(this->plan_filename, temp_plan_filename, 100);
}

PlannerIteraction::~PlannerIteraction()
{
}

int PlannerIteraction::getPlan()
{
    string line;
    char commentSymbol[] = ";";
    cout << "Path to plan: " << this->plan_filename << "\n";
    ifstream myfile ((const char *)this->plan_filename);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if (strncmp(line.c_str(),commentSymbol,1)!=0)
            {
                cout << line << endl; //ToDo: Заменить на создание собственного варианта QGraphicsItem и добавление в массив QList
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file"; //ToDo: всплывающее окно об ошибке
    return 0; //ToDo: Возврат QList
}
