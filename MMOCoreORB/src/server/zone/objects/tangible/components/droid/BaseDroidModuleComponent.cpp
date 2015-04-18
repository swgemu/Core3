/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */
#include "BaseDroidModuleComponent.h"

BaseDroidModuleComponent::BaseDroidModuleComponent() {
	setLoggingName("DroidModuleDataComponent");
	setLogging(false);
	species = 0;
}
BaseDroidModuleComponent::~BaseDroidModuleComponent() {
}
String BaseDroidModuleComponent::getModuleName() {
	return String("base");
}
void BaseDroidModuleComponent::initializeTransientMembers() {
}
void BaseDroidModuleComponent::initialize(CreatureObject* droid) {
}
void BaseDroidModuleComponent::fillAttributeList(AttributeListMessage* msg, CreatureObject* droid) {
}
void BaseDroidModuleComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
}
int BaseDroidModuleComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {
	return 0;
}
void BaseDroidModuleComponent::loadSkillMods(CreatureObject* player) {
}
void BaseDroidModuleComponent::unloadSkillMods(CreatureObject* player) {

}
bool BaseDroidModuleComponent::skillsByRange() {
	return false;
}
void BaseDroidModuleComponent::handlePetCommand(String cmd, CreatureObject* speaker){

}
int BaseDroidModuleComponent::getBatteryDrain() {
	return 0;
}
void BaseDroidModuleComponent::deactivate() {

}
bool BaseDroidModuleComponent::actsAsCraftingStation() {
	return false;
}
String BaseDroidModuleComponent::toString() {
	StringBuffer str;
	str << getModuleName() << "\n";
	return str.toString();
}
void BaseDroidModuleComponent::onCall() {
}
void BaseDroidModuleComponent::onStore() {
}
ManagedReference<DroidObject*> BaseDroidModuleComponent::getDroidObject() {
	ManagedReference<DroidObject*> droid = cast<DroidObject*>(getParent()->getParentRecursively(SceneObjectType::DROIDCREATURE).get().get());
	return droid;
}

void BaseDroidModuleComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
}
