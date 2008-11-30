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

#include "../../ZoneServerImplementation.h"

#include "GuildImplementation.h"
#include "../../managers/guild/GuildManager.h"
#include "../../managers/guild/GuildMap.h"

#include "../../../chat/ChatManager.h"

#include "../player/Player.h"

#include "../../managers/player/PlayerMap.h"

#include "../../packets.h"


class ZoneServer;
class ZoneProcessServerImplementation;

GuildImplementation::GuildImplementation(uint32 gid, const String& name, const String& tag) : GuildServant() {
	guildID = gid;

	guildName = name;
	guildTag = tag;

	guildManager = NULL;

	guildChannel = NULL;

	guildLeader = 0;
}

void GuildImplementation::sendGuildListTo(Player* player, bool doLock) {
	SceneObjectCreateMessage* socm = new SceneObjectCreateMessage(0xDEADBABE, 0x7D40E2E6);
	player->sendMessage(socm);

	guildManager->lock(doLock);

	GuildMap* guildMap = guildManager->getGuildMap();

	GuildObjectMessage3* gild3 = new GuildObjectMessage3(0xDEADBABE);

	for (int i = 0; i < guildMap->size(); ++i) {
		Guild* guild = guildMap->get(i);
		gild3->addListMember(guild->getGuildID(), guild->getGuildTag());
	}

	gild3->addListSize(64, guildMap->size());
	gild3->finishGild();

	guildManager->unlock(doLock);

	player->sendMessage(gild3);

	GuildObjectMessage6* gild6 = new GuildObjectMessage6(0xDEADBABE);
	player->sendMessage(gild6);

	SceneObjectCloseMessage* soclm = new SceneObjectCloseMessage(0xDEADBABE);
	player->sendMessage(soclm);

}

void GuildImplementation::updateGuildFor(Player* player) {
	// TODO: add guild delta to udate this guild for player
}

void GuildImplementation::deleteGuildFor(Player* player) {
	// TODO: add guild delta to remove this guild for player
}

