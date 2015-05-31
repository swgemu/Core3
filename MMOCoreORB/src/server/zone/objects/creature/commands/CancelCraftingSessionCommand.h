/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CANCELCRAFTINGSESSIONCOMMAND_H_
#define CANCELCRAFTINGSESSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"

class CancelCraftingSessionCommand : public QueueCommand {
public:

	CancelCraftingSessionCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return INVALIDTARGET;

		Reference<CraftingSession*> session = creature->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();

		if(session == NULL) {
			return GENERALERROR;
		}

		Locker locker(session);
		session->cancelSession();

		return SUCCESS;
	}

};

#endif //CANCELCRAFTINGSESSIONCOMMAND_H_
