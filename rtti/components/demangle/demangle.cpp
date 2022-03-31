/*
 * demangle.cpp
 *
 *  Created on: 07.03.2022
 *      Author: Franz
 */



#include <string>
#include <cxxabi.h>
#include <iostream>
#include "demangle.h"


/* Helper function which converts typeid().name() to a human-readable type name */
std::string demangle(const char* name)
{
    int status = 0;
    char* result = abi::__cxa_demangle(name, NULL, NULL, &status);
    std::string str_result;
    if (status == 0) {
        str_result = result;
    } else {
        str_result = name;
    }
    free(result);
    return str_result;
}
