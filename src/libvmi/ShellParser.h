#ifndef _SHELLPARSER_H_
#define _SHELLPARSER_H_

#include "ConsoleMonitor.h"

namespace libVMI {

/*!
 * \exception ShellParserException ShellParser.h
 * \brief Exception for ShellParser.
 */
class ShellParserException: public std::exception {
	virtual const char* what() const throw () {
		return "ShellParser abort";
	}
};

/*!
 * \class ShellParser ShellParser.h
 *
 * \brief Parser for a Serial Shell Session.
 */
class ShellParser : public ConsoleMonitor {
	private:
		bool loggedin;
		bool login(const char* username, const char * password);
		void logout();

		bool isLoggedin(void);

	public:
		ShellParser();
		virtual ~ShellParser();

		bool sudo(const char* password);
};

}

#endif /* _SHELLPARSER_H_ */
