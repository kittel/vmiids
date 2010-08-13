/*
 * Modintern.h
 *
 *  Created on: Aug 13, 2010
 *      Author: kittel
 */

#ifndef MODINTERN_H_
#ifndef VMIIDS_H_
#define MODINTERN_H_

#include "vmiids/VmiIDS.h"

namespace vmi {

template <class module>
class proxy {
  public:
    proxy (){
		try {
			module * ptr = new module;
			std::cerr << "Loading " << ptr->getName() << "... ";
			vmi::VmiIDS::getInstance()->enqueueModule(ptr);
			std::cerr << "Success" << std::endl;
		} catch (vmi::ModuleException &e) {
			std::cerr << "FAILED" << std::endl;
			e.printException();
		} catch (std::exception &e) {
			std::cerr << "FAILED" << std::endl;
			std::cerr << e.what() << std::endl;
		}
    };

};

}

#define ADDMODULE(classname) \
	static vmi::proxy<classname> CONCAT(classname, p);

#endif /* VMIIDS_H_ */
#endif /* MODINTERN_H_ */
