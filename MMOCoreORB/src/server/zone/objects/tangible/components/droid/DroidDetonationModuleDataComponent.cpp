/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidDetonationModuleDataComponent.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/events/DroidDetonationTask.h"
#include "server/zone/objects/creature/CreatureObject.h"

DroidDetonationModuleDataComponent::DroidDetonationModuleDataComponent() {
	setLoggingName("DroidDetonationModule");
	rating = 0;
	moduleCount = 0;
	initialized = false;
	started = false;
	mseDroid = false;
	advanced = false;
}

DroidDetonationModuleDataComponent::~DroidDetonationModuleDataComponent() {

}

String DroidDetonationModuleDataComponent::getModuleName() {
	return String("detonation_module");
}

void DroidDetonationModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("bomb_level");
}

void DroidDetonationModuleDataComponent::initialize(DroidObject* droid) {
	if (droid->getSpecies() == DroidObject::MSE) {
		mseDroid = true;
	}

	// ensure state on init
	started = false;
	initialized = false;
}

void DroidDetonationModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	/*for (int i = 0; i < droidComponent->getPropertyCount(); i++) {
		String prop = droidComponent->getProperty(i);
	}*/

	if (droidComponent->hasKey("bomb_level")) {
		rating = droidComponent->getAttributeValue("bomb_level");
	}

	if (droidComponent->hasKey("module_count")) {
		moduleCount = droidComponent->getAttributeValue("module_count");
	}

	if (droidComponent->hasKey("species")) {
		species = droidComponent->getAttributeValue("species");
	}

	if (species == DroidObject::MSE) {
		mseDroid = true;
	}
}

void DroidDetonationModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	if (mseDroid) {
		int bonus = moduleCount * 10;
		alm->insertAttribute("bomb_level", rating + bonus);
	} else {
		alm->insertAttribute( "bomb_level", rating);
	}
}

void DroidDetonationModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == NULL)
		return;

	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == NULL)
		return;

	ManagedReference<CreatureObject*> owner = droid->getLinkedCreature().get();

	if (owner == NULL)
		return;

	// Novice Bounty Hunter or Smuggler required to access radial
	if (owner == player && (player->hasSkill("combat_bountyhunter_novice") || player->hasSkill("combat_smuggler_novice"))) {
		menuResponse->addRadialMenuItemToRadialID(132, DETONATE_DROID, 3, "@pet/droid_modules:detonate_droid");
	}
}

int DroidDetonationModuleDataComponent::calculateDamage(DroidObject* droid) {
	int bonus  = 0;
	if (droid->getSpecies() == DroidObject::MSE)
		bonus = moduleCount * 10;

	// generate a damage value 150 - 200 per module 175 is mid so we calc 150 + 1..50 as damage output
	return (System::random(50) + 150) * (bonus + rating);
}

void DroidDetonationModuleDataComponent::setSpecies(int i) {
	species = i;
	mseDroid = i == DroidObject::MSE;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL) {
		droidComponent->addProperty("species", (float)species, 0, "hidden", true);
	}
}

int DroidDetonationModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {
	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == NULL)
		return 0;

	if (selectedID == DETONATE_DROID) {
		player->enqueueCommand(STRING_HASHCODE("detonatedroid"), 0, droid->getObjectID(), "");
	}

	return 0;
}

void DroidDetonationModuleDataComponent::deactivate() {
	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == NULL) {
		info("Droid is null");
		return;
	}

	Locker dlock(droid);

	droid->removePendingTask("droid_detonation");
}

String DroidDetonationModuleDataComponent::toString() {
	return BaseDroidModuleComponent::toString();
}

void DroidDetonationModuleDataComponent::onCall() {
	initialized = false;
	deactivate();

	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == NULL)
		return;

	ManagedReference<CreatureObject*> owner = droid->getLinkedCreature().get();

	if (owner == NULL)
		return;

	owner->sendSystemMessage("@pet/droid_modules:detonation_warmup");

	Core::getTaskManager()->scheduleTask([droid]{
		if(droid != NULL) {
			Locker locker(droid);

			auto module = droid->getModule("detonation_module").castTo<DroidDetonationModuleDataComponent*>();

			if (module != NULL)
				module->setReadyForDetonation();
		}
	}, "InitDetModuleTask", 10000);
}

void DroidDetonationModuleDataComponent::onStore() {
	initialized = false;
	deactivate();
}

void DroidDetonationModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidDetonationModuleDataComponent* otherModule = cast<DroidDetonationModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	rating = rating + otherModule->rating;
	moduleCount += 1;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL) {
		droidComponent->changeAttributeValue("bomb_level", (float)rating);
		droidComponent->changeAttributeValue("module_count", (float)moduleCount);
	}
}

void DroidDetonationModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidDetonationModuleDataComponent* otherModule = cast<DroidDetonationModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	rating = otherModule->rating;
	moduleCount = 1;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL) {
		droidComponent->addProperty("bomb_level", (float)rating, 0, "exp_effectiveness");
		droidComponent->addProperty("module_count", (float)moduleCount, 0, "hidden", true);
	}
}
