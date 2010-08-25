/*
 * Thread.cpp
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#include "Thread.h"

namespace vmi {

void (*Thread::defaultExceptionHandler)(std::exception&) = NULL;

}
