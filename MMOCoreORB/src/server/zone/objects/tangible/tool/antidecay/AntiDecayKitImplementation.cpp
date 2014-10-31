

#include "engine/engine.h"
#include "server/zone/objects/tangible/tool/antidecay/AntiDecayKit.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
//#include "server/zone/templates/tangible/tool/RecycleToolTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void AntiDecayKitImplementation::initializeTransientMembers() {

	ContainerImplementation::initializeTransientMembers();

	setLoggingName("AntiDecayKit");
}

void AntiDecayKitImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if(isASubChildOf(player) && getContainerObjectsSize() > 0) {
		menuResponse->addRadialMenuItem(101, 3, "Apply Anti Decay");
		menuResponse->addRadialMenuItem(102, 3, "Retrieve Item");
	}
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

int AntiDecayKitImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	Reference<PlayerObject*> playerObject = player->getPlayerObject();

	if(isASubChildOf(player) && getContainerObjectsSize() > 0) {
		switch(selectedID){
		case 101:
			doApplyAntiDecay(player);
			break;
		case 102:
			doRetrieveItem(player);
			break;
		}
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void AntiDecayKitImplementation::doApplyAntiDecay(CreatureObject* player)
{
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if(inventory == NULL)
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

	tano->applyAntiDecayKit(player, _this.get());

	inventory->transferObject(tano, -1, false);
	tano->sendTo(player, true);

	player->sendSystemMessage("@veteran_new:successfully_used_anti_decay_kit");
}

void AntiDecayKitImplementation::doRetrieveItem(CreatureObject* player)
{
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if(inventory == NULL)
		return;

	if(inventory->isContainerFull() || inventory->getContainerVolumeLimit() < inventory->getContainerObjectsSize() + getContainerObjectsSize() ){
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
