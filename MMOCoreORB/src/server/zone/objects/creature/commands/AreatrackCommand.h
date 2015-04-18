/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AREATRACKCOMMAND_H_
#define AREATRACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/callbacks/AreaTrackSuiCallback.h"

class AreatrackCommand : public QueueCommand {
public:

	AreatrackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return GENERALERROR;

		if(!creature->hasSkill("outdoors_ranger_novice"))
			return GENERALERROR;

		if(creature->getParent() != NULL && creature->getParent().get()->isCellObject()) {
			creature->sendSystemMessage("@skl_use:sys_scan_inside"); // Your tracking skills only apply to outdoor environments.
			return GENERALERROR;
		}

		CooldownTimerMap* cooldownTimerMap = creature->getCooldownTimerMap();
		if(cooldownTimerMap == NULL || !cooldownTimerMap->isPast("areatrack")) {
			creature->sendSystemMessage("@skl_use:sys_scan_already"); // You are already searching for information.
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::RANGER_TRACK_OPTIONS)) {
			creature->sendSystemMessage("@skl_use:sys_scan_already"); // You are already searching for information.
			return 0;
		}

		ManagedReference<SuiListBox*> chooseTrackTarget = new SuiListBox(creature, SuiWindowType::RANGER_TRACK_OPTIONS);
		chooseTrackTarget->setUsingObject(creature);
		chooseTrackTarget->setCallback(new AreaTrackSuiCallback(server->getZoneServer(), "AreaTrack"));

		chooseTrackTarget->setPromptTitle("@skl_use:scan_type_t"); // Area Track Type
		chooseTrackTarget->setPromptText("@skl_use:scan_type_d"); // Select the type of entity you want to search the area for.

		chooseTrackTarget->addMenuItem("@cmd_n:areatrack_animal");

		if(creature->hasSkill("outdoors_ranger_harvest_02"))
			chooseTrackTarget->addMenuItem("@cmd_n:areatrack_npc");

		if(creature->hasSkill("outdoors_ranger_harvest_04"))
			chooseTrackTarget->addMenuItem("@cmd_n:areatrack_player");

		chooseTrackTarget->setCancelButton(true, "");
		chooseTrackTarget->setOkButton(true, "@ok");

		ghost->addSuiBox(chooseTrackTarget);
		creature->sendMessage(chooseTrackTarget->generateMessage());

		return SUCCESS;
	}

};

#endif //AREATRACKCOMMAND_H_
