/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidCraftingModuleDataComponent.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/templates/tangible/DroidCraftingModuleTemplate.h"

DroidCraftingModuleDataComponent::DroidCraftingModuleDataComponent() : craftingType(0) {
	setLoggingName("DroidCraftingModule");
}
DroidCraftingModuleDataComponent::~DroidCraftingModuleDataComponent() {

}
String DroidCraftingModuleDataComponent::getModuleName() {
	if (isClothingArmor())
		return "crafting_clothing";
	if(isWeaponDroidGeneric())
		return "crafting_weapon";
	if(isFoodChemical())
		return "crafting_food";
	if(isStructureFurniture())
		return "crafting_structure";
	if(isShip())
		return "crafting_ship";

	return "crafting_unknown";
}
void DroidCraftingModuleDataComponent::initializeTransientMembers() {
	// load template data here
	SceneObject* craftedModule = getParent();
	if (craftedModule == NULL) {
		return;
	}
	craftingStation = NULL;
	ManagedReference<DroidCraftingModuleTemplate*> moduleTemplate = cast<DroidCraftingModuleTemplate*>(craftedModule->getObjectTemplate());
	if (moduleTemplate == NULL){
		info("Module was null");
		return;
	}
	craftingType = moduleTemplate->getCraftingType();
	attributeListString = moduleTemplate->getAttributeListString();
}
void DroidCraftingModuleDataComponent::initialize(CreatureObject* droid) {
	// do we need to change any droid stats: no
}
void DroidCraftingModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute(attributeListString, "Installed");
}
void DroidCraftingModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// no menu options
}
int DroidCraftingModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {
	// no menu options
	return 0;
}
void DroidCraftingModuleDataComponent::loadSkillMods(CreatureObject* player) {
	// no op
}
void DroidCraftingModuleDataComponent::unloadSkillMods(CreatureObject* player) {
	// no op
}
bool DroidCraftingModuleDataComponent::skillsByRange() {
	// no op
	return false;
}
void DroidCraftingModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker) {
	// no op
}
int DroidCraftingModuleDataComponent::getBatteryDrain() {
	return 0;
}
void DroidCraftingModuleDataComponent::deactivate() {
	// no op
}
bool DroidCraftingModuleDataComponent::actsAsCraftingStation(){
	return true;
}
String DroidCraftingModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
// crafting droid module specific
CraftingStation* DroidCraftingModuleDataComponent::getCraftingStation(){
	return craftingStation;
}
bool DroidCraftingModuleDataComponent::isWeaponDroidGeneric(){
	return craftingType == CraftingTool::WEAPON;
}
bool DroidCraftingModuleDataComponent::isFoodChemical(){
	return craftingType == CraftingTool::FOOD;
}
bool DroidCraftingModuleDataComponent::isClothingArmor(){
	return craftingType == CraftingTool::CLOTHING;
}
bool DroidCraftingModuleDataComponent::isStructureFurniture(){
	return craftingType == CraftingTool::STRUCTURE;
}
bool DroidCraftingModuleDataComponent::isShip(){
	return craftingType == CraftingTool::SPACE;
}
bool DroidCraftingModuleDataComponent::validCraftingType(int type) {
	return craftingType == type;
}
void DroidCraftingModuleDataComponent::onCall() {
	SceneObject* craftedModule = getParent();
	ManagedReference<DroidCraftingModuleTemplate*> moduleTemplate = cast<DroidCraftingModuleTemplate*>(craftedModule->getObjectTemplate());
	if( craftingStation == NULL ){
		String stationTemplate = moduleTemplate->getCraftingStationTemplate();
		craftingStation = (craftedModule->getZoneServer()->createObject(stationTemplate.hashCode(), 0)).castTo<CraftingStation*>();
		craftingStation->setEffectiveness(25);
	}
}
void DroidCraftingModuleDataComponent::onStore() {
	craftingStation = NULL;
}

void DroidCraftingModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	// no Op when the new object is made, init transient is called so all info is set.
}

