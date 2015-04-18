/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNINVITECOMMAND_H_
#define UNINVITECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"



class UninviteCommand : public QueueCommand {
public:

	UninviteCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* play = cast<CreatureObject*>( object.get());

		try {
			Locker clocker(play, creature);

			if (play->getGroupInviterID() != creature->getObjectID()) {
				creature->sendSystemMessage("@group:must_be_leader");
				return GENERALERROR;
			} else {
				play->updateGroupInviterID(0);
				play->sendSystemMessage("@group:uninvite_self");

				StringIdChatParameter stringId;
				stringId.setStringId("group", "uninvite_target");
				stringId.setTT(play);
				creature->sendSystemMessage(stringId);
			}

		} catch (Exception& e) {
			System::out << "Exception in parseGroupUninvite(CreatureObject* player, Message* pack)\n";
			return GENERALERROR;
		}

		return SUCCESS;
	}

};

#endif //UNINVITECOMMAND_H_

