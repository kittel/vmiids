#include "MonitorParser.h"

#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#define VERBOSE "MonitorParser"
#endif /* DEBUG */
#include "Debug.h"


namespace libVMI {

#define MONITORDEVICE "/dev/ttyS1"
#define MONITORSHELL  "(qemu)"


MonitorParser::MonitorParser()  throw(MonitorParserException): ConsoleMonitor(MONITORDEVICE, MONITORSHELL){}

MonitorParser::~MonitorParser(){}

bool MonitorParser::isRunning() throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("isRunning called");
	std::string string;
	this->parseCommandOutput("info status", string);
	if(string.rfind("running") != std::string::npos) return true;
	else if(string.rfind("paused") != std::string::npos) return false;
	throw MonitorParserException();
}

void MonitorParser::pauseVM() throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("pauseVM called");
	std::string string;
	this->parseCommandOutput("stop", string);
}

void MonitorParser::resumeVM() throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("resumeVM called");
	std::string string;
	this->parseCommandOutput("c", string);
}

void MonitorParser::help(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("help called");
	this->parseCommandOutput("help", helptext);
}

void MonitorParser::infoHelp(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoHelp called");
	this->parseCommandOutput("info help", helptext);
}

void MonitorParser::infoVersion(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoVersion called");
	this->parseCommandOutput("info version", helptext);
}

void MonitorParser::infoCommands(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoCommands called");
	this->parseCommandOutput("info commands", helptext);
}

void MonitorParser::infoNetwork(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoNetwork called");
	this->parseCommandOutput("info network", helptext);
}

void MonitorParser::infoChardev(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoChardev called");
	this->parseCommandOutput("info chardev", helptext);
}

void MonitorParser::infoBlock(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoBlock called");
	this->parseCommandOutput("info block", helptext);
}

void MonitorParser::infoBlockstats(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoBlockstats called");
	this->parseCommandOutput("info blockstats", helptext);
}

void MonitorParser::infoRegisters(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoRegisters called");
	this->parseCommandOutput("info registers", helptext);
}

void MonitorParser::infoCpus(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoCpus called");
	this->parseCommandOutput("info cpus", helptext);
}

void MonitorParser::infoHistory(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoHistory called");
	this->parseCommandOutput("info history", helptext);
}

void MonitorParser::infoIrq(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoIrq called");
	this->parseCommandOutput("info irq", helptext);
}

void MonitorParser::infoPic(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoPic called");
	this->parseCommandOutput("info pic", helptext);
}

void MonitorParser::infoPci(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoPci called");
	this->parseCommandOutput("info pci", helptext);
}

void MonitorParser::infoTlb(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoTlb called");
	this->parseCommandOutput("info tlb", helptext);
}

void MonitorParser::infoMem(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoMem called");
	this->parseCommandOutput("info mem", helptext);
}

void MonitorParser::infoHpet(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoHpet called");
	this->parseCommandOutput("info hpet", helptext);
}

void MonitorParser::infoJit(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoJit called");
	this->parseCommandOutput("info jit", helptext);
}

void MonitorParser::infoKvm(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoKvm called");
	this->parseCommandOutput("info kvm", helptext);
}

void MonitorParser::infoNuma(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoNuma called");
	this->parseCommandOutput("info numa", helptext);
}

void MonitorParser::infoUsb(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoUsb called");
	this->parseCommandOutput("info usb", helptext);
}

void MonitorParser::infoUsbhost(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoUsbhost called");
	this->parseCommandOutput("info usbhost", helptext);
}

void MonitorParser::infoProfile(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoProfile called");
	this->parseCommandOutput("info profile", helptext);
}

void MonitorParser::infoCapture(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoCapture called");
	this->parseCommandOutput("info capture", helptext);
}

void MonitorParser::infoSnapshots(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoSnapshots called");
	this->parseCommandOutput("info snapshots", helptext);
}

void MonitorParser::infoStatus(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoStatus called");
	this->parseCommandOutput("info status", helptext);
}

void MonitorParser::infoPcmcia(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoPcmcia called");
	this->parseCommandOutput("info pcmcia", helptext);
}

void MonitorParser::infoMice(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoMice called");
	this->parseCommandOutput("info mice", helptext);
}

void MonitorParser::infoVnc(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoVnc called");
	this->parseCommandOutput("info vnc", helptext);
}

void MonitorParser::infoName(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoName called");
	this->parseCommandOutput("info name", helptext);
}

void MonitorParser::infoUuid(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoUuid called");
	this->parseCommandOutput("info uuid", helptext);
}

void MonitorParser::infoUsernet(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoUsernet called");
	this->parseCommandOutput("info usernet", helptext);
}

void MonitorParser::infoMigrate(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoMigrate called");
	this->parseCommandOutput("info migrate", helptext);
}

void MonitorParser::infoBallon(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoBallon called");
	this->parseCommandOutput("info ballon", helptext);
}

void MonitorParser::infoQtree(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoQtree called");
	this->parseCommandOutput("info qtree", helptext);
}

void MonitorParser::infoQdm(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoQdm called");
	this->parseCommandOutput("info qdm", helptext);
}

void MonitorParser::infoRoms(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoRoms called");
	this->parseCommandOutput("info roms", helptext);
}

}
