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

#include "RebelRecruiterCreature.h"

#include "../../../player/Player.h"

#include "../../../player/faction/FactionRankTable.h"

#include "../../../../packets.h"


#ifndef REBELRECRUITERCREATUREIMPLEMENTATION_H_
#define REBELRECRUITERCREATUREIMPLEMENTATION_H_

class RebelRecruiterCreatureImplementation : public RebelRecruiterCreatureServant {
public:
	RebelRecruiterCreatureImplementation(uint64 oid) : RebelRecruiterCreatureServant(oid) {
		objectCRC = 0xB39C9594;
		factionCRC = String("rebel").hashCode();
		enemyFactionCRC = String("imperial").hashCode();
		factionString = "rebel";
		stfName = "rebel_recruiter";
	}

	void greetEnemy() {
		say("conversation/faction_recruiter_rebel", "s_464", new StfParameter());
	}

	void greetHated() {
		say("conversation/faction_recruiter_rebel", "s_462", new StfParameter());
	}

	void greetChangingStatusMemeber() {
		say("conversation/faction_recruiter_rebel", "s_596", new StfParameter());
	}

	void greetMember(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_466"));
		sendMemberStart(player);
	}

	void sendMemberStart(Player * player) {
		player->setLastNpcConvMessStr("member_start");

		StringList* slist = new StringList(player);

		if (qualifiesForPromotion(player))
			slist->insertOption("conversation/faction_recruiter_rebel", "s_468");

		if (canOfferBribe(player))
			slist->insertOption("conversation/faction_recruiter_rebel", "s_568");

		slist->insertOption("conversation/faction_recruiter_rebel", "s_504");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_526");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_538");
		player->sendMessage(slist);
	}

	void sendNeutralStart(Player * player) {
		player->setLastNpcConvMessStr("neutral_start");

		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_566"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_580");
		player->sendMessage(slist);
	}

	void sendOnLeaveStart(Player * player) {
		player->setLastNpcConvMessStr("neutral_start");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_448"));
		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_450");
		player->sendMessage(slist);
	}

	void confirmGoCovert(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_covert");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_506"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_508");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_512");
		player->sendMessage(slist);
	}

	void playerAcceptedGoCovert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_510"));
	}

	void playerRejectedGoCovert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_514"));
		sendMemberStart(player);
	}

	void confirmGoOvert(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_overt");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_516"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_518");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_522");
		player->sendMessage(slist);
	}

	void playerAcceptedGoOvert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_520"));
	}

	void playerRejectedGoOvert(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_524"));
		sendMemberStart(player);
	}

	void confirmGoOnLeave(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_on_leave");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_528"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_530");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_534");
		player->sendMessage(slist);
	}

	void playerAcceptedGoOnLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_532"));
	}

	void playerRejectedGoOnLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_536"));
		sendMemberStart(player);
	}

	void confirmJoinGoActive(Player * player) {
		player->setLastNpcConvMessStr("confirm_go_active");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_452"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_454");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_458");
		player->sendMessage(slist);
	}

	void playerAcceptedGoActive(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_456"));
	}

	void playerRejectedGoActive(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_460"));
	}

	void rejectJoinFaction(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_582"));
	}

	void confirmJoinFaction(Player * player) {
		player->setLastNpcConvMessStr("confirm_join_faction");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_584"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_586");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_592");
		player->sendMessage(slist);
	}

	void playerAcceptedJoin(Player * player) {
		player->setLastNpcConvMessStr("player_accepted_join");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_588"));
		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_590");
		player->sendMessage(slist);
	}

	void playerRejectedJoin(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_594"));
	}

	void confirmLeaveFaction(Player * player) {
		player->setLastNpcConvMessStr("confirm_leave_faction");
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_540"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_542");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_546");
		player->sendMessage(slist);

	}

	void playerAcceptedLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_544"));
	}

	void playerRejectedLeave(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_548"));
	}

	void confirmPromotion(Player * player) {
		player->setLastNpcConvMessStr("confirm_promotion");

		StfParameter * param = new StfParameter();
		param->addTO("faction_recruiter", FactionRankTable::getRankName(player->getFactionRank() + 1));
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_470", param));
		delete param;

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_472");
		slist->insertOption("conversation/faction_recruiter_rebel", "s_476");
		player->sendMessage(slist);
	}

	void playerAcceptedPromotion(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_474"));
	}

	void playerRejectedPromotion(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_478"));
	}

	void confirmBribe(Player * player) {
		player->setLastNpcConvMessStr("confirm_bribe");

		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_570"));

		StringList* slist = new StringList(player);
		slist->insertOption("conversation/faction_recruiter_rebel", "s_572");

		if (player->getCashCredits() >= 100000 &&
		   (player->getMaxFactionPoints(factionString) >= player->getFactionPoints(factionString) + 1250))
			slist->insertOption("conversation/faction_recruiter_rebel", "s_576");

		player->sendMessage(slist);
	}

	void playerAcceptedBribe(Player * player) {
		player->sendMessage(new NpcConversationMessage(player, "conversation/faction_recruiter_rebel", "s_574"));
	}
};

#endif /* REBELRECRUITERCREATUREIMPLEMENTATION_H_ */
