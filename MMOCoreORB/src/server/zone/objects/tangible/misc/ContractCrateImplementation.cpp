#include "server/zone/objects/tangible/misc/ContractCrate.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"
#include "templates/manager/TemplateManager.h"

void ContractCrateImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);

	alm->insertAttribute("item_required", itemName);

	if (currentAmount == amountNeeded)
		alm->insertAttribute("job_status", "Complete");
	else
		alm->insertAttribute("job_status", String::valueOf(currentAmount) + " of " + String::valueOf(amountNeeded) + " required");
}


int ContractCrateImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	ManagedReference<CreatureObject*>  player = getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (player == NULL)
		return TransferErrorCode::MUSTBEINPLAYERINVENTORY;

	String itemTemplate = object->getObjectTemplate()->getFullTemplateString();

	if (requiredItem != itemTemplate) {
		errorDescription = "@quest/crafting_contract/system_messages:wrong_item";
		return TransferErrorCode::INVALIDTYPE;
	}

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);

	if (tano == NULL)
		return TransferErrorCode::INVALIDTYPE;

	if (tano->getCraftersName() == "") {
		errorDescription =  "@quest/crafting_contract/system_messages:not_crafted";
		return TransferErrorCode::INVALIDTYPE;
	}

	if (tano->getCraftersName() != player->getFirstName()) {
		errorDescription = "@quest/crafting_contract/system_messages:not_crafter";
		return TransferErrorCode::INVALIDTYPE;
	}

	if (currentAmount == amountNeeded) {
		errorDescription = "@quest/crafting_contract/system_messages:already_complete";
		return TransferErrorCode::INVALIDTYPE;
	}

	return TangibleObjectImplementation::canAddObject(object, containmentType, errorDescription);
}

int ContractCrateImplementation::notifyObjectInserted(SceneObject* object) {
	ManagedReference<CreatureObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (player == NULL)
		return 0;

	currentAmount++;

	if (currentAmount == amountNeeded) {
		player->sendSystemMessage("@quest/crafting_contract/system_messages:job_complete");
	} else {
		StringIdChatParameter str("@quest/crafting_contract/system_messages:items_remaining");
		str.setDI(amountNeeded - currentAmount);
		player->sendSystemMessage(str);
	}

	return 0;
}

int ContractCrateImplementation::notifyObjectRemoved(SceneObject* object) {
	// Cover cases where radial menu options can force an object to be removed despite ContractCrateImplementation::checkContainerPermission
	// Ex: fireworks
	currentAmount--;

	return 0;
}

byte ContractCrateImplementation::checkContainerPermission(CreatureObject* player, uint16 permission) {
	if (permission == ContainerPermissions::MOVEOUT) {
		player->sendSystemMessage("@quest/crafting_contract/system_messages:cannot_remove");

		return false;
	}

	return SceneObjectImplementation::checkContainerPermission(player, permission);
}

void ContractCrateImplementation::parseDraftSchematic(const String& schematic) {
	DraftSchematic* schematicTemplate = SchematicMap::instance()->get(schematic.hashCode());

	if (schematicTemplate == NULL)
		return;

	xpType = schematicTemplate->getXpType();
	itemName = schematicTemplate->getCustomName();
	xpAmount = schematicTemplate->getXpAmount();
}
