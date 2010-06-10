/*
 * QemuMonitorTest.cpp
 *
 *  Created on: Jun 2, 2010
 *      Author: kittel
 */
#include "QemuMonitorTest.h"
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( QemuMonitorTest );

void QemuMonitorTest::setUp() {
	monitor = new libVMI::QemuMonitorParser();
}

void QemuMonitorTest::tearDown() {
	delete(monitor);
}

void QemuMonitorTest::testConstructor() {
	libVMI::QemuMonitorParser* monitor2;
	CPPUNIT_ASSERT_NO_THROW( monitor2 = new libVMI::QemuMonitorParser() );
	delete(monitor2);
}

void QemuMonitorTest::testIsRunning() {
	CPPUNIT_ASSERT_NO_THROW(monitor->isRunning());
	CPPUNIT_ASSERT_MESSAGE( "Test reports VM is not running. "
			"Ensure VM is not paused, when running this Test",
			monitor->isRunning());
}

void QemuMonitorTest::testPause() {
	monitor->pauseVM();
	CPPUNIT_ASSERT_NO_THROW(monitor->isRunning());
	CPPUNIT_ASSERT(!monitor->isRunning());
}

void QemuMonitorTest::testResume() {
	monitor->resumeVM();
	CPPUNIT_ASSERT_NO_THROW(monitor->isRunning());
	CPPUNIT_ASSERT(monitor->isRunning());
}


void QemuMonitorTest::testHelp(){
	std::string helptext;
	CPPUNIT_ASSERT_NO_THROW(monitor->cmdHelp(helptext));
	CPPUNIT_ASSERT(!helptext.empty());
}

void QemuMonitorTest::testInfoHelp(){
	std::string helptext;
	CPPUNIT_ASSERT_NO_THROW(monitor->infoHelp(helptext));
	CPPUNIT_ASSERT(!helptext.empty());
}
