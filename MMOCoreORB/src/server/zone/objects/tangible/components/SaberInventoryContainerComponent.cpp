/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "SaberInventoryContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/component/lightsaber/LightsaberCrystalComponent.h"

int SaberInventoryContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const {

	ManagedReference<SceneObject*> p = sceneObject->getParent().get();

	if (p != NULL){
		int containment = p->getContainmentType();

		if (containment == 4) {
			errorDescription = "@jedi_spam:saber_not_while_equpped";
			return TransferErrorCode::INVALIDTYPE;
		}
	}

	if (!object->isLightsaberCrystalObject()) {
		errorDescription = "@jedi_spam:saber_not_crystal";
		return TransferErrorCode::INVALIDTYPE;
	}

	LightsaberCrystalComponent* crystal = cast<LightsaberCrystalComponent*> (object);

	if (crystal->getOwnerID() == 0) {
		errorDescription = "@jedi_spam:saber_crystal_not_tuned";
		return TransferErrorCode::INVALIDTYPE;
	}

	ManagedReference<CreatureObject*> creature = crystal->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (creature == NULL || crystal->getOwnerID() != creature->getObjectID()){
		errorDescription = "@jedi_spam:saber_crystal_not_owner";
		return TransferErrorCode::INVALIDTYPE;
	}

	if (crystal->isDestroyed()) {
		errorDescription = "You cannot add a broken crystal to your lightsaber.";
		return TransferErrorCode::INVALIDTYPE;
	}

	if (sceneObject->getContainerObjectsSize() >= sceneObject->getContainerVolumeLimit()) {
		errorDescription = "@container_error_message:container03"; //This container is full.
		return TransferErrorCode::CONTAINERFULL;
	}

	for (int i = 0; i < sceneObject->getContainerObjectsSize(); i++) {
		Reference<LightsaberCrystalComponent*> crystalInside =  sceneObject->getContainerObject(i).castTo<LightsaberCrystalComponent*>();

		if (crystal->getColor() != 31 && crystalInside->getColor() != 31) {
				errorDescription = "@jedi_spam:saber_already_has_color";
				return TransferErrorCode::INVALIDTYPE;
		}
	}

	return 0;
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int SaberInventoryContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) const {
	ManagedReference<WeaponObject*> weao = cast<WeaponObject*>( sceneObject->getParent().get().get());

	Locker locker(weao);

	if (weao->isJediWeapon()) {
		ManagedReference<LightsaberCrystalComponent*> crystal = cast<LightsaberCrystalComponent*>( object);
		if (crystal->getColor() == 31){
			weao->setAttackSpeed(weao->getAttackSpeed() + crystal->getAttackSpeed());
			weao->setMinDamage(weao->getMinDamage() + crystal->getDamage());
			weao->setMaxDamage(weao->getMaxDamage() + crystal->getDamage());
			weao->setHealthAttackCost(weao->getHealthAttackCost() + crystal->getSacHealth());
			weao->setActionAttackCost(weao->getActionAttackCost() + crystal->getSacAction());
			weao->setMindAttackCost(weao->getMindAttackCost() + crystal->getSacMind());
			weao->setWoundsRatio(weao->getWoundsRatio() + crystal->getWoundChance());
			weao->setForceCost(weao->getForceCost() + crystal->getForceCost());
		}

		if (crystal->getColor() != 31) {
			int color = crystal->getColor();
			weao->setBladeColor(color);
			weao->setCustomizationVariable("/private/index_color_blade", color, true);
		}
	}

	return sceneObject->notifyObjectInserted(object);
}

/**
 * Is called when an object was removed
 * @param object object that has been inserted
 */
int SaberInventoryContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) const {
	ManagedReference<WeaponObject*> weao = cast<WeaponObject*>( sceneObject->getParent().get().get());

		if (weao->isJediWeapon()) {
			ManagedReference<LightsaberCrystalComponent*> crystal = cast<LightsaberCrystalComponent*>( object);

			if (crystal->isDestroyed()) {
				return sceneObject->notifyObjectRemoved(object);
			}

			Locker locker(weao);

			if (crystal->getColor() == 31){
				weao->setAttackSpeed(weao->getAttackSpeed() - crystal->getAttackSpeed());
				weao->setMinDamage(weao->getMinDamage() - crystal->getDamage());
				weao->setMaxDamage(weao->getMaxDamage() - crystal->getDamage());
				weao->setHealthAttackCost(weao->getHealthAttackCost() - crystal->getSacHealth());
				weao->setActionAttackCost(weao->getActionAttackCost() - crystal->getSacAction());
				weao->setMindAttackCost(weao->getMindAttackCost() - crystal->getSacMind());
				weao->setWoundsRatio(weao->getWoundsRatio() - crystal->getWoundChance());
				weao->setForceCost(weao->getForceCost() - crystal->getForceCost());
			}

			if (crystal->getColor() != 31) {
				weao->setBladeColor(31);
				weao->setCustomizationVariable("/private/index_color_blade", 31, true);
			}
		}

	return sceneObject->notifyObjectRemoved(object);
}

bool SaberInventoryContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	ManagedReference<WeaponObject*> saber = cast<WeaponObject*>( sceneObject->getParent().get().get());

	if (saber == NULL)
		return false;


	if (saber->isJediWeapon() && saber->isEquipped()) {
		ManagedReference<CreatureObject*> player = saber->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

		if (player == NULL)
			return false;

		player->sendSystemMessage("@jedi_spam:saber_not_while_equpped"); // You cannot modify the crystals in this lightsaber while it is equipped.

		return false;
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}
