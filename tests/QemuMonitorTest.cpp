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
//	monitor = new libVMI::MonitorParser();
}

void QemuMonitorTest::tearDown() {
//	delete(monitor);
}

void QemuMonitorTest::testConstructor() {
	libVMI::MonitorParser* monitor2;
	CPPUNIT_ASSERT_NO_THROW( monitor2 = new libVMI::MonitorParser() );
	delete(monitor2);
}

void QemuMonitorTest::testIsRunning() {
	CPPUNIT_FAIL("Not Implemented");
//	printf("Running test.\n");
//	CPPUNIT_ASSERT_MESSAGE( "Test reports VM is not running. "
//			"Ensure VM is not paused, when running this Test",
//			monitor->isRunning());
}

void QemuMonitorTest::testPause() {
	CPPUNIT_FAIL("Not Implemented");
	//	monitor->pauseVM();
//	CPPUNIT_ASSERT(!monitor->isRunning());
}

void QemuMonitorTest::testResume() {
	CPPUNIT_FAIL("Not Implemented");
//	monitor->resumeVM();
//	CPPUNIT_ASSERT(monitor->isRunning());
}

void QemuMonitorTest::testDestructor() {
	CPPUNIT_FAIL("Not Implemented");
//	libVMI::MonitorParser* monitor2;
//	monitor2 = new libVMI::MonitorParser();
//	CPPUNIT_ASSERT_NO_THROW( delete(monitor2) );
}
