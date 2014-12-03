#include "server/zone/objects/tangible/pharmaceutical/EnhancePack.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/skill/SkillModManager.h"

uint32 EnhancePackImplementation::calculatePower(CreatureObject* healer, CreatureObject* patient, bool applyBattleFatigue) {
		float power = getEffectiveness();

		if (applyBattleFatigue)
			power = power - (power * patient->calculateBFRatio() * healer->calculateBFRatio());
		int droidBuff = healer->getSkillModOfType("private_medical_rating",SkillModManager::DROID);
		int bldBuff = healer->getSkillModOfType("private_medical_rating", SkillModManager::STRUCTURE);
		int mod = healer->getSkillModOfType("private_medical_rating", SkillModManager::CITY);
		mod +=  droidBuff > bldBuff ? droidBuff : bldBuff;
		float modEnvironment = ((float) mod / 100);
		float modSkill = (float) healer->getSkillMod("healing_wound_treatment");

		return power * modEnvironment * (100 + modSkill) / 100;
}
