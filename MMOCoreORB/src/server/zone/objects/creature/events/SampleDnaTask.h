#ifndef SAMPLEDNATASK_H_
#define SAMPLEDNATASK_H_

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/templates/tangible/DnaSampleTemplate.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"
#include "engine/engine.h"

class SampleDnaTask : public Task {

private:
	enum Phase { BEGIN, SAMPLING, END} currentPhase;
	int waitCount;
	int originalMask;
	int faction;
	ManagedReference<Creature*> creature;
	ManagedReference<CreatureObject*> player;
public:

	SampleDnaTask(Creature* cre, CreatureObject* playo) : Task() {
		currentPhase = BEGIN;
		waitCount = 0;
		creature = cre;
		player = playo;
		originalMask = creature->getPvpStatusBitmask();
		faction = creature->getFaction();
	}
	void resetCreatureStatus() {
		creature->setFaction(faction);
		creature->setPvpStatusBitmask(originalMask,true);
	}
	void prepareCreatureForSampling() {
		creature->setFaction(player->getFaction());
		creature->setPvpStatusBitmask(CreatureFlag::NONE,true);
	}
	void run() {
		Locker locker(player);
		Locker crosslocker(creature,player);
		player->removePendingTask("sampledna");
		if (!creature->isInRange(player, 16.f) ) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_out_of_range");
			resetCreatureStatus();
			return;
		}
		if (creature->isDead()) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_target_corpse");
			resetCreatureStatus();
			return;
		}
		if (creature->isInCombat()) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_creature_in_combat");
			resetCreatureStatus();
			return;
		}
		if (!creature->hasDNA()){
			player->sendSystemMessage("@bio_engineer:harvest_dna_cant_harvest");
			resetCreatureStatus();
			return;
		}
		int mindCost = player->calculateCostAdjustment(CreatureAttribute::FOCUS, 200);
		int skillMod = player->getSkillMod("dna_harvesting");
		int cl = creature->getLevel();
		switch(currentPhase){
			case BEGIN:
				// We should be good to go now and try the sample
				if (player->getHAM(CreatureAttribute::MIND) < mindCost) {
					player->sendSystemMessage("@bio_engineer:harvest_dna_attrib_too_low");
				} else {
					prepareCreatureForSampling();
					player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false, true);
					player->sendSystemMessage("@bio_engineer:harvest_dna_begin_harvest");
					currentPhase = SAMPLING;
					// We grab the original mask and faction in ctor
					// Turn off attackable flag while sampling (publish 3)
					// now rescheudle ourselves
					player->addPendingTask("sampledna",this,1000);
					player->doAnimation("heal_other");
				}
				break;
			case SAMPLING:
				if (waitCount == 9) {
					currentPhase = END;
				}else {
					waitCount++;
				}
				player->addPendingTask("sampledna",this,1000);
				break;
			case END:
				// Re-Enable Mask and faction
				resetCreatureStatus();
				// We get stuck apparently sometimes
				bool success = false;
				bool critical = false;
				bool aggro = false;
				bool death = false;
				int result = 1;
				// The old system was stated as if the HAM > 13k would could not sample at all
				// however we have creature data such as mutant rancor vs enraged rancor, both have the same HAM settings.
				// but their levels are 75 vs 80, so either our template data is wrong is HAM was never a factor.
				// Need to revist the 5 states are
				// 1. Critical Failure -> creature attacks
				// 2. Failure -> no Op
				// 3. Success -> attacks
				// 4. Success -> Dies
				// 5. Success -> no change
				// Lower skill more likely it dies on 1 sample (i.e. max sample count == dies)
				// If 5, then inc count on creature. When it maxes for your skill it dies.
				// Higher skill, lower chance of aggro
				int sampleRoll = System::random(100);
				sampleRoll += System::random(player->getSkillMod("luck") + player->getSkillMod("force_luck"));
				// need to revist master against CL70 i.e. ((100-70)/70) + (100-70) = 0 + (30) = 30/2 = ( roll mod is 15)
				// need to revist master against CL2 i.e. ((100-2)/2) + (100-2) = 49 + (98) = 147/2 = ( roll mod is 73)
				// so with no luck you need 95 or better roll for amazing
				float rollMod = (((skillMod-cl)/cl))  + (skillMod-cl);
				rollMod /= 2;
				// We have the players roll. NOW to determine if success of failure;
				if (sampleRoll > 75) { // adjust great success ot 75% and above
					int maxSamples = ceil(skillMod/25);
					if (creature->getDnaSampleCount() > maxSamples ){
						creature->setDnaState(CreatureManager::DNASAMPLED);
						// We took the max samples the shock it too much and kils the creature.
						result = 4;
					} else {
						// did we aggro?
						creature->activateAwarenessEvent(player);
						result = 5;
					}
				}
				else if (sampleRoll < 5) {
					// Critical failure, this can always occur
					result = 1;
				} else if ( (35 + rollMod) < sampleRoll) { // failure your roll < 50%
					result = 2;
				} else { // success
					int maxSamples = ceil(skillMod/25);
					if (creature->getDnaSampleCount() > maxSamples ){
						creature->setDnaState(CreatureManager::DNASAMPLED);
						// We took the max samples the shock it too much and kils the creature.
						result = 4;
					} else {
						// did we aggro?
						int aggroChance = System::random(100);
						int aggroMod = (creature->getDnaSampleCount() * 5);
						if ( (aggroChance+aggroMod) > (sampleRoll+rollMod) || aggroChance <= 5)  // aggro
							result = 3;
						else { // it didnt care and we didnt kill it
							creature->activateAwarenessEvent(player);
							result = 5;
						}
					}
				}
				switch(result) {
					case 1:
						success = false;
						aggro = true;
						break;
					case 2:
						success = false;
						break;
					case 3:
						success = true;
						aggro = true;
						break;
					case 4:
						success = true;
						death = true;
						break;
					case 5:
						success = true;
						break;
					default:
						break;
				}
				if (success && cl <= 75) {
					player->sendSystemMessage("@bio_engineer:harvest_dna_succeed");
					creature->incDnaSampleCount();
					award(cl,rollMod,skillMod);
					if (creature->getDnaSampleCount() > 5) {
						creature->setDnaState(CreatureManager::DNASAMPLED);
					}
					if (aggro) {
						crosslocker.release();
						CombatManager::instance()->startCombat(creature,player,true);
					}
					if (death) {
						killCreature();
					}
				} else {
					player->sendSystemMessage("@bio_engineer:harvest_dna_failed");
					if (aggro) {
						crosslocker.release();
						CombatManager::instance()->startCombat(creature,player,true);
					}
				}
				break;
		}
		return;
	}
	void killCreature() {
		int dam = 9999999;
		creature->inflictDamage(creature, 0, dam, true, false);
		creature->inflictDamage(creature, 3, dam, true, false);
		creature->inflictDamage(creature, 6, dam, true, false);
		StringIdChatParameter str("@bio_engineer:harvest_dna_creature_killed");
		str.setTT(creature->getObjectID());
		creature->addAlreadyHarvested(player);
		creature->setDnaState(CreatureManager::DNADEATH);
		player->sendSystemMessage(str);
	}
	void award(int cl, float rollMod, int skillMod) {
		int xp = DnaManager::instance()->generateXp(cl);
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();
		if(playerManager != NULL)
			playerManager->awardExperience(player, "bio_engineer_dna_harvesting", xp, true);
		int quality = 0;
		// generate quality based on skill
		int luckRoll = System::random(100);
		luckRoll += System::random(player->getSkillMod("luck") + player->getSkillMod("force_luck"));
		int qualityRoll = luckRoll + rollMod;

		int low = 7;
		int mid = 6;
		int high = 5;
		if (skillMod <= 15) {
			low = 7;mid=6;high=5;
		}
		else if (skillMod <= 30 ) {
			low = 7; mid = 6; high = 5;
		}
		else if (skillMod <= 45) {
			low = 6; mid = 5; high = 4;
		}
		else if (skillMod <= 60) {
			low = 5; mid = 4; high = 3;
		}
		else if (skillMod <= 75) {
			low = 4; mid = 3; high = 2;
		}
		else {
			low = 3; mid = 2; high = 1;
		}
		//15 	VLQ, LQ, BAQ
		//30 	VLQ, LQ, BAQ
		//45 	LQ, BAQ, AQ
		//60 	BAQ, AQ,AAQ
		//75 	AQ,AAQ,HQ
		//100 	AAQ,HQ, VHQ
		if (qualityRoll < 33)
			quality = low;
		else if (qualityRoll < 66)
			quality = mid;
		else
			quality = high;
		DnaManager::instance()->generateSample(creature,player,quality);
	}
};
#endif //SAMPLEDNATASK_H_
