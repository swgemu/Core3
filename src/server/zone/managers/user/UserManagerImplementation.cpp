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

	userCap = 200;

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
	ifstream banFile("bannedusers.lst");

	if (!banFile)
		return;
	else
		info("parsing ban list: bannedusers.lst", true);

 	char line[100];

	while (banFile.getline(line, 100)) {
		StringTokenizer tokenizer(line);

		string ip;
		tokenizer.getStringToken(ip);

		if (ip.size() > 0)
			banUser(ip);
	}

	banFile.close();
}

void UserManagerImplementation::parseAdminList() {
	ifstream adminFile("adminusers.lst");

	if (!adminFile)
		return;
	else
		info("parsing admin list: adminusers.lst", true);

 	char line[100];

	while (adminFile.getline(line, 100)) {
		StringTokenizer tokenizer(line);

		string name;
		tokenizer.getStringToken(name);

		String::toLower(name);

		//trim whitespace
			int swhite = name.find_first_not_of(" \t\n\r\f");
			int ewhite = name.find_last_not_of(" \t\n\r\f");

			if (swhite == string::npos)
				name = "";
			else
				name = name.substr(swhite, ewhite - swhite + 1);

		if (name.size() > 0)
			grantAdmin(name);
	}

	adminFile.close();
}

bool UserManagerImplementation::checkUser(uint32 ipid) {
	/*string ip = addr->getFullIPAddress();
	if (ip.substr(0, 12) != "80.99.84.166")
		return false;*/

	//uint32 ipid = addr->getIPID();
	if (server->getConnectionCount() > userCap || isBannedUser(ipid)) {
		info("restricting user from logging in");

		return false;
	} else
		return true;
}

void UserManagerImplementation::grantAdmin(const string& n) {
	string name = n;
	String::toLower(name);
	adminUsers->add(name);
}

bool UserManagerImplementation::isAdmin(const string& n) {
	string name = n;
	String::toLower(name);
	return adminUsers->contains(name);
}

void UserManagerImplementation::banUser(const string& ipaddr) {
	try {
		SocketAddress addr(ipaddr, 0);

		uint32 ipid = addr.getIPID();
		bannedClients.add(ipid);
	} catch (Exception& e) {
		error("on ban: " + e.getMessage());
	}
}

bool UserManagerImplementation::banUserByName(string& name, string& admin) {
	PlayerManager* playerManager = server->getPlayerManager();

	String::toLower(name);
	Player* player = playerManager->getPlayer(name);

	if (player != NULL) {
		ZoneClientSession* client = player->getClient();
		if (client == NULL)
			return false;

		//string ip = client->getIPAddress();
		string ip = client->getAddress();
		ip = ip.substr(0, ip.find(":"));

		banUser(ip);

		server->unlock();

		client->disconnect();

		server->lock();

		string line = ip + " // " + name + " (" + admin + ")\n";

		ofstream banFile;
		banFile.open("bannedusers.lst", ios::app);

		banFile.write(line.c_str(), line.size());
		banFile.close();

		info("user \'" + name + "\' banned", true);

		return true;
	} else {
		info("unable to ban user \'" + name + "\'", true);

		return false;
	}
}

bool UserManagerImplementation::kickUser(string& name, string& admin) {
	PlayerManager* playerManager = server->getPlayerManager();

	String::toLower(name);
	Player* player = playerManager->getPlayer(name);

	if (player != NULL) {
		ZoneClientSession* client = player->getClient();
		if (client == NULL)
			return false;

		player->explode(1);

		ErrorMessage* errMsg = new ErrorMessage(admin.c_str(), "You were disconnected from the server. "
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

	stringstream msg;
	msg << dec << "cap raised to " << userCap << "\n";
	info(msg, true);
}
