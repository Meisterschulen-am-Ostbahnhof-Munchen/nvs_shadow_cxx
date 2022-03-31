#include <iostream>
#include <map>
#include <string>
#include <any>

#include "demangle.h"

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




    auto petName = notebook["PetName"];
    cout << "typeid(petName).name() is: " << demangle(petName.type().name()) << endl;
	std::string name2 = std::any_cast<std::string>(petName); // = "Pluto"

    cout << "typeid(std::string).name() is: " << demangle(typeid(std::string).name()) << endl;


	auto born = notebook["Born"];
    cout << "typeid(born).name() is: " << demangle(born.type().name()) << endl;
	int year2 = std::any_cast<int>(born); // = 2015




    cout << "app_main done" << endl;
}
