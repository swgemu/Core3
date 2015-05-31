#ifndef SAMPLEDEEDTASK_H_
#define SAMPLEDEEDTASK_H_

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/pet/PetDeed.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/templates/tangible/DnaSampleTemplate.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"
#include "engine/engine.h"

class SampleDeedTask : public Task {

private:
	enum Phase { BEGIN, SAMPLING, END} currentPhase;
	int waitCount;
	ManagedReference<PetDeed*> deed;
	ManagedReference<CreatureObject*> player;
public:

	SampleDeedTask(PetDeed* obj, CreatureObject* playo) : Task() {
		currentPhase = BEGIN;
		waitCount = 0;
		deed = obj;
		player = playo;
	}
	void run() {
		if (deed == NULL)
			return;
		if (deed->isGenerated()) {
			return;
		}
		if(!player->hasSkill("outdoors_bio_engineer_novice") || !deed->isASubChildOf(player)) {
			return;
		}
		Locker locker(player);
		Locker crosslocker(deed,player);
		player->removePendingTask("sampledeed");

		int mindCost = player->calculateCostAdjustment(CreatureAttribute::FOCUS, 200);
		int skillMod = player->getSkillMod("dna_harvesting");
		int cl = deed->getLevel();
		if (skillMod < 1 || cl > skillMod + 15){
			player->sendSystemMessage("@bio_engineer:harvest_dna_skill_too_low");
			return;
		}

		switch(currentPhase){
			case BEGIN:
				// We should be good to go now and try the sample
				if (player->getHAM(CreatureAttribute::MIND) < mindCost) {
					player->sendSystemMessage("@bio_engineer:harvest_dna_attrib_too_low");
				} else {
					player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false, true);
					player->sendSystemMessage("@bio_engineer:harvest_dna_begin_harvest");
					currentPhase = SAMPLING;
					player->addPendingTask("sampledeed",this,1000);
				}
				break;
			case SAMPLING:
				if (waitCount == 9) {
					currentPhase = END;
				}else {
					waitCount++;
				}
				player->addPendingTask("sampledeed",this,1000);
				break;
			case END:
				int count = deed->getSampleCount();
				int level = deed->getLevel();
				int skillMod = player->getSkillMod("dna_harvesting");
				float rollMod = (((skillMod-level)/level))  + (skillMod-level);
				int sampleRoll = System::random(100);
				sampleRoll += System::random(player->getSkillMod("luck") + player->getSkillMod("force_luck"));
				// max samples 1/2 of real creatures
				int maxSamples = (int) ceil((float)skillMod/25.f)/2.f;
				deed->incrementSampleCount();
				if ((30 + rollMod) < sampleRoll || cl > 75) {
					// failure but we increment the count
					player->sendSystemMessage("@bio_engineer:harvest_dna_failed");
				} else {
					player->sendSystemMessage("@bio_engineer:harvest_dna_succeed");
					award(cl,rollMod);
					if (count >= maxSamples ){
						// nuke deed you killed it
						ManagedReference<SceneObject*> deedContainer = deed->getParent();
						if (deedContainer != NULL) {
							deed->destroyObjectFromWorld(true);
						}
						deed->destroyObjectFromDatabase(true);
					}
				}
				break;
		}
		return;
	}

	void award(int cl, float rollMod) {
		int xp = DnaManager::instance()->generateXp(cl);
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();
		if(playerManager != NULL)
			playerManager->awardExperience(player, "bio_engineer_dna_harvesting", xp, true);
		int quality = deed->getQuality();
		int newQuality = quality;
		// generate quality based on skill
		int luckRoll = System::random(100);
		luckRoll += System::random(player->getSkillMod("luck") + player->getSkillMod("force_luck"));
		int qualityRoll = luckRoll + rollMod;
		if (qualityRoll > 60)
			newQuality += 0;
		else if (qualityRoll > 50)
			newQuality += 1;
		else if (qualityRoll > 40)
			newQuality += 2;
		else if (qualityRoll > 30)
			newQuality += 3;
		else if (qualityRoll > 20)
			newQuality += 4;
		else if (qualityRoll > 10)
			newQuality += 5;
		else
			newQuality += 6;
		if(newQuality > 7)
			newQuality = 7;
		DnaManager::instance()->generationalSample(deed,player,newQuality);
	}
};
#endif //SAMPLEDEEDTASK_H_
