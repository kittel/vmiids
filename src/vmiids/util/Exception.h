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

/**
 * @class Exception Exception.h "vmiids/util/Exception.h"
 *
 * This class is the frameworks basic exception class.
 * Inherited from std::exception to provide stdlib compatibility.
 */
class Exception: public std::exception {
protected:
	std::string message; //!< String containing the exceptions throw reason.
public:
	/**
	 * Default Constructor. No exception message is set.
	 */
	Exception(){ this->message = ""; }

	/**
	 * Constructor
	 *
	 * @param text Exceptions throw reason.
	 * @return
	 */
	Exception(std::string text){ this->message = text; }

	/**
	 * Destructor
	 * @return
	 */
	virtual ~Exception() throw(){};

	/**
	 * Function inherited from std::exception
	 * @return Exceptions throw reason.
	 */
	virtual const char* what() const throw () {
		return "Exception abort";
	}

	/**
	 * Print exceptions reason to std::cerr.
	 */
	virtual void printException(){ std::cerr << what() << ": " << this->message << std::endl; }
};

}

#endif /* EXCEPTION_H */
