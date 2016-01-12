/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISMOUNTCOMMAND_H_
#define DISMOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "server/zone/templates/tangible/SharedCreatureObjectTemplate.h"

class DismountCommand : public QueueCommand {
	Vector<uint32> restrictedBuffCRCs;

public:

	DismountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		restrictedBuffCRCs.add(STRING_HASHCODE("gallop"));
		restrictedBuffCRCs.add(STRING_HASHCODE("burstrun"));
		restrictedBuffCRCs.add(STRING_HASHCODE("retreat"));
		restrictedBuffCRCs.add(BuffCRC::JEDI_FORCE_RUN_1);
		restrictedBuffCRCs.add(BuffCRC::JEDI_FORCE_RUN_2);
		restrictedBuffCRCs.add(BuffCRC::JEDI_FORCE_RUN_3);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> mount = creature->getParent();

		if (mount == NULL || !mount->isCreatureObject()) {
			creature->clearState(CreatureState::RIDINGMOUNT);

			return GENERALERROR;
		}

		if (!creature->checkCooldownRecovery("mount_dismount")) {
			return GENERALERROR;
		}

		CreatureObject* vehicle = cast<CreatureObject*>( mount.get());

		Locker clocker(vehicle, creature);

		vehicle->clearState(CreatureState::MOUNTEDCREATURE);

		/*if (!vehicle->removeObject(creature, true))
			vehicle->error("could not remove creature from mount creature");*/

		Zone* zone = vehicle->getZone();

		if (vehicle != creature->getParent().get())
			return GENERALERROR;

		if (zone == NULL)
			return GENERALERROR;

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		if (planetManager == NULL)
			return GENERALERROR;

		ManagedReference<TerrainManager*> terrainManager = planetManager->getTerrainManager();

		if (terrainManager == NULL)
			return GENERALERROR;

		creature->removeMountedCombatSlow();

		zone->transferObject(creature, -1, false);

		clocker.release();

		IntersectionResults intersections;
		CollisionManager::getWorldFloorCollisions(creature->getPositionX(), creature->getPositionY(), zone, &intersections, (CloseObjectsVector*) creature->getCloseObjects());
		float z = planetManager->findClosestWorldFloor(creature->getPositionX(), creature->getPositionY(), creature->getPositionZ(), creature->getSwimHeight(), &intersections, (CloseObjectsVector*) creature->getCloseObjects());

		creature->teleport(creature->getPositionX(), z, creature->getPositionY(), 0);

		uint32 buffCRC = 0;
		for(int i=0; i<restrictedBuffCRCs.size(); i++) {
			buffCRC = restrictedBuffCRCs.get(i);
			if(creature->hasBuff(buffCRC)) {
				ManagedReference<Buff*> buff = creature->getBuff(buffCRC);

				Locker lock(buff, creature); // Is this necessary?

				buff->applyAllModifiers();
			}
		}

		creature->clearState(CreatureState::RIDINGMOUNT);

		SpeedMultiplierModChanges* changeBuffer = creature->getSpeedMultiplierModChanges();
		int bufferSize = changeBuffer->size();

		if (bufferSize > 5) {
			changeBuffer->remove(0);
		}

		changeBuffer->add(SpeedModChange(creature->getSpeedMultiplierMod()));

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		playerManager->updateSwimmingState(creature, z);

		ManagedReference<ControlDevice*> device = vehicle->getControlDevice();
		
		if (device != NULL && vehicle->getServerObjectCRC() == 0x32F87A54) // Auto-store jetpack on dismount.
			device->storeObject(creature);
		
		creature->updateToDatabase();

		SharedObjectTemplate* templateData = creature->getObjectTemplate();
		SharedCreatureObjectTemplate* playerTemplate = dynamic_cast<SharedCreatureObjectTemplate*> (templateData);

		if (playerTemplate != NULL) {
			Vector<FloatParam> speedTempl = playerTemplate->getSpeed();
			creature->setRunSpeed(speedTempl.get(0));
		}

		creature->updateCooldownTimer("mount_dismount", 2000);

		return SUCCESS;
	}

};

#endif //DISMOUNTCOMMAND_H_
