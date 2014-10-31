
#ifndef ANTIDECAYKITCONTAINERCOMPONENT_H_
#define ANTIDECAYKITCONTAINERCOMPONENT_H_


#include "server/zone/objects/scene/components/ContainerComponent.h"

class AntiDecayKitContainerComponent : public ContainerComponent {
public:
	int notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) {
		return ContainerComponent::notifyObjectInserted(sceneObject, object);
	}

	bool removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) {
		return ContainerComponent::removeObject(sceneObject, object, destination, notifyClient);
	}

	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {

		ManagedReference<SceneObject*> parent = sceneObject->getParentRecursively(SceneObjectType::PLAYERCREATURE).get();

		if (parent == NULL){
			errorDescription = "@veteran_new:error_kit_not_in_player_inventory"; // This Anti Decay Kit can only be used when it is in your inventory.
			return TransferErrorCode::MUSTBEINPLAYERINVENTORY;
		}

		if(sceneObject->getContainerObjectsSize() > 0){ //FIXME: canAddObject is never called when the container is full. (volumelimit:1)
			errorDescription = "@veteran_new:error_kit_already_has_item"; // This Anti Decay Kit already has an item inside. Please use the Anti Decay Kit or retrieve the item from the Anti Decay Kit by using the radial menu options on the Anti Decay Kit.
			return TransferErrorCode::CONTAINERFULL;
		}

		if (parent != object->getParentRecursively(SceneObjectType::PLAYERCREATURE).get()){
			errorDescription = "@veteran_new:error_item_not_in_player_inventory"; // You can only use the Anti Decay Kit on an item that is in your inventory.
			return TransferErrorCode::MUSTBEINPLAYERINVENTORY;
		}

		if(!object->isTangibleObject() || !(object->isWeaponObject() || object->isWearableObject())){
			errorDescription = "@veteran_new:error_item_not_valid_for_anti_decay"; // This item is not valid to be used by the Anti Decay Kit. Valid items are items that can be insured and weapons.
			return TransferErrorCode::INVALIDTYPE;
		}

		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);
		if(tano->hasAntiDecayKit()){
			errorDescription = "@veteran_new:error_item_is_already_anti_decay"; // The item you attempted to place in the Anti Decay Kit already has Anti Decay applied to it. Please use another item.
			return TransferErrorCode::INVALIDTYPE;
		}

		int containerObjects = parent->getSlottedObject("inventory")->getContainerObjectsSize();

		if (containerObjects >= parent->getSlottedObject("inventory")->getContainerVolumeLimit()) {
			errorDescription = "@error_message:inv_full"; // Your inventory is full.
			return TransferErrorCode::CONTAINERFULL;
		}

		return ContainerComponent::canAddObject(sceneObject, object, containmentType, errorDescription);
	}

	bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow = false) {

		return ContainerComponent::transferObject(sceneObject, object, containmentType, notifyClient, allowOverflow);
	}
};

#endif /* ANTIDECAYKITCONTAINERCOMPONENT_H_ */
