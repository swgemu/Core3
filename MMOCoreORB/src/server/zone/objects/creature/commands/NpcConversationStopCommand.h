/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSTOPCOMMAND_H_
#define NPCCONVERSATIONSTOPCOMMAND_H_

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

		uint64 conversationCreatureOid = ghost->getConversatingCreature();
		ManagedReference<SceneObject*> object = zoneServer->getObject(conversationCreatureOid);

		if (object == nullptr || !object->isCreatureObject())
			return GENERALERROR;

		ManagedReference<CreatureObject*> agentCreo = (object).castTo<CreatureObject*>();

		if (agentCreo != nullptr) {
			try {
				Locker clocker(agentCreo, creature);

				agentCreo->notifyObservers(ObserverEventType::STOPCONVERSATION, creature);
				agentCreo->stopConversation();
			} catch (Exception& e) {
			}
		}

		return SUCCESS;
	}

};

#endif //NPCCONVERSATIONSTOPCOMMAND_H_
