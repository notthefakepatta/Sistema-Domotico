#include<iostream>
#include <limits>  // per std::numeric_limits
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include "DomoticSystem.h"
#include "Time.h"


/*Funzioni utilizzate per stampare un menu' iniziale e sua volta dei
sottomenu' in base all'azione che si vuole compiere*/
void menu()
{
    std::cout<<"****************************************\n";
    std::cout<<"*            USER INTERFACE            *\n";
    std::cout<<"****************************************\n";
    std::cout<<"* Choose one of the following options: *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*       (1) Insertion of Devices       *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*       (2)  Turn on/off Devices       *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*       (3) Set Timer of Devices       *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*           (4) Show Devices           *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*             (5) Set Time             *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*        (6) Debugging Commands        *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               (0)  End               *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"****************************************\n";
}


void menuDevices()
{
    std::cout<<"****************************************\n";
    std::cout<<"*            USER INTERFACE            *\n";
    std::cout<<"****************************************\n";
    std::cout<<"*         INSERTION OF DEVICES         *\n";
    std::cout<<"****************************************\n";
    std::cout<<"* Choose one of the following options: *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*            MANUAL DEVICES            *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*(1)Impianto  Fotovoltaico      +1.5kW *\n";
    std::cout<<"*(2)Pompa di Calore+Termostato  -2.0kW *\n";
    std::cout<<"*(3)Scaldabagno                 -1.0kW *\n";
    std::cout<<"*(4)Frigorifero                 -0.4kW *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*              CP DEVICES              *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*(5)Lavatrice       1h50m       -2.0kW *\n";
    std::cout<<"*(6)Lavastoviglie   3h15m       -1.5kW *\n";
    std::cout<<"*(7)Tapparelle       1m         -0.3kW *\n";
    std::cout<<"*(8)Microonde        2m         -0.8kW *\n";
    std::cout<<"*(9)Asciugatrice     1h         -0.5kW *\n";
    std::cout<<"*(10)Televisore       1h        -0.5kW *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               (0) Back               *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"****************************************\n";
}


void menuSetTimerofDevices()
{
    std::cout<<"****************************************\n";
    std::cout<<"*            USER INTERFACE            *\n";
    std::cout<<"****************************************\n";
    std::cout<<"*         SET TIMER OF DEVICES         *\n";
    std::cout<<"****************************************\n";
    std::cout<<"* Choose one of the following options: *\n";
    std::cout<<"*     (Attention!  Case Sensitive)     *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*              FOR MANUAL              *\n";
    std::cout<<"*         Set ON and OFF time:         *\n";
    std::cout<<"* set ${DEVICENAME} ${START} [${STOP}] *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*                FOR CP                *\n";
    std::cout<<"*              Set ON time:            *\n";
    std::cout<<"*       set ${DEVICENAME} ${START}     *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*            Remove  Timer:            *\n";
    std::cout<<"*           rm ${DEVICENAME}           *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               (0) Back               *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"****************************************\n";
}

void menuTurnDevices()
{
    std::cout<<"****************************************\n";
    std::cout<<"*            USER INTERFACE            *\n";
    std::cout<<"****************************************\n";
    std::cout<<"*          TURN ON\\OFF DEVICES         *\n";
    std::cout<<"****************************************\n";
    std::cout<<"* Choose one of the following options: *\n";
    std::cout<<"*     (Attention!  Case Sensitive)     *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*          Turn on  a device:          *\n";
    std::cout<<"*         set ${DEVICENAME} on         *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*          Turn off a device:          *\n";
    std::cout<<"*         set ${DEVICENAME} off        *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               (0) Back               *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"****************************************\n";
}

void menuShow()
{
    std::cout<<"****************************************\n";
    std::cout<<"*            USER INTERFACE            *\n";
    std::cout<<"****************************************\n";
    std::cout<<"*             SHOW DEVICES             *\n";
    std::cout<<"****************************************\n";
    std::cout<<"* Choose one of the following options: *\n";
    std::cout<<"*     (Attention!  Case Sensitive)     *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*          Show all devices :          *\n";
    std::cout<<"*                 show                 *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*        Show a specific device :      *\n";
    std::cout<<"*          show ${DEVICENAME}          *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               (0) Back               *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"****************************************\n";
}

void menuSetTime()
{
    std::cout<<"****************************************\n";
    std::cout<<"*            USER INTERFACE            *\n";
    std::cout<<"****************************************\n";
    std::cout<<"*               SET TIME               *\n";
    std::cout<<"****************************************\n";
    std::cout<<"* Choose one of the following options: *\n";
    std::cout<<"*     (Attention!  Case Sensitive)     *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               Set time:              *\n";
    std::cout<<"*           set time ${TIME}           *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               (0) Back               *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"****************************************\n";
}

void menuDebug()
{
    std::cout<<"****************************************\n";
    std::cout<<"*            USER INTERFACE            *\n";
    std::cout<<"****************************************\n";
    std::cout<<"*          DEBUGGING COMMANDS          *\n";
    std::cout<<"****************************************\n";
    std::cout<<"* Choose one of the following options: *\n";
    std::cout<<"*     (Attention!  Case Sensitive)     *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               reset time             *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*              reset timers            *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               reset all              *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"*               (0) Back               *\n";
    std::cout<<"*                                      *\n";
    std::cout<<"****************************************\n";
}

/*Funzione per verificare ed avere la certezza che l'input
da tastiera inserito dall'utente sia un int e sia all'interno
dell'range di scelte disponibili(il range � sempre da 0 ad un numero x di possibili scelte)*/
int readInt(int x)
{
    int value;
    while(true)
    {
        std::cin>>value;
        if(std::cin.fail() || value < 0 || value > x)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"This input is not an Integer or is out of range\n";
        }else
        {
            break;
        }
    }
    return value;
}

/*Funzione alla quale passo come parametro una stringa insieme al carattere separatore che mi interessa e mi
restituice un vettore di stringhe composto dalle singole parole della stringa di partenza*/
std::vector<std::string> splitString(const std::string& str, char x)
{
    std::vector<std::string> container;

    int start = 0;
    int space_pos;

    while((space_pos = str.find(x,start)) != std::string::npos)
    {
        //Trova la sottostringa fino al primo spazio e la inserisce nel vettore
        container.push_back(str.substr(start, space_pos - start));
        start = space_pos + 1;
    }

    //Aggiunge l'ultima sottostringa dopo l'ultimo spazio
    container.push_back(str.substr(start));
    return container;
}

//Funzione che determina se un dispositivo è manuale o automatico
int getDeviceType(const std::string& name) {

    std::regex pattern("^(.*?)(\\s*\\d+)?$");
    std::smatch match;

    std::unordered_map<std::string, int> type
    {
        {"Impianto Fotovoltaico", 1},
        {"Pompa di calore + Termostato", 1},
        {"Scaldabagno", 1},
        {"Frigorifero", 1},
        {"Lavatrice", 2},
        {"Lavastoviglie", 2},
        {"Tapparelle Elettriche", 2},
        {"Microonde", 2},
        {"Asciugatrice", 2},
        {"Televisore", 2}
    };

    if(std::regex_match(name,match,pattern))
    {
        std::unordered_map<std::string, int>::iterator it = type.find(match[1]);

        if (it != type.end()) {
            return it->second;  // Restituisce il tipo (manuale o automatico)
        } else {
            return 0;  // Se il dispositivo non esiste nella mappa
        }
    }
}


//Lambda Function per la gestione delle eccezioni per i vari metodi di Domotic System

void execute_with_exception_handling(const std::function<void()>& operation)
{
    try
    {
        operation();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<"Error: "<<e.what()<<std::endl;
    }
    catch(const std::domain_error& e)
    {
        std::cerr<<"Error "<<e.what()<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr<<"Generic error: "<<e.what()<<std::endl;
    }
}


int main()
{

    /*Oggetti di tipo Time utilizzati per inizializzare i dispositivi a ciclo prefissato*/
    const Time time_Lavatrice (1 , 50);
    const Time time_Lavastoviglie (3 , 15);
    const Time time_Tapparelle (0 , 1);
    const Time time_Microonde (0 , 2);
    const Time time_Asciugatrice (1 , 0);
    const Time time_Televisore (1 , 0);

    /*Oggetti di tipo time utilizzati per impostare un orario di inizio e di fine per i dispositivi manual,
    mentre per i dispositivi CP si imposta solo l'orario di inzio*/
    Time time_begin;
    Time time_end;

    /*Oggetto di tipo Time per tenere conto dell'ora effettiva della giornata in cui siamo*/
    Time real_time;

    /*Variabili int per tenere conto di quanti dispositivi dello
    stesso tipo sono presenti e per poter dare nomi diversi
    (es. Sono presenti due lavatrici: Lavatrice 1 e Lavatrice 2)*/
    int num_Impianto = 1;
    int num_Lavatrice = 1;
    int num_Lavastoviglie = 1;
    int num_Pompa = 1;
    int num_Tapparelle = 1;
    int num_Scaldabagno = 1;
    int num_Frigorifero = 1;
    int num_Microonde = 1;
    int num_Asciugatrice = 1;
    int num_Televisore = 1;

    /*Costanti int per impostare il numero massimo che può acquisire
    la scelta nei vari menu'(variabili create per evitare l'uso dei magic
    number nel codice e per poterle cambiare in modo efficiente se si vogliano
    modificare le scelte nei menu')*/
    const int CHOICES_MENU = 6;
    const int CHOICES_MENU_DEVICES = 10;


    //Regex per il controllo e la correttezza dei comandi inseriti dall'utente
    std::regex pattern1("^set\\s(.+{2,})\\s(on|off)$");
    std::regex pattern2("^set\\s(.+{2,})\\s([0-2][0-9]:[0-5][0-9])(?:\\s\\[(?:([0-2][0-9]:[0-5][0-9]))\\])?$");
    std::regex pattern3("^rm\\s+(.+)$");
    std::regex pattern4("^set time\\s([0-2][0-9]:[0-5][0-9])$");
    std::regex pattern5("^show(\\s+)?((.+))?$");
    std::smatch match;

    DomoticSystem ds;

    ManualDevice m;
    PresetDevice ps;

    int choice;

    /*Costante utilizzata perchè choice rimane a 0 e termina il programma
    piuttosto di tornare al menu precedente, evita l'utilizzo di un magic number*/
    const int BACK_TO_MAIN_MENU = 1000;

    std::string command = "";
    std::string name = "";
    std::vector<std::string> hour;

    //Menu principale
    do
    {
        menu();
        choice = readInt(CHOICES_MENU);
        switch(choice)
        {
            case 1:
                //Menu per inserire i dispositivi nel sistema domotico
                do
                {
                    menuDevices();
                    choice = readInt(CHOICES_MENU_DEVICES);
                    switch(choice)
                    {
                        //Inserimento dispositivi nel sistema domotico in base alla scelta
                        case 1:
                            name = "Impianto Fotovoltaico " + std::to_string(num_Impianto);
                            ds.add(ManualDevice(name, 1.5));
                            std::cout<< name <<" was added\n";
                            num_Impianto++;
                        break;

                        case 2:
                            name = "Pompa di calore + Termostato " + std::to_string(num_Pompa);
                            ds.add(ManualDevice(name, -2.0));
                            std::cout<< name <<" was added\n";
                            num_Pompa++;
                        break;

                        case 3:
                            name = "Scaldabagno " + std::to_string(num_Scaldabagno);
                            ds.add(ManualDevice(name, -1.0));
                            std::cout<< name <<" was added\n";
                            num_Scaldabagno++;
                        break;

                        case 4:
                            name = "Frigorifero " + std::to_string(num_Frigorifero);
                            ds.add(ManualDevice(name, -0.4));
                            std::cout<< name <<" was added\n";
                            num_Frigorifero++;
                        break;

                        case 5:
                            name = "Lavatrice " + std::to_string(num_Lavatrice);
                            ds.add(PresetDevice(name, -2.0, time_Lavatrice));
                            std::cout<< name <<" was added\n";
                            num_Lavatrice++;
                        break;

                        case 6:
                            name = "Lavastoviglie " + std::to_string(num_Lavastoviglie);
                            ds.add(PresetDevice(name, -1.5, time_Lavastoviglie));
                            std::cout<< name <<" was added\n";
                            num_Lavastoviglie++;
                        break;

                        case 7:
                            name = "Tapparelle Elettriche " + std::to_string(num_Tapparelle);
                            ds.add(PresetDevice(name, -0.3, time_Tapparelle));
                            std::cout<< name <<" was added\n";
                            num_Tapparelle++;
                        break;

                        case 8:
                            name = "Microonde " + std::to_string(num_Microonde);
                            ds.add(PresetDevice(name, -0.8, time_Microonde));
                            std::cout<< name <<" was added\n";
                        break;

                        case 9:
                            name = "Asciugatrice " + std::to_string(num_Asciugatrice);
                            ds.add(PresetDevice(name, -0.5, time_Asciugatrice));
                            std::cout<< name <<" was added\n";
                            num_Asciugatrice++;
                        break;

                        case 10:
                            name = "Televisore " + std::to_string(num_Televisore);
                            ds.add(PresetDevice(name, -0.2, time_Televisore));
                            std::cout<< name <<" was added\n";
                            num_Televisore++;
                        break;

                        case 0:
                        break;
                    }
                }
                while(choice != 0);
                choice = BACK_TO_MAIN_MENU;
            break;

            case 2:
                //Pulisco il buffer di input per evitare di avere messaggi non validi appena entro in questo sottomenu
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                //Menu per accendere o spegnere i dispositivi inseriti nel sistema domotico
                do
                {
                    menuTurnDevices();
                    std::getline(std::cin,command);
                    if(command != "0")
                    {
                        if(std::regex_match(command,match,pattern1))
                        {
                            name = match[1];
                            if(match[2] == "on")
                            {
                                //Accensione dispositivo se presente e se non gia' acceso
                                execute_with_exception_handling([&]()
                                {
                                    ds.set_on(name);
                                    std::cout<<"Operation completed successfully\n";
                                });
                            }else if(match[2] == "off")
                            {
                                //Spegnimento dispositivo se presente e se acceso
                                execute_with_exception_handling([&]()
                                {
                                    ds.set_off(name);
                                    std::cout<<"Operation completed successfully\n";
                                });
                            }
                        }else
                        {
                            std::cout<<"Invalid Command\n";
                        }
                    }else if(command == "0")
                    {
                        break;
                    }
                }
                while(choice != 0);
                choice = BACK_TO_MAIN_MENU;
            break;

            case 3:

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                //Menu per impostare o rimuovere un timer ai dispositivi inseriti nel sistema domotico
                do
                {
                    menuSetTimerofDevices();
                    std::getline(std::cin,command);

                    if(command != "0")
                    {
                        if(std::regex_match(command,match,pattern2))
                        {
                            name = match[1];
                            if(getDeviceType(name) == 1)
                            {
                                //Impostazione del timer per un dispositivo manual

                                hour = splitString(match[2],':');
                                time_begin = Time(std::stoi(hour[0]),std::stoi(hour[1]));

                                hour.clear();

                                hour = splitString(match[3],':');
                                time_end = Time(std::stoi(hour[0]),std::stoi(hour[1]));

                                hour.clear();
                                hour.shrink_to_fit();

                                execute_with_exception_handling([&]()
                                {
                                    ds.start_and_stop(name,time_begin,time_end);
                                    std::cout<<"Operation completed successfully\n";
                                });
                            }else if(getDeviceType(name) == 2)
                            {
                                //Impostazione del timer per un dispositivo CP

                                hour = splitString(match[2],':');
                                time_begin = Time(std::stoi(hour[0]),std::stoi(hour[1]));

                                hour.clear();
                                hour.shrink_to_fit();

                                execute_with_exception_handling([&]()
                                {
                                    ds.start_and_stop(name,time_begin);
                                    std::cout<<"Operation completed successfully\n";
                                });

                            }else
                            {
                                std::cout<<"Device not found or name not valid\n";
                            }
                        }else if(std::regex_match(command,match,pattern3))
                        {
                            //Rimozione del timer per un dispositivo se presente e se precedentemente impostato
                            name = match[1];

                            execute_with_exception_handling([&]()
                            {
                                ds.remove(name);
                                std::cout<<"Operation completed successfully\n";
                            });
                        }else
                        {
                        std::cout<<"Invalid command\n";
                        }

                    }else if(command == "0")
                    {
                        break;
                    }
                }while(choice != 0);
                choice = BACK_TO_MAIN_MENU;

            break;

            case 4:
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                //Menu per stampare a schermo tutti i dispositivi o un dispositivo in particolare
                do
                {
                    menuShow();
                    std::getline(std::cin, command);

                    if(command != "0")
                    {
                        if(std::regex_match(command,match,pattern5))
                        {
                            name = match[2];
                            if(name.empty())
                            {
                                //Stampa di tutti i dispositivi nel sistema domotico e dei loro eventuali timer
                                ds.show();
                            }else
                            {
                                //Stampa di un dispositivo se presente nel sistema domotico e del suo timer se impostato
                                execute_with_exception_handling([&]()
                                {
                                    ds.show(name);
                                });
                            }
                        }else
                        {
                            std::cout<<"Invalid command\n";
                        }
                    }else if(command == "0")
                    {
                        choice = 0;
                    }
                }while(choice != 0);
                choice = BACK_TO_MAIN_MENU;

            break;

            case 5:
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                //Menu per impostare un orario della giornata
                do
                {
                    menuSetTime();
                    std::getline(std::cin, command);


                    if(command != "0")
                    {
                        if(std::regex_match(command,match,pattern4))
                        {
                            //Impostazione orario della giornata

                            hour = splitString(match[1],':');
                            real_time = Time(std::stoi(hour[0]),std::stoi(hour[1]));

                            execute_with_exception_handling([&]()
                            {
                                ds.set_time(real_time);
                                std::cout<<"Operation completed successfully\n";
                            });

                        }else{
                            std::cout<<"Invalid command\n";
                        }
                    }else if(command == "0")
                    {
                        choice = 0;
                    }
                }while(choice != 0);
                choice = BACK_TO_MAIN_MENU;
            break;

            case 6:
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                //Menu per i comandi di debug
                do
                {
                    menuDebug();
                    std::getline(std::cin, command);
                    if(command != "0")
                    {
                        if(command == "reset time")
                        {
                            /*Imposta l'orario alle 00:00 e riporta tutti i dispositivi alle
                            condizioni inziali mantenendo i loro timer*/
                            ds.reset_time();
                        }else if(command == "reset timers")
                        {
                            //Imposta l'orario alle 00:00 e mantiene lo stato di tutti i dispositivi ma senza i loro timer
                            ds.reset_timers();
                        }else if(command == "reset all")
                        {
                            /*Imposta l'orario alle 00:00 e tutto viene riportato
                            alle condizioni inziali, rimuovendo anche i timer*/
                            ds.reset_all();
                        }else
                        {
                            std::cout<<"Invalid command\n";
                        }

                    }else if(command == "0")
                    {
                        break;
                    }

                }while(choice != 0);
                choice = BACK_TO_MAIN_MENU;
            break;

            case 0:
                //Fine del programma
                std::cout<<"System shutdown\n";
            break;
        }
        name = "Impianto Fotovoltaico " + std::to_string(num_Impianto);
    }while(choice != 0);
}
