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

/**
 * @class NotificationModuleStreamBuffer NotificationModule.h "vmiids/NotificationModule.h"
 * @brief VmiIDS Stream buffer
 * @sa NotificationModule
 *
 * Custom std::streambuf implementation. The stream buffer forwards the
 * output to all NotificationModules loaded into the framework. It was implemented
 * to enable a module developer to use the standard c++ ostream API.
 *
 * This class contains a buffer to store output in. Whenever this output is to be flushed,
 * its content is forwarded to all registered NotificationModules. Flushing can either be
 * triggered manually or is conducted whenever a '\n' character was written.
 *
 * An instance of this class is created for each OutputModule and each available severity.
 */
template <class cT, class traits = std::char_traits<cT> >
class NotificationModuleStreamBuffer : public std::basic_streambuf<cT, traits>
{
public:
	/**
	 * Constructor
	 * @param p_name Name of the module this stream buffer referres to.
	 * @param p_notifyFunction Notify function. See NotificationModule.
	 */
	NotificationModuleStreamBuffer(std::string p_name,
			void (*p_notifyFunction)(std::string, std::string)) :
    	buf(BUF_SIZE), name(p_name), notifyFunction(p_notifyFunction){
    	std::basic_streambuf<cT, traits>::setp(&buf[0], &buf[0] + buf.capacity());
    }
protected:
	/**
	 * Function called whenever the internal buffer is full.
	 * This function resizes the underlying buffer and enqueues the last byte,
	 *  which did not fit into the buffer.
	 * @param c Last byte which did not fit into the buffer.
	 * @return Returns if the buffer is still writable.
	 */
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

    /**
     * Function called whenever the buffer is about to be flushed.
     * This function forwards the buffers contents to the dispatcher inside the NotificationModule class.
     * @return Zero.
     */
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
    static size_t const BUF_SIZE = 64; //!< Size of the internal buffer.
    std::vector<cT> buf; //!< Internal buffer.
    std::string name; //!< Name of the module this stream buffer referres to.
    void (*notifyFunction)(std::string, std::string);  //!< Notify function. See NotificationModule.
};

/**
 * @class NotificationModuleStreamTemplate NotificationModule.h "vmiids/NotificationModule.h"
 * @brief VmiIDS Stream buffer
 * @sa NotificationModule
 *
 * Custom std::ostream implementation. The stream buffer forwards the
 * output to all NotificationModules loaded into the framework. It was implemented
 * to enable a module developer to use the standard c++ ostream API.
 *
 * This class contains the ostream class usable by module developers. Whenever this output
 * is to be flushed, its content is forwarded to all registered NotificationModules. Flushing
 * can either be triggered manually or is conducted whenever a '\n' character was written.
 *
 * An instance of this class is created for each OutputModule and each available severity.
 */
template <class cT, class traits = std::char_traits<cT> >
class NotificationModuleStreamTemplate: public std::basic_ostream< cT, traits >
{
public:
	/**
	 * Constructor
	 * @param name Name of the module this stream buffer referres to.
	 * @param notifyFunction Notify function. See NotificationModule.
	 */
	NotificationModuleStreamTemplate(std::string name, void (*notifyFunction)(std::string, std::string)) :
    	std::basic_ostream< cT, traits >(&buf), buf(name, notifyFunction){}
private:
    NotificationModuleStreamBuffer<cT> buf;  //!< internal stream buffer
};

/**
 * Typedef for easier internal use.
 * This version is used for char buffers.
 * One character is 8 bits long (UTF-8).
 */
typedef NotificationModuleStreamTemplate<char> NotificationStream;
/**
 * Typedef for easier internal use.
 * This version is used for wchar_t buffers.
 * One character is 16 bits long (UTF-16).
 */
typedef NotificationModuleStreamTemplate<wchar_t> wNotificationStream;


//Throw away all output - see from:
//http://www.velocityreviews.com/forums/t450028-null-ostream.html
/**
 * @class basic_nullbuf NotificationModule.h "vmiids/NotificationModule.h"
 *
 * Stream buffer used throwing all contents away. Was used before custom ostream
 * was implemented.
 *
 * @deprecated
 */
template <class cT, class traits = std::char_traits<cT> >
class basic_nullbuf: public std::basic_streambuf<cT, traits> {
typename traits::int_type overflow(typename traits::int_type c)
{
return traits::not_eof(c); // indicate success
}
};

/**
 * @class basic_onullstream NotificationModule.h "vmiids/NotificationModule.h"
 *
 * Stream buffer used throwing all contents away. Was used before custom ostream
 * was implemented.
 *
 * @sa basic_nullbuf
 * @deprecated
 */
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

/**
 * Typedef for easier internal use.
 * This version is used for char buffers.
 * One character is 8 bits long (UTF-8).
 */
typedef basic_onullstream<char> nullstream;
/**
 * Typedef for easier internal use.
 * This version is used for wchar_t buffers.
 * One character is 16 bits long (UTF-16).
 */
typedef basic_onullstream<wchar_t> wnullstream;

/**
 * @enum DEBUG_LEVEL
 *
 * Different levels of severity.
 */
typedef enum {
	OUTPUT_DEBUG = 0,//!< Debug
	OUTPUT_INFO,     //!< Information
	OUTPUT_WARN,     //!< Warning
	OUTPUT_ERROR,    //!< Error
	OUTPUT_CRITICAL, //!< Critical
	OUTPUT_ALERT     //!< Alert
} DEBUG_LEVEL;

/**
 * @class NotificationModule NotificationModule.h "vmiids/NotificationModule.h"
 *
 * Basic output logic.
 *
 * Notification modules are the basic output mechanism in VmiIDS.
 * The NotificationModule class is a Singleton (Multiton).
 *
 * @sa OutputModule
 */
class NotificationModule : public vmi::Module{
	protected:
		DEBUG_LEVEL debugLevel; //!< Severity threshold

	private:
		nullstream nullStream;

		/**
		 * Map of all loaded instances of NotificationModule class.
		 * The ModuleName is used as key.
		 */
		static std::map<std::string, vmi::NotificationModule *> modules;
		static vmi::Mutex mutex;  //!< Mutex to handle reentrance.

	public:
		/**
		 * Constructor
		 *
		 * The name of the module can be specified by the dynamic classloader provided by
		 * the module interface (LOADMODULE())
		 *
		 * @param moduleName Name of the detectionModule
		 */
		NotificationModule(std::string moduleName);
		/**
		 * Destructor
		 */
		virtual ~NotificationModule();

		/**
		 * Debug Output function.
		 * This function must be implemented by NotificationModules.
		 *
		 * @param module Name of the module which caused the output.
		 * @param message Message to output.
		 */
		virtual void doDebug(std::string module, std::string message) = 0;

		/**
		 * Information Output function.
		 * This function must be implemented by NotificationModules.
		 *
		 * @param module Name of the module which caused the output.
		 * @param message Message to output.
		 */
		virtual void doInfo(std::string module, std::string message) = 0;

		/**
		 * WArning Output function.
		 * This function must be implemented by NotificationModules.
		 *
		 * @param module Name of the module which caused the output.
		 * @param message Message to output.
		 */
		virtual void doWarn(std::string module, std::string message) = 0;

		/**
		 * Error Output function.
		 * This function must be implemented by NotificationModules.
		 *
		 * @param module Name of the module which caused the output.
		 * @param message Message to output.
		 */
		virtual void doError(std::string module, std::string message) = 0;

		/**
		 * Critical Output function.
		 * This function must be implemented by NotificationModules.
		 *
		 * @param module Name of the module which caused the output.
		 * @param message Message to output.
		 */
		virtual void doCritical(std::string module, std::string message) = 0;

		/**
		 * Alert Output function.
		 * This function must be implemented by NotificationModules.
		 *
		 * @param module Name of the module which caused the output.
		 * @param message Message to output.
		 */
		virtual void doAlert(std::string module, std::string message) = 0;

		/**
		 * Dispatcher for Debug output
		 * @param module Name of the module which caused the output.
		 * @param message Message to output
		 */
		static void debug(std::string module, std::string message);
		/**
		 * Dispatcher for Info output
		 * @param module Name of the module which caused the output.
		 * @param message Message to output
		 */
		static void info(std::string module, std::string message);
		/**
		 * Dispatcher for Warn output
		 * @param module Name of the module which caused the output.
		 * @param message Message to output
		 */
		static void warn(std::string module, std::string message);
		/**
		 * Dispatcher for Error output
		 * @param module Name of the module which caused the output.
		 * @param message Message to output
		 */
		static void error(std::string module, std::string message);
		/**
		 * Dispatcher for Critical output
		 * @param module Name of the module which caused the output.
		 * @param message Message to output
		 */
		static void critical(std::string module, std::string message);
		/**
		 * Dispatcher for Alert output
		 * @param module Name of the module which caused the output.
		 * @param message Message to output
		 */
		static void alert(std::string module, std::string message);

		/**
		 * Clear list of active NotificationModules.
		 */
		static void killInstances();
};

}

#endif /* NOTIFICATIONMODULE_H_ */
