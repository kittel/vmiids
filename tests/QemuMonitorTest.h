/*
 * QemuMonitorTest.h
 *
 *  Created on: Jun 2, 2010
 *      Author: kittel
 */

#ifndef QEMUMONITORTEST_H_
#define QEMUMONITORTEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include "libvmi.h"


class QemuMonitorTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( QemuMonitorTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testIsRunning );
  CPPUNIT_TEST( testPause );
  CPPUNIT_TEST( testResume );
  CPPUNIT_TEST_SUITE_END();
private:

  libVMI::MonitorParser *monitor;

public:
  void setUp();
  void tearDown();

  void testConstructor();
  void testIsRunning();
  void testPause();
  void testResume();
};


#endif /* QEMUMONITORTEST_H_ */
