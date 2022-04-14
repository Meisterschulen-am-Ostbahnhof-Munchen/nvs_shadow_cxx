#include <iostream>
#include <map>
#include <string>
#include <any>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "demangle.h"

using std::cout;
using std::endl;




typedef void (*ScriptFunction)(void); // function pointer type


void ScriptFunction_string(void){
    cout << "ScriptFunction_string" << endl;
}


void ScriptFunction_int(void){
    cout << "ScriptFunction_int" << endl;
}

//Inspiration coming from: https://stackoverflow.com/questions/24702235/c-stdmap-holding-any-type-of-value

/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{
    cout << "app_main starting" << endl;



    std::map<std::string, std::any> notebook;
    std::unordered_map<std::type_index, ScriptFunction> script_map;


    script_map[std::type_index(typeid(std::string))] = ScriptFunction_string;
    script_map[std::type_index(typeid(int))]         = ScriptFunction_int;

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



	script_map[std::type_index(petName.type())]();
	script_map[std::type_index(born.type())]();


    cout << "app_main done" << endl;
}
