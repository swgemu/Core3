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

#ifndef RECRUITERCREATUREIMPLEMENTATION_H_
#define RECRUITERCREATUREIMPLEMENTATION_H_

#include "engine/engine.h"

#include "RecruiterCreature.h"
#include "../../player/faction/FactionRankTable.h"
#include "../../player/Player.h"

class SceneObject;



class RecruiterCreatureImplementation : public RecruiterCreatureServant {
public:
	static const uint8 IMPERIAL = 1;
	static const uint8 REBEL = 2;
	static const uint8 MINFACTIONSTANDING = 0; //TEMPORARY!!!

protected:
	uint64 factionCRC;
	uint64 enemyFactionCRC;
	uint8 recruiterType;
	String factionString;

	virtual void greetEnemy() { };
	virtual void greetHated() { };
	virtual void greetChangingStatusMember() { };
	virtual void greetMember(Player * player) { };
	virtual void sendMemberStart(Player * player) { };
	virtual void sendNeutralStart(Player * player) { };
	virtual void sendOnLeaveStart(Player * player) { };
	virtual void rejectJoinFaction(Player * player) { };
	virtual void confirmJoinFaction(Player * player) { };
	virtual void playerAcceptedJoin(Player * player) { };
	virtual void playerRejectedJoin(Player * player) { };
	virtual void confirmGoCovert(Player * player) { };
	virtual void playerAcceptedGoCovert(Player * player) { };
	virtual void playerRejectedGoCovert(Player * player) { };
	virtual void confirmGoOvert(Player * player) { };
	virtual void playerAcceptedGoOvert(Player * player) { };
	virtual void playerRejectedGoOvert(Player * player) { };
	virtual void confirmGoOnLeave(Player * player) { };
	virtual void playerAcceptedGoOnLeave(Player * player) { };
	virtual void playerRejectedGoOnLeave(Player * player) { };
	virtual void confirmGoActive(Player * player) { };
	virtual void playerAcceptedGoActive(Player * player) { };
	virtual void playerRejectedGoActive(Player * player) { };
	virtual void confirmLeaveFaction(Player * player) { };
	virtual void playerAcceptedLeave(Player * player) { };
	virtual void playerRejectedLeave(Player * player) { };
	virtual void confirmPromotion(Player * player) { };
	virtual void playerAcceptedPromotion(Player * player) { };
	virtual void playerRejectedPromotion(Player * player) { };
	virtual void confirmBribe(Player * player) { };
	virtual void playerAcceptedBribe(Player * player) { };

private:
	void addPlayerToFaction(Player * player);
	void removePlayerFromFaction(Player * player);
	void setPlayerOnLeave(Player * player, uint32 timer);
	void setPlayerCovert(Player * player, uint32 timer);
	void setPlayerOvert(Player * player, uint32 timer);
	void promotePlayer(Player * player);
	void grantBribe(Player * player, uint32 cost, uint32 fp);

protected:
	inline bool isHighestRank(Player * player) {
		return !FactionRankTable::rankExists(player->getFactionRank() + 1);
	}

	inline bool canOfferBribe(Player * player) {
		String requiredSkill = "combat_smuggler_underworld_04";

		return player->hasSkillBox(requiredSkill) &&
			(player->getCashCredits() >= 20000) &&
			(player->getMaxFactionPoints(factionString) >= player->getFactionPoints(factionString) + 250);
	}

	inline bool qualifiesForPromotion(Player * player) {
		if (isHighestRank(player))
			return false;

		uint32 requiredPoints = FactionRankTable::getRequiredPoints(player->getFactionRank() + 1) + MINFACTIONSTANDING;

		return (player->getFactionPoints(factionString) >= requiredPoints);
	}

public:
	RecruiterCreatureImplementation(uint64 oid);

	void sendConversationStartTo(SceneObject* obj);

	void selectConversationOption(int option, SceneObject* obj);
};

#endif /*RECRUITERCREATUREIMPLEMENTATIO_H_*/
