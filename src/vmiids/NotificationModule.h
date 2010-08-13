/*
 * NotificationModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef NOTIFICATIONMODULE_H_
#define NOTIFICATIONMODULE_H_

#include "Module.h"

#include <ostream>
#include <streambuf>
#include <ostream>

namespace vmi {

//Throw away all output - see from:
//http://www.velocityreviews.com/forums/t450028-null-ostream.html
template <class cT, class traits = std::char_traits<cT> >
class basic_nullbuf: public std::basic_streambuf<cT, traits> {
typename traits::int_type overflow(typename traits::int_type c)
{
return traits::not_eof(c); // indicate success
}
};

template <class cT, class traits = std::char_traits<cT> >
class basic_onullstream: public std::basic_ostream<cT, traits> {
public:
basic_onullstream():
std::basic_ios<cT, traits>(&m_sbuf),
std::basic_ostream<cT, traits>(&m_sbuf)
{
init(&m_sbuf);
}

private:
basic_nullbuf<cT, traits> m_sbuf;
};

typedef basic_onullstream<char> nullstream;
typedef basic_onullstream<wchar_t> wnullstream;

typedef enum {
	OUTPUT_DEBUG = 0,
	OUTPUT_INFO,
	OUTPUT_WARN,
	OUTPUT_ERROR,
	OUTPUT_CRITICAL,
	OUTPUT_ALERT
} DEBUG_LEVEL;

class NotificationModule : public vmi::Module{
	protected:
		DEBUG_LEVEL debugLevel;
		nullstream nullStream;

	public:
		NotificationModule(std::string moduleName);
		virtual ~NotificationModule(){};

		virtual void debug(Module *module, std::string message) = 0;
		virtual void info(Module *module, std::string message) = 0;
		virtual void warn(Module *module, std::string message) = 0;
		virtual void error(Module *module, std::string message) = 0;
		virtual void critical(Module *module, std::string message) = 0;
		virtual void alert(Module *module, std::string message) = 0;

		virtual std::ostream& debug(Module *module) = 0;
		virtual std::ostream& info(Module *module) = 0;
		virtual std::ostream& warn(Module *module) = 0;
		virtual std::ostream& error(Module *module) = 0;
		virtual std::ostream& critical(Module *module) = 0;
		virtual std::ostream& alert(Module *module) = 0;
};

}

#include "Modintern.h"

#define GETNOTIFICATIONMODULE(variable, modulename) \
		variable = vmi::VmiIDS::getInstance()->getNotificationModule(QUOTE(modulename)); \
		if (!variable) { \
			throw vmi::DependencyNotFoundException(QUOTE(modulename)); \
		}

#endif /* NOTIFICATIONMODULE_H_ */
