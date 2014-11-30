
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/skill/SkillModManager.h"

bool WoundPackImplementation::isDroidReconstructionKit() {
	return getObjectNameStringIdName().contains("droid_wound_kit");
}
uint32 WoundPackImplementation::calculatePower(CreatureObject* healer, CreatureObject* patient, bool applyBattleFatigue) {
	float power = getEffectiveness();

	if (applyBattleFatigue) {
		power = power - (power * patient->calculateBFRatio() * healer->calculateBFRatio());
	}

	if (isDroidReconstructionKit()) {
		return power;
	} else {
		int droidBuff = healer->getSkillModOfType("private_medical_rating",SkillModManager::DROID);
		int bldBuff = healer->getSkillModOfType("private_medical_rating", SkillModManager::STRUCTURE);
		int mod = healer->getSkillModOfType("private_medical_rating", SkillModManager::CITY);
		mod +=  droidBuff > bldBuff ? droidBuff : bldBuff;
		float modEnvironment = 1 + ((float) mod / 100.0f);
		float modSkill = (float) healer->getSkillMod("healing_wound_treatment");
		return (power * modEnvironment * (100.0f + modSkill) / 100.0f);
	}
}
