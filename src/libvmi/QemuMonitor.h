/*
 * QemuMonitor.h
 *
 *  Created on: Jun 10, 2010
 *      Author: kittel
 */

#ifndef QEMUMONITOR_H_
#define QEMUMONITOR_H_

#include "QemuMonitorParser.h"

namespace libVMI {

/*!
 * \exception QemuMonitorException QemuMonitor.h
 * \brief Exception for QemuMonitor.
 */
class QemuMonitorException: public std::exception {
	virtual const char* what() const throw () {
		return "QemuMonitor abort";
	}
};

/*!
 * \class QemuMonitor QemuMonitor.h
 *
 * \brief Parser for the QEmu Monitor Console. Results are parsed to structs.
 */
class QemuMonitor: public QemuMonitorParser {
private:
	static int callCount;

public:
	QemuMonitor() throw(QemuMonitorException);
	virtual ~QemuMonitor();


	/**
	 * \brief Function to get the current vm state.
	 * @return Returns true when the monitored VM is currently running.
	 */
	bool isRunning() throw(QemuMonitorException);

	/**
	 * \brief Function to pause the execution of the monitored VM.
	 */
	void pauseVM() throw(QemuMonitorException);

	/**
	 * \brief Function to resume the execution of the monitored VM.
	 */
	void resumeVM() throw(QemuMonitorException);
};

}

#endif /* QEMUMONITOR_H_ */
