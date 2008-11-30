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

#include "Action.h"
#include "ActionImplementation.h"

#include "../../../managers/mission/MissionManagerImplementation.h"

#include "../../../packets.h"

#include "../../player/Player.h"

ActionImplementation::ActionImplementation(SceneObject* po, int actMask, int tpr) : ActionServant() {
	parentObject = po;
	actionMask = actMask;
	preRequisites = tpr; //MAY NOT BE A BITMASK - OVERHAUL PREREQ SYSTEM
	sayText = "";
	giveMissionKey = "";
}

ActionImplementation::~ActionImplementation() {
}

void ActionImplementation::execAction(Player* player) {
	if (!prereqCheck(player))
		return;

	if ((actionMask & TYPE_MOVE)) {
	}

	if ((actionMask & TYPE_CONVERSE)) {
		if (!parentObject->isNonPlayerCreature() /*|| !parentObject->isAttackableObject()*/)
			return;
		carryConversation(player);
	}

	if ((actionMask & TYPE_SAY)) {
	}

	if ((actionMask & TYPE_GIVEITEM)) {
	}

	if ((actionMask & TYPE_TAKEITEM)) {
		String misoKey;
		TangibleObject* pItem;

		if (parentObject->isNonPlayerCreature()) {
			ActionCreature* parentCreature = (ActionCreature*)parentObject;
			if (parentCreature->getType() != CreatureImplementation::ACTION)
				return;

			if (!parentCreature->isMissionNpc())
				return;

			misoKey = parentCreature->getMissionKey();

			pItem = player->getMissionItem(misoKey);

			if (pItem == NULL) {
				//Elaborate with NPC dialogue later.
				//printf("Cannot get mission item from player, it is NULL\n");
				return;
			}

		} else {
		}
	}

	if ((actionMask & TYPE_GIVEMISSION)) {
	}

	if ((actionMask & TYPE_COMPMISSION)) {
		String misoKey;
		MissionManagerImplementation* mMgr;

		if (parentObject->isNonPlayerCreature()) {
			ActionCreature* parentCreature = (ActionCreature*)parentObject;
			if (parentCreature->getType() != CreatureImplementation::ACTION)
				return;

			if (!parentCreature->isMissionNpc())
				return;

			misoKey = parentCreature->getMissionKey();
			mMgr = parentCreature->getMisoMgr();

			if (mMgr == NULL) {
				printf("Cannot complete mission, mission manager is null in parent creature\n");
				return;
			}

			if (misoKey.isEmpty()) {
				return;
			}

			mMgr->doMissionComplete(player, misoKey, false);
		} /*else if (parentObject->isAttackableObject()) {
			//For lairs
		}*/ else {
		}
	}

	if ((actionMask & TYPE_FAILMISSION)) {
		String misoKey;
		MissionManagerImplementation* mMgr;

		if (parentObject->isNonPlayerCreature()) {
			ActionCreature* parentCreature = (ActionCreature*)parentObject;
			if (parentCreature->getType() != CreatureImplementation::ACTION)
				return;

			if (!parentCreature->isMissionNpc())
				return;

			misoKey = parentCreature->getMissionKey();
			mMgr = parentCreature->getMisoMgr();

			if (mMgr == NULL) {
				//printf("Cannot abort mission, mission manager is null in parent creature\n");
				return;
			}

			mMgr->doMissionAbort(player, misoKey, false);

		} /*else if (parentObject->isAttackableObject()) {
			//For lairs
		}*/ else {
		}
	}
}

void ActionImplementation::addConvoScreen(String screenID, String leftBoxText, int numOptions, String Options, String optLinks) {
	//optLinks syntax: nextScreenID,actionKey|next|next etc. Goes to convoOptLink<"screenID,OptionNumber","nextScreenID,actionKey">
	String screenStr;
	screenStr += leftBoxText + "~" + Options;
	convoScreens.put(screenID, screenStr);

	StringTokenizer token(optLinks);
	token.setDelimeter("|");

	for (int i = 0; i < numOptions; i++) {
		String key = "";
		char numBuf[10];
		sprintf(numBuf,"%d",i);
		key = screenID + "," + numBuf;

		String link = "";
		token.getStringToken(link);

		convoOptLink.put(key, link);
	}
}

//private:

void ActionImplementation::carryConversation(Player* player) {
	if (player->getLastNpcConvStr() != "action_npc") {
		//printf("debug: aborting ActionImpl carryConversation() because getLastNpcConvStr = %s\n", player->getLastNpcConvStr().toCharArray());
		return;
	}

	ActionCreature* parentCreature = (ActionCreature*)parentObject;

	String chk = player->getLastNpcConvMessStr();
	String tScreenID;
	String tOptNum;
	StringTokenizer token(chk);
	token.setDelimeter(",");
	token.getStringToken(tScreenID);
	token.getStringToken(tOptNum);

	if ((tScreenID == "0") && (tOptNum == "init")) {
		StartNpcConversation* conv = new StartNpcConversation(player, parentCreature->getObjectID(), "");
		player->sendMessage(conv);

		// 0 Should always be the ID of the startup converse window:
		String screenId = "0";

		sendConvoScreen(player, screenId);
	} else {
		//Retrive Screen/Option pair from convoOptLink and send new screen.
		String tns = "";
		tns = convoOptLink.get(player->getLastNpcConvMessStr());
		if (tns == "") {
			//printf("carryConversation() : No such Conversation Option link found in map.");
			return;
		}

		String newScreenID;
		String actKey;
		StringTokenizer token2(tns);
		token2.setDelimeter(",");
		token2.getStringToken(newScreenID);
		token2.getStringToken(actKey);

		//Check for special words set as the new screen id:
		if (newScreenID == "EXECACTION") {
			Action* nAction = parentCreature->getAction(actKey);
			nAction->execAction(player);

			StopNpcConversation* scv = new StopNpcConversation(player, parentCreature->getObjectID());
			player->sendMessage(scv);
		} else if (newScreenID == "ENDCNV") {
			StopNpcConversation* scv = new StopNpcConversation(player, parentCreature->getObjectID());
			player->sendMessage(scv);
			player->setLastNpcConvStr("");
			player->setLastNpcConvMessStr("");
		} else { //If no special work is found, send the new screen:
			sendConvoScreen(player, newScreenID);
		}
	}
}

void ActionImplementation::sendConvoScreen(Player* player, String& screenID) {
	String windowStr = convoScreens.get(screenID);
	//Take the windowStr = "Left Box Text~Option1Text|O2|O3". Parse it and send the convo screen packet.

	//Parse and send the left box of the conversation:
	StringTokenizer token(windowStr);
	token.setDelimeter("~");
	String temp;
	token.getStringToken(temp);
	UnicodeString utemp = temp;

	NpcConversationMessage* m1 = new NpcConversationMessage(player, utemp);
	player->sendMessage(m1);

	//Parse and send the options:
	token.getStringToken(temp);
	StringTokenizer token2(temp);
	token2.setDelimeter("|");
	StringList* slist = new StringList(player);

	while (token2.hasMoreTokens()) {
		String tempOpt;
		token2.getStringToken(tempOpt);
		slist->insertOption(tempOpt);
	}
	player->sendMessage(slist);

	//Set last screenID:
	String newConvStr = (screenID + ",0");
	player->setLastNpcConvMessStr(newConvStr);
}

bool ActionImplementation::prereqCheck(Player* player) {
	//private. call this when triggers are fired so they know if its ok to exec action

	//temp
	String misoKey;
	misoKey = "";

	if (parentObject->isNonPlayerCreature()) {
		ActionCreature* parentCreature = (ActionCreature*)parentObject;

		if (parentCreature->getType() != CreatureImplementation::ACTION)
			return false;

		if (!parentCreature->isMissionNpc())
			return false;

		misoKey = parentCreature->getMissionKey();

		if (misoKey == "") {
			//printf("Unable to get Mission key from parentCreature in prereqCheck()\n");
			return false;
		} else {
			return player->isOnCurMisoKey(misoKey);
		}
	}

	return false;
}


