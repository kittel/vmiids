/*
 ============================================================================
 Name        : libvmi.cpp
 Author      : Thomas Kittel
 Version     :
 Copyright   : (c) Thomas Kittel
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include "libvmi.h"

using namespace std ;

#define DEBUG

#ifdef DEBUG
#define VERBOSE "ShellParser"
#endif /* DEBUG */
#include "Debug.h"

int main(int argc, char ** argv){

	libVMI::Shell shell;
	shell.startShell();

	shell.stopShell();
	return 0;
}
