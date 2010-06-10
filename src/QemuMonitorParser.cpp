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

void QemuMonitorParser::help(std::string &helptext) throw(QemuMonitorParserException){
	LIBVMI_DEBUG_MSG("help called");
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
