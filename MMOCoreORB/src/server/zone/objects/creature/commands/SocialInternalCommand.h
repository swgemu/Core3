/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SOCIALINTERNALCOMMAND_H_
#define SOCIALINTERNALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/chat/ChatManager.h"

class SocialInternalCommand : public QueueCommand {
public:

	SocialInternalCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;


		ChatManager* chatManager = server->getChatManager();
		if (chatManager == NULL)
			return GENERALERROR;

		chatManager->handleSocialInternalMessage(creature, arguments);

		// Parse arguments
		StringTokenizer tokenizer(arguments.toString());
		uint64 targetid;
		uint32 emoteid;
		try {
			targetid = tokenizer.getLongToken();
			emoteid = tokenizer.getIntToken();
		} catch (const Exception& e) {
			return GENERALERROR;
		}

		// If target is a pet, enqueue command to handle it
		Reference<AiAgent*> aiAgent = server->getZoneServer()->getObject(targetid, true).castTo<AiAgent*>();
		if(aiAgent == NULL)
			return SUCCESS;

		Locker crossLocker(aiAgent, creature);

		if (aiAgent->isPet()) {

			PetManager* petManager = aiAgent->getZoneServer()->getPetManager();
			if (petManager == NULL)
				return GENERALERROR;

			petManager->enqueueOwnerOnlyPetCommand(creature, aiAgent,String("petEmote").toLowerCase().hashCode(), arguments.toString() );

		} else {

			ReactionManager* reactionManager = creature->getZoneServer()->getReactionManager();

			if (reactionManager != NULL)
				reactionManager->emoteReaction(creature, aiAgent, emoteid);

		}
		return SUCCESS;
	}

};

#endif //SOCIALINTERNALCOMMAND_H_
