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

class ConfigManager : public Lua {

	bool makeLogin;
	bool makeZone;
	bool makePing;
	bool makeStatus;

	String orbNamingDirectoryAddress;

	String forumsdBHost;
	uint16 forumsdBPort;
	String forumsdBName;
	String forumsdBUser;
	String forumsdBPass;
	String forumsBannedGroupID;
	String forumsStandardGroupID;
	String forumsUserTable;
	String forumsBannedTable;
	String forumsNewActivationTable;

	String dBHost;
	uint16 dBPort;
	String dBName;
	String dBUser;
	String dBPass;

	uint16 statusPort;
	uint16 loginPort;
	uint16 pingPort;

	int loginAllowedConnections;
	bool autoReg;
	bool useVBIngeration;

	int zoneProcessingThreads;
	int zoneAllowedConnections;
	int zoneGalaxyID;

	int statusAllowedConnections;
	unsigned int statusInterval;

	int pingAllowedConnections;

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

		forumsdBHost = "127.0.0.1";
		forumsdBPort = 3306;
		forumsdBName = "swgemu";
		forumsdBUser = "root";
		forumsdBPass = "Gemeni1";
		forumsBannedGroupID = "8";
		forumsStandardGroupID = "2";
		forumsUserTable = "vb3_users";
		forumsBannedTable = "vb3_bannedusers";
		forumsNewActivationTable = "vb3_useractivation";
		useVBIngeration = 0;

		statusPort = 44455;

		pingPort = 44462;

		loginPort = 44453;
		loginAllowedConnections = 30;
		autoReg = true;

		zoneProcessingThreads = 10;
		zoneAllowedConnections = 300;
		zoneGalaxyID = 2;

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

	inline String& getForumsDBHost() {
		return forumsdBHost;
	}

	inline uint16& getForumsDBPort() {
		return forumsdBPort;
	}

	inline String& getForumsDBName() {
		return forumsdBName;
	}

	inline String& getForumsDBUser() {
		return forumsdBUser;
	}

	inline String& getForumsDBPass() {
		return forumsdBPass;
	}

	inline String& getForumsBannedGroup() {
		return forumsBannedGroupID;
	}

	inline String& getForumsStandardGroup() {
		return forumsStandardGroupID;
	}

	inline String& getForumsUserTable() {
		return forumsUserTable;
	}

	inline String& getForumsBannedTable() {
		return forumsBannedTable;
	}

	inline String& getForumsNewActivationTable() {
		return forumsNewActivationTable;
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

	inline int getUseVBIngeration() {
		return useVBIngeration ;
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

};

#endif // #ifndef CONFIGMANAGER_H_



