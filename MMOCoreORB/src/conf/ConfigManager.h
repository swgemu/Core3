/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "engine/engine.h"

namespace conf {
	class ConfigManager : public Singleton<ConfigManager>, public Lua {
		bool makeLogin;
		bool makeZone;
		bool makePing;
		bool makeStatus;
		bool makeWeb;
		bool dumpObjFiles;
		bool unloadContainers;
		bool useMetrics;
		bool pvpMode;

		String orbNamingDirectoryAddress;
		uint16 orbNamingDirectoryPort;

		String dBHost;
		uint16 dBPort;
		String dBName;
		String dBUser;
		String dBPass;
		String dBSecret;

		String mantisHost;
		uint16 mantisPort;
		String mantisName;
		String mantisUser;
		String mantisPass;
		String mantisPrfx;

		String trePath;

		uint16 statusPort;
		uint16 loginPort;
		uint16 pingPort;

		String webPorts;
		String webAccessLog;
		String webErrorLog;
		int webSessionTimeout;
		String revision;

		String metricsHost;
		String metricsPrefix;
		int metricsPort;

		int purgeDeletedCharacters;

		String loginRequiredVersion;
		int loginProcessingThreads;
		int loginAllowedConnections;
		bool autoReg;
		bool progressMonitors;

		int zoneProcessingThreads;
		int zoneAllowedConnections;
		int zoneGalaxyID;
		int zoneOnlineCharactersPerAccount;
		int zonePort;

		int statusAllowedConnections;
		unsigned int statusInterval;

		int pingAllowedConnections;

		int maxNavMeshJobs;

		String messageOfTheDay;

		Vector<String> treFiles;
		SortedVector<String> enabledZones;

		String logFile;
		int logFileLevel;

		String termsOfService;
		int tosVersion;

	public:

		ConfigManager();

		~ConfigManager() {
		}

		bool loadConfigFile() {
			return runFile("conf/config.lua");
		}

		bool loadConfigData();
		void loadMOTD();
		void loadRevision();
		void loadTreFileList();
		void loadEnabledZones();

		//getters

		inline bool getMakeLogin() const {
			return makeLogin;
		}

		inline bool getMakeZone() const {
			return makeZone;
		}

		inline bool getMakePing() const {
			return makePing;
		}

		inline bool getMakeStatus() const {
			return makeStatus;
		}

		inline bool getMakeWeb() const {
			return makeWeb;
		}

		inline bool getDumpObjFiles() const {
			return dumpObjFiles;
		}

		inline bool shouldUnloadContainers() const {
			return unloadContainers;
		}

		inline bool shouldUseMetrics() const {
			return useMetrics;
		}

		inline bool getPvpMode() const {
			return pvpMode;
		}

		inline const String& getORBNamingDirectoryAddress() const {
			return orbNamingDirectoryAddress;
		}

		inline uint16 getORBNamingDirectoryPort() const {
			return orbNamingDirectoryPort;
		}

		inline const String& getDBHost() const {
			return dBHost;
		}

		inline bool isProgressMonitorActivated() {
			return progressMonitors;
		}

		inline const uint16& getDBPort() const {
			return dBPort;
		}

		inline const String& getDBName() const {
			return dBName;
		}

		inline const String& getDBUser() const {
			return dBUser;
		}

		inline const String& getDBPass() const {
			return dBPass;
		}

		inline const String& getDBSecret() const {
			return dBSecret;
		}

		inline const String& getMantisHost() const {
			return mantisHost;
		}

		inline const uint16& getMantisPort() const {
			return mantisPort;
		}

		inline const Vector<String>& getTreFiles() const {
			return treFiles;
		}

		inline const String& getMantisName() const {
			return mantisName;
		}

		inline const String& getMantisUser() const {
			return mantisUser;
		}

		inline const String& getMantisPass() const {
			return mantisPass;
		}

		inline const String& getMantisPrefix() const {
			return mantisPrfx;
		}

		inline const String& getMessageOfTheDay() const {
			return messageOfTheDay;
		}

		inline const String& getRevision() const {
			return revision;
		}

		inline const String& getMetricsHost() const {
			return metricsHost;
		}

		inline const String& getMetricsPrefix() const {
			return metricsPrefix;
		}

		inline int getMetricsPort() const {
			return metricsPort;
		}

		inline const String& getTrePath() const {
			return trePath;
		}

		inline uint16 getLoginPort() const {
			return loginPort;
		}

		inline uint16 getStatusPort() const {
			return statusPort;
		}

		inline uint16 getPingPort() const {
			return pingPort;
		}

		inline const String& getWebPorts() const {
			return webPorts;
		}

		inline const String& getWebAccessLog() const {
			return webAccessLog;
		}

		inline const String& getWebErrorLog() const {
			return webErrorLog;
		}

		inline int getWebSessionTimeout() const {
			return webSessionTimeout;
		}

		inline const String& getLoginRequiredVersion() const {
			return loginRequiredVersion;
		}

		inline int getLoginProcessingThreads() const {
			return loginProcessingThreads;
		}

		inline int getLoginAllowedConnections() const {
			return loginAllowedConnections;
		}

		inline int getStatusAllowedConnections() const {
			return statusAllowedConnections;
		}

		inline int getPingAllowedConnections() const {
			return pingAllowedConnections;
		}

		inline int getStatusInterval() const {
			return statusInterval;
		}

		inline int getAutoReg() const {
			return autoReg;
		}

		inline int getZoneProcessingThreads() const {
			return zoneProcessingThreads;
		}

		inline int getZoneAllowedConnections() const {
			return zoneAllowedConnections;
		}

		inline int getZoneGalaxyID() const {
			return zoneGalaxyID;
		}

		inline int getZoneOnlineCharactersPerAccount() const {
			return zoneOnlineCharactersPerAccount;
		}

		inline int getZoneServerPort() const {
			return zonePort;
		}

		const SortedVector<String>* getEnabledZones() const {
			return &enabledZones;
		}

		inline int getPurgeDeletedCharacters() const {
			return purgeDeletedCharacters;
		}

		inline int getMaxNavMeshJobs() const {
			return maxNavMeshJobs;
		}

		inline const String& getLogFile() const {
			return logFile;
		}

		inline int getLogFileLevel() const {
			return logFileLevel;
		}

		inline void setProgressMonitors(bool val) {
			progressMonitors = val;
		}

		inline const String& getTermsOfService() const {
			return termsOfService;
		}

		inline int getTermsOfServiceVersion() const {
			return tosVersion;
		}
	};
}


using namespace conf;

#endif // #ifndef CONFIGMANAGER_H_



