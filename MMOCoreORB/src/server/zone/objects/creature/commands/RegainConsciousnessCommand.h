/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REGAINCONSCIOUSNESSCOMMAND_H_
#define REGAINCONSCIOUSNESSCOMMAND_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/buffs/PrivateBuff.h"
#include "server/zone/objects/creature/buffs/PrivateSkillMultiplierBuff.h"

#include "JediQueueCommand.h"

class RegainConsciousnessCommand : public JediQueueCommand {
public:

	RegainConsciousnessCommand(const String& name, ZoneProcessServer* server)
	: JediQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		// They should be dead...
		if (creature->isDead()){

			int res = doCommonJediSelfChecks(creature);
			if(res != SUCCESS)
				return res;

			doForceCost(creature);

			// Cut Force Regen in Half for 30 Minutes.
			ManagedReference<PrivateSkillMultiplierBuff *> regenDebuff = new PrivateSkillMultiplierBuff(creature, STRING_HASHCODE("private_force_regen_debuff"), 60*30, BuffType::JEDI);
			Locker regenLocker(regenDebuff);
			regenDebuff->setSkillModifier("private_force_regen_divisor", 2);
			// TODO: Find potential end message for force regen debuff


			// Apply grogginess debuff
			ManagedReference<PrivateBuff *> groggyDebuff = new PrivateBuff(creature, STRING_HASHCODE("private_groggy_debuff"), 60, BuffType::JEDI);
			Locker groggyLocker(groggyDebuff);

			for(int i=0; i<CreatureAttribute::ARRAYSIZE; i++)
				groggyDebuff->setAttributeModifier(i, -100);
			// TODO: Find potential end message for groggy debuff

			// Add buffs to creature
			creature->addBuff(groggyDebuff);
			creature->addBuff(regenDebuff);

			ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

			//close clone window
			playerObject->removeSuiBoxType(SuiWindowType::CLONE_REQUEST);

			//send hard coded buff messages
			creature->sendSystemMessage("Your grogginess will expire in 60.0 seconds.");
			creature->sendSystemMessage("Your force regeneration rate has been temporarily reduced due to your near death experience.");

			// Jedi XP Loss
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->awardExperience(creature, "jedi_general", -50000, true);

			StringIdChatParameter message("base_player","prose_revoke_xp");
			message.setDI(-50000);
			message.setTO("exp_n", "jedi_general");
			creature->sendSystemMessage(message);

			// Revive user by setting posture to standing.
			
			creature->removeFeignedDeath();

			creature->setPosture(CreaturePosture::UPRIGHT);

			if(creature->getHAM(CreatureAttribute::HEALTH) <= 0) {
				creature->setHAM(CreatureAttribute::HEALTH, 500, true);
			}

			if(creature->getHAM(CreatureAttribute::ACTION) <= 0) {
				creature->setHAM(CreatureAttribute::ACTION, 500, true);
			}

			if(creature->getHAM(CreatureAttribute::MIND) <= 0) {
				creature->setHAM(CreatureAttribute::MIND, 500, true);
			}


			return SUCCESS;
		}

		return GENERALERROR;

	}

};

#endif //REGAINCONSCIOUSNESSCOMMAND_H_
