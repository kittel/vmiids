/*
 * Exception.h
 *
 *  Created on: Aug 27, 2010
 *      Author: tom
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <iostream>

namespace vmi {

class Exception: public std::exception {
protected:
	std::string message;
public:
	Exception(){ this->message = ""; }
	Exception(std::string text){ this->message = text; }
	virtual ~Exception() throw(){};
	virtual const char* what() const throw () {
		return "Exception abort";
	}
	virtual void printException(){ std::cerr << what() << ": " << this->message << std::endl; }
};

}

#endif /* EXCEPTION_H */
