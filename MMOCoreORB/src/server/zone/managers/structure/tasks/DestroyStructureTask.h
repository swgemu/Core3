/*
 * DestroyStructureTask.h
 *
 *  Created on: Jun 29, 2013
 *      Author: TheAnswer
 */

#ifndef DESTROYSTRUCTURETASK_H_
#define DESTROYSTRUCTURETASK_H_

#include "engine/engine.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

class DestroyStructureTask : public Task {
protected:
	ManagedReference<StructureObject*> structureObject;
	bool destroyQuestStructure;

public:
	DestroyStructureTask(StructureObject* structure, bool destroyQuest = false) {
		structureObject = structure;
		destroyQuestStructure = destroyQuest;
	}

	void run() {
		Locker locker(structureObject);

		ManagedReference<Zone*> zone = structureObject->getZone();

		if (zone == NULL)
			return;

		ZoneServer* zoneServer = structureObject->getZoneServer();

		if (zoneServer != NULL && zoneServer->isServerLoading()) {
			schedule(1000);

			return;
		}

		float x = structureObject->getPositionX();
		float y = structureObject->getPositionY();
		float z = zone->getHeight(x, y);

		if (destroyQuestStructure)
		{
			PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(structureObject, "clienteffect/lair_damage_heavy.cef", "");
			structureObject->broadcastMessage(explode, false);

			PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", structureObject->getZone()->getZoneName(), structureObject->getPositionX(), structureObject->getPositionZ(), structureObject->getPositionY());
			structureObject->broadcastMessage(explodeLoc, false);
		}

		if (structureObject->isBuildingObject()) {
			ManagedReference<BuildingObject*> buildingObject =
					cast<BuildingObject*>(structureObject.get());

			for (uint32 i = 1; i <= buildingObject->getTotalCellNumber(); ++i) {
				ManagedReference<CellObject*> cellObject = buildingObject->getCell(i);

				if (cellObject == NULL)
					continue;

				int childObjects = cellObject->getContainerObjectsSize();

				if (childObjects <= 0)
					continue;

				//Traverse the vector backwards since the size will change as objects are removed.
				for (int j = childObjects - 1; j >= 0; --j) {
					ReadLocker rlocker(cellObject->getContainerLock());

					ManagedReference<SceneObject*> obj =
							cellObject->getContainerObject(j);

					rlocker.release();

					if (obj->isPlayerCreature() || obj->isPet()) {
						CreatureObject* playerCreature =
								cast<CreatureObject*>(obj.get());

						structureObject->unlock();

						try {
							Locker plocker(playerCreature);

							if (destroyQuestStructure) {
								playerCreature->inflictDamage(structureObject, 0, 9999999, true, true);
								playerCreature->inflictDamage(structureObject, 3, 9999999, true, true);
								playerCreature->inflictDamage(structureObject, 6, 9999999, true, true);
							}

							playerCreature->teleport(x, z, y, 0);
						} catch (...) {
							playerCreature->error("unreported exception caught while teleporting");
						}

						structureObject->wlock();
					}
				}
			}

		}

		//Get the owner of the structure, and remove the structure from their possession.
		ManagedReference<SceneObject*> owner = zone->getZoneServer()->getObject(
				structureObject->getOwnerObjectID());

		if (owner != NULL) {
			ManagedReference<SceneObject*> ghost = owner->getSlottedObject("ghost");

			if (ghost != NULL && ghost->isPlayerObject()) {
				PlayerObject* playerObject = cast<PlayerObject*>(ghost.get());
				playerObject->removeOwnedStructure(structureObject);
			}
		}

		structureObject->destroyObjectFromDatabase(true);
		structureObject->destroyObjectFromWorld(true);
		structureObject->notifyObservers(ObserverEventType::OBJECTDESTRUCTION, structureObject, 0);
	}
};

#endif /* DESTROYSTRUCTURETASK_H_ */

