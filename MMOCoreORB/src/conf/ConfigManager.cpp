/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ConfigManager.h"
#include <regex>

using namespace sys::thread;

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
	Locker guard(&mutex);

	logChanges = false;

	if (configStartTime.getStartTime() != 0)
		configStartTime.stop();

	configStartTime.start();

	if (!lua.runFile("conf/config.lua")) {
		fatal("ConfigManager failed to parse conf/config.lua");
		return false;
	}

	File file("conf/config-local.lua");

	if (file.setReadOnly()) {
		if (!lua.runFile("conf/config-local.lua")) {
			error("ConfigManager failed to parse conf/config-local.lua");
			return false;
		}
	} else {
		info("Did not find conf/config-local.lua", true);
	}

#ifdef DEBUG_CONFIGMANAGER
	info("Loaded config file(s) in " + String::valueOf(getConfigDataAgeMs()) + "ms", true);
#endif // DEBUG_CONFIGMANAGER

	bool resultGlobal, resultCore3;

	clearConfigData();

	// Load new-style "Core3.value" settings
	LuaObject core3 = lua.getGlobalObject("Core3");

	resultCore3 = parseConfigData("Core3");

	if (!resultCore3)
		error("Failed to parse Core3 configuration table, falling back on old Globals style config.");

	core3.pop();

	// Load legacy "globals" style configuration
	lua_State* L = lua.getLuaState();

	lua_pushglobaltable(L);

	resultGlobal = parseConfigData("Core3", true);

	if (!resultGlobal)
		error("Failed to parse legacy configuration globals.");

	lua_pop(L, 1);

	// Load file based strings into config
	setStringFromFile("Core3.MOTD", "conf/motd.txt");
	setStringFromFile("Core3.Revision", "conf/rev.txt");

#ifdef DEBUG_CONFIGMANAGER
	info("Parsed config into memory in " + String::valueOf(getConfigDataAgeMs()) + "ms", true);
	setString("Core3.ConfigManagerDebug", "Test1");
	setString("Core3.ConfigManagerDebug", "Compiled with DEBUG_CONFIGMANAGER");
	dumpConfig();
#endif // DEBUG_CONFIGMANAGER

	logChanges = true;

	return resultGlobal || resultCore3;
}

void ConfigManager::clearConfigData() {
	Locker guard(&mutex);

	for (int i = 0; i < configData.size(); ++i) {
		auto entry = configData.getUnsafe(i).getValue();
		delete entry;
	}

	configData.removeAll();
	configData.setNoDuplicateInsertPlan();
	incrementConfigVersion();
}

void ConfigManager::dumpConfig(bool includeSecure) {
	ReadLocker guard(&mutex);

	uint64 age = getConfigDataAgeMs() / 1000;

	info(true) << "dumpConfig: START (Config Age: " << age << " s, Version#:" << getConfigVersion() << ")";

	String hottestKey;
	int maxPS = 0;
	int maxUsageCounter = 0;

	for (int i = 0; i < configData.size(); ++i) {
		auto entry = configData.elementAt(i);
		String key = entry.getKey();
		ConfigDataItem* itm = entry.getValue();

		String stringVal = itm->toString();

		if (!includeSecure && isSensitiveKey(key)) {
			stringVal = "*******";
		}

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

	auto engineConfig = Core::getPropertiesString();

	info(true) << engineConfig;

	info("dumpConfig: END", true);
}

bool ConfigManager::parseConfigData(const String& prefix, bool isGlobal, int maxDepth) {
	lua_State* L = lua.getLuaState();

	// Enter with table on top of lua stack
	if (!lua_istable(L, -1)) {
#ifdef DEBUG_CONFIGMANAGER
		error("Configuration error, expected table in ConfigManager::parseConfigData, prefix=" + prefix);
#endif // DEBUG_CONFIGMANAGER
		return false;
	}

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

bool ConfigManager::parseConfigJSONRecursive(const String prefix, JSONSerializationType jsonNode, String& errorMessage, bool updateOnly) {
	for (auto jsonData = jsonNode.begin(); jsonData != jsonNode.end(); ++jsonData) {
		String key = (prefix.isEmpty() ? "" : prefix + ".") + jsonData.key();

		if (jsonData->is_array()) {
			if (updateOnly && !contains(key)) {
				errorMessage = "Array key " + key + " doesn't exist.";
				error() << "parseConfigJSONRecursive(" << key << "): " << errorMessage;
				return false;
			}

			bool isValid = true;
			Vector <ConfigDataItem *>* elements = new Vector <ConfigDataItem *>();

			for (auto jsonElement = jsonData->begin();isValid && jsonElement != jsonData->end(); ++jsonElement) {
				switch (jsonElement->type()) {
				case JSONSerializationType::value_t::boolean:
					elements->add(new ConfigDataItem((bool)jsonElement.value().get<bool>()));
					break;

				case JSONSerializationType::value_t::number_float:
				case JSONSerializationType::value_t::number_unsigned:
				case JSONSerializationType::value_t::number_integer:
					elements->add(new ConfigDataItem((lua_Number)jsonElement.value().get<double>()));
					break;

				case JSONSerializationType::value_t::string:
					elements->add(new ConfigDataItem(jsonElement.value().get<std::string>()));
					break;

				default:
					isValid = false;
					errorMessage = "Failed to parse json type " + String(jsonElement->type_name()) + " into array " + key;
					error() << "parseConfigJSONRecursive(" << key << "): " << errorMessage;
					break;
				}
			}

			if (isValid && !updateItem(key, new ConfigDataItem(elements))) {
				isValid = false;
			}

			if (!isValid) {
				delete elements;
				return false;
			}

			continue;
		}

		if (jsonData->is_object()) {
			if (!parseConfigJSONRecursive(key, jsonData.value(), errorMessage, updateOnly)) {
				return false;
			}
			continue;
		}

		if (updateOnly && !contains(key)) {
			errorMessage = "Key " + key + " doesn't exist.";
			error() << "parseConfigJSONRecursive(" << key << "): " << errorMessage;
			return false;
		}

		switch (jsonData->type()) {
		case JSONSerializationType::value_t::boolean:
			setBool(key, jsonData.value().get<bool>());
			break;

		case JSONSerializationType::value_t::number_float:
		case JSONSerializationType::value_t::number_unsigned:
		case JSONSerializationType::value_t::number_integer:
			setNumber(key, (lua_Number)jsonData.value().get<double>());
			break;

		case JSONSerializationType::value_t::string:
			setString(key, jsonData.value().get<std::string>());
			break;

		default:
			errorMessage = "Failed to parse json type " + String(jsonData->type_name()) + " into " + key;
			error() << "parseConfigJSONRecursive(" << key << "): " << errorMessage;
			return false;
			break;
		}
	}

	return true;
}

bool ConfigManager::parseConfigJSON(const JSONSerializationType jsonData, String& errorMessage, bool updateOnly) {
	Locker guard(&mutex);

	try {
		return parseConfigJSONRecursive("", jsonData, errorMessage, updateOnly);
	} catch (const JSONSerializationType::exception& e) {
		errorMessage = "Exception while parsing json:" + String(e.what()) + "(" + e.id + ")";
		error() << "parseConfigJSON: " << errorMessage;
	} catch (const Exception& e) {
		errorMessage = "Exception while parsing config:" + e.getMessage();
		error() << "parseConfigJSON: " << errorMessage;
	} catch (...) {
		StringBuffer err;
		err << "Uncaptured exception parsing config"
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
			<< ": " << __cxxabiv1::__cxa_current_exception_type()->name()
#endif
			<< ".";
		errorMessage = err.toString();
		error() << "parseConfigJSON: " << errorMessage;
	}

	return false;
}

bool ConfigManager::parseConfigJSON(const String& jsonString, String& errorMessage, bool updateOnly) {
	Locker guard(&mutex);

	try {
		JSONSerializationType jsonData = JSONSerializationType::parse(jsonString);
		return parseConfigJSONRecursive("", jsonData, errorMessage, updateOnly);
	} catch (const JSONSerializationType::exception& e) {
		errorMessage = "Exception while parsing json:" + String(e.what()) + "(" + e.id + ")";
		error() << "parseConfigJSON(" << jsonString << "): " << errorMessage;
	} catch (const Exception& e) {
		errorMessage = "Exception while parsing config:" + e.getMessage();
		error() << "parseConfigJSON(" << jsonString << "): " << errorMessage;
	} catch (...) {
		StringBuffer err;
		err << "Uncaptured exception parsing config"
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
			<< ": " << __cxxabiv1::__cxa_current_exception_type()->name()
#endif
			<< ".";
		errorMessage = err.toString();
		error() << "parseConfigJSON(" << jsonString << "): " << errorMessage;
	}

	return false;
}

bool ConfigManager::contains(const String& name, unsigned int accountID) const {
	return configData.find(name) != -1 || configData.find(withAccount(name, accountID)) != -1;
}

ConfigDataItem* ConfigManager::findItem(const String& name, unsigned int accountID) const {
	int pos = -1;

	if (pos == -1 && accountID > 0) {
		pos = configData.find(withAccount(name, accountID));
	}

	if (pos == -1) {
		pos = configData.find(name);
	}

	if (pos == -1) {
		return nullptr;
	}

	return configData.get(pos);
}

int ConfigManager::getUsageCounter(const String& name) const {
	ConfigDataItem* itm = findItem(name);

	if (itm == nullptr) {
		return -1;
	}

	return itm->getUsageCounter();
}

int ConfigManager::getInt(const String& name, int defaultValue, unsigned int accountID) {
	ReadLocker guard(&mutex);

	ConfigDataItem* itm = findItem(name, accountID);

	if (itm == nullptr)
		return defaultValue;

	return itm->getInt();
}

bool ConfigManager::getBool(const String& name, bool defaultValue, unsigned int accountID) {
	ReadLocker guard(&mutex);

	ConfigDataItem* itm = findItem(name, accountID);

	if (itm == nullptr)
		return defaultValue;

	return itm->getBool();
}

float ConfigManager::getFloat(const String& name, float defaultValue, unsigned int accountID) {
	ReadLocker guard(&mutex);

	ConfigDataItem* itm = findItem(name, accountID);

	if (itm == nullptr)
		return defaultValue;

	return itm->getFloat();
}

const String& ConfigManager::getString(const String& name, const String& defaultValue, unsigned int accountID) {
	Locker guard(&mutex);

	ConfigDataItem* itm = findItem(name, accountID);

	if (itm == nullptr) {
		itm = new ConfigDataItem(defaultValue);
		if (itm == nullptr || !updateItem(name, itm))
			throw Exception("ConfigManager::getString(" + name + ") failed to set default value: [" + defaultValue + "]");
	}

	return itm->getString();
}

const Vector<String>& ConfigManager::getStringVector(const String& name, unsigned int accountID) {
	ReadLocker guard(&mutex);

	ConfigDataItem* itm = findItem(name, accountID);

	if (itm == nullptr)
		throw Exception("ConfigManager::getStringVector(" + name + ") not found");

	return itm->getStringVector();
}

const SortedVector<String>& ConfigManager::getSortedStringVector(const String& name, unsigned int accountID) {
	ReadLocker guard(&mutex);

	ConfigDataItem* itm = findItem(name, accountID);

	if (itm == nullptr)
		throw Exception("ConfigManager::getSortedStringVector(" + name + ") not found");

	return itm->getSortedStringVector();
}

const Vector<int>& ConfigManager::getIntVector(const String& name, unsigned int accountID) {
	ReadLocker guard(&mutex);

	ConfigDataItem* itm = findItem(name, accountID);

	if (itm == nullptr)
		throw Exception("ConfigManager::getIntVector(" + name + ") not found");

	return itm->getIntVector();
}

bool ConfigManager::isSensitiveKey(const String& key) {
	auto lcKey = key.toLowerCase();

	return lcKey.contains("secret") || lcKey.contains("pass") || lcKey.contains("token");
}

void ConfigManager::writeJSONPath(StringTokenizer& tokens, JSONSerializationType& jsonData, const JSONSerializationType& jsonValue) {
	String nextName;
	tokens.getStringToken(nextName);

	if (tokens.hasMoreTokens()) {
		if (jsonData[nextName].is_null()) {
			jsonData[nextName] = JSONSerializationType::object();
		}
		writeJSONPath(tokens, jsonData[nextName], jsonValue);
	} else {
		jsonData[nextName] = jsonValue;
	}
}

bool ConfigManager::getAsJSON(const String& target, JSONSerializationType& jsonData) {
	ReadLocker guard(&mutex);

	try {
		auto re = std::regex((target + "(?:\\..*$|$)").toCharArray());
		jsonData = JSONSerializationType::object();

		for (int i = 0; i < configData.size(); ++i) {
			JSONSerializationType jsonValue;
			auto entry = configData.elementAt(i);
			String key = entry.getKey();

			if (isSensitiveKey(key)) {
				jsonValue = "*******";
			} else {
				ConfigDataItem* itm = entry.getValue();
				itm->getAsJSON(jsonValue);
			}

			if (std::regex_search(key.toCharArray(), re)) {
				StringTokenizer tokenizer(key);
				tokenizer.setDelimeter(".");
				writeJSONPath(tokenizer, jsonData, jsonValue);
			}
		}
	} catch(...) {
		return false;
	}

	return true;
}

bool ConfigManager::updateItem(const String& name, ConfigDataItem* newItem) {
	Locker guard(&mutex);

	if (newItem == nullptr || name.isEmpty())
		return false;

	int pos = configData.find(name);

	if (pos != -1) {
		ConfigDataItem* oldItem = configData.get(pos);
		configData.drop(name);
		delete oldItem;
		oldItem = nullptr;
	}

	if (logChanges) {
		if (isSensitiveKey(name)) {
			info(true) << "Configuration updated: " << name;
		} else {
			info(true) << "Configuration update: " << name << " = [" << newItem->toString() << "]";
		}
	}

#ifdef DEBUG_CONFIGMANAGER
	info("updateItem: " + name + " = [" + newItem->toString() + "]", true);
	newItem->setDebugTag(name);
#endif // DEBUG_CONFIGMANAGER

	configData.put(std::move(name), std::move(newItem));
	incrementConfigVersion();
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
	} catch (const FileNotFoundException& e) {
		error("setStringFromFile(" + name + ", " + fileName +") File Not Found.");
	} catch (const Exception& e) {
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

void ConfigDataItem::getAsJSON(JSONSerializationType& jsonData) {
	if (asVector != nullptr) {
		jsonData = JSONSerializationType::array();

		for (int i = 0;i < asVector->size(); i++) {
			JSONSerializationType jsonValue;
			ConfigDataItem* curItem = asVector->get(i);

			if (curItem == nullptr) {
				continue;
			}

			curItem->getAsJSON(jsonValue);
			jsonData.push_back(jsonValue);
		}

		return;
	}

	jsonData = asString;
}
