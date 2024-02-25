/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSELECTCOMMAND_H_
#define NPCCONVERSATIONSELECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/ai/SpaceStationObject.h"

class NpcConversationSelectCommand : public QueueCommand {
public:
	NpcConversationSelectCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		uint64 conversationCreatureOid = ghost->getConversatingObject();
		ManagedReference<SceneObject*> object = zoneServer->getObject(conversationCreatureOid).castTo<SceneObject*>();

		if (object == nullptr)
			return GENERALERROR;

		int option = Integer::valueOf(arguments.toString());

		try {
			Locker clocker(object, creature);

			ValidatedPosition* validPosition = ghost->getLastValidatedPosition();
			uint64 parentid = validPosition->getParent();

			if (object->isCreatureObject() && (parentid != object->getParentID()))
				return TOOFAR;

			Vector3 validCoords = validPosition->getWorldPosition(zoneServer);

			if (object->isShipObject() || validCoords.squaredDistanceTo(object->getWorldPosition()) < 25.f) {
				object->selectConversationOption(option, creature);

				object->notifyObservers(ObserverEventType::SELECTCONVERSATION, creature, option);
			} else {
				return TOOFAR;
			}
		} catch (Exception& e) {

		}

		return SUCCESS;
	}

};

#endif //NPCCONVERSATIONSELECTCOMMAND_H_
