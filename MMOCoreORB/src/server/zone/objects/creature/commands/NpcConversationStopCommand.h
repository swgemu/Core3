/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSTOPCOMMAND_H_
#define NPCCONVERSATIONSTOPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class NpcConversationStopCommand : public QueueCommand {
public:
	NpcConversationStopCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		uint64 conversationCreatureOid = ghost->getConversatingObject();
		ManagedReference<SceneObject*> object = zoneServer->getObject(conversationCreatureOid);

		if (object == nullptr)
			return GENERALERROR;

		Locker clocker(object, creature);

		object->notifyObservers(ObserverEventType::STOPCONVERSATION, creature);

		if (object->isCreatureObject()) {
			auto targetCreature = object->asCreatureObject();

			if (targetCreature != nullptr) {
				try {
					targetCreature->stopConversation();
				} catch (Exception& e) {
				}
			}
		}

		return SUCCESS;
	}
};

#endif // NPCCONVERSATIONSTOPCOMMAND_H_
