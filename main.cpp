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
    double p_p_dev1 = -0.8;
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

    system.set_on("frigo");
    system.start_and_stop("fotovoltaico", Time(15, 20), Time(17, 03));
    system.set_time(Time(18, 43));
    system.start_and_stop("lavatrice", Time(19, 0), Time(22, 30));
    system.set_off("frigo");
    system.set_time(Time(20, 0));
    system.remove("lavatrice");
    system.set_on("microonde");
    system.show("fotovoltaico");
    system.show();
    system.set_time(end_of_day);

    system.reset_all();

    return 0;
}