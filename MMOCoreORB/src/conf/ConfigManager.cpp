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
	dumpObjFiles = true;
	unloadContainers = true;
	useMetrics = true;
	pvpMode = false;

	orbNamingDirectoryAddress = "";
	orbNamingDirectoryPort = 44419;

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

	metricsHost = "127.0.0.1";
	metricsPort = 8125;

	loginProcessingThreads = 1;
	loginRequiredVersion = "20050408-18:00";
	loginPort = 44453;
	loginAllowedConnections = 30;
	autoReg = true;

	zoneProcessingThreads = 10;
	zoneAllowedConnections = 300;
	zoneGalaxyID = 2;
	zoneOnlineCharactersPerAccount = 1;
	zonePort = 0;

	statusAllowedConnections = 100;
	statusInterval = 60;

	pingAllowedConnections = 3000;
	enabledZones.setNoDuplicateInsertPlan();

	purgeDeletedCharacters = 10; //Default is 10 minutes.

	maxNavMeshJobs = 6;
	maxAuctionSearchJobs = 1;

	termsOfService = "";
	tosVersion = 0;

	logFileLevel = Logger::INFO;
	jsonLogOutput = false;
	syncLogOutput = false;
	pathfinderLogJSON = false;
	luaLogJSON = false;

	restPort = 0;

	Logger::setLoggingName("ConfigManager");
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
	dumpObjFiles = getGlobalByte("DumpObjFiles");
	unloadContainers = getGlobalByte("UnloadContainers");
	useMetrics = getGlobalByte("UseMetrics");
	pvpMode = getGlobalByte("PvpMode");

	orbNamingDirectoryAddress = getGlobalString("ORB");
	orbNamingDirectoryPort = getGlobalShort("ORBPort");

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
	zonePort = getGlobalInt("ZoneServerPort");

	statusAllowedConnections = getGlobalInt("StatusAllowedConnections");
	statusInterval = getGlobalInt("StatusInterval");

	webPorts = getGlobalString("WebPorts");
	webAccessLog = getGlobalString("WebAccessLog");
	webErrorLog = getGlobalString("WebErrorLog");
	webSessionTimeout = getGlobalInt("WebSessionTimeout");

	metricsHost = getGlobalString("MetricsHost");
	metricsPrefix = getGlobalString("MetricsPrefix");
	metricsPort = getGlobalInt("MetricsPort");

	progressMonitors = getGlobalBoolean("ProgressMonitors");

	purgeDeletedCharacters = getGlobalInt("PurgeDeletedCharacters");

	maxNavMeshJobs = getGlobalInt("MaxNavMeshJobs");
	maxAuctionSearchJobs = getGlobalInt("MaxAuctionSearchJobs");

	logFile = getGlobalString("LogFile");
	logFileLevel = getGlobalInt("LogFileLevel");

	jsonLogOutput = getGlobalByte("LogJSON");
	syncLogOutput = getGlobalByte("LogSync");
	luaLogJSON = getGlobalByte("LuaLogJSON");
	pathfinderLogJSON = getGlobalByte("PathfinderLogJSON");

	cleanupMailCount = getGlobalInt("CleanupMailCount");

	termsOfService = getGlobalString("TermsOfService");
	tosVersion = getGlobalInt("TermsOfServiceVersion");

	restPort = getGlobalInt("RESTServerPort");

	loadTweaks();

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
		file = nullptr;
		reader = nullptr;
	}

	delete reader;
	delete file;
}

void ConfigManager::loadRevision() {
	revision = "";

	try {
		File file("conf/rev.txt");
		FileReader reader(&file);

		String line;

		while (reader.readLine(line))
			revision += line;

		reader.close();
	} catch (FileNotFoundException& e) {
	} catch (Exception& e) {
	}

	//revision = revision.replaceAll("\n", "");
}

// Tweak functions
void ConfigManager::loadTweaks() {
	LuaObject tweaks = getGlobalObject("tweaks");

	if(!tweaks.isValidTable()) {
		info("Error initializing tweaks: not a valid table", true);
		tweaks.pop();
		return;
	}

	tweaksTable.removeAll();

	lua_State* L = getLuaState();

	lua_pushnil(L); // First key

	for (int i = 0; lua_next(L, -2) != 0; ++i) {
		// -2 = key -1 = value

		// Keys must be strings for tweaks
		if (lua_type(L, -2) != LUA_TSTRING) {
			info("Error initializing tweaks: key for row #" + String::valueOf(i) + " is not a string.", true);
			lua_pop(L, 1);
			continue;
		}

		TweakValueItem itm;
		String key = lua_tostring(L, -2);
		int luaType = lua_type(L, -1);

		switch (luaType) {
		case LUA_TBOOLEAN:
			itm.setBool(lua_toboolean(L, -1));
			break;
		case LUA_TNUMBER:
			itm.setNumber(lua_tonumber(L, -1));
			break;
		case LUA_TSTRING:
			itm.setString(lua_tostring(L, -1));
			break;
		default:
			info("loadTweaks: row #" + String::valueOf(i) + " " + key + " type: " + lua_typename(L, luaType) + " is no supported", true);
			lua_pop(L, 1);
			continue;
		}

		lua_pop(L, 1);

		tweaksTable.put(key, itm);

		info("tweaks[" + key + "] = [" + itm.toString() + "]", true);
	}

	tweaks.pop();
}

int ConfigManager::getTweakInt(const String& name, int defaultValue) {
	int pos = tweaksTable.find(name);

	if (pos != -1) {
		TweakValueItem itm = tweaksTable.get(pos);
		return itm.getInt(defaultValue);
	}

	return defaultValue;
}

bool ConfigManager::getTweakBool(const String& name, bool defaultValue) {
	int pos = tweaksTable.find(name);

	if (pos != -1) {
		TweakValueItem itm = tweaksTable.get(pos);
		return itm.getBool(defaultValue);
	}

	return defaultValue;
}

float ConfigManager::getTweakFloat(const String& name, float defaultValue) {
	int pos = tweaksTable.find(name);

	if (pos != -1) {
		TweakValueItem itm = tweaksTable.get(pos);
		return itm.getFloat(defaultValue);
	}

    return defaultValue;
}

const String ConfigManager::getTweakString(const String& name, const String& defaultValue) {
	int pos = tweaksTable.find(name);

	if (pos != -1) {
		TweakValueItem itm = tweaksTable.get(pos);
		return itm.getString(defaultValue);
	}

    return defaultValue;
}
