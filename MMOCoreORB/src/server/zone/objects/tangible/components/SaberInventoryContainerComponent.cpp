/*
Copyright (C) 2007 <SWGEmu>
This File is part of Core3. 
This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.

*/

#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "SaberInventoryContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/component/lightsaber/LightsaberCrystalComponent.h"

int SaberInventoryContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {

	ManagedReference<SceneObject*> p = sceneObject->getParent();

	if (p != NULL){
		int containment = p->getContainmentType();
		if (containment == 4){
		errorDescription = "@jedi_spam:saber_not_while_equpped";
		return TransferErrorCode::INVALIDTYPE;
		}
	}

	if (!object->isLightsaberCrystalObject()) {
		errorDescription = "@jedi_spam:saber_not_crystal";
		return TransferErrorCode::INVALIDTYPE;
	}

	LightsaberCrystalComponent* crystal = cast<LightsaberCrystalComponent*> (object);

	if (crystal->getOwner() == ""){
		errorDescription = "@jedi_spam:saber_crystal_not_tuned";
		return TransferErrorCode::INVALIDTYPE;
	}

	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(object->getParent().get().get());

	if (creature != NULL && crystal->getOwner() != creature->getDisplayedName()){
		errorDescription = "@jedi_spam:saber_crystal_not_owner";
		return TransferErrorCode::INVALIDTYPE;
	}

	if (crystal->isDestroyed()) {
		errorDescription = "You cannot add a broken crystal to your lightsaber.";
		return TransferErrorCode::INVALIDTYPE;
	}

	VectorMap<uint64, ManagedReference<SceneObject*> >* containerObjects = sceneObject->getContainerObjects();

	if (containerObjects->size() >= sceneObject->getContainerVolumeLimit()) {
		errorDescription = "@container_error_message:container03"; //This container is full.
		return TransferErrorCode::CONTAINERFULL;
	}

	for (int i = 0; i < containerObjects->size(); i++){
		Reference<LightsaberCrystalComponent*> crystalInside =  sceneObject->getContainerObject(i).castTo<LightsaberCrystalComponent*>();

		if (crystal->getColor() != 31 && crystalInside->getColor() != 31){
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
int SaberInventoryContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) {
	ManagedReference<WeaponObject*> weao = cast<WeaponObject*>( sceneObject->getParent().get().get());

	if (weao->isJediWeapon()) {
		ManagedReference<LightsaberCrystalComponent*> crystal = cast<LightsaberCrystalComponent*>( object);
		if (crystal->getColor() == 31){
			weao->setAttackSpeed(weao->getAttackSpeed() + crystal->getAttackSpeed());
			weao->setMinDamage(weao->getMinDamage() + crystal->getMinimumDamage());
			weao->setMaxDamage(weao->getMaxDamage() + crystal->getMaximumDamage());
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
int SaberInventoryContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) {
	ManagedReference<WeaponObject*> weao = cast<WeaponObject*>( sceneObject->getParent().get().get());

		if (weao->isJediWeapon()) {
			ManagedReference<LightsaberCrystalComponent*> crystal = cast<LightsaberCrystalComponent*>( object);

			if (crystal->isDestroyed()) {
				return sceneObject->notifyObjectRemoved(object);
			}

			if (crystal->getColor() == 31){
				weao->setAttackSpeed(weao->getAttackSpeed() - crystal->getAttackSpeed());
				weao->setMinDamage(weao->getMinDamage() - crystal->getMinimumDamage());
				weao->setMaxDamage(weao->getMaxDamage() - crystal->getMaximumDamage());
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
