#include "QemuMonitorParser.h"

#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#define VERBOSE "QemuMonitorParser"
#endif /* DEBUG */
#include "Debug.h"


namespace libVMI {

#define MONITORDEVICE "/dev/ttyS1"
#define MONITORSHELL  "(qemu)"


QemuMonitorParser::QemuMonitorParser()  throw(QemuMonitorParserException): ConsoleMonitor(MONITORDEVICE, MONITORSHELL){}

QemuMonitorParser::~QemuMonitorParser(){}

bool QemuMonitorParser::isRunning() throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("isRunning called");
	std::string string;
	this->parseCommandOutput("info status", string);
	if(string.rfind("running") != std::string::npos) return true;
	else if(string.rfind("paused") != std::string::npos) return false;
	throw QemuMonitorParserException();
}

void QemuMonitorParser::pauseVM() throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("pauseVM called");
	std::string string;
	this->parseCommandOutput("stop", string);
}

void QemuMonitorParser::resumeVM() throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("resumeVM called");
	std::string string;
	this->parseCommandOutput("c", string);
}

void QemuMonitorParser::cmdHelp(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdHelp called");
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdCommit(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdCommit called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdInfo(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdInfo called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdQuit(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdQuit called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdEject(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdEject called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdChange(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdChange called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdScreendump(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdScreendump called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdLogfile(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdLogfile called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdLog(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdLog called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdSavevm(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdSavevm called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdLoadvm(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdLoadvm called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdDelvm(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdDelvm called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdSinglestep(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdSinglestep called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdStop(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdStop called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdCont(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdCont called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdGdbserver(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdGdbserver called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdX(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdX called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdXp(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdXp called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdPrint(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdPrint called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdI(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdI called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdO(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdO called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdSendkey(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdSendkey called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdSystem_reset(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdSystem_reset called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdSystem_powerdown(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdSystem_powerdown called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdSum(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdSum called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdUsb_add(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdUsb_add called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdUsb_del(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdUsb_del called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdDevice_add(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdDevice_add called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdDevice_del(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdDevice_del called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdCpu(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdCpu called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMouse_move(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMouse_move called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMouse_button(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMouse_button called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMouse_set(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMouse_set called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdWavecapture(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdWavecapture called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdStopcapture(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdStopcapture called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMemsave(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMemsave called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdPmemsave(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdPmemsave called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdBoot_set(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdBoot_set called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdNmi(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdNmi called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMigrate(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMigrate called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMigrate_cancel(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMigrate_cancel called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMigrate_set_speed(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMigrate_set_speed called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMigrate_set_downtime(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMigrate_set_speed called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdDrive_add(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdDrive_add called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdPci_add(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdPci_add called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdPci_del(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdPci_del called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdHost_net_add(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdHost_net_add called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdHost_net_remove(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdHost_net_remove called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdHostfwd_add(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdHostfwd_add called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdHostfwd_remove(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdHostfwd_remove called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdBalloon(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdBalloon called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdSet_link(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdSet_link called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdWatchdog_action(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdWatchdog_action called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdAcl_show(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdAcl_show called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdAcl_policy(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdAcl_policy called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdAcl_add(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdAcl_add called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdAcl_remove(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdAcl_remove called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdAcl_reset(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdAcl_reset called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdMce(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdMce called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdGetfd(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdGetfd called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdClosefd(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdClosefd called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdBlock_passwd(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdBlock_passwd called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::cmdCpu_set(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("cmdCpu_set called");
	throw QemuMonitorParserException;
	this->parseCommandOutput("help", helptext);
}

void QemuMonitorParser::infoHelp(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoHelp called");
	this->parseCommandOutput("info help", helptext);
}

void QemuMonitorParser::infoVersion(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoVersion called");
	this->parseCommandOutput("info version", helptext);
}

void QemuMonitorParser::infoCommands(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoCommands called");
	this->parseCommandOutput("info commands", helptext);
}

void QemuMonitorParser::infoNetwork(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoNetwork called");
	this->parseCommandOutput("info network", helptext);
}

void QemuMonitorParser::infoChardev(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoChardev called");
	this->parseCommandOutput("info chardev", helptext);
}

void QemuMonitorParser::infoBlock(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoBlock called");
	this->parseCommandOutput("info block", helptext);
}

void QemuMonitorParser::infoBlockstats(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoBlockstats called");
	this->parseCommandOutput("info blockstats", helptext);
}

void QemuMonitorParser::infoRegisters(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoRegisters called");
	this->parseCommandOutput("info registers", helptext);
}

void QemuMonitorParser::infoCpus(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoCpus called");
	this->parseCommandOutput("info cpus", helptext);
}

void QemuMonitorParser::infoHistory(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoHistory called");
	this->parseCommandOutput("info history", helptext);
}

void QemuMonitorParser::infoIrq(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoIrq called");
	this->parseCommandOutput("info irq", helptext);
}

void QemuMonitorParser::infoPic(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoPic called");
	this->parseCommandOutput("info pic", helptext);
}

void QemuMonitorParser::infoPci(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoPci called");
	this->parseCommandOutput("info pci", helptext);
}

void QemuMonitorParser::infoTlb(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoTlb called");
	this->parseCommandOutput("info tlb", helptext);
}

void QemuMonitorParser::infoMem(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoMem called");
	this->parseCommandOutput("info mem", helptext);
}

void QemuMonitorParser::infoHpet(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoHpet called");
	this->parseCommandOutput("info hpet", helptext);
}

void QemuMonitorParser::infoJit(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoJit called");
	this->parseCommandOutput("info jit", helptext);
}

void QemuMonitorParser::infoKvm(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoKvm called");
	this->parseCommandOutput("info kvm", helptext);
}

void QemuMonitorParser::infoNuma(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoNuma called");
	this->parseCommandOutput("info numa", helptext);
}

void QemuMonitorParser::infoUsb(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoUsb called");
	this->parseCommandOutput("info usb", helptext);
}

void QemuMonitorParser::infoUsbhost(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoUsbhost called");
	this->parseCommandOutput("info usbhost", helptext);
}

void QemuMonitorParser::infoProfile(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoProfile called");
	this->parseCommandOutput("info profile", helptext);
}

void QemuMonitorParser::infoCapture(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoCapture called");
	this->parseCommandOutput("info capture", helptext);
}

void QemuMonitorParser::infoSnapshots(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoSnapshots called");
	this->parseCommandOutput("info snapshots", helptext);
}

void QemuMonitorParser::infoStatus(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoStatus called");
	this->parseCommandOutput("info status", helptext);
}

void QemuMonitorParser::infoPcmcia(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoPcmcia called");
	this->parseCommandOutput("info pcmcia", helptext);
}

void QemuMonitorParser::infoMice(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoMice called");
	this->parseCommandOutput("info mice", helptext);
}

void QemuMonitorParser::infoVnc(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoVnc called");
	this->parseCommandOutput("info vnc", helptext);
}

void QemuMonitorParser::infoName(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoName called");
	this->parseCommandOutput("info name", helptext);
}

void QemuMonitorParser::infoUuid(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoUuid called");
	this->parseCommandOutput("info uuid", helptext);
}

void QemuMonitorParser::infoUsernet(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoUsernet called");
	this->parseCommandOutput("info usernet", helptext);
}

void QemuMonitorParser::infoMigrate(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoMigrate called");
	this->parseCommandOutput("info migrate", helptext);
}

void QemuMonitorParser::infoBallon(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoBallon called");
	this->parseCommandOutput("info ballon", helptext);
}

void QemuMonitorParser::infoQtree(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoQtree called");
	this->parseCommandOutput("info qtree", helptext);
}

void QemuMonitorParser::infoQdm(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoQdm called");
	this->parseCommandOutput("info qdm", helptext);
}

void QemuMonitorParser::infoRoms(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("infoRoms called");
	this->parseCommandOutput("info roms", helptext);
}

}
