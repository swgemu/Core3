

#include "engine/engine.h"
#include "server/zone/objects/tangible/tool/antidecay/AntiDecayKit.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void AntiDecayKitImplementation::initializeTransientMembers() {

	ContainerImplementation::initializeTransientMembers();

	setLoggingName("AntiDecayKit");
}

void AntiDecayKitImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if(isASubChildOf(player) && getContainerObjectsSize() > 0) {
		menuResponse->addRadialMenuItem(68, 3, "@ui_radial:apply_anti_decay");
		menuResponse->addRadialMenuItem(69, 3, "@ui_radial:retrieve_items_from_anti_decay_kit");
	}
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

int AntiDecayKitImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if(isASubChildOf(player)) {
		switch(selectedID){
		case 68:
			doApplyAntiDecay(player);
			break;
		case 69:
			doRetrieveItem(player);
			break;
		}
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void AntiDecayKitImplementation::doApplyAntiDecay(CreatureObject* player)
{
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if(inventory == NULL || getContainerObjectsSize() < 1)
		return;

	if(getContainerObjectsSize() > 1){
		player->sendSystemMessage("@veteran_new:error_kit_has_too_many_items"); // This Anti Decay Kit can only function with one item inside. There are currently more than one item inside. Please remove the items from the Anti Decay Kit first by selecting the "Retrieve Item" menu option before continuing to use this Anti Decay Kit.
		return;
	}

	ManagedReference<TangibleObject*> tano = getContainerObject(0).castTo<TangibleObject*>();
	if(tano == NULL){
		player->sendSystemMessage("@veteran_new:failed_item_not_made_anti_decay"); // The Anti Decay Kit failed to apply Anti Decay to this item.
		return;
	}

	Locker locker(tano, player);

	if(inventory->isContainerFullRecursive()){
		player->sendSystemMessage("@veteran_new:failed_item_cannot_be_placed_in_inventory"); // The Anti Decay Kit failed to place an item back into your inventory. Please make sure that your inventory has room for this item and try again.
		return;
	}

	tano->setConditionDamage(0);
	tano->applyAntiDecayKit(player, _this.getReferenceUnsafeStaticCast());

	inventory->transferObject(tano, -1, false);
	tano->sendTo(player, true);

	setUsed(true);

	player->sendSystemMessage("@veteran_new:successfully_used_anti_decay_kit"); // You have successfully used the Anti Decay Kit. The item you used this Anti Decay Kit on will no longer require insurance nor will decay from use.
}

void AntiDecayKitImplementation::doRetrieveItem(CreatureObject* player)
{
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if(inventory == NULL || getContainerObjectsSize() < 1)
		return;

	if(inventory->getContainerVolumeLimit() < (inventory->getCountableObjectsRecursive() + getCountableObjectsRecursive())){
		player->sendSystemMessage("@veteran_new:failed_item_cannot_be_placed_in_inventory"); // The Anti Decay Kit failed to place an item back into your inventory. Please make sure that your inventory has room for this item and try again.
		return;
	}

	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = getContainerObject(i);
		if(object != NULL){
			inventory->transferObject(object, -1, false);
			object->sendTo(player, true);
		}
	}
}

int AntiDecayKitImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if (used) {
		errorDescription = "@veteran_new:error_kit_already_used"; // This Anti Decay Kit has already been used and can not be used again.
		return TransferErrorCode::CANTADD;
	}

	ManagedReference<SceneObject*> parent = getParentRecursively(SceneObjectType::PLAYERCREATURE).get();

	if (parent == NULL){
		errorDescription = "@veteran_new:error_kit_not_in_player_inventory"; // This Anti Decay Kit can only be used when it is in your inventory.
		return TransferErrorCode::MUSTBEINPLAYERINVENTORY;
	}

	SceneObject* inventory = parent->getSlottedObject("inventory");
	if (inventory == NULL || !inventory->hasObjectInContainer(getObjectID())){
		errorDescription = "@veteran_new:error_kit_not_in_player_inventory"; // This Anti Decay Kit can only be used when it is in your inventory.
		return TransferErrorCode::MUSTBEINPLAYERINVENTORY;
	}

	if(getContainerObjectsSize() > 0){
		errorDescription = "@veteran_new:error_kit_already_has_item"; // This Anti Decay Kit already has an item inside. Please use the Anti Decay Kit or retrieve the item from the Anti Decay Kit by using the radial menu options on the Anti Decay Kit.
		return TransferErrorCode::CONTAINERFULL;
	}

	if (!inventory->hasObjectInContainer(object->getObjectID())){
		errorDescription = "@veteran_new:error_item_not_in_player_inventory"; // You can only use the Anti Decay Kit on an item that is in your inventory.
		return TransferErrorCode::MUSTBEINPLAYERINVENTORY;
	}

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);

	if(!(object->isWeaponObject() || object->isWearableObject()) || tano->isBroken()){
		errorDescription = "@veteran_new:error_item_not_valid_for_anti_decay"; // This item is not valid to be used by the Anti Decay Kit. Valid items are items that can be insured and weapons.
		return TransferErrorCode::INVALIDTYPE;
	}

	if(tano->hasAntiDecayKit()){
		errorDescription = "@veteran_new:error_item_is_already_anti_decay"; // The item you attempted to place in the Anti Decay Kit already has Anti Decay applied to it. Please use another item.
		return TransferErrorCode::INVALIDTYPE;
	}

	if (parent->getSlottedObject("inventory")->isContainerFullRecursive()) {
		errorDescription = "@error_message:inv_full"; // Your inventory is full.
		return TransferErrorCode::CONTAINERFULL;
	}

	return ContainerImplementation::canAddObject(object, containmentType, errorDescription);
}
