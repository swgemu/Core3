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

#include "../../../packets.h"

#include "../../../packets/object/StringList.h"

RecruiterCreatureImplementation::RecruiterCreatureImplementation(uint64 oid) : RecruiterCreatureServant(oid) {
	setType(CreatureImplementation::RECRUITER);
	setCreatureType("NPC");

	optionsBitmask = 0x108;

	StringBuffer loggingname;
	loggingname << "Recruiter = 0x" << oid;
	setLoggingName(loggingname.toString());

	templateTypeName = "mob/creature_names";

	setLogging(false);
	setGlobalLogging(true);
}

void RecruiterCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	Player* player = (Player*)obj;

	if (player->getFaction() == enemyFactionCRC) {
		updateTarget(player);
		greetEnemy();
		return;
	} else if (player->getFactionPoints(factionString) < -200) {
		updateTarget(player);
		greetHated();
		return;
	} else if (player->isChangingFactionStatus()) {
		updateTarget(player);
		greetChangingStatusMember();
		return;
	}

	StartNpcConversation* conv = new StartNpcConversation(player, objectID, "");
	player->sendMessage(conv);
	player->setLastNpcConvStr("recruiter");

	if (player->getFaction() == factionCRC) {
		if (player->isOnLeave())
			sendOnLeaveStart(player);
		else
			greetMember(player);
	} else
		sendNeutralStart(player);
}

void RecruiterCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*)obj;

	if (player->getLastNpcConvStr() != "recruiter") {
		sendConversationStartTo(player);
		return;
	}

	if (player->getLastNpcConvMessStr() == "neutral_start") {
		switch (option) {
		case 0:
			if (player->getFactionPoints(factionString) < MINFACTIONSTANDING)
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
	} else if (player->getLastNpcConvMessStr() == "onLeave_start") {
		switch (option) {
		case 0:
			confirmGoActive(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "confirm_go_active") {
		switch (option) {
		case 0:
			setPlayerCovert(player, 30000);
			playerAcceptedGoActive(player);
			break;
		case 1:
			playerRejectedGoActive(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "confirm_go_covert") {
		switch (option) {
		case 0:
			setPlayerCovert(player, 300000);
			playerAcceptedGoCovert(player);
			break;
		case 1:
			playerRejectedGoCovert(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "confirm_go_overt") {
		switch (option) {
		case 0:
			setPlayerOvert(player, 30000);
			playerAcceptedGoOvert(player);
			break;
		case 1:
			playerRejectedGoOvert(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "confirm_go_on_leave") {
		switch (option) {
		case 0:
			setPlayerOnLeave(player, 300000);
			playerAcceptedGoOnLeave(player);
			break;
		case 1:
			playerRejectedGoOnLeave(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "member_start") {
		if (qualifiesForPromotion(player)) {
			if (option == 0) {
				confirmPromotion(player);
				return;
			} else
				option--;
		}

		if (canOfferBribe(player)) {
			if (option == 0) {
				confirmBribe(player);
				return;
			} else
				option--;
		}

		switch (option) {
		case 0:
			if (player->isCovert())
				confirmGoOvert(player);
			else
				confirmGoCovert(player);
			break;
		case 1:
			confirmGoOnLeave(player);
			break;
		case 2:
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
	} else if (player->getLastNpcConvMessStr() == "confirm_promotion") {
		switch (option) {
		case 0:
			promotePlayer(player);
			playerAcceptedPromotion(player);
			break;
		case 1:
			playerRejectedPromotion(player);
			break;
		}
	} else if (player->getLastNpcConvMessStr() == "confirm_bribe") {
		playerAcceptedBribe(player);

		switch (option) {
		case 0:
			grantBribe(player, 20000, 250);
			break;
		case 1:
			grantBribe(player, 100000, 1250);
			break;
		}
	} else {
		player->sendMessage(new StopNpcConversation(player, getObjectID()));
	}

}

void RecruiterCreatureImplementation::addPlayerToFaction(Player * player) {
	player->setFaction(factionCRC);
	player->setCovert();
	player->makeCharacterMask();
}

void RecruiterCreatureImplementation::removePlayerFromFaction(Player * player) {
	player->setFaction(0);
	player->setOnLeave();
	player->makeCharacterMask();
	player->setFactionRank(0);
}

void RecruiterCreatureImplementation::setPlayerOnLeave(Player * player, uint32 timer) {
	player->newChangeFactionStatusEvent(0, timer);
}

void RecruiterCreatureImplementation::setPlayerCovert(Player * player, uint32 timer) {
	player->newChangeFactionStatusEvent(1, timer);
}

void RecruiterCreatureImplementation::setPlayerOvert(Player * player, uint32 timer) {
	player->newChangeFactionStatusEvent(2, timer);
}

void RecruiterCreatureImplementation::promotePlayer(Player * player) {
	uint8 rank = player->getFactionRank() + 1;
	player->setFactionRank(rank);
	player->subtractFactionPoints(factionString, FactionRankTable::getRequiredPoints(rank));
}

void RecruiterCreatureImplementation::grantBribe(Player * player, uint32 cost, uint32 fp) {
	if (player->getCashCredits() < cost)
		return;

	player->subtractCashCredits(cost);
	player->addFactionPoints(factionString, fp);
}
