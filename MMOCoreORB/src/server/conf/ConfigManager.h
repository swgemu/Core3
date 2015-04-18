/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "engine/engine.h"

namespace server {
	namespace conf {

		class ConfigManager : public Singleton<ConfigManager>, public Lua {

			bool makeLogin;
			bool makeZone;
			bool makePing;
			bool makeStatus;
			bool makeWeb;

			String orbNamingDirectoryAddress;

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

			int statusAllowedConnections;
			unsigned int statusInterval;

			int pingAllowedConnections;

			String messageOfTheDay;

			Vector<String> treFiles;
			SortedVector<String> enabledZones;

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

			inline bool getMakeLogin() {
				return makeLogin;
			}

			inline bool getMakeZone() {
				return makeZone;
			}

			inline bool getMakePing() {
				return makePing;
			}

			inline bool getMakeStatus() {
				return makeStatus;
			}

			inline bool getMakeWeb() {
				return makeWeb;
			}

			inline String& getORBNamingDirectoryAddress() {
				return orbNamingDirectoryAddress;
			}

			inline String& getDBHost() {
				return dBHost;
			}

			inline bool isProgressMonitorActivated() {
				return progressMonitors;
			}

			inline uint16& getDBPort() {
				return dBPort;
			}

			inline String& getDBName() {
				return dBName;
			}

			inline String& getDBUser() {
				return dBUser;
			}

			inline String& getDBPass() {
				return dBPass;
			}

			inline String& getDBSecret() {
				return dBSecret;
			}

			inline String& getMantisHost() {
				return mantisHost;
			}

			inline uint16& getMantisPort() {
				return mantisPort;
			}

			inline Vector<String>& getTreFiles() {
				return treFiles;
			}

			inline String& getMantisName() {
				return mantisName;
			}

			inline String& getMantisUser() {
				return mantisUser;
			}

			inline String& getMantisPass() {
				return mantisPass;
			}

			inline String& getMantisPrefix() {
				return mantisPrfx;
			}

			inline String& getMessageOfTheDay() {
				return messageOfTheDay;
			}

			inline String& getRevision() {
				return revision;
			}

			inline String& getTrePath() {
				return trePath;
			}

			inline uint16 getLoginPort() {
				return loginPort;
			}

			inline uint16 getStatusPort() {
				return statusPort;
			}

			inline uint16 getPingPort() {
				return pingPort;
			}

			inline String getWebPorts() {
				return webPorts;
			}

			inline String getWebAccessLog() {
				return webAccessLog;
			}

			inline String getWebErrorLog() {
				return webErrorLog;
			}

			inline int getWebSessionTimeout() {
				return webSessionTimeout;
			}

			inline String& getLoginRequiredVersion() {
				return loginRequiredVersion;
			}

			inline int getLoginProcessingThreads() {
				return loginProcessingThreads;
			}

			inline int getLoginAllowedConnections() {
				return loginAllowedConnections;
			}

			inline int getStatusAllowedConnections() {
				return statusAllowedConnections;
			}

			inline int getPingAllowedConnections() {
				return pingAllowedConnections;
			}

			inline int getStatusInterval() {
				return statusInterval;
			}

			inline int getAutoReg() {
				return autoReg;
			}

			inline int getZoneProcessingThreads() {
				return zoneProcessingThreads;
			}

			inline int getZoneAllowedConnections() {
				return zoneAllowedConnections;
			}

			inline int getZoneGalaxyID() {
				return zoneGalaxyID;
			}

			inline int getZoneOnlineCharactersPerAccount() {
				return zoneOnlineCharactersPerAccount;
			}

			SortedVector<String>* getEnabledZones() {
				return &enabledZones;
			}

			inline int getPurgeDeletedCharacters() {
				return purgeDeletedCharacters;
			}

			inline void setProgressMonitors(bool val) {
				progressMonitors = val;
			}
		};
	}
}

using namespace server::conf;

#endif // #ifndef CONFIGMANAGER_H_



