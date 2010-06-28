#ifndef _QEMUMONITORPARSER_H_
#define _QEMUMONITORPARSER_H_

#include "ConsoleMonitor.h"

namespace libVMI {

/*!
 * \exception QemuMonitorParserException QemuMonitorParser.h
 * \brief Exception for QemuMonitorParser.
 */
class QemuMonitorParserException: public std::exception {
	virtual const char* what() const throw () {
		return "QemuMonitorParser abort";
	}
};

/*!
 * \exception QemuMonitorParserNotImplementedException QemuMonitorParser.h
 * \brief Exception for QemuMonitorParser.
 */
class QemuMonitorParserNotImplementedException: public QemuMonitorParserException {
	virtual const char* what() const throw () {
		return "Function not implemented";
	}
};

/*!
 * \class QemuMonitorParser QemuMonitorParser.h
 *
 * \brief Parser for the QEmu Monitor Console.
 *
 * The normal way to communicate with the QEmu Hypervisor is
 * the QEmu Monitor Console. \sa http://wiki.qemu.org/download/qemu-doc.html#pcsys_005fmonitor<p>
 *
 * At the time of implementation the following commands were available:
 *
 *
 * <pre>
 help|? [cmd] 					-- show the help
commit device|all 				-- commit changes to the disk images (if -snapshot is used) or backing files
info [subcommand] 				-- show various information about the system state
q|quit  					-- quit the emulator
eject [-f] device 				-- eject a removable medium (use -f to force it)
change device filename [format]		 	-- change a removable medium, optional format
screendump filename 				-- save screen into PPM image 'filename'
logfile filename 				-- output logs to 'filename'
log item1[,...] 				-- activate logging of the specified items to '/tmp/qemu.log'
savevm [tag|id] 				-- save a VM snapshot. If no tag or id are provided, a new snapshot is created
loadvm tag|id 					-- restore a VM snapshot from its tag or id
delvm tag|id 					-- delete a VM snapshot from its tag or id
singlestep [on|off] 				-- run emulation in singlestep mode or switch to normal mode
stop  						-- stop emulation
c|cont  					-- resume emulation
gdbserver [device] 				-- start gdbserver on given device (default 'tcp::1234'), stop with 'none'
x /fmt addr 					-- virtual memory dump starting at 'addr'
xp /fmt addr 					-- physical memory dump starting at 'addr'
p|print /fmt expr 				-- print expression value (use $reg for CPU register access)
i /fmt addr 					-- I/O port read
o /fmt addr value 				-- I/O port write
sendkey keys [hold_ms] 				-- send keys to the VM (e.g. 'sendkey ctrl-alt-f1', default hold time=100 ms)
system_reset  					-- reset the system
system_powerdown  				-- send system power down event
sum addr size 					-- compute the checksum of a memory region
usb_add device 					-- add USB device (e.g. 'host:bus.addr' or 'host:vendor_id:product_id')
usb_del device 					-- remove USB device 'bus.addr'
device_add device 				-- add device, like -device on the command line
device_del device 				-- remove device
cpu index 					-- set the default CPU
mouse_move dx dy [dz] 				-- send mouse move events
mouse_button state 				-- change mouse button state (1=L, 2=M, 4=R)
mouse_set index 				-- set which mouse device receives events
wavcapture path [frequency [bits [channels]]] 	-- capture audio to a wave file (default frequency=44100 bits=16 channels=2)
stopcapture capture index 			-- stop capture
memsave addr size file 				-- save to disk virtual memory dump starting at 'addr' of size 'size'
pmemsave addr size file 			-- save to disk physical memory dump starting at 'addr' of size 'size'
boot_set bootdevice 				-- define new values for the boot device list
nmi cpu 					-- inject an NMI on the given CPU
migrate [-d] [-b] [-i] uri 			-- migrate to URI (using -d to not wait for completion)
			 -b for migration without shared storage with full copy of disk
			 -i for migration without shared storage with incremental copy of disk (base image shared between src and destination)
migrate_cancel  				-- cancel the current VM migration
migrate_set_speed value 			-- set maximum speed (in bytes) for migrations
migrate_set_downtime value 			-- set maximum tolerated downtime (in seconds) for migrations
drive_add [[<domain>:]<bus>:]<slot>
	[file=file][,if=type][,bus=n]
	[,unit=m][,media=d][index=i]
	[,cyls=c,heads=h,secs=s[,trans=t]]
	[snapshot=on|off][,cache=on|off] 	-- add drive to PCI storage controller
pci_add auto|[[<domain>:]<bus>:]
	<slot> nic|storage|host
	[[vlan=n][,macaddr=addr][,model=type]]
	 [file=file][,if=type][,bus=nr]...
	[host=02:00.0[,name=string][,dma=none] 	-- hot-add PCI device
pci_del [[<domain>:]<bus>:]<slot> 		-- hot remove PCI device
host_net_add tap|user|socket|vde|dump [options] -- add host VLAN client
host_net_remove vlan_id name 			-- remove host VLAN client
hostfwd_add [vlan_id name]
	[tcp|udp]:[hostaddr]:hostport-
	[guestaddr]:guestport 			-- redirect TCP or UDP connections from host to guest (requires -net user)
hostfwd_remove [vlan_id name]
	[tcp|udp]:[hostaddr]:hostport 		-- remove host-to-guest TCP or UDP redirection
balloon target 					-- request VM to change it's memory allocation (in MB)
set_link name up|down 				-- change the link status of a network adapter
watchdog_action
[reset|shutdown|poweroff|pause|debug|none] 	-- change watchdog action
acl_show aclname 				-- list rules in the access control list
acl_policy aclname allow|deny 			-- set default access control list policy
acl_add aclname match allow|deny [index] 	-- add a match rule to the access control list
acl_remove aclname match 			-- remove a match rule from the access control list
acl_reset aclname 				-- reset the access control list
mce cpu bank status mcgstatus addr misc 	-- inject a MCE on the given CPU
getfd getfd name 				-- receive a file descriptor via SCM rights and assign it a name
closefd closefd name 				-- close a file descriptor previously passed via SCM rights
block_passwd block_passwd device password 	-- set the password of encrypted block devices
cpu_set cpu [online|offline] 			-- change cpu state
</pre>

Furthermore the following info commands were available:<br>
<pre>
info version           -- show the version of QEMU
info commands          -- list QMP available commands
info network           -- show the network state
info chardev           -- show the character devices
info block             -- show the block devices
info blockstats        -- show block device statistics
info registers         -- show the cpu registers
info cpus              -- show infos for each CPU
info history           -- show the command line history
info irq               -- show the interrupts statistics (if available)
info pic               -- show i8259 (PIC) state
info pci               -- show PCI info
info tlb               -- show virtual to physical memory mappings
info mem               -- show the active virtual memory mappings
info hpet              -- show state of HPET
info jit               -- show dynamic compiler info
info kvm               -- show KVM information
info numa              -- show NUMA information
info usb               -- show guest USB devices
info usbhost           -- show host USB devices
info profile           -- show profiling information
info capture           -- show capture information
info snapshots         -- show the currently saved VM snapshots
info status            -- show the current VM status (running|paused)
info pcmcia            -- show guest PCMCIA status
info mice              -- show which guest mouse is receiving events
info vnc               -- show the vnc server status
info name              -- show the current VM name
info uuid              -- show the current VM UUID
info usernet           -- show user network stack connection states
info migrate           -- show migration status
info balloon           -- show balloon information
info qtree             -- show device tree
info qdm               -- show qdev device model list
info roms              -- show roms
</pre>

 */
class QemuMonitorParser : public ConsoleMonitor {
	public:
	QemuMonitorParser(const char* consoleString,
			const char* shellString) throw(QemuMonitorParserException);
		virtual ~QemuMonitorParser();

		/**
		 * \brief show the help.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void cmdHelp(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief commit changes to the disk images (if -snapshot is used) or backing files.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * commit device|all 				-- commit changes to the disk images (if -snapshot is used) or backing files
		 */
		void cmdCommit(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show various information about the system state.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * info [subcommand] 				-- show various information about the system state
		 */
		void cmdInfo(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief quit the emulator.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * q|quit  					-- quit the emulator
		 */
		void cmdQuit(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief eject a removable medium (use -f to force it).
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * eject [-f] device 				-- eject a removable medium (use -f to force it)
		 */
		void cmdEject(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief change a removable medium, optional format.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * change device filename [format]		 	-- change a removable medium, optional format
		 */
		void cmdChange(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief save screen into PPM image 'filename'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * screendump filename 				-- save screen into PPM image 'filename'
		 */
		void cmdScreendump(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief output logs to 'filename'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * logfile filename 				-- output logs to 'filename'
		 */
		void cmdLogfile(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief activate logging of the specified items to '/tmp/qemu.log'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * log item1[,...] 				-- activate logging of the specified items to '/tmp/qemu.log'
		 */
		void cmdLog(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief save a VM snapshot. If no tag or id are provided, a new snapshot is created.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * savevm [tag|id] 				-- save a VM snapshot. If no tag or id are provided, a new snapshot is created
		 */
		void cmdSavevm(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief restore a VM snapshot from its tag or id.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * loadvm tag|id 					-- restore a VM snapshot from its tag or id
		 */
		void cmdLoadvm(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief delete a VM snapshot from its tag or id.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * delvm tag|id 					-- delete a VM snapshot from its tag or id
		 */
		void cmdDelvm(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief run emulation in singlestep mode or switch to normal mode.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * singlestep [on|off] 				-- run emulation in singlestep mode or switch to normal mode
		 */
		void cmdSinglestep(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief stop emulation.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * stop  						-- stop emulation
		 */
		void cmdStop(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief resume emulation.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * c|cont  					-- resume emulation
		 */
		void cmdCont(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief start gdbserver on given device (default 'tcp::1234'), stop with 'none'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * gdbserver [device] 				-- start gdbserver on given device (default 'tcp::1234'), stop with 'none'
		 */
		void cmdGdbserver(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief virtual memory dump starting at 'addr'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * x /fmt addr 					-- virtual memory dump starting at 'addr'
		 */
		void cmdX(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief physical memory dump starting at 'addr'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * xp /fmt addr 					-- physical memory dump starting at 'addr'
		 */
		void cmdXp(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief print expression value (use $reg for CPU register access).
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * p|print /fmt expr 				-- print expression value (use $reg for CPU register access)
		 */
		void cmdPrint(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief I/O port read.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * i /fmt addr 					-- I/O port read
		 */
		void cmdI(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief I/O port write.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * o /fmt addr value 				-- I/O port write
		 */
		void cmdO(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief send keys to the VM (e.g. 'sendkey ctrl-alt-f1', default hold time=100 ms).
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * sendkey keys [hold_ms] 				-- send keys to the VM (e.g. 'sendkey ctrl-alt-f1', default hold time=100 ms)
		 */
		void cmdSendkey(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief reset the system.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * system_reset  					-- reset the system
		 */
		void cmdSystem_reset(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief send system power down event.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * system_powerdown  				-- send system power down event
		 */
		void cmdSystem_powerdown(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief compute the checksum of a memory region.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * sum addr size 					-- compute the checksum of a memory region
		 */
		void cmdSum(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief add USB device (e.g. 'host:bus.addr' or 'host:vendor_id:product_id').
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * usb_add device 					-- add USB device (e.g. 'host:bus.addr' or 'host:vendor_id:product_id')
		 */
		void cmdUsb_add(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief remove USB device 'bus.addr'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * usb_del device 					-- remove USB device 'bus.addr'
		 */
		void cmdUsb_del(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief add device, like -device on the command line.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * device_add device 				-- add device, like -device on the command line
		 */
		void cmdDevice_add(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief remove device.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * device_del device 				-- remove device
		 */
		void cmdDevice_del(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief set the default CPU.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * cpu index 					-- set the default CPU
		 */
		void cmdCpu(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief send mouse move events.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * mouse_move dx dy [dz] 				-- send mouse move events
		 */
		void cmdMouse_move(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief change mouse button state (1=L, 2=M, 4=R).
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * mouse_button state 				-- change mouse button state (1=L, 2=M, 4=R)
		 */
		void cmdMouse_button(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief set which mouse device receives events.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * mouse_set index 				-- set which mouse device receives events
		 */
		void cmdMouse_set(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief capture audio to a wave file (default frequency=44100 bits=16 channels=2).
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * wavcapture path [frequency [bits [channels]]] 	-- capture audio to a wave file (default frequency=44100 bits=16 channels=2)
		 */
		void cmdWavecapture(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief stop capture.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * stopcapture capture index 			-- stop capture
		 */
		void cmdStopcapture(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief save to disk virtual memory dump starting at 'addr' of size 'size'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * memsave addr size file 				-- save to disk virtual memory dump starting at 'addr' of size 'size'
		 */
		void cmdMemsave(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief save to disk physical memory dump starting at 'addr' of size 'size'.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * pmemsave addr size file 			-- save to disk physical memory dump starting at 'addr' of size 'size'
		 */
		void cmdPmemsave(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief define new values for the boot device list.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * boot_set bootdevice 				-- define new values for the boot device list
		 */
		void cmdBoot_set(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief inject an NMI on the given CPU.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * nmi cpu 					-- inject an NMI on the given CPU
		 */
		void cmdNmi(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief migrate to URI (using -d to not wait for completion)
		 * @param helptext String Buffer in which the result will be returned in.
		 * migrate to URI (using -d to not wait for completion)
		 * 	 -b for migration without shared storage with full copy of disk
		 *	 -i for migration without shared storage with incremental copy of disk (base image shared between src and destination)
		 *
		 * migrate [-d] [-b] [-i] uri 			-- migrate to URI (using -d to not wait for completion)
		 * 			 -b for migration without shared storage with full copy of disk
		 * 			 -i for migration without shared storage with incremental copy of disk (base image shared between src and destination)
		 */
		void cmdMigrate(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief cancel the current VM migration.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * migrate_cancel  				-- cancel the current VM migration
		 */
		void cmdMigrate_cancel(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief set maximum speed (in bytes) for migrations.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * migrate_set_speed value 			-- set maximum speed (in bytes) for migrations
		 */
		void cmdMigrate_set_speed(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief set maximum tolerated downtime (in seconds) for migrations.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * migrate_set_downtime value 			-- set maximum tolerated downtime (in seconds) for migrations
		 */
		void cmdMigrate_set_downtime(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief add drive to PCI storage controller.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * drive_add [[<domain>:]<bus>:]<slot>
		 * 	[file=file][,if=type][,bus=n]
		 * 	[,unit=m][,media=d][index=i]
		 * 	[,cyls=c,heads=h,secs=s[,trans=t]]
		 * 	[snapshot=on|off][,cache=on|off] 	-- add drive to PCI storage controller
		 */
		void cmdDrive_add(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief hot-add PCI device.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * pci_add auto|[[<domain>:]<bus>:]
		 * 	<slot> nic|storage|host
		 * 	[[vlan=n][,macaddr=addr][,model=type]]
		 * 	 [file=file][,if=type][,bus=nr]...
		 * 	[host=02:00.0[,name=string][,dma=none] 	-- hot-add PCI device
		 */
		void cmdPci_add(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief hot remove PCI device.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * pci_del [[<domain>:]<bus>:]<slot> 		-- hot remove PCI device
		 */
		void cmdPci_del(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief add host VLAN client.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * host_net_add tap|user|socket|vde|dump [options] -- add host VLAN client
		 */
		void cmdHost_net_add(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief remove host VLAN client.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * host_net_remove vlan_id name 			-- remove host VLAN client
		 */
		void cmdHost_net_remove(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief redirect TCP or UDP connections from host to guest (requires -net user).
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * hostfwd_add [vlan_id name]
		 * 	[tcp|udp]:[hostaddr]:hostport-
		 * 	[guestaddr]:guestport 			-- redirect TCP or UDP connections from host to guest (requires -net user)
		 */
		void cmdHostfwd_add(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief remove host-to-guest TCP or UDP redirection.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * hostfwd_remove [vlan_id name]
		 * 	[tcp|udp]:[hostaddr]:hostport 		-- remove host-to-guest TCP or UDP redirection
		 */
		void cmdHostfwd_remove(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief request VM to change it's memory allocation (in MB).
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * balloon target 					-- request VM to change it's memory allocation (in MB)
		 */
		void cmdBalloon(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief change the link status of a network adapter.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * set_link name up|down 				-- change the link status of a network adapter
		 */
		void cmdSet_link(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief change watchdog action.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * watchdog_action
		 * [reset|shutdown|poweroff|pause|debug|none] 	-- change watchdog action
		 */
		void cmdWatchdog_action(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief list rules in the access control list.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * acl_show aclname 				-- list rules in the access control list
		 */
		void cmdAcl_show(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief set default access control list policy.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * acl_policy aclname allow|deny 			-- set default access control list policy
		 */
		void cmdAcl_policy(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief add a match rule to the access control list.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * acl_add aclname match allow|deny [index] 	-- add a match rule to the access control list
		 */
		void cmdAcl_add(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief remove a match rule from the access control list.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * acl_remove aclname match 			-- remove a match rule from the access control list
		 */
		void cmdAcl_remove(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief reset the access control list.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * acl_reset aclname 				-- reset the access control list
		 */
		void cmdAcl_reset(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief inject a MCE on the given CPU.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * mce cpu bank status mcgstatus addr misc 	-- inject a MCE on the given CPU
		 */
		void cmdMce(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief receive a file descriptor via SCM rights and assign it a name.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * getfd getfd name 				-- receive a file descriptor via SCM rights and assign it a name
		 */
		void cmdGetfd(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief close a file descriptor previously passed via SCM rights.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * closefd closefd name 				-- close a file descriptor previously passed via SCM rights
		 */
		void cmdClosefd(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief set the password of encrypted block devices.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * block_passwd block_passwd device password 	-- set the password of encrypted block devices
		 */
		void cmdBlock_passwd(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief change cpu state.
		 * @param helptext String Buffer in which the result will be returned in.
		 *
		 * cpu_set cpu [online|offline] 			-- change cpu state
		 */
		void cmdCpu_set(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the help of the info command.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoHelp(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the version of QEMU.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoVersion(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief list QMP available commands.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoCommands(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the network state.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoNetwork(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the character devices.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoChardev(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the block devices.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoBlock(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show block device statistics.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoBlockstats(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the cpu registers.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoRegisters(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show infos for each CPU.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoCpus(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the command line history.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoHistory(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the interrupts statistics (if available).
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoIrq(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show i8259 (PIC) state.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoPic(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show PCI info.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoPci(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show virtual to physical memory mappings.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoTlb(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the active virtual memory mappings.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoMem(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show state of HPET.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoHpet(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show dynamic compiler info.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoJit(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show KVM information.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoKvm(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show NUMA information.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoNuma(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show guest USB devices.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoUsb(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show host USB devices.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoUsbhost(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show profiling information.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoProfile(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show capture information.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoCapture(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the currently saved VM snapshots.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoSnapshots(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the current VM status (running|paused).
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoStatus(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show guest PCMCIA status.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoPcmcia(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show which guest mouse is receiving events.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoMice(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the vnc server status.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoVnc(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the current VM name.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoName(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show the current VM UUID.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoUuid(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show user network stack connection states.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoUsernet(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show migration status.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoMigrate(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show balloon information.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoBallon(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show device tree.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoQtree(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show qdev device model list.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoQdm(std::string &helptext) throw(QemuMonitorParserException);

		/**
		 * \brief show roms.
		 * @param helptext String Buffer in which the result will be returned in.
		 */
		void infoRoms(std::string &helptext) throw(QemuMonitorParserException);

};

}
#endif /* _QEMUMONITORPARSER_H_ */
