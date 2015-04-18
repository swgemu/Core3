/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DESTROYSTRUCTURECOMMAND_H_
#define DESTROYSTRUCTURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/player/sessions/DestroyStructureSession.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/tangible/components/CampTerminalMenuComponent.h"

class DestroystructureCommand : public QueueCommand {
public:

	DestroystructureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->containsActiveSession(SessionFacadeType::DESTROYSTRUCTURE)) {
			creature->sendSystemMessage("@player_structure:pending_destroy"); //You already have an outstanding destroy command for another structure. You must wait for that to expire before attempting a new structure destroy action.
			return GENERALERROR;
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, target);

		if (obj == NULL || !obj->isStructureObject())
			return INVALIDTARGET;

		StructureObject* structure = cast<StructureObject*>( obj.get());

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		if (!ghost->isOwnedStructure(structure) && !ghost->isPrivileged()) {
			creature->sendSystemMessage("@player_structure:destroy_must_be_owner"); //You must be the owner to destroy a structure.
			return INVALIDTARGET;
		}

		if ((structure->isGCWBase() && !ghost->isPrivileged()) || structure->isTurret() || structure->isMinefield()) {
			return INVALIDTARGET;
		}

		if (structure->isCampStructure())
			return disbandCamp(creature, structure);

		String message = structure->getRedeedMessage();
		if(!message.isEmpty()) {
			creature->sendSystemMessage("@player_structure:" + message);
			return INVALIDTARGET;
		}

		ManagedReference<DestroyStructureSession*> session = new DestroyStructureSession(creature, structure);
		session->initializeSession();

		return SUCCESS;
	}

	int disbandCamp(CreatureObject* creature, StructureObject* structure) const {
		Reference<Terminal*> campTerminal = NULL;
		SortedVector < ManagedReference<SceneObject*> > *childObjects = structure->getChildObjects();

		for (int i = 0; i < childObjects->size(); ++i) {
			if (childObjects->get(i)->isTerminal()) {
				campTerminal = cast<Terminal*> (childObjects->get(i).get());
				break;
			}
		}

		if (campTerminal == NULL) {
			return GENERALERROR;
		}

		CampTerminalMenuComponent* campMenu = cast<CampTerminalMenuComponent*>(campTerminal->getObjectMenuComponent());

		if (campMenu == NULL)
			return GENERALERROR;

		campMenu->disbandCamp(campTerminal, creature);

		return SUCCESS;
	}
};

#endif //DESTROYSTRUCTURECOMMAND_H_
