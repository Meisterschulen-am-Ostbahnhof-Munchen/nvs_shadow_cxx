#include <iostream>

using std::cout;
using std::endl;


/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{
    cout << "app_main starting" << endl;


    cout << "app_main done" << endl;
}
