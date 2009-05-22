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

#include "IgnoreListImplementation.h"

#include "Player.h"
#include "PlayerObject.h"

#include "../../packets/player/AddIgnoreMessage.h"
#include "../../packets/player/IgnoreListMessage.h"
#include "../../packets/player/PlayerObjectDeltaMessage9.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "../../objects/terrain/PlanetNames.h"

#include "../../managers/player/PlayerManager.h"

#include "../waypoint/WaypointObject.h"
#include "../../managers/object/ObjectManager.h"

IgnoreListImplementation::IgnoreListImplementation(Player* pl) : IgnoreListServant() {
	player = pl;
	ignoreMagicNumber = 0;
}

void IgnoreListImplementation::addIgnore(String& name, String& server) {
	PlayerObject* playerObject = player->getPlayerObject();
	int magicnumber = ignoreMagicNumber;

	name = name.toLowerCase();

	for (int i = 0; i < ignoreName.size(); ++i) {
		if (ignoreName.get(i) == name) {
			StringBuffer ignoreString;
			ignoreString << "You are already ignoring " << name << ".";

			UnicodeString message = UnicodeString(ignoreString.toString());
			player->sendSystemMessage(message);
			return;
		}
	}

	try {
		StringBuffer query;
		String mysqlName = name;
		MySqlDatabase::escapeString(mysqlName);

		query << "SELECT * from `characters` where lower(`firstname`) = '" << mysqlName << "';";
		ResultSet* ignore = ServerDatabase::instance()->executeQuery(query);

		if (!ignore->next()) {
			StringBuffer ignoreString;
			ignoreString << name << " is not a valid name.";

			UnicodeString message = UnicodeString(ignoreString.toString());
			player->sendSystemMessage(message);

			delete ignore;
			return;
		}

		delete ignore;

	} catch (DatabaseException& e) {
		System::out << "IgnorelistImplementation void addIgnore -> Select DB Query exception! \n";
		return;
	} catch (...) {
		System::out << "unreported exception caught in IgnoreListImplementation::addIgnore(String& name, String& server)\n";
		return;
	}

	ignoreName.add(name);
	ignoreServer.add(server);

	ignoreMagicNumber = magicnumber + (ignoreName.size() +1);

	//toString();

	AddIgnoreMessage* add = new AddIgnoreMessage(player->getObjectID(),	name, server, true);
	player->sendMessage(add);

	Player* playerToAdd = player->getZone()->getZoneServer()->getPlayerManager()->getPlayer(name);

	StringBuffer ignoreString;
	ignoreString << name << " is now ignored.";
	UnicodeString message = UnicodeString(ignoreString.toString());
	player->sendSystemMessage(message);

	IgnoreListMessage* list = new IgnoreListMessage(player);
	player->sendMessage(list);

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
	dplay9->updateIgnoreList();
	dplay9->close();
	player->sendMessage(dplay9);
}

void IgnoreListImplementation::removeIgnore(String& name) {
	int i = 0;
	int magicnumber = ignoreMagicNumber;

	name = name.toLowerCase();

	PlayerObject* playerObject = player->getPlayerObject();

	for (int i = 0; i < ignoreName.size(); ++i) {
		if (ignoreName.get(i) == name) {
			String inServer = ignoreServer.get(i);

			ignoreName.remove(i);
			ignoreServer.remove(i);

			ignoreMagicNumber = magicnumber + (ignoreName.size() +1);

			//toString();

			AddIgnoreMessage* remove = new AddIgnoreMessage(player->getObjectID(),name, inServer, false);
			player->sendMessage(remove);

			StringBuffer ignoreString;
			ignoreString << name << " is no longer ignored.";
			UnicodeString message = UnicodeString(ignoreString.toString());
			player->sendSystemMessage(message);

			IgnoreListMessage* list = new IgnoreListMessage(player);
			player->sendMessage(list);

			PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
			dplay9->updateIgnoreList();
			dplay9->close();
			player->sendMessage(dplay9);

			break;
		}
	}
}

void IgnoreListImplementation::toString() {
	System::out << "Ignore List for " << player->getFirstName() << endl;
	System::out << "Number of Ignores = " << ignoreName.size() << endl;

	for (int i = 0; i < ignoreName.size(); ++i) {
		System::out << ignoreName.get(i) << " on " << ignoreServer.get(i) << ". Current magicnumber is " << ignoreMagicNumber << endl;
	}
}

void IgnoreListImplementation::loadIgnore() {
	int magicnumber;

	//Clean before loading! Some server functions (eg. reInserting a player) are using cached objects.
	// We dont want the ignorelist entries get doubled !
	ignoreMagicNumber = 0;
	ignoreName.removeAll();
	ignoreServer.removeAll();

	try {
		StringBuffer loadQuery;
		loadQuery << "SELECT ignorelist.character_id, ignorelist.ignore_id, ignorelist.ignore_galaxy, characters.firstname "
				  << "FROM ignorelist "
				  << "Inner Join characters ON ignorelist.ignore_id = characters.character_id "
				  << "WHERE ignorelist.character_id = " << player->getCharacterID() << ";";

		ResultSet* ignore = ServerDatabase::instance()->executeQuery(loadQuery);

		while (ignore->next()) {
			magicnumber = ignoreMagicNumber;

			String server = ignore->getString(2);
			String name = String(ignore->getString(3)).toLowerCase();

			ignoreName.add(name);
			ignoreServer.add(server);

			int newMagicNumber = magicnumber + (ignoreName.size() +1);
			ignoreMagicNumber = newMagicNumber;

			//toString();

			AddIgnoreMessage* add = new AddIgnoreMessage(player->getObjectID(),	name, server, true);
			player->sendMessage(add);

			Player* playerToAdd = player->getZone()->getZoneServer()->getPlayerManager()->getPlayer(name);

			IgnoreListMessage* list = new IgnoreListMessage(player);
			player->sendMessage(list);

			PlayerObject* playerObject = player->getPlayerObject();
			PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
			dplay9->updateIgnoreList();
			dplay9->close();
			player->sendMessage(dplay9);
		}

		delete ignore;
	} catch (DatabaseException& e) {
		System::out << "IgnorelistImplementation void loadIgnore -> Select DB Query exception! \n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in IgnoreListImplementation::loadIgnore()\n";
	}
}


void IgnoreListImplementation::saveIgnore() {
	try {
		StringBuffer deleteQuery;
		deleteQuery << "DELETE FROM ignorelist WHERE character_id = " << player->getCharacterID();

		ServerDatabase::instance()->executeStatement(deleteQuery);
	} catch (DatabaseException& e) {
		System::out << "IgnorelistImplementation void saveIgnore -> Delete from Ignorelist Query exception! \n";

		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "IgnorelistImplementation void saveIgnore -> Delete from Ignorelist Query exception! \n";
	}

	for (int i = 0; i < ignoreName.size(); ++i) {
		try {
			String lcaseName = ignoreName.get(i).toLowerCase();

			String mysqlName = lcaseName;
			MySqlDatabase::escapeString(mysqlName);

			StringBuffer query;
			query << "SELECT * FROM characters WHERE lower(firstname) = \"" + mysqlName + "\"";

			ResultSet* ignore = ServerDatabase::instance()->executeQuery(query);

			if (ignore->next()) {
				StringBuffer saveQuery;
				saveQuery << "INSERT INTO `ignorelist` "
						  << "(`character_id`,`ignore_id`,`ignore_galaxy`)"
						  << " VALUES ('"
						  << player->getCharacterID() << "','" << ignore->getUnsignedInt(0) << "','"
						  << ignore->getUnsignedInt(2) << "');";

				ServerDatabase::instance()->executeStatement(saveQuery);
			}

			delete ignore;
		} catch (DatabaseException& e) {
			System::out << "IgnorelistImplementation void saveIgnores -> Insert DB Query exception! \n";
			System::out << e.getMessage() << endl;
		} catch (...) {
			System::out << "unreported exception caught in IgnorelistImplementation void saveIgnores\n";
		}
	}
}
