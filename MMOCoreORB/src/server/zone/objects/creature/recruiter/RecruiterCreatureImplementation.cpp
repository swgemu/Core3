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

#include "RecruiterCreatureImplementation.h"

#include "../CreatureImplementation.h"

#include "../../player/Player.h"
#include "../../player/PlayerImplementation.h"

#include "../../player/events/ChangeFactionEvent.h"

#include "../../../packets.h"

#include "../../../packets/object/StringList.h"

RecruiterCreatureImplementation::RecruiterCreatureImplementation(uint64 oid) : RecruiterCreatureServant(oid) {
	setType(CreatureImplementation::RECRUITER);

	creatureBitmask = 0x108;

	stringstream loggingname;
	loggingname << "Recruiter = 0x" << oid;
	setLoggingName(loggingname.str());

	stfName = "mob/creature_names";

	setLogging(false);
	setGlobalLogging(true);
}

void RecruiterCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	Player* player = (Player*)obj;

	if (player->getFaction() == enemyFactionCRC) {
		greetEnemy();
		return;
	} else if (player->getFactionPoints(factionString) < -200) {
		greetHated();
		return;
	}

	StartNpcConversation* conv = new StartNpcConversation(player, objectID, "");
	player->sendMessage(conv);
	player->setLastNpcConvStr("recruiter");

	if (player->getFaction() == factionCRC)
		sendMemberStart(player);
	else
		sendNeutralStart(player);
}

void RecruiterCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*)obj;

	if(player->getLastNpcConvStr() != "recruiter") {
		sendConversationStartTo(player);
		return;
	}

	if (player->getLastNpcConvMessStr() == "neutral_start") {
		switch (option) {
		case 0:
			if (player->getFactionPoints(factionString) < 200)
				rejectJoinFaction(player);
			else
				confirmJoinFaction(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "confirm_join_faction") {
		switch (option) {
		case 0:
			addPlayerToFaction(player);
			playerAcceptedJoin(player);
			break;
		case 1:
			playerRejectedJoin(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "member_start") {
		switch (option) {
		case 0:
			confirmLeaveFaction(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "confirm_leave_faction") {
		switch (option) {
		case 0:
			removePlayerFromFaction(player);
			playerAcceptedLeave(player);
			break;
		case 1:
			playerRejectedLeave(player);
			break;
		}
	} else {
		player->sendMessage(new StopNpcConversation(player, getObjectID()));
	}

}

void RecruiterCreatureImplementation::addPlayerToFaction(Player * player) {
	player->setFaction(factionCRC);
	player->setOvert();
	player->makeCharacterMask();
}

void RecruiterCreatureImplementation::removePlayerFromFaction(Player * player) {
	player->setFaction(0);
	player->setCovert();
	player->makeCharacterMask();
}
