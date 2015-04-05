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

#ifndef DISMOUNTCOMMAND_H_
#define DISMOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "server/zone/templates/tangible/SharedCreatureObjectTemplate.h"

class DismountCommand : public QueueCommand {
public:

	DismountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

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

		if (creature->hasBuff(String("burstrun").hashCode())
				|| creature->hasBuff(String("retreat").hashCode())) {
			//Clear the active negation of the burst run or retreat buff.
			creature->setSpeedMultiplierMod(1.f);
			creature->setAccelerationMultiplierMod(1.f);
		}

		unsigned int crc = String("gallop").hashCode();
		if (creature->hasBuff(crc)) {
			ManagedReference<Buff*> buff = creature->getBuff(crc);

			if (buff != NULL) {
				//Negate effect of the active gallop buff. The negation will be cleared automatically when the buff is deactivated.
				creature->setSpeedMultiplierMod(1.f / buff->getSpeedMultiplierMod());
				creature->setAccelerationMultiplierMod(1.f / buff->getAccelerationMultiplierMod());
			}
		}

		Locker vehicleLocker(vehicle, creature);

		if (vehicle->hasBuff(crc)) {
			ManagedReference<Buff*> buff = creature->getBuff(crc);

			if (buff != NULL) {
				//Negate effect of the active gallop buff. The negation will be cleared automatically when the buff is deactivated.
				vehicle->setSpeedMultiplierMod(1.f / buff->getSpeedMultiplierMod());
				vehicle->setAccelerationMultiplierMod(1.f / buff->getAccelerationMultiplierMod());
			}
		}

		vehicleLocker.release();

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
