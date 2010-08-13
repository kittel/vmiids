/*
 * QemuMonitorSensorModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include "QemuMonitorSensorModule.h"

ADDMODULE(QemuMonitorSensorModule);

QemuMonitorSensorModule::QemuMonitorSensorModule() : SensorModule("QemuMonitorSensorModule"), ConsoleMonitor(){
	//Get NotificationModule
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

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

void QemuMonitorSensorModule::initSensorModule(){

}

bool QemuMonitorSensorModule::isRunning() throw(vmi::ModuleException){
	notify->debug(this, "isRunning called");
	std::string string;
	this->infoStatus(string);
	if(string.rfind("running") != std::string::npos) return true;
	else if(string.rfind("paused") != std::string::npos) return false;
	throw vmi::ModuleException();
}

void QemuMonitorSensorModule::pauseVM() throw(vmi::ModuleException){
	notify->debug(this, "pauseVM called");
	std::string string;
	this->cmdStop(string);
}

void QemuMonitorSensorModule::resumeVM() throw(vmi::ModuleException){
	notify->debug(this, "resumeVM called");
	std::string string;
	this->cmdCont(string);
}

void QemuMonitorSensorModule::cmdHelp(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHelp called");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCommit(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCommit called");
	throw vmi::FunctionNotImplementedException("cmdCommit");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdInfo(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdInfo called");
	try{ this->parseCommandOutput("info", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdQuit(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdQuit called");
	try{ this->parseCommandOutput("quit", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdEject(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdEject called");
	throw vmi::FunctionNotImplementedException("cmdEject");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdChange(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdChange called");
	throw vmi::FunctionNotImplementedException("cmdChange");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdScreendump(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdScreendump called");
	throw vmi::FunctionNotImplementedException("cmdScreendump");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdLogfile(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdLogfile called");
	throw vmi::FunctionNotImplementedException("cmdLogfile");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdLog(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdLog called");
	throw vmi::FunctionNotImplementedException("cmdLog");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSavevm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSavevm called");
	throw vmi::FunctionNotImplementedException("cmdSavevm");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdLoadvm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdLoadvm called");
	throw vmi::FunctionNotImplementedException("cmdLoadvm");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDelvm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDelvm called");
	throw vmi::FunctionNotImplementedException("cmdDelvm");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSinglestep(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSinglestep called");
	throw vmi::FunctionNotImplementedException("cmdSinglestep");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdStop(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdStop called");
	try{ this->parseCommandOutput("stop", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCont(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCont called");
	try{ this->parseCommandOutput("cont", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdGdbserver(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdGdbserver called");
	throw vmi::FunctionNotImplementedException("cmdGdbserver");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdX(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdX called");
	throw vmi::FunctionNotImplementedException("cmdX");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdXp(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdXp called");
	throw vmi::FunctionNotImplementedException("cmdXp");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPrint(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPrint called");
	throw vmi::FunctionNotImplementedException("cmdPrint");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdI(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdI called");
	throw vmi::FunctionNotImplementedException("cmdI");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdO(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdO called");
	throw vmi::FunctionNotImplementedException("cmdO");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSendkey(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSendkey called");
	throw vmi::FunctionNotImplementedException("cmdSendkey");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSystem_reset(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSystem_reset called");
	try{ this->parseCommandOutput("system_reset", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSystem_powerdown(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSystem_powerdown called");
	try{ this->parseCommandOutput("system_powerdown", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSum(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSum called");
	throw vmi::FunctionNotImplementedException("cmdSum");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdUsb_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdUsb_add called");
	throw vmi::FunctionNotImplementedException("cmdUsb_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdUsb_del(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdUsb_del called");
	throw vmi::FunctionNotImplementedException("cmdUsb_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDevice_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDevice_add called");
	throw vmi::FunctionNotImplementedException("cmdDevice_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDevice_del(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDevice_del called");
	throw vmi::FunctionNotImplementedException("cmdDevice_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCpu(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCpu called");
	throw vmi::FunctionNotImplementedException("cmdCpu");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMouse_move(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMouse_move called");
	throw vmi::FunctionNotImplementedException("cmdMouse_move");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMouse_button(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMouse_button called");
	throw vmi::FunctionNotImplementedException("cmdMouse_button");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMouse_set(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMouse_set called");
	throw vmi::FunctionNotImplementedException("cmdMouse_set");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdWavecapture(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdWavecapture called");
	throw vmi::FunctionNotImplementedException("cmdWavecapture");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdStopcapture(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdStopcapture called");
	throw vmi::FunctionNotImplementedException("cmdStopcapture");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMemsave(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMemsave called");
	throw vmi::FunctionNotImplementedException("cmdStopcapture");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPmemsave(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPmemsave called");
	throw vmi::FunctionNotImplementedException("cmdPmemsave");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdBoot_set(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdBoot_set called");
	throw vmi::FunctionNotImplementedException("cmdBoot_set");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdNmi(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdNmi called");
	throw vmi::FunctionNotImplementedException("cmdNmi");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate called");
	throw vmi::FunctionNotImplementedException("cmdMigrate");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate_cancel(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate_cancel called");
	throw vmi::FunctionNotImplementedException("cmdMigrate_cancel");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate_set_speed(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate_set_speed called");
	throw vmi::FunctionNotImplementedException("cmdMigrate_set_speed");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMigrate_set_downtime(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate_set_speed called");
	throw vmi::FunctionNotImplementedException("cmdMigrate_set_downtime");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdDrive_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDrive_add called");
	throw vmi::FunctionNotImplementedException("cmdDrive_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPci_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPci_add called");
	throw vmi::FunctionNotImplementedException("cmdPci_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdPci_del(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPci_del called");
	throw vmi::FunctionNotImplementedException("cmdPci_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHost_net_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHost_net_add called");
	throw vmi::FunctionNotImplementedException("cmdPci_del");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHost_net_remove(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHost_net_remove called");
	throw vmi::FunctionNotImplementedException("cmdHost_net_remove");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHostfwd_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHostfwd_add called");
	throw vmi::FunctionNotImplementedException("cmdHostfwd_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdHostfwd_remove(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHostfwd_remove called");
	throw vmi::FunctionNotImplementedException("cmdHostfwd_remove");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdBalloon(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdBalloon called");
	throw vmi::FunctionNotImplementedException("cmdBalloon");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdSet_link(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSet_link called");
	throw vmi::FunctionNotImplementedException("cmdSet_link");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdWatchdog_action(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdWatchdog_action called");
	throw vmi::FunctionNotImplementedException("cmdWatchdog_action");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_show(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_show called");
	throw vmi::FunctionNotImplementedException("cmdAcl_show");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_policy(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_policy called");
	throw vmi::FunctionNotImplementedException("cmdAcl_policy");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_add called");
	throw vmi::FunctionNotImplementedException("cmdAcl_add");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_remove(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_remove called");
	throw vmi::FunctionNotImplementedException("cmdAcl_remove");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdAcl_reset(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_reset called");
	throw vmi::FunctionNotImplementedException("cmdAcl_reset");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdMce(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMce called");
	throw vmi::FunctionNotImplementedException("cmdMce");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdGetfd(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdGetfd called");
	throw vmi::FunctionNotImplementedException("cmdGetfd");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdClosefd(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdClosefd called");
	throw vmi::FunctionNotImplementedException("cmdClosefd");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdBlock_passwd(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdBlock_passwd called");
	throw vmi::FunctionNotImplementedException("cmdBlock_passwd");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::cmdCpu_set(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCpu_set called");
	throw vmi::FunctionNotImplementedException("cmdCpu_set");
	try{ this->parseCommandOutput("help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoHelp(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoHelp called");
	try{ this->parseCommandOutput("info help", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoVersion(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoVersion called");
	try{ this->parseCommandOutput("info version", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoCommands(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoCommands called");
	try{ this->parseCommandOutput("info commands", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoNetwork(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoNetwork called");
	try{ this->parseCommandOutput("info network", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoChardev(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoChardev called");
	try{ this->parseCommandOutput("info chardev", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoBlock(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoBlock called");
	try{ this->parseCommandOutput("info block", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoBlockstats(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoBlockstats called");
	try{ this->parseCommandOutput("info blockstats", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoRegisters(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoRegisters called");
	try{ this->parseCommandOutput("info registers", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoCpus(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoCpus called");
	try{ this->parseCommandOutput("info cpus", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoHistory(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoHistory called");
	try{ this->parseCommandOutput("info history", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoIrq(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoIrq called");
	try{ this->parseCommandOutput("info irq", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoPic(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoPic called");
	try{ this->parseCommandOutput("info pic", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoPci(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoPci called");
	try{ this->parseCommandOutput("info pci", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoTlb(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoTlb called");
	try{ this->parseCommandOutput("info tlb", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoMem(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoMem called");
	try{ this->parseCommandOutput("info mem", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoHpet(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoHpet called");
	try{ this->parseCommandOutput("info hpet", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoJit(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoJit called");
	try{ this->parseCommandOutput("info jit", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoKvm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoKvm called");
	try{ this->parseCommandOutput("info kvm", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoNuma(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoNuma called");
	try{ this->parseCommandOutput("info numa", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUsb(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUsb called");
	try{ this->parseCommandOutput("info usb", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUsbhost(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUsbhost called");
	try{ this->parseCommandOutput("info usbhost", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoProfile(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoProfile called");
	try{ this->parseCommandOutput("info profile", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoCapture(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoCapture called");
	try{ this->parseCommandOutput("info capture", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoSnapshots(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoSnapshots called");
	try{ this->parseCommandOutput("info snapshots", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoStatus(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoStatus called");
	try{ this->parseCommandOutput("info status", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoPcmcia(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoPcmcia called");
	try{ this->parseCommandOutput("info pcmcia", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoMice(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoMice called");
	try{ this->parseCommandOutput("info mice", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoVnc(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoVnc called");
	try{ this->parseCommandOutput("info vnc", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoName(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoName called");
	try{ this->parseCommandOutput("info name", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUuid(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUuid called");
	try{ this->parseCommandOutput("info uuid", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoUsernet(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUsernet called");
	try{ this->parseCommandOutput("info usernet", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoMigrate(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoMigrate called");
	try{ this->parseCommandOutput("info migrate", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoBallon(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoBallon called");
	try{ this->parseCommandOutput("info ballon", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoQtree(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoQtree called");
	try{ this->parseCommandOutput("info qtree", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoQdm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoQdm called");
	try{ this->parseCommandOutput("info qdm", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}

void QemuMonitorSensorModule::infoRoms(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoRoms called");
	try{ this->parseCommandOutput("info roms", helptext); }
	catch(vmi::ConsoleMonitorException &e){throw vmi::ModuleException("QEmu Monitor Parse error");}
}
