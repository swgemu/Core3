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

#include "ActionCreatureImplementation.h"
#include "ActionCreature.h"

#include "../CreatureImplementation.h"
#include "../../player/Player.h"

#include "../../../managers/mission/MissionManagerImplementation.h"

#include "../../../packets.h"

#include "../../../../ServerCore.h"

ActionCreatureImplementation::ActionCreatureImplementation(uint64 oid, uint32 objCrc, String& creName, String& stf,
		String& missionKey) : ActionCreatureServant(oid) {

	// General NPC:
	customName = UnicodeString(creName);
	setObjectFileName(stf);
	objectCRC = objCrc;
	setType(CreatureImplementation::ACTION);

	optionsBitmask = 0x108; //RAMSEY: LOOK INTO

	pvpStatusBitmask = 0;

	// Action:
	actionList.setNullValue(NULL);
	converseKeys = "";
	tradeKeys = "";
	attackKeys = "";
	deathKeys = "";

	// Mission:
	misoKey = missionKey;

	StringBuffer loggingname;
	loggingname << "ActionCreature = 0x" << oid;
	setLoggingName(loggingname.toString());

	setLogging(true); //RAMSEY: REMOVE WHEN DONE
	setGlobalLogging(true);
}

ActionCreatureImplementation::~ActionCreatureImplementation() {
}

void ActionCreatureImplementation::execActionByKey(String key, Player* player) {
	//In some cases, player CAN be null. Make sure its checked in the action
	Action* act = actionList.get(key);
	if(act == NULL)
		return;

	act->execAction(player);
}

void ActionCreatureImplementation::onConverse(String tco, Player* player) {
	if (!tco.isEmpty()) { //add to conversation keys if String tco is set
		converseKeys+=(tco+",");
		return;
	}

	if (player == NULL)
		return;

	//Parse converseKeys and exec all actions linked to onConverse
	StringTokenizer token(converseKeys);
	token.setDelimeter(",");

	while (token.hasMoreTokens()) {
		String temp;
		token.getStringToken(temp);

		Action* act = actionList.get(temp);
		if (act == NULL)
			return;

		act->execAction(player);
	}
}

void ActionCreatureImplementation::onTrade(String ttr = "") {
	if (!ttr.isEmpty()) { //trade keys
		tradeKeys+=(ttr+",");
		return;
	}
}

void ActionCreatureImplementation::onAttack(String tat = "") {
	if (!tat.isEmpty()) { //attack keys
		attackKeys += (tat + ",");
		return;
	}
}

void ActionCreatureImplementation::onDeath(String tde = "") {
	if (!tde.isEmpty()) { //death keys
		deathKeys+=(tde + ",");
		return;
	}
}

void ActionCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	player->setLastNpcConvStr("action_npc");
	player->setLastNpcConvMessStr("0, init");

	onConverse("", player);
}

void ActionCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	if (player->getLastNpcConvStr() != "action_npc") {
		return;
	}

	String chk = player->getLastNpcConvMessStr();
	String tScreenID;
	StringTokenizer token(chk);
	token.setDelimeter(",");
	token.getStringToken(tScreenID);

	//Convert option to String:
	String optionStr = String::valueOf(option);

	String newConvStr = (tScreenID + "," + optionStr);
	player->setLastNpcConvMessStr(newConvStr);

	onConverse("", player);
}

bool ActionCreatureImplementation::isMissionNpc() {
	if (misoKey.isEmpty()) {
		return false;
	} else {
		return true;
	}
}


