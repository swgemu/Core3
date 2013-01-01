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

#ifndef MOUNTCOMMAND_H_
#define MOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

class MountCommand : public QueueCommand {
public:

	MountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (creature->isRidingMount()) {
			ZoneServer* zoneServer = server->getZoneServer();

			ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();
			objectController->activateCommand(creature, String("dismount").hashCode(), 0, 0, "");

			return GENERALERROR;
		}

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = server->getZoneServer();

		ManagedReference<SceneObject*> object = zoneServer->getObject(target);

		if (object == NULL)
			return INVALIDTARGET;

		if (!object->isVehicleObject() /* && !object->isPetObject() */)
			return GENERALERROR;

		CreatureObject* vehicle = cast<CreatureObject*>( object.get());

		if (vehicle->getCreatureLinkID() != creature->getObjectID())
			return GENERALERROR;

		if (!vehicle->isInRange(creature, 5))
			return GENERALERROR;

		if (creature->getParent() != NULL)
			return GENERALERROR;

		if (vehicle->isDestroyed()) {
			creature->sendSystemMessage("@pet/pet_menu:cant_mount_veh_disabled");
			return GENERALERROR;
		}

		if (!creature->checkCooldownRecovery("mount_dismount")) {
			return GENERALERROR;
		}

		try {
			Locker clocker(vehicle, creature);

			vehicle->setState(CreatureState::MOUNTEDCREATURE);

			if (!vehicle->transferObject(creature, 4, true))
				vehicle->error("could not add creature");

			if (creature->hasBuff(String("burstrun").hashCode())
					|| creature->hasBuff(String("retreat").hashCode())) {
				//Negate effect of the active burst run or retreat buff. The negation will be cleared automatically when the buff is deactivated.
				creature->setSpeedMultiplierMod(1.f / 1.822f);
				creature->setAccelerationMultiplierMod(1.f / 1.822f);
			}

			creature->setState(CreatureState::RIDINGMOUNT);

			SpeedMultiplierModChanges* changeBuffer = creature->getSpeedMultiplierModChanges();
			int bufferSize = changeBuffer->size();

			if (bufferSize > 5) {
				changeBuffer->remove(0);
			}

			changeBuffer->add(SpeedModChange(vehicle->getRunSpeed() / creature->getRunSpeed()));

			creature->updateToDatabase();


		} catch (Exception& e) {

		}

		creature->updateCooldownTimer("mount_dismount", 2000);

		return SUCCESS;
	}

};

#endif //MOUNTCOMMAND_H_
