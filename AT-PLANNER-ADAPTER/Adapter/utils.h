#ifndef UTILS_H
#define UTILS_H

namespace utils
{
    class PlannerIteraction;
}

class PlannerIteraction
{
    private:
    char plan_filename[100];
    public:
        PlannerIteraction(char path[]);
        ~PlannerIteraction();
        int getPlan();
};


#endif // UTILS_H
