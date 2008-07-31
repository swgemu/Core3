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

#include "../../ZoneServer.h"

#include "../player/PlayerManager.h"

#include "../../objects/guild/Guild.h"
#include "../../objects/guild/GuildImplementation.h"

#include "GuildManagerImplementation.h"

#include "../../objects/player/Player.h"

#include "../player/PlayerMap.h"

GuildManagerImplementation::GuildManagerImplementation(ZoneServer* serv) : GuildManagerServant(), Mutex("GuildManager") {
	server = serv;

	playerManager = server->getPlayerManager();

	guilds = new GuildMap();
	guilds->deploy("GuildMap");

}

GuildManagerImplementation::~GuildManagerImplementation() {
	removeGuilds();

	guilds->finalize();
	guilds = NULL;
}

void GuildManagerImplementation::load() {
	lock();

	ResultSet* guildList;

	stringstream query;
	query << "SELECT * FROM guilds";

	guildList = ServerDatabase::instance()->executeQuery(query);

	while (guildList->next()) {
		uint32 gid = guildList->getInt(0);

		string tag = guildList->getString(1);
		string name = guildList->getString(2);

		Guild* guild = new Guild(gid, name, tag);

		guild->setGuildManager((GuildManager*) _this);

		guilds->add(guild);
	}

	delete guildList;

	Guild* defaultGuild = new Guild(0, "", "");

	defaultGuild->setGuildManager((GuildManager*) _this);

	guilds->add(defaultGuild);

	unlock();
}

bool GuildManagerImplementation::createGuild(string& tag, string& name) {
	lock();

	if (getGuild(tag, false) != NULL) {
		unlock();
		return false;
	}

	uint32 gid;

	try {
		string tagString = tag;
		MySqlDatabase::escapeString(tagString);

		string nameString = name;
		MySqlDatabase::escapeString(nameString);

		stringstream query;
	    query << "INSERT INTO `guilds` "
	          << "(`guild_tag`,`guild_name`)"
		      << "VALUES ('" << tagString << "','" << nameString << "');" ;

		ResultSet* resins = ServerDatabase::instance()->executeQuery(query);

		gid = resins->getLastAffectedRow();

		delete resins;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";

		unlock();
		return false;
	}

	Guild* guild = new Guild(gid, name, tag);

	guild->setGuildManager((GuildManager*) _this);

	guilds->add(guild);

	server->lock();

	PlayerMap* players = playerManager->getPlayerMap();
	players->lock();

	players->resetIterator(false);

	while (players->hasNext(false)) {
		Player* player = players->getNextValue(false);

		guild->sendGuildListTo(player, false);
	}

	players->unlock();

	server->unlock();

	unlock();
	return true;
}

Guild* GuildManagerImplementation::getGuild(string& tag, bool doLock) {
	lock(doLock);

	Guild* guild = guilds->get(tag);

	unlock(doLock);
	return guild;
}

Guild* GuildManagerImplementation::getGuild(uint32 gid, bool doLock) {
	lock(doLock);

	Guild* guild = guilds->get(gid);

	unlock(doLock);
	return guild;
}

bool GuildManagerImplementation::removeGuild(string& tag) {
	lock();

	Guild* guild = guilds->get(tag);
	if (guild == NULL) {
		unlock();
		return false;
	}

	bool res = removeGuild(guild->getGuildID(), false);

	unlock();
	return res;
}

bool GuildManagerImplementation::removeGuild(int gid, bool doLock) {
	lock(doLock);

	if (gid == 0 || getGuild(gid, false) == NULL) {
		unlock(doLock);
		return false;
	}

	removePlayersFromGuild(gid);

	try {
		stringstream query;
		query << "DELETE FROM guilds WHERE guild_id = '" << gid <<"';";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";

		unlock(doLock);
		return false;
	}

	guilds->remove(gid);

	unlock(doLock);
	return true;
}

void GuildManagerImplementation::removeGuilds() {
	for (int i = 0; i < guilds->size(); ++i) {
		Guild* guild = guilds->get(i);
		guild->finalize();
	}

	guilds->removeAll();
}

void GuildManagerImplementation::removePlayersFromGuild(int gid) {
	server->lock();

	PlayerMap* players = playerManager->getPlayerMap();

	players->lock();

	players->resetIterator(false);

	while (players->hasNext(false)) {
		Player* player = players->getNextValue(false);

		if (player->getGuildID() == gid)
			player->updateGuild(defaultGuild);
	}

	players->unlock();

	server->unlock();
}
