#include "DomoticSystem.h"
#include "Time.h"
using namespace std;

int main()
{
    DomoticSystem system;
    
    string n_m_dev0 = "frigo";
    double p_m_dev0 = -0.4;
    ManualDevice frigo(n_m_dev0, p_m_dev0);
    // add FRIGO
    system.add(frigo);

    string n_p_dev0 = "lavatrice";
    double p_p_dev0 = -2;
    Time t_dev0(1, 50);
    PresetDevice lavatrice(n_p_dev0, p_p_dev0, t_dev0);
    // add LAVATRICE
    system.add(lavatrice);

    string n_p_dev1 = "microonde";
    double p_p_dev1 = 0.8;
    Time t_dev1(0, 5);
    PresetDevice microonde(n_p_dev1, p_p_dev1, t_dev1);
    // add MICROONDE
    system.add(microonde);

    string n_m_dev1 = "fotovoltaico";
    double p_m_dev1 = 1.5;
    ManualDevice fotovoltaico(n_m_dev1, p_m_dev1);
    // add FOTOVOLTAICO
    system.add(fotovoltaico);

    Time end_of_day(23, 59);

    system.start_and_stop(frigo, Time(), Time(15,0));
    system.start_and_stop(fotovoltaico, Time(15,0), Time(17, 0));

    return 0;
}