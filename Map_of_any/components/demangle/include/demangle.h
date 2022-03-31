/*
 * demangle.h
 *
 *  Created on: 07.03.2022
 *      Author: Franz
 */

#ifndef COMPONENTS_LIBRARIES_UTIL_DEMANGLE_HPP_
#define COMPONENTS_LIBRARIES_UTIL_DEMANGLE_HPP_


std::string demangle(const char* name);

#define DEBG_OBJ(typ)	std::cout << __FILE__ << "(" << __LINE__ << ") FUNC: " << __FUNCTION__  << " type: " << demangle(typeid(typ).name()) << "*********************************************************" <<std::endl

#define DEBG_LINE()	std::cout << __FILE__ << "(" << __LINE__ << ") FUNC: " << __FUNCTION__  << "*********************************************************" <<std::endl

#endif /* COMPONENTS_LIBRARIES_UTIL_DEMANGLE_HPP_ */
