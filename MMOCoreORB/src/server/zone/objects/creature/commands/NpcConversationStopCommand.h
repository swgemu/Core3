/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSTOPCOMMAND_H_
#define NPCCONVERSATIONSTOPCOMMAND_H_

class NpcConversationStopCommand : public QueueCommand {
public:

	NpcConversationStopCommand(const String& name, ZoneProcessServer* server)
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
		ManagedReference<CreatureObject*> object = (server->getZoneServer()->getObject(conversationCreatureOid)).castTo<CreatureObject*>();

		if (object != NULL) {

			try {
				Locker clocker(object, creature);

				//object->selectConversationOption(option, player);

				object->notifyObservers(ObserverEventType::STOPCONVERSATION, creature);
			} catch (Exception& e) {

			}
		}

		return SUCCESS;
	}

};

#endif //NPCCONVERSATIONSTOPCOMMAND_H_
