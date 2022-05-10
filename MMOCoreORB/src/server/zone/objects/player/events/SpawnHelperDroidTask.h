/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

/**
 * SpawnHelperDroidTask.h
 *
 *  Created: Monday May 9, 2022
 *   Author: H
 *
 */

#ifndef SPAWNHELPERDROIDTASK_H_
#define SPAWNHELPERDROIDTASK_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/HelperDroidObject.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/ai/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class SpawnHelperDroidTask: public Task {
	ManagedWeakReference<CreatureObject*> player;

public:
	SpawnHelperDroidTask(CreatureObject* creature) {
		player = creature;
	}

	void run() {
		CreatureObject* playerCreo = player.get();

		if (playerCreo == nullptr)
			return;

		ZoneServer* zoneServer = playerCreo->getZoneServer();

		if (zoneServer == nullptr)
			return;

		String controlDeviceObjectTemplate = "object/intangible/pet/nhelper_droid.iff";
		String mobileTemplate = "helper_r2_unit";
		String generatedObjectTemplate = "object/mobile/nhelper_droid.iff";

		Locker plock(playerCreo);

		SceneObject* datapad = playerCreo->getSlottedObject("datapad");
		PlayerManager* playerManager = zoneServer->getPlayerManager();
		ObjectManager* objectManager = zoneServer->getObjectManager();

		if (datapad == nullptr || playerManager == nullptr || objectManager == nullptr) {
			return;
		}

		// Check for already existing helper droid
		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj != nullptr && obj->isPetControlDevice()) {
				Reference<PetControlDevice*> controlDevice = cast<PetControlDevice*>(obj.get());

				if (controlDevice != nullptr && controlDevice->getPetType() == PetManager::HELPERDROIDPET) {
					ManagedReference<HelperDroidObject*> helperDroidObject = dynamic_cast<HelperDroidObject*>(controlDevice->getControlledObject());

					if (helperDroidObject != nullptr) {
						Locker lock(controlDevice);
						Locker clock(helperDroidObject, playerCreo);

						controlDevice->callObject(playerCreo);
						return;
					}
				}
			}
		}

		CreatureManager* creatureManager = playerCreo->getZone()->getCreatureManager();

		if (creatureManager == nullptr)
			return;

		CreatureTemplate* creatureTemplate =  CreatureTemplateManager::instance()->getTemplate(mobileTemplate.hashCode());

		if (creatureTemplate == nullptr) {
			return;
		}

		ManagedReference<PetControlDevice*> controlDevice = zoneServer->createObject(controlDeviceObjectTemplate.hashCode(), 1).castTo<PetControlDevice*>();

		if (controlDevice == nullptr) {
			return;
		}

		Locker cdlocker(controlDevice);

		Reference<CreatureObject*> creatureObject = creatureManager->createCreature(generatedObjectTemplate.hashCode(), true, mobileTemplate.hashCode());

		if (creatureObject == nullptr) {
			controlDevice->destroyObjectFromDatabase(true);
			return;
		}

		Locker clocker(creatureObject, playerCreo);

		Reference<HelperDroidObject*> helperdroid = creatureObject.castTo<HelperDroidObject*>();

		if (helperdroid == nullptr) {
			controlDevice->destroyObjectFromDatabase(true);
			creatureObject->destroyObjectFromDatabase(true);
			return;
		}

		helperdroid->loadTemplateData(creatureTemplate);
		helperdroid->createChildObjects();
		helperdroid->setControlDevice(controlDevice);

		StringId s;
		s.setStringId(helperdroid->getObjectName()->getFullPath());
		controlDevice->setObjectName(s, false);
		controlDevice->setPetType(PetManager::HELPERDROIDPET);
		controlDevice->setControlledObject(creatureObject);

		if (!datapad->transferObject(controlDevice, -1)) {
			controlDevice->destroyObjectFromDatabase(true);
			creatureObject->destroyObjectFromDatabase(true);
		}

		datapad->broadcastObject(controlDevice, true);

		controlDevice->callObject(playerCreo);
	}
};

#endif /* SPAWNHELPERDROIDTASK_H_ */