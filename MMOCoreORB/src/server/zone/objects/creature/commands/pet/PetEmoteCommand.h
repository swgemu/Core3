/*
 * PetEmoteCommand.h
 *
 *  Created on: Jan 28, 2014
 *      Author: Klivian
 */

#ifndef PETEMOTECOMMAND_H_
#define PETEMOTECOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/CreatureEmote.h"

class PetEmoteCommand : public QueueCommand {
public:
	PetEmoteCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		// Parse arguments (client arguments from SocialInternalCommand /socialInternal)
		StringTokenizer tokenizer(arguments.toString());
		uint64 targetid;
		uint32 emoteid;
		try {
			targetid = tokenizer.getLongToken();
			emoteid = tokenizer.getIntToken();
		} catch (const Exception& e) {
			return GENERALERROR;
		}

		if (!creature->isAiAgent())
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		// Creature specific command
		if( controlDevice->getPetType() != PetManager::CREATUREPET )
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		if( emoteid == CreatureEmote::PET || emoteid == CreatureEmote::REASSURE ||
			emoteid == CreatureEmote::NUZZLE || emoteid == CreatureEmote::HUG ){

			return praise( pet );

		}
		else if( emoteid == CreatureEmote::BONK || emoteid == CreatureEmote::WHAP ||
				 emoteid == CreatureEmote::SCOLD || emoteid == CreatureEmote::BAD ||
				 emoteid == CreatureEmote::SLAP ){

			return shame(pet);

		}
		else if( emoteid == CreatureEmote::POINTAT || emoteid == CreatureEmote::TAP ){

			return alert(pet);

		}
		else if( emoteid == CreatureEmote::SUMMON || emoteid == CreatureEmote::BECKON ){

			return summon(pet, controlDevice);

		}

		return SUCCESS;
	}

	int praise( AiAgent* pet ) const {


		// TODO: Random chance to change posture to sitting or laying down instead of happy animation
		pet->doAnimation("happy");
		return SUCCESS;
	}

	int shame( AiAgent* pet ) const {
		pet->doAnimation("ashamed");
		return SUCCESS;
	}

	int alert( AiAgent* pet ) const {
		pet->doAnimation("alert");
		return SUCCESS;
	}

	int summon( AiAgent* pet, PetControlDevice* controlDevice ) const {

		// Follow owner if command is trained
		if( controlDevice->hasTrainedCommand( PetManager::FOLLOW ) ){

			// Always a chance the pet will just be stubborn
			if (System::random(100) <= 90 ){
				pet->setFollowObject( pet->getLinkedCreature().get() );
			}
			else{
				pet->doAnimation("confused");
				pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			}

		}
		else{
			pet->doAnimation("confused");
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
		}

		return SUCCESS;
	}

};


#endif /* PETEMOTECOMMAND_H_ */
