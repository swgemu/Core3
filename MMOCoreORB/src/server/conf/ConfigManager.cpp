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
	LuaObject files = getGlobalObject("TreFiles");

	for (int i = 1; i <= files.getTableSize(); ++i) {
		treFiles.add(files.getStringAt(i));
	}

	files.pop();
}

void ConfigManager::loadEnabledZones() {
	LuaObject zones = getGlobalObject("ZonesEnabled");

	for (int i = 1; i <= zones.getTableSize(); ++i)
		enabledZones.put(zones.getStringAt(i));

	zones.pop();
}

void ConfigManager::loadMOTD() {
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
