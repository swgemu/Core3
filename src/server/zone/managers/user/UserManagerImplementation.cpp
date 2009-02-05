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

#include <iostream>
#include <fstream>

#include "UserManagerImplementation.h"

#include "../../objects/player/Player.h"

#include "../../ZoneServer.h"
#include "../../ZoneClientSession.h"
#include "../player/PlayerManager.h"

#include "../../../login/packets/ErrorMessage.h"

UserManagerImplementation::UserManagerImplementation(ZoneServer* serv) : UserManagerServant(), Logger("UserManager") {
	server = serv;

	userCap = 400;

	adminUsers = new AdminSet();

	parseBanList();

	parseAdminList();

	setLogging(false);
}

UserManagerImplementation::~UserManagerImplementation() {
	delete adminUsers;
	adminUsers = NULL;
}

void UserManagerImplementation::parseBanList() {
	File* banFile = new File("bannedusers.lst");

	try {
		FileReader banReader(banFile);

		info("parsing ban list: bannedusers.lst", true);

		String line;

		while (banReader.readLine(line)) {
			StringTokenizer tokenizer(line);

			String ip;
			tokenizer.getStringToken(ip);

			if (!ip.isEmpty())
				banUser(ip);
		}

		banFile->close();
	} catch (FileNotFoundException& e) {
	}

	delete banFile;
}

void UserManagerImplementation::parseAdminList() {
	File* adminFile = new File("adminusers.lst");

	try {
		FileReader adminReader(adminFile);

		info("parsing admin list: adminusers.lst", true);

		String line;

		while (adminReader.readLine(line)) {
			StringTokenizer tokenizer(line);

			String name;
			tokenizer.getStringToken(name);

			name = name.trim().toLowerCase();

			if (!name.isEmpty())
				grantAdmin(name);
		}

		adminFile->close();
	} catch (FileNotFoundException& e) {
	}

	delete adminFile;
}

bool UserManagerImplementation::checkUser(uint32 ipid) {
	/*String ip = addr->getFullIPAddress();
	if (ip.substr(0, 12) != "80.99.84.166")
		return false;*/

	//uint32 ipid = addr->getIPID();
	if (server->getConnectionCount() > userCap || isBannedUser(ipid)) {
		info("restricting user from logging in");

		return false;
	} else
		return true;
}

void UserManagerImplementation::grantAdmin(const String& name) {
	adminUsers->add(name.toLowerCase());
}

bool UserManagerImplementation::isAdmin(const String& name) {
	return adminUsers->contains(name.toLowerCase());
}

void UserManagerImplementation::banUser(const String& ipaddr) {
	try {
		SocketAddress addr(ipaddr, 0);

		uint32 ipid = addr.getIPID();
		bannedClients.add(ipid);
	} catch (Exception& e) {
		error("on ban: " + e.getMessage());
	}
}

bool UserManagerImplementation::banUserByName(String& name, String& admin) {
	PlayerManager* playerManager = server->getPlayerManager();

	name = name.toLowerCase();

	Player* player = playerManager->getPlayer(name);

	if (player != NULL) {
		ZoneClientSession* client = player->getClient();
		if (client == NULL)
			return false;

		//String ip = client->getIPAddress();
		String ip = client->getAddress();
		ip = ip.subString(0, ip.indexOf(":"));

		banUser(ip);

		server->unlock();

		client->disconnect();

		server->lock();

		String line = ip + " // " + name + " (" + admin + ")\n";

		File* banFile = new File("bannedusers.lst");

		try {
			FileWriter banWriter(banFile);

			banWriter.writeLine(line);

			banFile->close();

			info("user \'" + name + "\' banned", true);

			delete banFile;
		} catch (FileNotFoundException& e) {
			delete banFile;

			return false;
		}

		return true;
	} else {
		info("unable to ban user \'" + name + "\'", true);

		return false;
	}
}

bool UserManagerImplementation::kickUser(String& name, String& admin) {
	PlayerManager* playerManager = server->getPlayerManager();

	name = name.toLowerCase();

	Player* player = playerManager->getPlayer(name);

	if (player != NULL) {
		ZoneClientSession* client = player->getClient();
		if (client == NULL)
			return false;

		player->explode(1);

		ErrorMessage* errMsg = new ErrorMessage(admin.toCharArray(), "You were disconnected from the server. "
				"Don't log in before sorting out the issue with an admin on the forums "
				"or (better) IRC to avoid getting a perma-ban.", 0);
		player->sendMessage(errMsg);

		Thread::sleep(250);

		server->unlock();

		client->disconnect();

		server->lock();

		info("user \'" + name + "\' kicked by \'" + admin + "\'" , true);

		return true;
	} else {
		info("unable to kick user \'" + name + "\'", true);

		return false;
	}
}

void UserManagerImplementation::changeUserCap(int amount) {
	userCap += amount;

	StringBuffer msg;
	msg << dec << "cap raised to " << userCap << "\n";
	info(msg, true);
}
