/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISMOUNTCOMMAND_H_
#define DISMOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "templates/creature/SharedCreatureObjectTemplate.h"

class DismountCommand : public QueueCommand {
	Vector<uint32> restrictedBuffCRCs;
	uint32 gallopCRC;

public:

	DismountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

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

		ManagedReference<SceneObject*> mount = creature->getParent().get();

		if (mount == NULL || !mount->isCreatureObject()) {
			creature->clearState(CreatureState::RIDINGMOUNT);
			return GENERALERROR;
		}

		if (!creature->checkCooldownRecovery("mount_dismount")) {
			return GENERALERROR;
		}

		CreatureObject* vehicle = cast<CreatureObject*>(mount.get());

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

		zone->transferObject(creature, -1, false);

		IntersectionResults intersections;
		CollisionManager::getWorldFloorCollisions(creature->getPositionX(), creature->getPositionY(), zone, &intersections, (CloseObjectsVector*) creature->getCloseObjects());
		float z = planetManager->findClosestWorldFloor(creature->getPositionX(), creature->getPositionY(), creature->getPositionZ(), creature->getSwimHeight(), &intersections, (CloseObjectsVector*) creature->getCloseObjects());

		creature->teleport(creature->getPositionX(), z, creature->getPositionY(), 0);

		clocker.release(); // Buff needs to be locked below

		//reapply speed buffs if they exist
		for (int i=0; i<restrictedBuffCRCs.size(); i++) {

			uint32 buffCRC = restrictedBuffCRCs.get(i);

			if (creature->hasBuff(buffCRC)) {
				ManagedReference<Buff*> buff = creature->getBuff(buffCRC);
				if(buff != NULL) {
					Locker lock(buff, creature);
					buff->applyAllModifiers();
				}
			}
		}

		Locker storeLocker(vehicle, creature); // Yet another locker for jetpack storage below

		creature->clearState(CreatureState::RIDINGMOUNT);

		SpeedMultiplierModChanges* changeBuffer = creature->getSpeedMultiplierModChanges();
		int bufferSize = changeBuffer->size();

		if (bufferSize > 5) {
			changeBuffer->remove(0);
		}

		changeBuffer->add(SpeedModChange(creature->getSpeedMultiplierMod()));

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		playerManager->updateSwimmingState(creature, z);

		ManagedReference<ControlDevice*> device = vehicle->getControlDevice().get();

		if (device != NULL && vehicle->getServerObjectCRC() == 0x32F87A54) { // Auto-store jetpack on dismount.
			device->storeObject(creature);
			creature->sendSystemMessage("@pet/pet_menu:jetpack_dismount"); // "You have been dismounted from the jetpack, and it has been stored."
		}

		creature->updateToDatabase();

		SharedObjectTemplate* templateData = creature->getObjectTemplate();
		SharedCreatureObjectTemplate* playerTemplate = dynamic_cast<SharedCreatureObjectTemplate*> (templateData);

		if (playerTemplate != NULL) {
			Vector<FloatParam> speedTempl = playerTemplate->getSpeed();
			creature->setRunSpeed(speedTempl.get(0));
			creature->updateSpeedAndAccelerationMods(); // Reset Force Sensitive control mods to default.
		}

		creature->updateCooldownTimer("mount_dismount", 2000);

		creature->removeMountedCombatSlow(false); // these are already removed off the player - Just remove it off the mount

		if (vehicle->hasBuff(gallopCRC)) {
			ManagedReference<Buff*> buff = vehicle->getBuff(gallopCRC);
			if (buff != NULL) {
				Core::getTaskManager()->executeTask([=] () {
					Locker lock(vehicle);
					Locker buffLocker(buff, vehicle);
					buff->removeAllModifiers();
				}, "RemoveGallopModsLambda");
			}
		}

		return SUCCESS;
	}

};

#endif //DISMOUNTCOMMAND_H_
