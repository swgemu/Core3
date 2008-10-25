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

#include "engine/engine.h"
#include "ImperialRecruiterCreature.h"

#include "../../../player/Player.h"
#include "../../../player/faction/FactionRankTable.h"
#include "../../../../packets.h"

#ifndef IMPERIALRECRUITERCREATUREIMPLEMENTATION_H_
#define IMPERIALRECRUITERCREATUREIMPLEMENTATION_H_

class ImperialRecruiterCreatureImplementation : public ImperialRecruiterCreatureServant {
public:
	ImperialRecruiterCreatureImplementation(uint64 oid) : ImperialRecruiterCreatureServant(oid) {
		objectCRC = 0xCC13B720;
		factionCRC = String::hashCode("imperial");
		enemyFactionCRC = String::hashCode("rebel");
		factionString = "imperial";
		speciesName = "imperial_recruiter";
	}

	void greetEnemy() {
		say("conversation/faction_recruiter_imperial", "s_306", new StfParameter());
	}

	void greetHated() {
		say("conversation/faction_recruiter_imperial", "s_308", new StfParameter());
	}

	void greetChangingStatusMember() {
		say("conversation/faction_recruiter_imperial", "s_444", new StfParameter());
	}

	void greetMember(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_310"));
		sendMemberStart(player);
	}

	void sendMemberStart(Player * player) {
		player->setLastNpcConvMessStr("member_start");

		StringList * slist = new StringList(player);
		if (qualifiesForPromotion(player))
			slist->insertOption("conversation/faction_recruiter_imperial", "s_312");

		if(canOfferBribe(player))
			slist->insertOption("conversation/faction_recruiter_imperial", "s_398");

		slist->insertOption("conversation/faction_recruiter_imperial", "s_352");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_374");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_386");
		player->sendMessage(slist);
	}

	void sendNeutralStart(Player * player) {
		player->setLastNpcConvMessStr("neutral_start");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_414"));
		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_428");
		player->sendMessage(slist);
	}


	void sendOnLeaveStart(Player * player) {
		player->setLastNpcConvMessStr("onLeave_start");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_80"));
		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_294");
		player->sendMessage(slist);
	}

	void confirmGoCovert(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_covert");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_354"));

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_356");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_360");
		player->sendMessage(slist);
	}

	void playerAcceptedGoCovert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_358"));
	}

	void playerRejectedGoCovert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_362"));
		sendMemberStart(player);
	}

	void confirmGoOvert(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_overt");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_364"));

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_366");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_370");
		player->sendMessage(slist);
	}

	void playerAcceptedGoOvert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_368"));
	}

	void playerRejectedGoOvert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_372"));
		sendMemberStart(player);
	}

	void confirmGoOnLeave(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_on_leave");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_376"));

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_378");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_382");
		player->sendMessage(slist);
	}

	void playerAcceptedGoOnLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_380"));
	}

	void playerRejectedGoOnLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_384"));
		sendMemberStart(player);
	}

	void confirmGoActive(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_active");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_296"));

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_298");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_302");
		player->sendMessage(slist);
	}

	void playerAcceptedGoActive(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_300"));
	}

	void playerRejectedGoActive(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_304"));
	}

	void rejectJoinFaction(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_430"));
	}

	void confirmJoinFaction(Player * player) {
		player->setLastNpcConvMessStr("confirm_join_faction");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_432"));

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_434");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_440");
		player->sendMessage(slist);
	}

	void playerAcceptedJoin(Player * player) {
		player->setLastNpcConvMessStr("player_accepted_join");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_436"));
		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_438");
		player->sendMessage(slist);
	}

	void playerRejectedJoin(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_442"));
	}

	void confirmLeaveFaction(Player * player) {
		player->setLastNpcConvMessStr("confirm_leave_faction");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_388"));

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_390");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_394");
		player->sendMessage(slist);

	}

	void playerAcceptedLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_392"));
	}

	void playerRejectedLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_396"));
	}

	void confirmPromotion(Player * player) {
		player->setLastNpcConvMessStr("confirm_promotion");

		StfParameter * param = new StfParameter();
		param->addTO("faction_recruiter", FactionRankTable::getRankName(player->getFactionRank() + 1));
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_314", param));
		delete param;

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_93");
		slist->insertOption("conversation/faction_recruiter_imperial", "s_320");
		player->sendMessage(slist);
	}

	void playerAcceptedPromotion(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_318"));
	}

	void playerRejectedPromotion(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_322"));
	}

	void confirmBribe(Player * player) {
		player->setLastNpcConvMessStr("confirm_bribe");

		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_400"));

		StringList * slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_imperial", "s_402");

		if (player->getCashCredits() >= 100000 &&
		   (player->getMaxFactionPoints(factionString) >= player->getFactionPoints(factionString) + 1250))
			slist->insertOption("conversation/faction_recruiter_imperial", "s_406");

		player->sendMessage(slist);
	}

	void playerAcceptedBribe(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_imperial", "s_408"));
	}
};

#endif /* IMPERIALRECRUITERCREATUREIMPLEMENTATION_H_ */
