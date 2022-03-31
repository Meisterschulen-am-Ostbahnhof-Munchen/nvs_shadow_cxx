#include <iostream>
#include <map>
#include <string>
#include <any>

using std::cout;
using std::endl;


/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{
    cout << "app_main starting" << endl;



    std::map<std::string, std::any> notebook;

    std::string name{ "Pluto" };
    int year = 2015;

    notebook["PetName"] = name;
    notebook["Born"] = year;

    std::string name2 = std::any_cast<std::string>(notebook["PetName"]); // = "Pluto"
    int year2 = std::any_cast<int>(notebook["Born"]); // = 2015




    cout << "app_main done" << endl;
}
