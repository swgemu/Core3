/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "SharedLabratory.h"
#include "server/zone/managers/crafting/CraftingManager.h"

SharedLabratory::SharedLabratory() : Logger("SharedLabratory"){
}

SharedLabratory::~SharedLabratory() {
}

bool SharedLabratory::allowFactoryRun(ManufactureSchematic* manufactureSchematic) {
	return manufactureSchematic->allowFactoryRun();
}

void SharedLabratory::initialize(ZoneServer* server) {
	zoneServer = server;
}

float SharedLabratory::calculateExperimentationValueModifier(int experimentationResult, int pointsAttempted) {
	// Make it so failure detract
	float results;
	switch (experimentationResult) {
	case CraftingManager::AMAZINGSUCCESS:
		results = 0.08f;
		break;
	case CraftingManager::GREATSUCCESS:
		results = 0.07f;
		break;
	case CraftingManager::GOODSUCCESS:
		results = 0.055f;
		break;
	case CraftingManager::MODERATESUCCESS:
		results = 0.015f;
		break;
	case CraftingManager::SUCCESS:
		results = 0.01f;
		break;
	case CraftingManager::MARGINALSUCCESS:
		results = 0.00f;
		break;
	case CraftingManager::OK:
		results = -0.04f;
		break;
	case CraftingManager::BARELYSUCCESSFUL:
		results = -0.07f;
		break;
	case CraftingManager::CRITICALFAILURE:
		results = -0.08f;
		break;
	default:
		results = 0;
		break;
	}
	results *= pointsAttempted;
	return results;
}
float SharedLabratory::calculateAssemblyValueModifier(int assemblyResult) {

	if(assemblyResult == CraftingManager::AMAZINGSUCCESS)
		return 1.05f;
	float result = 1.1f - (assemblyResult * .1f);
	return result;
}

float SharedLabratory::getAssemblyPercentage(float value) {

	float percentage = (value * (0.000015f * value + .015f)) * 0.01f;
	return percentage;
}
float SharedLabratory::getWeightedValue(ManufactureSchematic* manufactureSchematic, int type) {

	int nsum = 0;
	float weightedAverage = 0;
	int n = 0;
	int stat = 0;

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {

		Reference<IngredientSlot* > ingredientslot = manufactureSchematic->getSlot(i);
		Reference<DraftSlot* > draftslot = manufactureSchematic->getDraftSchematic()->getDraftSlot(i);

		/// If resource slot, continue
		if(!ingredientslot->isResourceSlot())
			continue;

		ResourceSlot* resSlot = cast<ResourceSlot*>(ingredientslot.get());

		if(resSlot == NULL)
			continue;

		ManagedReference<ResourceSpawn* > spawn = resSlot->getCurrentSpawn();

		if (spawn == NULL) {
			error("Spawn object is null when running getWeightedValue");
			return 0.0f;
		}

		n = draftslot->getQuantity();
		stat = spawn->getValueOf(type);

		if (stat != 0) {

			nsum += n;
			weightedAverage += (stat * n);
		}
	}

	if (weightedAverage != 0)
		weightedAverage /= float(nsum);

	return weightedAverage;
}
int SharedLabratory::calculateAssemblySuccess(CreatureObject* player,DraftSchematic* draftSchematic, float effectiveness){
	// assemblyPoints is 0-12
	/// City bonus should be 10
	float cityBonus = player->getSkillMod("private_spec_assembly");

	float assemblyPoints = ((float)player->getSkillMod(draftSchematic->getAssemblySkill())) / 10.0f;
	int failMitigate = (player->getSkillMod(draftSchematic->getAssemblySkill()) - 100 + cityBonus) / 7;

	if(failMitigate < 0)
		failMitigate = 0;
	if(failMitigate > 5)
		failMitigate = 5;

	// 0.85-1.15
	float toolModifier = 1.0f + (effectiveness / 100.0f);

	//Pyollian Cake

	float craftbonus = 0;
	if (player->hasBuff(BuffCRC::FOOD_CRAFT_BONUS)) {
		Buff* buff = player->getBuff(BuffCRC::FOOD_CRAFT_BONUS);

		if (buff != NULL) {
			craftbonus = buff->getSkillModifierValue("craft_bonus");
			toolModifier *= 1.0f + (craftbonus / 100.0f);
		}
	}

	int luckRoll = System::random(100) + cityBonus;

	if(luckRoll > (95 - craftbonus))
		return CraftingManager::AMAZINGSUCCESS;

	if(luckRoll < (5 - craftbonus - failMitigate))
		luckRoll -= System::random(100);

	//if(luckRoll < 5)
	//	return CRITICALFAILURE;

	luckRoll += System::random(player->getSkillMod("luck") + player->getSkillMod("force_luck"));

	int assemblyRoll = (toolModifier * (luckRoll + (assemblyPoints * 5)));

	if (assemblyRoll > 70)
		return CraftingManager::GREATSUCCESS;

	if (assemblyRoll > 60)
		return CraftingManager::GOODSUCCESS;

	if (assemblyRoll > 50)
		return CraftingManager::MODERATESUCCESS;

	if (assemblyRoll > 40)
		return CraftingManager::SUCCESS;

	if (assemblyRoll > 30)
		return CraftingManager::MARGINALSUCCESS;

	if (assemblyRoll > 20)
		return CraftingManager::OK;

	return CraftingManager::BARELYSUCCESSFUL;
}

