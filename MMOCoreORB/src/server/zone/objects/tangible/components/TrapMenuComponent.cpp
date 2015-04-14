/*
 * TrapMenuComponent.cpp
 *
 *  Created on: 10/30/2011
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/tangible/components/droid/DroidTrapModuleDataComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "TrapMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/TrapTemplate.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

void TrapMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
	// load trap menu needs add
	if (player != NULL){
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
			ManagedReference<AiAgent*> object = ghost->getActivePet(i);
			if (object != NULL) {
				if(object->isDroidObject()) {
					DroidObject* droid = cast<DroidObject*>(object.get());
					if (droid != NULL) {
						if (droid->isTrapDroid()) {
							menuResponse->addRadialMenuItem(25, 3, "@pet/droid_modules:add_trap_to_droid" );
							return;
						}
					}
				}
			}
		}
	}
}

int TrapMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	if(!sceneObject->isASubChildOf(player))
		return 0;

	if (!sceneObject->isTangibleObject())
		return 0;

	if (!sceneObject->isASubChildOf(player))
			return 0;

	if(selectedID == 20) {
		player->sendCommand(String("throwtrap").hashCode(), String::valueOf(sceneObject->getObjectID()), player->getTargetID());

		return 1;
	}
	if (selectedID == 25) {
		// call droid loading.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
			ManagedReference<AiAgent*> object = ghost->getActivePet(i);
			if (object != NULL) {
				if(object->isDroidObject()) {
					DroidObject* droid = cast<DroidObject*>(object.get());
					if (droid != NULL) {
						if (droid->isTrapDroid()) {
							Locker lock(droid);
							DroidTrapModuleDataComponent* module = cast<DroidTrapModuleDataComponent*>(droid->getModule("trap_module"));
							if (module != NULL) {
								module->handleInsertTrap(player,cast<TangibleObject*>(sceneObject));
								return 0;
							}
						}
					}
				}
			}
		}

	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

