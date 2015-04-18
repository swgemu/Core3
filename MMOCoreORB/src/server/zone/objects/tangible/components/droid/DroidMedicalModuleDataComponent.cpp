/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidMedicalModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"

DroidMedicalModuleDataComponent::DroidMedicalModuleDataComponent() {
	setLoggingName("DroidMedicalModule");
	rating = 0;
}
DroidMedicalModuleDataComponent::~DroidMedicalModuleDataComponent() {

}
String DroidMedicalModuleDataComponent::getModuleName() {
	return String("medical_module");
}
void DroidMedicalModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey( "medical_module")) {
		rating = droidComponent->getAttributeValue( "medical_module");
	}
}
void DroidMedicalModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("medical_module");
}
int DroidMedicalModuleDataComponent::getMedicalRating() {
	switch(rating) {
		case 1:
		case 2:
			return 55;
		case 3:
		case 4:
			return 65;
		case 5:
		case 6:
			return 75;
		case 7:
		case 8:
			return 85;
		case 9:
		case 10:
			return 100;
	}
	return 110;
}
void DroidMedicalModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute( "medical_module", getMedicalRating() );
}
String DroidMedicalModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidMedicalModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidMedicalModuleDataComponent* otherModule = cast<DroidMedicalModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = rating + otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->changeAttributeValue("medical_module",(float)rating);
}
void DroidMedicalModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidMedicalModuleDataComponent* otherModule = cast<DroidMedicalModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->addProperty("medical_module",(float)rating,0,"exp_effectiveness");
}
void DroidMedicalModuleDataComponent::onCall() {
	// no op
}
void DroidMedicalModuleDataComponent::onStore() {
	// no op on store
}
void DroidMedicalModuleDataComponent::loadSkillMods(CreatureObject* player) {
	// add the rating to the player as a private medical center for right now we ignore the part about not usable in a static cantina we will handle that in the injury treatment task
	// only add this is the payer didnt have it already.
	player->removeAllSkillModsOfType(SkillModManager::DROID,true);
	player->addSkillMod(SkillModManager::DROID,"private_medical_rating",getMedicalRating(),true);
}
void DroidMedicalModuleDataComponent::unloadSkillMods(CreatureObject* player) {
	player->removeAllSkillModsOfType(SkillModManager::DROID,true);
	//player->removeSkillMod(SkillModManager::DROID,"private_medical_rating",true);
}

