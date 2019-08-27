/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ConfigManager.h"

ConfigManager::ConfigManager() {
	setLoggingName("ConfigManager");
#ifdef DEBUG_CONFIGMANAGER
	setLogLevel(Logger::DEBUG);
#else // DEBUG_CONFIGMANAGER
	setLogLevel(Logger::INFO);
#endif // DEBUG_CONFIGMANAGER
}

ConfigManager::~ConfigManager() {
	clearConfigData();
}

bool ConfigManager::loadConfigData() {
	if (configStartTime.getStartTime() != 0)
		configStartTime.stop();

	configStartTime.start();

	if (!runFile("conf/config.lua")) {
		error("ConfigManager failed to parse conf/config.lua");
		return false;
	}

	File file("conf/config-local.lua");

	if (file.setReadOnly()) {
		if (!runFile("conf/config-local.lua")) {
			error("ConfigManager failed to parse conf/config-local.lua");
			return false;
		}
	} else {
		info("Did not find conf/config-local.lua", true);
	}

#ifdef DEBUG_CONFIGMANAGER
	info("Loaded config file(s) in " + String::valueOf(getConfigDataAgeMs()) + "ms", true);
#endif // DEBUG_CONFIGMANAGER

	bool result_global, result_core3;

	clearConfigData();

	// Load new-style "Core3.value" settings
	LuaObject core3 = getGlobalObject("Core3");

	result_core3 = parseConfigData("Core3");

	if (!result_core3)
		error("Failed to parse Core3 configuration table, falling back on old Globals style config.");

	core3.pop();

	// Load legacy "globals" style configuration
	lua_State* L = getLuaState();

	lua_pushglobaltable(L);

	result_global = parseConfigData("Core3", true);

	if (!result_global)
		error("Failed to parse legacy configuration globals.");

	lua_pop(L, 1);

	// Load file based strings into config
	setStringFromFile("Core3.MOTD", "conf/motd.txt");
	setStringFromFile("Core3.Revision", "conf/rev.txt");

	cacheHotItems();

#ifdef DEBUG_CONFIGMANAGER
	info("Parsed config into memory in " + String::valueOf(getConfigDataAgeMs()) + "ms", true);
	setString("Core3.ConfigManagerDebug", "Test1");
	setString("Core3.ConfigManagerDebug", "Compiled with DEBUG_CONFIGMANAGER");
	dumpConfig();
#endif // DEBUG_CONFIGMANAGER

	return result_global || result_core3;
}

void ConfigManager::clearConfigData() {
	for (int i = 0; i < configData.size(); ++i) {
		auto entry = configData.getUnsafe(i).getValue();
		delete entry;
	}

	configData.removeAll();
	configData.setNoDuplicateInsertPlan();

	// Clear any cached values below
	cache_PvpMode = false;
	cache_ProgressMonitors = false;
	cache_UnloadContainers = false;
	cache_UseMetrics = false;
	cache_SessionStatsSeconds = 3600;
	cache_OnlineLogSize = 100000000;
}

void ConfigManager::cacheHotItems() {
	// Items here are asked for often enough to have a performance impact
	cache_PvpMode = getBool("Core3.PvpMode", false);
	cache_ProgressMonitors = getBool("Core3.ProgressMonitors", false);
	cache_UnloadContainers = getBool("Core3.UnloadContainers", true);
	cache_UseMetrics = getBool("Core3.UseMetrics", false);
	cache_SessionStatsSeconds = getInt("Core3.SessionStatsSeconds", 3600);
	cache_OnlineLogSize = getInt("Core3.OnlineLogSize", 100000000);
}

void ConfigManager::dumpConfig(bool includeSecure) {
	uint64 age = getConfigDataAgeMs() / 1000;

	info(true) << "dumpConfig: START (Config Age: " << age << " s)";

	String hottestKey;
	int maxPS = 0;
	int maxUsageCounter = 0;

	for (int i = 0; i < configData.size(); ++i) {
		auto entry = configData.elementAt(i);
		String key = entry.getKey();
		ConfigDataItem* itm = entry.getValue();

		String stringVal = itm->toString();

		if (!includeSecure && (key.toLowerCase().contains("pass") || key.toLowerCase().contains("secret")))
			stringVal = "*******";

		auto msg = info(true);

		int ps = age > 0 ? itm->getUsageCounter() / age : 0;

		if (ps > maxPS || itm->getUsageCounter() > maxUsageCounter) {
			hottestKey = String(key);
			maxPS = ps;
			maxUsageCounter = itm->getUsageCounter();
		}

		msg << key
			<< " usageCounter: " << itm->getUsageCounter()
			<< " (" << ps << "/s)"
			<< " bool: " << itm->getBool()
			<< " int: " << itm->getInt()
			<< " float: " << itm->getFloat()
			<< " str: '" << stringVal.escapeString()
			<< "'";

		msg.flush();
	}

	if (!hottestKey.isEmpty()) {
		info(true) << "Hottest key: " <<
		       	hottestKey << " usageCounter: " << maxUsageCounter << " (" << maxPS << "/s)";
	}

#ifdef DEBUG_CONFIGMANAGER
	if (getLogLevel() >= Logger::DEBUG) {
		testConfig(this);
	}
#endif // DEBUG_CONFIGMANAGER

	info("dumpConfig: END", true);
}

#ifdef DEBUG_CONFIGMANAGER
bool ConfigManager::testConfig(ConfigManager* configManager) {
	info("testConfig: START", true);

	auto tmp1 = configManager->getString("Core3.InactiveAccountText", "Account Disabled");
	info("Core3.InactiveAccountTitle = " + tmp1, true);

	auto tmp2 = configManager->getInactiveAccountText();
	info("getInactiveAccountText = " + tmp2, true);

	if (tmp1 != tmp2)
		throw Exception("testConfig() return value mismatch");

	info("LogFile = " + configManager->getLogFile(), true);

	if (configManager->getMakeZone()) {
		info("getMakeZone() = true", true);
	} else {
		info("getMakeZone() = false", true);
	}

	auto enabledZones = configManager->getEnabledZones();

	info("ZonesEnabled:", true);

	for (int i = 0; i < enabledZones.size(); ++i) {
		String zoneName = enabledZones.get(i);
		info("    '" + zoneName + "'", true);
	}

	Vector<String> treFilesToLoad = configManager->getTreFiles();

	info("TreFiles:", true);

	for (int i = 0; i < treFilesToLoad.size(); ++i) {
		String zoneName = treFilesToLoad.get(i);
		info("    '" + zoneName + "'", true);
	}

	const uint16& dbPort = configManager->getDBPort();

	info("DBPort = " + String::valueOf(dbPort), true);

	info("testConfig: END", true);

	return true;
}
#endif // DEBUG_CONFIGMANAGER

bool ConfigManager::parseConfigData(const String& prefix, bool isGlobal, int maxDepth) {
	// Enter with table on top of lua stack
	if (!lua_istable(L, -1)) {
#ifdef DEBUG_CONFIGMANAGER
		error("Configuration error, expected table in ConfigManager::parseConfigData, prefix=" + prefix);
#endif // DEBUG_CONFIGMANAGER
		return false;
	}

	lua_State* L = getLuaState();

	lua_pushnil(L); // First key

	bool isArray = true;

	// Crude array detection, is there a better way?
	for (int i = 0; lua_next(L, -2) != 0; ++i) {
		// -2 = key -1 = value
		int luaType = lua_type(L, -2);
		lua_pop(L, 1);

		if (luaType == LUA_TSTRING) {
			isArray = false;
			lua_pop(L, 1);
			break;
		}
	}

	if (isArray) {
		Vector <ConfigDataItem *>* elements = new Vector <ConfigDataItem *>();

		lua_pushnil(L); // First key

		for (int i = 0; lua_next(L, -2) != 0; ++i) {
			// -2 = key -1 = value

			int luaType = lua_type(L, -1);

			switch (luaType) {
			case LUA_TBOOLEAN:
				elements->add(new ConfigDataItem((bool)lua_toboolean(L, -1)));
				break;

			case LUA_TNUMBER:
				elements->add(new ConfigDataItem((lua_Number)lua_tonumber(L, -1)));
				break;

			case LUA_TSTRING:
				elements->add(new ConfigDataItem((String)lua_tostring(L, -1)));
				break;

			default:
				error("parseConfigData: row #" + String::valueOf(i) + " " + prefix + " type: " + lua_typename(L, luaType) + " is not supported in an array.");
				lua_pop(L, 1);
				continue;
			}

			lua_pop(L, 1);
		}

		return updateItem(prefix, new ConfigDataItem(elements));
	}

	// Handle Tables
	lua_pushnil(L); // First key

	for (int i = 0; lua_next(L, -2) != 0; ++i) {
		// -2 = key -1 = value
		int luaType = lua_type(L, -2);

		// Only use the string keys
		if (luaType != LUA_TSTRING) {
			if (luaType != LUA_TNUMBER)
				info("Error initializing configuration key for row #" + String::valueOf(i) + "(" + lua_typename(L, luaType) + ") is not a string.", true);

			lua_pop(L, 1);
			continue;
		}

		String luaKey = lua_tostring(L, -2);
		bool skipKey = false;

		// Ignore keys starting with underscore
		if (luaKey.subString(0, 1) == '_')
			skipKey = true;

		if (isGlobal) {
			// Avoid well known lua names
			if (luaKey.indexOf("Core3") == 0 || luaKey.subString(0, 1).toLowerCase() == luaKey.subString(0, 1))
				skipKey = true;
		}

		if (skipKey) {
			lua_pop(L, 1);
			continue;
		}

		String key = prefix + "." + luaKey;
		luaType = lua_type(L, -1);

		switch (luaType) {
		case LUA_TBOOLEAN:
			setBool(key, lua_toboolean(L, -1));
			break;

		case LUA_TNUMBER:
			setNumber(key, lua_tonumber(L, -1));
			break;

		case LUA_TSTRING:
			setString(key, lua_tostring(L, -1));
			break;

		case LUA_TTABLE:
			if (maxDepth <= 0) {
				error("Configuration error, reached max depth in ConfigManager::parseConfigData, prefix=" + prefix);
			} else if (!parseConfigData(key, isGlobal, maxDepth - 1)) {
				lua_pop(L, 1);
				return false;
			}
			lua_pop(L, 1);
			continue;

		case LUA_TFUNCTION:
			if (isGlobal) {
				lua_pop(L, 1);
				continue;
			}

			// [[fallthrough]];

		default:
			error("parseConfigData: row #" + String::valueOf(i) + " " + key + " type: " + lua_typename(L, luaType) + " is not supported");
			lua_pop(L, 1);
			continue;
		}

		lua_pop(L, 1);
	}

	return true;
}

ConfigDataItem* ConfigManager::findItem(const String& name) {
	int pos = configData.find(name);

	if (pos == -1) {
		return nullptr;
#ifdef DEBUG_CONFIGMANAGER
		info("findItem failed for: " + name, true);
#endif // DEBUG_CONFIGMANAGER
	}

	return configData.get(pos);
}

int ConfigManager::getInt(const String& name, int defaultValue) {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr)
		return defaultValue;

	return itm->getInt();
}

bool ConfigManager::getBool(const String& name, bool defaultValue) {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr)
		return defaultValue;

	return itm->getBool();
}

float ConfigManager::getFloat(const String& name, float defaultValue) {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr)
		return defaultValue;

	return itm->getFloat();
}

const String& ConfigManager::getString(const String& name, const String& defaultValue) {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr) {
		itm = new ConfigDataItem(defaultValue);
		if (itm == nullptr || !updateItem(name, itm))
			throw Exception("ConfigManager::getString(" + name + ") failed to set default value: [" + defaultValue + "]");
	}

	return itm->getString();
}

const Vector<String>& ConfigManager::getStringVector(const String& name) {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr)
		throw Exception("ConfigManager::getStringVector(" + name + ") not found");

	return itm->getStringVector();
}

const SortedVector<String>& ConfigManager::getSortedStringVector(const String& name) {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr)
		throw Exception("ConfigManager::getSortedStringVector(" + name + ") not found");

	return itm->getSortedStringVector();
}

const Vector<int>& ConfigManager::getIntVector(const String& name) {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr)
		throw Exception("ConfigManager::getIntVector(" + name + ") not found");

	return itm->getIntVector();
}

bool ConfigManager::updateItem(const String& name, ConfigDataItem* newItem) {
	if (newItem == nullptr || name.isEmpty())
		return false;

	int pos = configData.find(name);

	if (pos != -1) {
		ConfigDataItem* oldItem = configData.get(pos);
		configData.drop(name);
		delete oldItem;
		oldItem = nullptr;
	}

#ifdef DEBUG_CONFIGMANAGER
	info("updateItem: " + name + " = [" + newItem->toString() + "]", true);
	newItem->setDebugTag(name);
#endif // DEBUG_CONFIGMANAGER

	configData.put(std::move(name), std::move(newItem));
	return true;
}

bool ConfigManager::setNumber(const String& name, lua_Number newValue) {
	return updateItem(name, new ConfigDataItem(newValue));
}

bool ConfigManager::setInt(const String& name, int newValue) {
	return updateItem(name, new ConfigDataItem(newValue));
}

bool ConfigManager::setBool(const String& name, bool newValue) {
	return updateItem(name, new ConfigDataItem(newValue));
}

bool ConfigManager::setFloat(const String& name, float newValue) {
	return updateItem(name, new ConfigDataItem(newValue));
}

bool ConfigManager::setString(const String& name, const String& newValue) {
	return updateItem(name, new ConfigDataItem(newValue));
}

bool ConfigManager::setStringFromFile(const String& name, const String& fileName) {
	StringBuffer newValue;

	try {
		File file(fileName);
		FileReader reader(&file);
		String line;

		while (reader.readLine(line))
			newValue << line;

		reader.close();

		return setString(name, newValue.toString());
	} catch (FileNotFoundException& e) {
		error("setStringFromFile(" + name + ", " + fileName +") File Not Found.");
	} catch (Exception& e) {
		error("setStringFromFile(" + name + ", " + fileName +") Unexpected exception reading file.");
	}

	return false;
}

/*
** ConfigDataItem
*/

ConfigDataItem::ConfigDataItem(lua_Number value) {
	asNumber = value;
	asBool   = (bool)asNumber;
	asString = String::valueOf(value);
	asVector = nullptr;
	asStringVector = nullptr;
	asSortedStringVector = nullptr;
	usageCounter = 0;
}

ConfigDataItem::ConfigDataItem(int value) {
	asNumber = (lua_Number)value;
	asBool   = (bool)asNumber;
	asString = String::valueOf(value);
}

ConfigDataItem::ConfigDataItem(bool value) {
	asNumber = value ? 1.0f : 0.0f;
	asBool   = value;
	asString = String(value ? "true" : "false");
}

ConfigDataItem::ConfigDataItem(float value) {
	asNumber = (lua_Number)value;
	asBool   = (bool)asNumber;
	asString = String::valueOf(value);
}

ConfigDataItem::ConfigDataItem(const String& value) {
	if (value == "true") {
		asNumber = 1.0f;
		asBool = true;
	} else if (value == "false") {
		asNumber = 0.0f;
		asBool = false;
	} else {
		asNumber = atof(value.toCharArray());
		asBool = asNumber != 0.0 ? true : false;
	}
	asString = String(value);
}

ConfigDataItem::ConfigDataItem(Vector <ConfigDataItem *>* value) {
	asBool = true;
	asNumber = value->size();
	asString = String("<Vector " + String::valueOf((int)asNumber) + ">");
	asVector = value;
}

ConfigDataItem::~ConfigDataItem() {
#ifdef DEBUG_CONFIGMANAGER
	std::cout << "ConfigDataItem destroyed " << debugTag.toCharArray() << " usageCounter = " << usageCounter << std::endl << std::flush;
#endif // DEBUG_CONFIGMANAGER

	if (asVector != nullptr) {
		for (int i = 0;i < asVector->size(); ++i) {
			auto element = asVector->getUnsafe(i);
			delete element;
		}

		delete asVector;
		asVector = nullptr;
	}

	if (asStringVector != nullptr) {
		delete asStringVector;
		asStringVector = nullptr;
	}

	if (asSortedStringVector != nullptr) {
		delete asSortedStringVector;
		asSortedStringVector = nullptr;
	}

	if (asIntVector != nullptr) {
		delete asIntVector;
		asIntVector = nullptr;
	}
}
