/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DENYSERVICECOMMAND_H_
#define DENYSERVICECOMMAND_H_

class DenyServiceCommand : public QueueCommand {
public:

	DenyServiceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<CreatureObject*> targetObject = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();

		if(targetObject == NULL)
			return GENERALERROR;

		if(targetObject == creature || !targetObject->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<EntertainingSession*> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if(session == NULL)
			return GENERALERROR;

		StringIdChatParameter selfMessage;
		StringIdChatParameter otherMessage;

		if(session->isInDenyServiceList(targetObject)) {
			session->removeFromDenyServiceList(targetObject);

			selfMessage.setStringId("performance", "deny_service_remove_self");
			selfMessage.setTT(targetObject->getDisplayedName());

			otherMessage.setStringId("performance", "deny_service_remove_other");
			otherMessage.setTU(creature->getDisplayedName());

			creature->sendSystemMessage(selfMessage);
			targetObject->sendSystemMessage(otherMessage);
		}
		else {
			session->addToDenyServiceList(targetObject);

			selfMessage.setStringId("performance", "deny_service_add_self");
			selfMessage.setTT(targetObject->getDisplayedName());

			otherMessage.setStringId("performance", "deny_service_add_other");
			otherMessage.setTU(creature->getDisplayedName());

			creature->sendSystemMessage(selfMessage);
			targetObject->sendSystemMessage(otherMessage);
		}

		return SUCCESS;
	}

};

#endif //DENYSERVICECOMMAND_H_
