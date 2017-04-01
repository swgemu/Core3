#include "ScavengerDroidContainerComponent.h"
#include "server/zone/objects/tangible/eventperk/ScavengerDroid.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

int ScavengerDroidContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const {
	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(sceneObject);

	if (creature == NULL)
		return TransferErrorCode::INVALIDTYPE;

	ManagedReference<ScavengerDroid*> droid = cast<ScavengerDroid*>(creature.get());

	if (droid == NULL)
		return TransferErrorCode::INVALIDTYPE;

	ManagedReference<CreatureObject*> player = object->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (player == NULL)
		return TransferErrorCode::INVALIDTYPE;

	EventPerkDataComponent* gameData = cast<EventPerkDataComponent*>(droid->getDataObjectComponent()->get());

	if (gameData == NULL)
		return TransferErrorCode::INVALIDTYPE;

	EventPerkDeed* deed = gameData->getDeed();

	if (deed == NULL)
		return TransferErrorCode::INVALIDTYPE;

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	if (owner == NULL)
		return TransferErrorCode::INVALIDTYPE;

	int gameStatus = droid->getGameStatus();
	String itemTemplate = object->getObjectTemplate()->getFullTemplateString();

	if (gameStatus == ScavengerDroid::GAMESETUP) {
		if (player != owner) {
			return TransferErrorCode::CANTADD;
		} else if (droid->getItemListSize() >= 10) {
			player->sendSystemMessage("@event_perk:scavenger_max_items");
			return TransferErrorCode::CANTADD;
		} else if (droid->hasItemInItemList(itemTemplate)) {
			player->sendSystemMessage("@event_perk:scavenger_already_added");
			return TransferErrorCode::CANTADD;
		} else {
			return TransferErrorCode::SUCCESS;
		}
	} else if (gameStatus == ScavengerDroid::GAMESTARTED) {
		if (droid->hasItemInPlayerItemList(player->getObjectID(), itemTemplate)) {
			player->sendSystemMessage("@event_perk:scavenger_already_turned_in");
			return TransferErrorCode::CANTADD;
		} else if (droid->hasItemInItemList(itemTemplate)) {
			return TransferErrorCode::SUCCESS;
		}
	}

	return TransferErrorCode::CANTADD;
}

bool ScavengerDroidContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) const {
	ManagedReference<CreatureObject*> player = object->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (player == NULL)
		return false;

	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(sceneObject);

	if (creature == NULL)
		return false;

	ManagedReference<ScavengerDroid*> droid = cast<ScavengerDroid*>(creature.get());

	if (droid == NULL)
		return false;

	String itemTemplate = object->getObjectTemplate()->getFullTemplateString();

	int gameStatus = droid->getGameStatus();

	player->sendSystemMessage("@event_perk:scavenger_you_showed_me " + object->getObjectTemplate()->getObjectName());

	if (gameStatus == ScavengerDroid::GAMESETUP) {
		droid->addToItemList(itemTemplate);
	} else if (gameStatus == ScavengerDroid::GAMESTARTED) {
		droid->addToPlayerItemList(player->getObjectID(), itemTemplate);
		droid->updatePlayerScore(player);
	}

	return false;
}
