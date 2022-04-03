/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SOCIALINTERNALCOMMAND_H_
#define SOCIALINTERNALCOMMAND_H_

#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
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
		if (chatManager == nullptr)
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

		Reference<CreatureObject*> creo = server->getZoneServer()->getObject(targetid, true).castTo<CreatureObject*>();

		if (creo == nullptr)
			return SUCCESS;

		if (creo->isPlayerCreature()) {
			String socialType = chatManager->getSocialType(emoteid);

			if (socialType != "applaud" && socialType != "cheer" && socialType != "clap")
				return SUCCESS;

			if (creo->isEntertaining() && creo->isInRange(creature, 40.0f)) {
				ManagedReference<EntertainingSession*> session = creo->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

				if (session != nullptr && session->getApplauseCount() < 100)
					session->incrementApplauseCount();
			}

			return SUCCESS;
		}

		Reference<AiAgent*> aiAgent = creo->asAiAgent();

		if (aiAgent == nullptr || aiAgent->isDead() || aiAgent->isIncapacitated())
			return GENERALERROR;

		Locker crossLocker(aiAgent, creature);

		if (aiAgent->isMonster()) {
			// If target is a pet, enqueue command to handle it
			if (aiAgent->isPet()) {
				PetManager* petManager = aiAgent->getZoneServer()->getPetManager();
				if (petManager == nullptr)
					return GENERALERROR;

				petManager->enqueueOwnerOnlyPetCommand(creature, aiAgent, STRING_HASHCODE("petemote"), arguments.toString() );
			} else {
				int chance = 40; // % chance out of 100 they creature will rest

				if (!aiAgent->isResting() && !aiAgent->isInCombat() && chance > System::random(100)) {
					Time* restDelay = aiAgent->getRestDelay();

					if (restDelay != nullptr) {
						int delay = 300 * 1000;

						restDelay->updateToCurrentTime();
						restDelay->addMiliTime(delay);

						aiAgent->setMovementState(AiAgent::RESTING);

						int speciesID = aiAgent->getSpecies();
						bool canSitDown = false;

						Zone* zone = aiAgent->getZone();

						if (zone == nullptr)
							return SUCCESS;

						ManagedReference<CreatureManager*> creoManager = zone->getCreatureManager();

						if (creoManager != nullptr) {
							AiSpeciesData* speciesData = creoManager->getAiSpeciesData(speciesID);

							if (speciesData != nullptr) {
								canSitDown = speciesData->canSitDown();
							}
						}

						if (canSitDown && System::random(100) > 50) {
							aiAgent->setPosture(CreaturePosture::SITTING, true);
						} else {
							aiAgent->setPosture(CreaturePosture::LYINGDOWN, true);
						}
					}
				}
			}
		} else {

			ReactionManager* reactionManager = creature->getZoneServer()->getReactionManager();

			if (reactionManager != nullptr)
				reactionManager->emoteReaction(creature, aiAgent, emoteid);

		}
		return SUCCESS;
	}

};

#endif //SOCIALINTERNALCOMMAND_H_
