#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

class PlannerIteraction
{
    private:
        char plan_filename[100];
    public:
        PlannerIteraction(std::string path);
        ~PlannerIteraction();
        std::string getPlan();
};


#endif // UTILS_H
