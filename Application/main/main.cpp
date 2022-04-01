/* C++ run-time type info (RTTI) example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <iostream>
#include <memory>
#include "settingsNVS.h"

using std::cout;
using std::endl;
using std::string;


/* Inside a .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main()
{

	/* Initialize application */
	initSettings();


	preloadS8("CF-A", "byte", 55);


    int8_t r = -9;
    r = getS8("CF-A", "byte", r);
    cout << "r = " << +r << endl;




    int8_t z = -9;
    z = getS8("CF-A", "123XXX123", 45);
    cout << "z = " << +z << endl;


    z = getS8("CF-A", "123XXX123", 12);
    cout << "z = " << +z << endl;


    cout << "Example finished." << endl;
}


