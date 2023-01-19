/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSELECTCOMMAND_H_
#define NPCCONVERSATIONSELECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/SpaceStationObject.h"

class NpcConversationSelectCommand : public QueueCommand {
public:

	NpcConversationSelectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);
		PlayerObject* ghost = player->getPlayerObject();

		uint64 conversationCreatureOid = ghost->getConversatingCreature();
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(conversationCreatureOid).castTo<SceneObject*>();

		if (object != nullptr) {
			int option = Integer::valueOf(arguments.toString());

			try {
				Locker clocker(object, creature);

				ValidatedPosition* validPosition = ghost->getLastValidatedPosition();
				uint64 parentid = validPosition->getParent();

				if (object->isCreatureObject()) {
					if (parentid != object->getParentID())
						return TOOFAR;
				}

				Vector3 vec = validPosition->getWorldPosition(server->getZoneServer());

				if (vec.distanceTo(object->getWorldPosition()) <= 5.f) {
					object->selectConversationOption(option, player);

					object->notifyObservers(ObserverEventType::SELECTCONVERSATION, creature, option);

				} else if (object->isSpaceStationObject()) {
					object->selectConversationOption(option, player);

					object->notifyObservers(ObserverEventType::SELECTCONVERSATION, creature, option);

				} else {
					return TOOFAR;
				}
			} catch (Exception& e) {

			}
		}

		return SUCCESS;
	}

};

#endif //NPCCONVERSATIONSELECTCOMMAND_H_
