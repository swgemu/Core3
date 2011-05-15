/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "engine/engine.h"

namespace server {
	namespace conf {

		class ConfigManager : public Singleton<ConfigManager>, public Lua, public Object {

			bool makeLogin;
			bool makeZone;
			bool makePing;
			bool makeStatus;

			String orbNamingDirectoryAddress;

			String dBHost;
			uint16 dBPort;
			String dBName;
			String dBUser;
			String dBPass;

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

			String loginRequiredVersion;
			int loginProcessingThreads;
			int loginAllowedConnections;
			bool autoReg;

			int zoneProcessingThreads;
			int zoneAllowedConnections;
			int zoneGalaxyID;
			int zoneOnlineCharactersPerAccount;

			int statusAllowedConnections;
			unsigned int statusInterval;

			int pingAllowedConnections;

			String messageOfTheDay;

			Vector<String> treFiles;

		public:

			ConfigManager() {
				makeLogin = true;
				makeZone = true;
				makePing = true;
				makeStatus = true;

				orbNamingDirectoryAddress = "";

				dBHost = "127.0.0.1";
				dBPort = 3306;
				dBName = "swgemu";
				dBUser = "root";
				dBPass = "Gemeni1";

				mantisHost = "127.0.0.1";
				mantisPort = 3306;
				mantisName = "swgemu";
				mantisUser = "root";
				mantisPass = "Gemeni1";

				statusPort = 44455;

				pingPort = 44462;

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
			}

			~ConfigManager() {
			}

			bool loadConfigFile() {
				return runFile("conf/config.lua");
			}

			bool loadConfigData();
			void loadMOTD();
			void loadTreFileList();

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

			inline String& getORBNamingDirectoryAddress() {
				return orbNamingDirectoryAddress;
			}

			inline String& getDBHost() {
				return dBHost;
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

		};
	}
}

using namespace server::conf;

#endif // #ifndef CONFIGMANAGER_H_



