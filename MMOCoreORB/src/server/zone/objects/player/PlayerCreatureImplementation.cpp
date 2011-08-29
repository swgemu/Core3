/*
 * PlayerCreatureImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerCreature.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/weather/WeatherManager.h"
#include "server/zone/packets/object/CommandQueueRemove.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/ui/ExecuteConsoleCommand.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/managers/creature/CreatureManager.h"

#include "server/chat/room/ChatRoom.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"


#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/variables/SkillBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/listbox/teachplayerlistbox/TeachPlayerListBox.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/professions/SkillManager.h"

#include "server/chat/StringIdChatParameter.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"


#include "PlayerObject.h"

void PlayerCreatureImplementation::initializeTransientMembers() {
	CreatureObjectImplementation::initializeTransientMembers();

	setLoggingName("PlayerCreature");

	/**
	 * Here we are loading the schematics based on the skills that the
	 * player has, we do this incase we change the items
	 * in the schematic group.
	 */
	ZoneServer* zoneServer = server->getZoneServer();
	SkillManager* professionManager = zoneServer->getSkillManager();

	SkillBoxList* playerSkillBoxList = getSkillBoxList();

	if (getPlayerObject() != NULL) {
		for(int i = 0; i < playerSkillBoxList->size(); ++i) {
			Skill* skillBox = playerSkillBoxList->get(i);
			professionManager->awardDraftSchematics(skillBox, getPlayerObject(), false);
		}
	}

}

void PlayerCreatureImplementation::finalize() {
	if (server != NULL) {
		ManagedReference<ZoneServer*> zoneServer = server->getZoneServer();

		if (zoneServer != NULL)
			zoneServer->increaseTotalDeletedPlayers();
	}
}



void PlayerCreatureImplementation::notifyLoadFromDatabase() {
	CreatureObjectImplementation::notifyLoadFromDatabase();

	/*StackTrace::printStackTrace();

	if (parent != NULL) {
		info("loading from database with parent not null", true);
	}*/

	group = NULL;
	listenToID = 0;
	watchToID = 0;
	setMood(getMoodID());

	if (getZone() != NULL && !isInQuadTree())
		setZone(NULL);

	clearCombatState(true);
	clearState(CreatureState::ALERT);

	if (posture == CreaturePosture::SKILLANIMATING)
		setPosture(CreaturePosture::UPRIGHT, true);

	if (performanceCounter != 0)
		setPerformanceCounter(0);

	if (instrumentID != 0)
		setInstrumentID(0);

	if (hasState(CreatureState::RIDINGMOUNT) && parent == NULL)
		clearState(CreatureState::RIDINGMOUNT);

	speedMultiplierModChanges.removeAll();

	movementCounter = 0;
}

void PlayerCreatureImplementation::updateToDatabase() {
	/*if (zone != NULL) {
		savedZoneID = zone->getZoneID();
	}

	if (parent != NULL) {
		savedParentID = parent->getObjectID();
	} *//*else
		savedParentID = 0;*/

	CreatureObjectImplementation::updateToDatabase();
}

void PlayerCreatureImplementation::setCombatState() {
	CreatureObjectImplementation::setCombatState();

/*	if (tradeContainer.isTryingToTrade()) {
		PlayerManager* playerManager = getZoneServer()->getPlayerManager();
		playerManager->handleAbortTradeMessage(_this, false);
	}*/
}

