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

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "../../db/ServerDatabase.h"
#include "../../db/ForumsDatabase.h"

#include "../LoginClient.h"
#include "../objects.h"

#include "CharacterList.h"

#include "../../conf/ConfigManager.h"

class LoginServer;

class Account {
	String username;
	String password;
	String version;

	uint32 stationID;
	uint32 accountID;

public:
	Account(Packet* pack) {
		AccountVersionMessage::parse(pack, username, password, version);

		Database::escapeString(username);
		Database::escapeString(password);
	}

	//Checks for publish 14 clients. To disable: have the function return true all the time.
	//Disabling Version check could be hazardous in game.
	inline bool checkVersion() {
		if (version == "20050408-18:00")
			return true;

		return false;
	}

	/**
	 * Attempts to verify that an account is valid, and exists.
	 * If auto creation is enabled, and the account fails to authenticate, it will attempt to create it.
	 * @param configManager The configuration manager containing information about how accounts are handled by the server.
	 * @param client The client attempting to login. Any error messages will be sent to this client.
	 * @return Returns true if validation succeeds and the user has permission to continue logging in.
	 */
	bool validate(ConfigManager* configManager, LoginClient* client);

	bool create(ConfigManager* configManager, LoginClient* client);

	void login(LoginClient* client, LoginServer* loginServer);

	/**
	 * Sends an error message to the client attempting to login to the server.
	 * @param client The LoginClient attempting to login.
	 * @param title The title for the message box that appears.
	 * @param msg The message to be displayed in the message box.
	 * @param fatal [optional] Should the message cause the client to close on a fatal error. Defaults to false.
	 */
	void sendErrorMessageTo(LoginClient* client, const String& title, const String& msg, bool fatal = false) {
		ErrorMessage* errmsg = new ErrorMessage(title, msg, (byte) fatal);
		client->sendMessage(errmsg);
	}

	/**
	 * Sends a message containing information about a ban to the client.
	 * @param client The client that will receive the information about the ban.
	 * @param banID The ban id of the ban to send information about.
	 */
	void sendBanMessageTo(LoginClient* client, uint32 banID);

	friend class AccountVersionMessage;
};

#endif /*ACCOUNT_H_*/
