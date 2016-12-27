/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidArmorModuleDataComponent.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"

DroidArmorModuleDataComponent::DroidArmorModuleDataComponent() {
	armorModule = 0;
	setLoggingName("DroidArmorModule");
}

DroidArmorModuleDataComponent::~DroidArmorModuleDataComponent() {

}

String DroidArmorModuleDataComponent::getModuleName() {
	return String("armor_module");
}

void DroidArmorModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	if (droidComponent->hasKey("armor_module")) {
		armorModule = droidComponent->getAttributeValue("armor_module");
	}
}

void DroidArmorModuleDataComponent::initialize(DroidObject* droid) {
	// Change droid resist and armor stat

	int level = armorModule;
	unsigned int armor = 0;
	float resist = 0;

	// Capped at 6
	if (level > 6)
		level = 6;

	// Set armor type
	if (level == 0) {
		armor = 0; // NO ARMOR
	}
	else if (level <= 3) {
		armor = 1; // LIGHT ARMOR
	}
	else if (level <= 6) {
		armor = 2; // MEDIUM ARMOR
	}

	// Set damage resistance
	if (level == 1 || level == 4) {
		resist = 15;
	}
	else if (level == 2 || level == 5) {
		resist = 25;
	}
	else if (level == 3 || level == 6) {
		resist = 40;
	} else {
		resist = 0;
	}

	droid->setArmor(armor);
	droid->setResists(resist);
}

void DroidArmorModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// Armor/resists filled from AiAgent, but add total module level  here for deeds/components
	alm->insertAttribute("armor_module", armorModule);
}

int DroidArmorModuleDataComponent::getBatteryDrain() {
	return 0;
}

String DroidArmorModuleDataComponent::toString() {
	return BaseDroidModuleComponent::toString();
}

void DroidArmorModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	armorModule = values->getCurrentValue("armor_module");
}

void DroidArmorModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {

	DroidArmorModuleDataComponent* otherModule = cast<DroidArmorModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	armorModule = armorModule + otherModule->armorModule;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	// Attribute should have already been created in copy method
	if (!droidComponent->changeAttributeValue( "armor_module", armorModule)) {
		info( "addToStack updateAttributeValue failed");
		return;
	}
}

void DroidArmorModuleDataComponent::copy(BaseDroidModuleComponent* other) {

	DroidArmorModuleDataComponent* otherModule = cast<DroidArmorModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	armorModule = otherModule->armorModule;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	droidComponent->addProperty("armor_module", armorModule, 0, "exp_effectiveness");
}
