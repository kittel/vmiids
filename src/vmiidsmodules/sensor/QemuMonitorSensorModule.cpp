/*
 * QemuMonitorSensorModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include "QemuMonitorSensorModule.h"

ADDDYNAMICSENSORMODULE(QemuMonitorSensorModule, __LINE__);

QemuMonitorSensorModule::QemuMonitorSensorModule() : SensorModule("QemuMonitorSensorModule"), ConsoleMonitor(){
	//Get NotificationModule
	notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	notify->debug(this, "Constructor called\n");

	std::string optionConsoleName;
	std::string optionMonitorShell;

	libconfig::Setting *setting = VmiIDS::getInstance()->getSetting(
			this->getName());

	if (setting == NULL || !setting->lookupValue("consoleName",
			optionConsoleName) || !setting->lookupValue("monitorShell",
			optionMonitorShell)) {
		notify->critical(this)
				<< "Could not parse Options. Please add the following section to the config file:"
				<< std::endl << this->getName() << " = {" << std::endl
				<< "\tconsoleName   =  \"<shell device>\";        e.g. \"/dev/ttyS1\""
				<< std::endl
				<< "\tmonitorShell  =  \"<shell identifier>\";    e.g. \"(qemu)\""
				<< std::endl
				<< "};";

		throw vmi::ModuleException();
	}

	this->initConsoleMonitor(optionConsoleName.c_str(),
			optionMonitorShell.c_str());
}

QemuMonitorSensorModule::~QemuMonitorSensorModule() {
	// TODO Auto-generated destructor stub
}

void QemuMonitorSensorModule::initSensorModule(){

}

bool QemuMonitorSensorModule::isRunning() throw(vmi::ModuleException){
	notify->debug(this, "isRunning called\n");
	std::string string;
	this->infoStatus(string);
	if(string.rfind("running") != std::string::npos) return true;
	else if(string.rfind("paused") != std::string::npos) return false;
	throw vmi::ModuleException();
}

void QemuMonitorSensorModule::pauseVM() throw(vmi::ModuleException){
	notify->debug(this, "pauseVM called\n");
	std::string string;
	this->cmdStop(string);
}

void QemuMonitorSensorModule::resumeVM() throw(vmi::ModuleException){
	notify->debug(this, "resumeVM called\n");
	std::string string;
	this->cmdCont(string);
}

void QemuMonitorSensorModule::cmdHelp(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHelp called");
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdCommit(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCommit called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdInfo(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdInfo called");
	this->parseCommandOutput("info", helptext);
}

void QemuMonitorSensorModule::cmdQuit(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdQuit called");
	this->parseCommandOutput("quit", helptext);
}

void QemuMonitorSensorModule::cmdEject(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdEject called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdChange(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdChange called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdScreendump(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdScreendump called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdLogfile(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdLogfile called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdLog(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdLog called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdSavevm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSavevm called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdLoadvm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdLoadvm called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdDelvm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDelvm called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdSinglestep(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSinglestep called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdStop(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdStop called");
	this->parseCommandOutput("stop", helptext);
}

void QemuMonitorSensorModule::cmdCont(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCont called");
	this->parseCommandOutput("cont", helptext);
}

void QemuMonitorSensorModule::cmdGdbserver(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdGdbserver called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdX(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdX called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdXp(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdXp called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdPrint(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPrint called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdI(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdI called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdO(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdO called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdSendkey(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSendkey called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdSystem_reset(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSystem_reset called");
	this->parseCommandOutput("system_reset", helptext);
}

void QemuMonitorSensorModule::cmdSystem_powerdown(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSystem_powerdown called");
	this->parseCommandOutput("system_powerdown", helptext);
}

void QemuMonitorSensorModule::cmdSum(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSum called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdUsb_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdUsb_add called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdUsb_del(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdUsb_del called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdDevice_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDevice_add called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdDevice_del(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDevice_del called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdCpu(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCpu called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMouse_move(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMouse_move called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMouse_button(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMouse_button called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMouse_set(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMouse_set called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdWavecapture(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdWavecapture called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdStopcapture(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdStopcapture called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMemsave(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMemsave called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdPmemsave(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPmemsave called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdBoot_set(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdBoot_set called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdNmi(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdNmi called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMigrate(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMigrate_cancel(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate_cancel called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMigrate_set_speed(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate_set_speed called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMigrate_set_downtime(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMigrate_set_speed called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdDrive_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdDrive_add called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdPci_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPci_add called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdPci_del(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdPci_del called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdHost_net_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHost_net_add called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdHost_net_remove(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHost_net_remove called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdHostfwd_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHostfwd_add called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdHostfwd_remove(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdHostfwd_remove called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdBalloon(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdBalloon called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdSet_link(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdSet_link called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdWatchdog_action(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdWatchdog_action called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdAcl_show(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_show called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdAcl_policy(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_policy called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdAcl_add(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_add called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdAcl_remove(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_remove called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdAcl_reset(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdAcl_reset called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdMce(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdMce called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdGetfd(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdGetfd called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdClosefd(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdClosefd called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdBlock_passwd(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdBlock_passwd called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::cmdCpu_set(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "cmdCpu_set called");
	throw vmi::FunctionNotImplementedException();
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorSensorModule::infoHelp(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoHelp called");
	this->parseCommandOutput("info help", helptext);
}

void QemuMonitorSensorModule::infoVersion(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoVersion called");
	this->parseCommandOutput("info version", helptext);
}

void QemuMonitorSensorModule::infoCommands(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoCommands called");
	this->parseCommandOutput("info commands", helptext);
}

void QemuMonitorSensorModule::infoNetwork(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoNetwork called");
	this->parseCommandOutput("info network", helptext);
}

void QemuMonitorSensorModule::infoChardev(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoChardev called");
	this->parseCommandOutput("info chardev", helptext);
}

void QemuMonitorSensorModule::infoBlock(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoBlock called");
	this->parseCommandOutput("info block", helptext);
}

void QemuMonitorSensorModule::infoBlockstats(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoBlockstats called");
	this->parseCommandOutput("info blockstats", helptext);
}

void QemuMonitorSensorModule::infoRegisters(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoRegisters called");
	this->parseCommandOutput("info registers", helptext);
}

void QemuMonitorSensorModule::infoCpus(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoCpus called");
	this->parseCommandOutput("info cpus", helptext);
}

void QemuMonitorSensorModule::infoHistory(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoHistory called");
	this->parseCommandOutput("info history", helptext);
}

void QemuMonitorSensorModule::infoIrq(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoIrq called");
	this->parseCommandOutput("info irq", helptext);
}

void QemuMonitorSensorModule::infoPic(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoPic called");
	this->parseCommandOutput("info pic", helptext);
}

void QemuMonitorSensorModule::infoPci(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoPci called");
	this->parseCommandOutput("info pci", helptext);
}

void QemuMonitorSensorModule::infoTlb(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoTlb called");
	this->parseCommandOutput("info tlb", helptext);
}

void QemuMonitorSensorModule::infoMem(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoMem called");
	this->parseCommandOutput("info mem", helptext);
}

void QemuMonitorSensorModule::infoHpet(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoHpet called");
	this->parseCommandOutput("info hpet", helptext);
}

void QemuMonitorSensorModule::infoJit(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoJit called");
	this->parseCommandOutput("info jit", helptext);
}

void QemuMonitorSensorModule::infoKvm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoKvm called");
	this->parseCommandOutput("info kvm", helptext);
}

void QemuMonitorSensorModule::infoNuma(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoNuma called");
	this->parseCommandOutput("info numa", helptext);
}

void QemuMonitorSensorModule::infoUsb(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUsb called");
	this->parseCommandOutput("info usb", helptext);
}

void QemuMonitorSensorModule::infoUsbhost(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUsbhost called");
	this->parseCommandOutput("info usbhost", helptext);
}

void QemuMonitorSensorModule::infoProfile(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoProfile called");
	this->parseCommandOutput("info profile", helptext);
}

void QemuMonitorSensorModule::infoCapture(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoCapture called");
	this->parseCommandOutput("info capture", helptext);
}

void QemuMonitorSensorModule::infoSnapshots(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoSnapshots called");
	this->parseCommandOutput("info snapshots", helptext);
}

void QemuMonitorSensorModule::infoStatus(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoStatus called");
	this->parseCommandOutput("info status", helptext);
}

void QemuMonitorSensorModule::infoPcmcia(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoPcmcia called");
	this->parseCommandOutput("info pcmcia", helptext);
}

void QemuMonitorSensorModule::infoMice(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoMice called");
	this->parseCommandOutput("info mice", helptext);
}

void QemuMonitorSensorModule::infoVnc(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoVnc called");
	this->parseCommandOutput("info vnc", helptext);
}

void QemuMonitorSensorModule::infoName(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoName called");
	this->parseCommandOutput("info name", helptext);
}

void QemuMonitorSensorModule::infoUuid(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUuid called");
	this->parseCommandOutput("info uuid", helptext);
}

void QemuMonitorSensorModule::infoUsernet(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoUsernet called");
	this->parseCommandOutput("info usernet", helptext);
}

void QemuMonitorSensorModule::infoMigrate(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoMigrate called");
	this->parseCommandOutput("info migrate", helptext);
}

void QemuMonitorSensorModule::infoBallon(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoBallon called");
	this->parseCommandOutput("info ballon", helptext);
}

void QemuMonitorSensorModule::infoQtree(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoQtree called");
	this->parseCommandOutput("info qtree", helptext);
}

void QemuMonitorSensorModule::infoQdm(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoQdm called");
	this->parseCommandOutput("info qdm", helptext);
}

void QemuMonitorSensorModule::infoRoms(std::string &helptext) throw(vmi::ModuleException){
	notify->debug(this, "infoRoms called");
	this->parseCommandOutput("info roms", helptext);
}
