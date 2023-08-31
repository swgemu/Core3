/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISMOUNTCOMMAND_H_
#define DISMOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "templates/creature/SharedCreatureObjectTemplate.h"
#include "server/zone/packets/object/DataTransform.h"

class DismountCommand : public QueueCommand {
	Vector<uint32> restrictedBuffCRCs;
	uint32 gallopCRC;

public:
	DismountCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
		gallopCRC = STRING_HASHCODE("gallop");

		restrictedBuffCRCs.add(gallopCRC); // Remove the old buff off of any players on dismount
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

		if (!creature->hasState(CreatureState::RIDINGMOUNT))
			return INVALIDSTATE;

		if (!creature->checkCooldownRecovery("mount_dismount")) {
			return GENERALERROR;
		}

		creature->clearState(CreatureState::RIDINGMOUNT);

		ManagedReference<SceneObject*> mount = creature->getParent().get();

		// Handle dismount, removal of gallop and storing of Jetpacks
		if (mount != nullptr && mount->isCreatureObject()) {
			handleMount(creature, mount);
		}

		// reapply speed buffs if they exist
		for (int i = 0; i < restrictedBuffCRCs.size(); i++) {
			uint32 buffCRC = restrictedBuffCRCs.get(i);

			if (creature->hasBuff(buffCRC)) {
				ManagedReference<Buff*> buff = creature->getBuff(buffCRC);

				if (buff != nullptr) {
					Locker lock(buff, creature);
					buff->applyAllModifiers();
				}
			}
		}

		SpeedMultiplierModChanges* changeBuffer = creature->getSpeedMultiplierModChanges();
		int bufferSize = changeBuffer->size();

		if (bufferSize > 5) {
			changeBuffer->remove(0);
		}

		changeBuffer->add(SpeedModChange(creature->getSpeedMultiplierMod()));

		creature->updateToDatabase();

		SharedObjectTemplate* templateData = creature->getObjectTemplate();
		SharedCreatureObjectTemplate* playerTemplate = dynamic_cast<SharedCreatureObjectTemplate*>(templateData);

		if (playerTemplate != nullptr) {
			Vector<FloatParam> speedTempl = playerTemplate->getSpeed();
			creature->setRunSpeed(speedTempl.get(0));
			creature->updateSpeedAndAccelerationMods(); // Reset Force Sensitive control mods to default.
		}

		creature->updateCooldownTimer("mount_dismount", 2000);
		creature->setNextAllowedMoveTime(300);

		creature->removeMountedCombatSlow(false); // these are already removed off the player - Just remove it off the mount

		return SUCCESS;
	}

	void handleMount(CreatureObject* creature, SceneObject* mount) const {
		if (creature == nullptr || mount == nullptr)
			return;

		CreatureObject* vehicle = mount->asCreatureObject();

		if (vehicle == nullptr)
			return;

		Locker clocker(vehicle, creature);

		vehicle->clearState(CreatureState::MOUNTEDCREATURE);

		Zone* zone = vehicle->getZone();

		// Handle dismounting player
		if (zone != nullptr && vehicle == creature->getParent().get()) {
			ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();
			float z = vehicle->getWorldPositionZ();

			if (planetManager != nullptr) {
				TerrainManager* terrainManager = planetManager->getTerrainManager();

				if (terrainManager != nullptr) {
					zone->transferObject(creature, -1, false);

					IntersectionResults intersections;
					CollisionManager::getWorldFloorCollisions(creature->getPositionX(), creature->getPositionY(), zone, &intersections, (CloseObjectsVector*)creature->getCloseObjects());
					z = planetManager->findClosestWorldFloor(creature->getPositionX(), creature->getPositionY(), creature->getPositionZ(), creature->getSwimHeight(), &intersections, (CloseObjectsVector*)creature->getCloseObjects());
				}
			}

			creature->teleport(creature->getPositionX(), z, creature->getPositionY(), 0);

			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

			if (playerManager != nullptr)
				playerManager->updateSwimmingState(creature, z);
		}

		// Remove gallop from mounts
		if (vehicle->hasBuff(gallopCRC)) {
			removeMountBuffs(vehicle);
		}

		// Store Jetpack
		ManagedReference<ControlDevice*> device = vehicle->getControlDevice().get();

		if (device != nullptr && vehicle->getServerObjectCRC() == 0x32F87A54) { // Auto-store jetpack on dismount.
			device->storeObject(creature);
			creature->sendSystemMessage("@pet/pet_menu:jetpack_dismount"); // "You have been dismounted from the jetpack, and it has been stored."
		}

		if (vehicle->getParentID() == 0) {
			vehicle->setCurrentSpeed(0.f);
			vehicle->incrementMovementCounter();

			auto data = new DataTransform(vehicle);
			vehicle->broadcastMessage(data, false);
		}
	}

	void removeMountBuffs(CreatureObject* vehicle) const {
		if (vehicle == nullptr)
			return;

		ManagedReference<Buff*> buff = vehicle->getBuff(gallopCRC);

		if (buff == nullptr)
			return;

		Reference<CreatureObject*> vehicleRef = vehicle;

		Core::getTaskManager()->executeTask([vehicleRef, buff]() {
			Locker lock(vehicleRef);
			Locker buffLocker(buff, vehicleRef);

			buff->removeAllModifiers();
		}, "RemoveGallopModsLambda");
	}
};

#endif // DISMOUNTCOMMAND_H_
