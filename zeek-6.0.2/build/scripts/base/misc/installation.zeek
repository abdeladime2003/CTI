##! This module collects properties of the Zeek installation.
##!
##! Directories are absolute and guaranteed to exist. Not all are necessarily in
##! operational use -- this depends on how you're running Zeek (as a standalone
##! process or clusterized, via zeekctl or the Management framework, etc).
##!
##! For details about Zeek's version, see the :zeek:see:`Version` module.
module Installation;

export {
	## Zeek installation root directory.
	const root_dir = "/usr/local/zeek";

	## The installation's configuration directory.
	const etc_dir = "/usr/local/zeek/etc";

	## The installation's log directory.
	const log_dir = "/usr/local/zeek/logs";

	## The installation's spool directory.
	const spool_dir = "/usr/local/zeek/spool";

	## The installation's variable-state directory.
	const state_dir = "/usr/local/zeek/var/lib";
}
