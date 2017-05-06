
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/skill/SkillModManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/FactionStatus.h"

bool WoundPackImplementation::isDroidReconstructionKit() {
	return getObjectNameStringIdName().contains("droid_wound_kit");
}
uint32 WoundPackImplementation::calculatePower(CreatureObject* healer, CreatureObject* patient, bool applyBattleFatigue) {
	float power = getEffectiveness();

	if (applyBattleFatigue)
		power *= patient->calculateBFRatio();

	if (isDroidReconstructionKit()) {
		return power;
	}

	int droidBuff = healer->getSkillModOfType("private_medical_rating",SkillModManager::DROID);
	int bldBuff = healer->getSkillModOfType("private_medical_rating", SkillModManager::STRUCTURE);
	int mod = healer->getSkillModOfType("private_medical_rating", SkillModManager::CITY);
	mod +=  droidBuff > bldBuff ? droidBuff : bldBuff;

	int factionPerk = healer->getSkillMod("private_faction_medical_rating");

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(healer->getRootParent());

	if (building != NULL && factionPerk > 0 && building->isPlayerRegisteredWithin(healer->getObjectID())) {
		unsigned int buildingFaction = building->getFaction();
		unsigned int healerFaction = healer->getFaction();

		if (healerFaction != 0 && healerFaction == buildingFaction && healer->getFactionStatus() == FactionStatus::OVERT) {
			mod += factionPerk;
		}
	}

	float modEnvironment = 1 + ((float) mod / 100.0f);
	float modSkill = (float) healer->getSkillMod("healing_wound_treatment");
	return (power * modEnvironment * (100.0f + modSkill) / 100.0f);
}
