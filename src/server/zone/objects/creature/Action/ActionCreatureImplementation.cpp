#include "ActionCreatureImplementation.h"
#include "ActionCreature.h"

#include "../CreatureImplementation.h"
#include "../../player/Player.h"

#include "../../../managers/mission/MissionManager.h"

#include "../../../packets.h"

#include "../../../../ServerCore.h"

ActionCreatureImplementation::ActionCreatureImplementation(uint64 oid, uint32 objCrc, string& creName, string& stf, 
		string& missionKey, MissionManager* mMgr) : ActionCreatureServant(oid) {
	
	// General NPC:
	characterName = unicode(creName);
	setObjectFileName(stf);
	objectCRC = objCrc;
	setType(CreatureImplementation::ACTION);
	creatureBitmask = 0x108; //RAMSEY: LOOK INTO
	pvpStatusBitmask = 0;
	
	// Action:
	actionList.setNullValue(NULL);
	converseKeys = "";
	tradeKeys = "";
	attackKeys = "";
	deathKeys = "";
	
	// Mission:
	misoKey = missionKey;
	misoMgr = mMgr;
	
	stringstream loggingname;
	loggingname << "ActionCreature = 0x" << oid;
	setLoggingName(loggingname.str());
	
	setLogging(true); //RAMSEY: REMOVE WHEN DONE
	setGlobalLogging(true);
}

ActionCreatureImplementation::~ActionCreatureImplementation() {
}

void ActionCreatureImplementation::onConverse(string tco, Player* player) {
	if(tco.size() > 0) { //add to conversation keys if string tco is set
		converseKeys+=(tco+",");
		return;
	}
	
	if(player == NULL)
		return;
	
	//Parse converseKeys and exec all actions linked to onConverse
	StringTokenizer token(converseKeys);
	token.setDelimeter(",");

	while(token.hasMoreTokens()) {
		string temp;
		token.getStringToken(temp);

		Action* act = actionList.get(temp);
		if(act == NULL)
			return;
		
		act->execAction(player);
	}
}

void ActionCreatureImplementation::onTrade(string ttr = "") {
	if(ttr.size() > 0) { //trade keys
		tradeKeys+=(ttr+",");
		return;
	}
}

void ActionCreatureImplementation::onAttack(string tat = "") {
	if(tat.size() > 0) { //attack keys
		attackKeys+=(tat+",");
		return;
	}
}

void ActionCreatureImplementation::onDeath(string tde = "") {
	if(tde.size() > 0) { //death keys
		deathKeys+=(tde+",");
		return;
	}
}

void ActionCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	if (!obj->isPlayer())
		return;
	
	Player* player = (Player*)obj;
	
	player->setLastNpcConvStr("action_npc");
	player->setLastNpcConvMessStr("0,init");
	
	onConverse("", player);
}

void ActionCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayer())
		return;
		
	Player* player = (Player*)obj;
	
	if(player->getLastNpcConvStr() != "action_npc") {
		return;
	}
	
	string chk = player->getLastNpcConvMessStr();
	string tScreenID;
	StringTokenizer token(chk);
	token.setDelimeter(",");
	token.getStringToken(tScreenID);
	
	//Convert option to string:
	string optionStr = "";
	char optCh[10];
	sprintf(optCh,"%d",option);
	optionStr = optCh;
	
	string newConvStr = (tScreenID + "," + optionStr);
	player->setLastNpcConvMessStr(newConvStr);
	
	//printf("ActionCreatureImpl selectConversationOption() - Set lastMessStr(lastScreenID,selectedOption): %s\n", player->getLastNpcConvMessStr().c_str());
	
	onConverse("", player);
}

bool ActionCreatureImplementation::isMissionNpc() {
	if(misoKey.size() == 0) {
		return false;
	} else {
		return true;
	}
}

MissionManager* ActionCreatureImplementation::getMisoMgr() {
	if(misoMgr == NULL) {
		misoMgr = server->getMissionManager();
	}
	return misoMgr;
}

