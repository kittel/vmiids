/*
 * QemuMonitorSensorModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include "QemuMonitorSensorModule.h"

#include "vmiids/util/MutexLocker.h"

LOADMODULE(QemuMonitorSensorModule);

QemuMonitorSensorModule::QemuMonitorSensorModule() : SensorModule("QemuMonitorSensorModule"), ConsoleMonitor(){
	std::string optionConsoleName;
	std::string optionMonitorShell;

	GETOPTION(consoleName, optionConsoleName);
	GETOPTION(monitorShell, optionMonitorShell);

	try{
		this->initConsoleMonitor(optionConsoleName.c_str(),
			optionMonitorShell.c_str());
	}catch(vmi::ConsoleMonitorException &e){
		throw vmi::ModuleException("Internal error while initializing");
	}catch (const char * exception) {
		throw vmi::ModuleException(exception);
	}
}

QemuMonitorSensorModule::~QemuMonitorSensorModule() {
	// TODO Auto-generated destructor stub
}

bool QemuMonitorSensorModule::isRunning() throw(vmi::ModuleException){
	debug << "isRunning called" << std::endl;
	std::string string;
	this->infoStatus(string);
	if(string.rfind("running") != std::string::npos) return true;
	else if(string.rfind("paused") != std::string::npos) return false;
	throw vmi::ModuleException();
}

void QemuMonitorSensorModule::pauseVM() throw(vmi::ModuleException){
	debug << "pauseVM called" << std::endl;
	std::string string;
	this->cmdStop(string);
}

void QemuMonitorSensorModule::resumeVM() throw(vmi::ModuleException){
	debug << "resumeVM called" << std::endl;
	std::string string;
	this->cmdCont(string);
}

void QemuMonitorSensorModule::cmdHelp(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdHelp called" << std::endl;
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCommit(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdCommit called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdCommit");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdInfo(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdInfo called" << std::endl;
	try{ this->parseCommandOutput("info", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdQuit(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdQuit called" << std::endl;
	try{ this->parseCommandOutput("quit", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdEject(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdEject called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdEject");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdChange(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdChange called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdChange");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdScreendump(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdScreendump called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdScreendump");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdLogfile(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdLogfile called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdLogfile");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdLog(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdLog called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdLog");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSavevm(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdSavevm called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdSavevm");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdLoadvm(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdLoadvm called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdLoadvm");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDelvm(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdDelvm called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdDelvm");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSinglestep(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdSinglestep called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdSinglestep");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdStop(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdStop called" << std::endl;
	try{ this->parseCommandOutput("stop", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCont(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdCont called" << std::endl;
	try{ this->parseCommandOutput("cont", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdGdbserver(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdGdbserver called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdGdbserver");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdX(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdX called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdX");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdXp(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdXp called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdXp");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPrint(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdPrint called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdPrint");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdI(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdI called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdI");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdO(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdO called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdO");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSendkey(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdSendkey called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdSendkey");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSystem_reset(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdSystem_reset called" << std::endl;
	try{ this->parseCommandOutput("system_reset", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSystem_powerdown(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdSystem_powerdown called" << std::endl;
	try{ this->parseCommandOutput("system_powerdown", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSum(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdSum called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdSum");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdUsb_add(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdUsb_add called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdUsb_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdUsb_del(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdUsb_del called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdUsb_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDevice_add(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdDevice_add called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdDevice_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDevice_del(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdDevice_del called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdDevice_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCpu(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdCpu called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdCpu");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMouse_move(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMouse_move called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMouse_move");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMouse_button(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMouse_button called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMouse_button");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMouse_set(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMouse_set called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMouse_set");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdWavecapture(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdWavecapture called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdWavecapture");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdStopcapture(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdStopcapture called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdStopcapture");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMemsave(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMemsave called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdStopcapture");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPmemsave(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdPmemsave called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdPmemsave");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdBoot_set(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdBoot_set called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdBoot_set");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdNmi(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdNmi called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdNmi");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMigrate called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMigrate");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate_cancel(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMigrate_cancel called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMigrate_cancel");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate_set_speed(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMigrate_set_speed called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMigrate_set_speed");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate_set_downtime(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMigrate_set_speed called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMigrate_set_downtime");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDrive_add(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdDrive_add called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdDrive_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPci_add(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdPci_add called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdPci_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPci_del(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdPci_del called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdPci_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHost_net_add(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdHost_net_add called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdPci_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHost_net_remove(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdHost_net_remove called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdHost_net_remove");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHostfwd_add(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdHostfwd_add called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdHostfwd_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHostfwd_remove(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdHostfwd_remove called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdHostfwd_remove");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdBalloon(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdBalloon called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdBalloon");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSet_link(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdSet_link called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdSet_link");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdWatchdog_action(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdWatchdog_action called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdWatchdog_action");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_show(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdAcl_show called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdAcl_show");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_policy(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdAcl_policy called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdAcl_policy");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_add(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdAcl_add called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdAcl_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_remove(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdAcl_remove called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdAcl_remove");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_reset(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdAcl_reset called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdAcl_reset");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMce(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdMce called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdMce");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdGetfd(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdGetfd called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdGetfd");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdClosefd(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdClosefd called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdClosefd");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdBlock_passwd(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdBlock_passwd called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdBlock_passwd");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCpu_set(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "cmdCpu_set called" << std::endl;
	throw vmi::FunctionNotImplementedException("cmdCpu_set");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoHelp(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoHelp called" << std::endl;
	try{ this->parseCommandOutput("info help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoVersion(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoVersion called" << std::endl;
	try{ this->parseCommandOutput("info version", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoCommands(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoCommands called" << std::endl;
	try{ this->parseCommandOutput("info commands", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoNetwork(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoNetwork called" << std::endl;
	try{ this->parseCommandOutput("info network", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoChardev(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoChardev called" << std::endl;
	try{ this->parseCommandOutput("info chardev", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoBlock(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoBlock called" << std::endl;
	try{ this->parseCommandOutput("info block", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoBlockstats(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoBlockstats called" << std::endl;
	try{ this->parseCommandOutput("info blockstats", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoRegisters(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoRegisters called" << std::endl;
	try{ this->parseCommandOutput("info registers", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoCpus(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoCpus called" << std::endl;
	try{ this->parseCommandOutput("info cpus", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoHistory(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoHistory called" << std::endl;
	try{ this->parseCommandOutput("info history", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoIrq(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoIrq called" << std::endl;
	try{ this->parseCommandOutput("info irq", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoPic(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoPic called" << std::endl;
	try{ this->parseCommandOutput("info pic", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoPci(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoPci called" << std::endl;
	try{ this->parseCommandOutput("info pci", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoTlb(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoTlb called" << std::endl;
	try{ this->parseCommandOutput("info tlb", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoMem(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoMem called" << std::endl;
	try{ this->parseCommandOutput("info mem", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoHpet(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoHpet called" << std::endl;
	try{ this->parseCommandOutput("info hpet", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoJit(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoJit called" << std::endl;
	try{ this->parseCommandOutput("info jit", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoKvm(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoKvm called" << std::endl;
	try{ this->parseCommandOutput("info kvm", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoNuma(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoNuma called" << std::endl;
	try{ this->parseCommandOutput("info numa", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUsb(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoUsb called" << std::endl;
	try{ this->parseCommandOutput("info usb", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUsbhost(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoUsbhost called" << std::endl;
	try{ this->parseCommandOutput("info usbhost", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoProfile(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoProfile called" << std::endl;
	try{ this->parseCommandOutput("info profile", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoCapture(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoCapture called" << std::endl;
	try{ this->parseCommandOutput("info capture", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoSnapshots(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoSnapshots called" << std::endl;
	try{ this->parseCommandOutput("info snapshots", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoStatus(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoStatus called" << std::endl;
	try{ this->parseCommandOutput("info status", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoPcmcia(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoPcmcia called" << std::endl;
	try{ this->parseCommandOutput("info pcmcia", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoMice(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoMice called" << std::endl;
	try{ this->parseCommandOutput("info mice", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoVnc(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoVnc called" << std::endl;
	try{ this->parseCommandOutput("info vnc", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoName(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoName called" << std::endl;
	try{ this->parseCommandOutput("info name", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUuid(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoUuid called" << std::endl;
	try{ this->parseCommandOutput("info uuid", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUsernet(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoUsernet called" << std::endl;
	try{ this->parseCommandOutput("info usernet", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoMigrate(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoMigrate called" << std::endl;
	try{ this->parseCommandOutput("info migrate", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoBallon(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoBallon called" << std::endl;
	try{ this->parseCommandOutput("info ballon", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoQtree(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoQtree called" << std::endl;
	try{ this->parseCommandOutput("info qtree", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoQdm(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoQdm called" << std::endl;
	try{ this->parseCommandOutput("info qdm", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoRoms(std::string &helptext) throw(vmi::ModuleException){
	vmi::MutexLocker lock(&mutex);
	debug << "infoRoms called" << std::endl;
	try{ this->parseCommandOutput("info roms", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}
