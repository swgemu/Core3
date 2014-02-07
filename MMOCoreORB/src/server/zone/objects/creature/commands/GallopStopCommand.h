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

#ifndef GALLOPSTOPCOMMAND_H_
#define GALLOPSTOPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GallopStopCommand : public QueueCommand {
public:

	GallopStopCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> parent = creature->getParent().get();

		if (parent == NULL || !parent->isMount()) {
			creature->sendSystemMessage("@combat_effects:cant_stop_gallop_not_mounted"); // You can't stop galloping if you aren't mounted.
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> mount = cast<CreatureObject*>(parent.get());
		if (mount == NULL)
			return GENERALERROR;

		Locker crossLocker(mount, creature);

		uint32 crc = String("gallop").hashCode();

		if (!creature->hasBuff(crc)) {
			if (mount->hasBuff(crc))
				mount->removeBuff(crc);

			creature->sendSystemMessage("@combat_effects:cant_stop_galloping_not_galloping"); // You can't stop galloping if you aren't already galloping.
			return GENERALERROR;
		} else if (!mount->hasBuff(crc)) {
			creature->removeBuff(crc);

			return GENERALERROR;
		}

		PetManager* petManager = server->getZoneServer()->getPetManager();
		ManagedReference<PetControlDevice*> pcd = mount->getControlDevice().get().castTo<PetControlDevice*>();
		if (petManager == NULL || pcd == NULL)
			return GENERALERROR;

		SharedObjectTemplate* objectTemplate = pcd->getObjectTemplate();
		if (objectTemplate == NULL)
			return GENERALERROR;

		MountSpeedData* mountSpeedData = petManager->getMountSpeedData(objectTemplate->getAppearanceFilename());
		if (mountSpeedData == NULL)
			return GENERALERROR;

		int cooldown = mountSpeedData->getGallopCooldown();

		if (creature->getPlayerObject()->isPrivileged())
			cooldown = 5;

		creature->removeBuff(crc);
		mount->removeBuff(crc);
		creature->getCooldownTimerMap()->updateToCurrentAndAddMili("gallop", cooldown * 1000);
		creature->removePendingTask("gallop_notify");

		Reference<GallopNotifyAvailableEvent*> task = new GallopNotifyAvailableEvent(creature);
		creature->addPendingTask("gallop_notify", task, cooldown * 1000);

		return SUCCESS;
	}

};

#endif //GALLOPSTOPCOMMAND_H_
