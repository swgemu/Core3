/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ConfigManager.h"

ConfigManager::ConfigManager() {
	makeLogin = true;
	makeZone = true;
	makePing = true;
	makeStatus = true;
	makeWeb = true;

	orbNamingDirectoryAddress = "";

	dBHost = "127.0.0.1";
	dBPort = 3306;
	dBName = "swgemu";
	dBUser = "root";
	dBPass = "Gemeni1";
	dBSecret = "swgemusecret";

	mantisHost = "127.0.0.1";
	mantisPort = 3306;
	mantisName = "swgemu";
	mantisUser = "root";
	mantisPass = "Gemeni1";

	progressMonitors = true;

	statusPort = 44455;

	pingPort = 44462;

	webPorts = "44460";
	webErrorLog = "log/web_error.log";
	webAccessLog = "log/web_access.log";
	webSessionTimeout = 600;

	loginProcessingThreads = 1;
	loginRequiredVersion = "20050408-18:00";
	loginPort = 44453;
	loginAllowedConnections = 30;
	autoReg = true;

	zoneProcessingThreads = 10;
	zoneAllowedConnections = 300;
	zoneGalaxyID = 2;
	zoneOnlineCharactersPerAccount = 1;

	statusAllowedConnections = 100;
	statusInterval = 60;

	pingAllowedConnections = 3000;
	enabledZones.setNoDuplicateInsertPlan();

	purgeDeletedCharacters = 10; //Default is 10 minutes.
}

bool ConfigManager::loadConfigData() {
	loadMOTD();
	loadRevision();

	if (!loadConfigFile())
		return false;

	makeLogin = getGlobalByte("MakeLogin");
	makeZone = getGlobalByte("MakeZone");
	makePing = getGlobalByte("MakePing");
	makeStatus = getGlobalByte("MakeStatus");
	makeWeb = getGlobalByte("MakeWeb");

	orbNamingDirectoryAddress = getGlobalString("ORB");

	dBHost = getGlobalString("DBHost");
	dBPort = getGlobalShort("DBPort");
	dBName = getGlobalString("DBName");
	dBUser = getGlobalString("DBUser");
	dBPass = getGlobalString("DBPass");
	dBSecret = getGlobalString("DBSecret");

	mantisHost = getGlobalString("MantisHost");
	mantisPort = getGlobalShort("MantisPort");
	mantisName = getGlobalString("MantisName");
	mantisUser = getGlobalString("MantisUser");
	mantisPass = getGlobalString("MantisPass");
	mantisPrfx = getGlobalString("MantisPrfx");

	trePath = getGlobalString("TrePath");
	loadTreFileList();

	loadEnabledZones();

	statusPort = getGlobalShort("StatusPort");

	pingPort = getGlobalShort("PingPort");
	pingAllowedConnections = getGlobalInt("PingAllowedConnections");

	loginRequiredVersion = getGlobalString("LoginRequiredVersion");
	loginPort = getGlobalShort("LoginPort");
	loginProcessingThreads = getGlobalInt("LoginProcessingThreads");
	loginAllowedConnections =  getGlobalInt("LoginAllowedConnections");
	autoReg = getGlobalByte("AutoReg");

	zoneProcessingThreads = getGlobalInt("ZoneProcessingThreads");
	zoneAllowedConnections = getGlobalInt("ZoneAllowedConnections");
	zoneGalaxyID = getGlobalInt("ZoneGalaxyID");
	zoneOnlineCharactersPerAccount = getGlobalInt("ZoneOnlineCharactersPerAccount");

	statusAllowedConnections = getGlobalInt("StatusAllowedConnections");
	statusInterval = getGlobalInt("StatusInterval");

	webPorts = getGlobalString("WebPorts");
	webAccessLog = getGlobalString("WebAccessLog");
	webErrorLog = getGlobalString("WebErrorLog");
	webSessionTimeout = getGlobalInt("WebSessionTimeout");

	progressMonitors = getGlobalBoolean("ProgressMonitors");

	purgeDeletedCharacters = getGlobalInt("PurgeDeletedCharacters");

	return true;
}

void ConfigManager::loadTreFileList() {
	treFiles.removeAll();

	LuaObject files = getGlobalObject("TreFiles");

	for (int i = 1; i <= files.getTableSize(); ++i) {
		treFiles.add(files.getStringAt(i));
	}

	files.pop();
}

void ConfigManager::loadEnabledZones() {
	enabledZones.removeAll();

	LuaObject zones = getGlobalObject("ZonesEnabled");

	for (int i = 1; i <= zones.getTableSize(); ++i)
		enabledZones.put(zones.getStringAt(i));

	zones.pop();
}

void ConfigManager::loadMOTD() {
	messageOfTheDay = "";

	File* file;
	FileReader* reader;

	try {
		file = new File("conf/motd.txt");
		reader = new FileReader(file);

		String line;

		while(reader->readLine(line)) {
			messageOfTheDay += line;
		}

		reader->close();
	} catch (FileNotFoundException& e) {
		file = NULL;
		reader = NULL;
	}

	delete reader;
	delete file;
}

void ConfigManager::loadRevision() {
	File* file;
	FileReader* reader;

	revision = "";

	try {
		file = new File("conf/rev.txt");
		reader = new FileReader(file);

		String line;

		while (reader->readLine(line))
			revision += line;

		reader->close();
	} catch (FileNotFoundException& e) {
		file = NULL;
		reader = NULL;
	} catch (Exception& e) {
		file = NULL;
		reader = NULL;
	}

	//revision = revision.replaceAll("\n", "");

	delete reader;
	delete file;
}
