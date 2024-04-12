/*
 * TrapMenuComponent.cpp
 *
 *  Created on: 10/30/2011
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/components/droid/DroidTrapModuleDataComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "TrapMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void TrapMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (player == nullptr || !player->isPlayerCreature() || sceneObject == nullptr || !sceneObject->isTangibleObject()) {
		return;
	}

	auto tano = sceneObject->asTangibleObject();

	if (tano == nullptr) {
		return;
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(tano, menuResponse, player);

	// Add droid trap menu load option if active pet is a trap droid
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
		ManagedReference<AiAgent*> pet = ghost->getActivePet(i);

		if (pet == nullptr || !pet->isDroidObject()) {
			continue;
		}

		auto droid = cast<DroidObject*>(pet.get());

		if (droid == nullptr || !droid->isTrapDroid()) {
			continue;
		}

		menuResponse->addRadialMenuItem(25, 3, "@pet/droid_modules:add_trap_to_droid");
		return;
	}
}

int TrapMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isASubChildOf(player) || !sceneObject->isTangibleObject()) {
		return 0;
	}

	if (selectedID == 20) {
		player->sendCommand(STRING_HASHCODE("throwtrap"), String::valueOf(sceneObject->getObjectID()), player->getTargetID());

		return 1;
	} else if (selectedID == 25) {
		// call droid loading.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
			ManagedReference<AiAgent*> pet = ghost->getActivePet(i);

			if (pet == nullptr || !pet->isDroidObject()) {
				continue;
			}

			auto droid = cast<DroidObject*>(pet.get());

			if (droid == nullptr || !droid->isTrapDroid()) {
				continue;
			}

			Locker lock(droid);

			auto module = droid->getModule("trap_module").castTo<DroidTrapModuleDataComponent*>();

			if (module == nullptr) {
				continue;
			}

			module->handleInsertTrap(player, cast<TangibleObject*>(sceneObject));
			return 0;
		}
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
