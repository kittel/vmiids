/*
 * NotificationModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef NOTIFICATIONMODULE_H_
#define NOTIFICATIONMODULE_H_

#include "vmiids/Module.h"
#include "vmiids/util/Mutex.h"

#include <streambuf>
#include <ostream>
#include <vector>
#include <map>
#include <cstring>

namespace vmi {


template <class cT, class traits = std::char_traits<cT> >
class NotificationModuleStreamBuffer : public std::basic_streambuf<cT, traits>
{
public:
	NotificationModuleStreamBuffer(std::string p_name,
			void (*p_notifyFunction)(std::string, std::string)) :
    	buf(BUF_SIZE), name(p_name), notifyFunction(p_notifyFunction){
    	std::basic_streambuf<cT, traits>::setp(&buf[0], &buf[0] + buf.capacity());
    }
protected:
    virtual typename traits::int_type overflow(typename traits::int_type c = traits::eof())
    {
    	size_t currentptr = buf.capacity();
    	buf.resize(buf.capacity()*2);
    	std::basic_streambuf<cT, traits>::setp(&buf[0], &buf[0] + buf.capacity());
    	std::basic_streambuf<cT, traits>::pbump(currentptr);
    	*std::basic_streambuf<cT, traits>::pptr() = c;
    	std::basic_streambuf<cT, traits>::pbump(1);
    	return traits::not_eof(c);
    }

    virtual int sync(void)
    {
        // Handle output
        notifyFunction(name, std::string(std::basic_streambuf<cT, traits>::pbase(),
        		std::basic_streambuf<cT, traits>::pptr()));

        // This tells that buffer is empty again
    	buf.resize(BUF_SIZE);
    	memset(&buf[0], 0, buf.capacity());
    	std::basic_streambuf<cT, traits>::setp(&buf[0], &buf[0] + buf.capacity());
        return 0;
    }
private:
    // Work in buffer mode. It is also possible to work without buffer.
    static size_t const BUF_SIZE = 64;
    std::vector<cT> buf;
    std::string name;
    void (*notifyFunction)(std::string, std::string);
};

template <class cT, class traits = std::char_traits<cT> >
class NotificationModuleStreamTemplate: public std::basic_ostream< cT, traits >
{
public:
	NotificationModuleStreamTemplate(std::string name, void (*notifyFunction)(std::string, std::string)) :
    	std::basic_ostream< cT, traits >(&buf), buf(name, notifyFunction){}
private:
    NotificationModuleStreamBuffer<cT> buf;
};

typedef NotificationModuleStreamTemplate<char> NotificationStream;
typedef NotificationModuleStreamTemplate<wchar_t> wNotificationStream;

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

	private:
		nullstream nullStream;

		static std::map<std::string, vmi::NotificationModule *> modules;
		static vmi::Mutex mutex;

	public:
		NotificationModule(std::string moduleName);
		virtual ~NotificationModule();

		virtual void doDebug(std::string module, std::string message) = 0;
		virtual void doInfo(std::string module, std::string message) = 0;
		virtual void doWarn(std::string module, std::string message) = 0;
		virtual void doError(std::string module, std::string message) = 0;
		virtual void doCritical(std::string module, std::string message) = 0;
		virtual void doAlert(std::string module, std::string message) = 0;

		static void debug(std::string module, std::string message);
		static void info(std::string module, std::string message);
		static void warn(std::string module, std::string message);
		static void error(std::string module, std::string message);
		static void critical(std::string module, std::string message);
		static void alert(std::string module, std::string message);

		static void killInstances();
};

}

#endif /* NOTIFICATIONMODULE_H_ */
