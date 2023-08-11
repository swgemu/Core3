#include "server/zone/objects/tangible/pharmaceutical/EnhancePack.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/skill/SkillModManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/FactionStatus.h"

uint32 EnhancePackImplementation::calculatePower(CreatureObject* healer, CreatureObject* patient, bool applyBattleFatigue) {
		float power = getEffectiveness();

		if (applyBattleFatigue)
			power *= patient->calculateBFRatio();

		int mod = healer->getSkillModOfType("private_medical_rating", SkillModManager::CITY);

		int droidBuff = healer->getSkillModOfType("private_medical_rating",SkillModManager::DROID);
		int bldBuff = healer->getSkillModOfType("private_medical_rating", SkillModManager::STRUCTURE);

		// Mantis #8884 - Building buff ratings should override a droid buff rating
		if (bldBuff > 0) {
			mod += bldBuff;
		} else {
			mod += droidBuff;
		}

		int factionPerk = healer->getSkillMod("private_faction_medical_rating");

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(healer->getRootParent());

		if (building != nullptr && factionPerk > 0 && building->isPlayerRegisteredWithin(healer->getObjectID())) {
			unsigned int buildingFaction = building->getFaction();
			unsigned int healerFaction = healer->getFaction();

			if (healerFaction != 0 && healerFaction == buildingFaction && healer->getFactionStatus() == FactionStatus::OVERT) {
				mod += factionPerk;
			}
		}

		float modEnvironment = ((float) mod / 100);
		float modSkill = (float) healer->getSkillMod("healing_wound_treatment");

		return power * modEnvironment * (100 + modSkill) / 100;
}
