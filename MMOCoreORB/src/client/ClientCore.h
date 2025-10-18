/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTCORE_H_
#define CLIENTCORE_H_

#include "system/lang.h"
#include "server/login/objects/GalaxyList.h"

class Zone;
class ActionBase;

struct ClientCoreOptions {
	// Single source of truth
	JSONSerializationType config;
	Vector<ActionBase*> actions;

	// Constructor does ALL parsing
	ClientCoreOptions() = default;
	ClientCoreOptions(int argc, char** argv);

	// Generic accessor with defaults
	template<typename T>
	T get(const char* path, T defaultVal = T()) const {
		try {
			return config.at(JSONSerializationType::json_pointer(path)).get<T>();
		} catch (...) {
			return defaultVal;
		}
	}

	// Setter
	void set(const char* path, const JSONSerializationType& val) {
		config[JSONSerializationType::json_pointer(path)] = val;
	}

	// Utility methods
	JSONSerializationType getAsJSON() const;
	String toString() const;
	String toStringData() const;

private:
	void loadEnvFile(const String& filename);
	int parseLogLevel(const String& levelStr);
	String resolveFileReference(const String& value);
	void parseArgumentsIntoActions(const Vector<String>& args);
	void parseJSONIntoActions(const JSONSerializationType& jsonActions);
	void resolveDependencies();
};

class ClientCore : public Core, public Logger {
public:
	ClientCoreOptions options;
	Reference<class LoginSession*> loginSession;
	Zone* zone;
	VectorMap<String, String> vars;
	uint64 selectedCharacterOid;  // Which character we're playing as (set by zoneInCharacter, confirmed by server)
	uint64 targetCharacterOid;    // Target character for operations (set by selectContext)
	uint32 targetGalaxyId;        // Target galaxy (set by selectContext)

private:
	Time overallStartTime;
	Optional<Galaxy> selectedGalaxy;

public:
	static int getLogLevel() {
		Core* instance = Core::getCoreInstance();
		if (instance) {
			ClientCore* clientCore = static_cast<ClientCore*>(instance);
			if (clientCore) {
				int level = clientCore->options.get<int>("/logLevel", -1);
				if (level != -1) return level;
			}
		}
		return Core::getIntProperty("Client3.LogLevel", Logger::INFO);
	}

	static String getLoginHost() {
		Core* instance = Core::getCoreInstance();
		if (instance) {
			ClientCore* clientCore = static_cast<ClientCore*>(instance);
			if (clientCore) {
				std::string host = clientCore->options.get<std::string>("/loginHost", "");
				if (!host.empty()) return String(host.c_str());
			}
		}
		return Core::getProperty("Client3.LoginHost", "127.0.0.1");
	}

	static int getLoginPort() {
		Core* instance = Core::getCoreInstance();
		if (instance) {
			ClientCore* clientCore = static_cast<ClientCore*>(instance);
			if (clientCore) {
				int port = clientCore->options.get<int>("/loginPort", 0);
				if (port != 0) return port;
			}
		}
		return Core::getIntProperty("Client3.LoginPort", 44453);
	}

	static String getClientVersion() {
		Core* instance = Core::getCoreInstance();
		if (instance) {
			ClientCore* clientCore = static_cast<ClientCore*>(instance);
			if (clientCore) {
				std::string ver = clientCore->options.get<std::string>("/clientVersion", "");
				if (!ver.empty()) return String(ver.c_str());
			}
		}
		return Core::getProperty("Client3.ClientVersion", "20050408-18:00");
	}

	static int getLoginTimeout() {
		Core* instance = Core::getCoreInstance();
		if (instance) {
			ClientCore* clientCore = static_cast<ClientCore*>(instance);
			if (clientCore) {
				int timeout = clientCore->options.get<int>("/loginTimeout", 0);
				if (timeout != 0) return timeout;
			}
		}
		return Core::getIntProperty("Client3.LoginTimeout", 10);
	}

	static int getZoneTimeout() {
		Core* instance = Core::getCoreInstance();
		if (instance) {
			ClientCore* clientCore = static_cast<ClientCore*>(instance);
			if (clientCore) {
				int timeout = clientCore->options.get<int>("/zoneTimeout", 0);
				if (timeout != 0) return timeout;
			}
		}
		return Core::getIntProperty("Client3.ZoneTimeout", 30);
	}

public:
	ClientCore(const ClientCoreOptions& opts);

	void initialize();

	void run();

	void executeActions();

	void setVar(const String& key, const String& value) {
		vars.put(key, value);
	}

	String getVar(const String& key) const {
		return vars.contains(key) ? vars.get(key) : "";
	}

	String substituteVars(const String& input) const {
		String result = input;

		for (int i = 0; i < vars.size(); i++) {
			String key = vars.elementAt(i).getKey();
			String value = vars.elementAt(i).getValue();
			String pattern = "{" + key + "}";

			result = result.replaceAll(pattern, value);
		}

		return result;
	}

private:
	void saveStateToFile(const String& filename, class LoginSession* loginSession);
};

#endif /*CLIENTCORE_H_*/
