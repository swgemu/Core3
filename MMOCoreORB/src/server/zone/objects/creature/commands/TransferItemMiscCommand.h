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

#ifndef TRANSFERITEMMISCCOMMAND_H_
#define TRANSFERITEMMISCCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/auction/Vendor.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"


class TransferItemMiscCommand : public QueueCommand {
public:

	TransferItemMiscCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->info("transfer item misc");

		/*StringBuffer infoMsg;
		infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
		creature->info(infoMsg.toString(), true);*/

		StringTokenizer tokenizer(arguments.toString());

		uint64 destinationID = tokenizer.getLongToken();
		int transferType = tokenizer.getIntToken(); // containment type .. -1 container, >=4 slotted container
		float unknown1 = tokenizer.getFloatToken();
		float unknown2 = tokenizer.getFloatToken();
		float unknown3 = tokenizer.getFloatToken();

		ManagedReference<SceneObject*> objectToTransfer = server->getZoneServer()->getObject(target);

		if (objectToTransfer == NULL) {
			creature->error("objectToTransfer NULL in transfermisc command");
			return GENERALERROR;
		}

		if (objectToTransfer->isStaticObject() || !objectToTransfer->isTangibleObject())
			return GENERALERROR;

		if (!objectToTransfer->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER)) {
			creature->sendSystemMessage("@error_message:perm_no_move");
			return GENERALERROR;
		}

		SceneObject* objectsParent = objectToTransfer->getParent();

		if (objectsParent == NULL)
			return GENERALERROR;

		if (!objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT)) {
			creature->sendSystemMessage("@error_message:perm_no_move");
			return GENERALERROR;
		}

		Zone* zoneObject = objectToTransfer->getZone();

		if (zoneObject != NULL) {
			ManagedReference<SceneObject*> rootParent = objectToTransfer->getRootParent();

			float maxDistance = 11;

			if (!rootParent->isBuildingObject()) {
				if (rootParent->getDistanceTo(creature) > maxDistance)
					return TOOFAR;
			} else {
				SceneObject* par = NULL;
				SceneObject* obj = objectToTransfer;

				while ((par = obj->getParent()) != NULL) {
					if (par->isCellObject()) {
						if (obj->getDistanceTo(creature) > maxDistance)
							return TOOFAR;
						else
							break;
					} else {
						obj = par;
					}
				}
			}
		}

		ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == NULL) {
			creature->error("destinationObject NULL in tansfermisc command");
			return GENERALERROR;
		}

		if (destinationObject->isIntangibleObject())
			return GENERALERROR;

		String errorDescription;
		int errorNumber = 0;

		if ((errorNumber = destinationObject->canAddObject(objectToTransfer, transferType, errorDescription)) != 0) {
			if (errorDescription.length() > 1)
				creature->sendSystemMessage(errorDescription);
			else
				creature->error("cannot add objectToTransfer to destinationObject " + String::valueOf(errorNumber));

			return GENERALERROR;
		}

		if (!destinationObject->checkContainerPermission(creature, ContainerPermissions::MOVEIN))
			return GENERALERROR;

		ZoneServer* zoneServer = server->getZoneServer();
		ObjectController* objectController = zoneServer->getObjectController();

		objectToTransfer->initializePosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());

		bool clearWeapon = objectToTransfer->isWeaponObject() && (creature == objectToTransfer->getParent());

		Locker clocker(objectsParent, creature);

		if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true))
			return GENERALERROR;

		if (clearWeapon) {
			creature->setWeapon(NULL, true);

			if (creature->hasBuff(String("centerofbeing").hashCode()))
				creature->removeBuff(String("centerofbeing").hashCode());
		}

		return SUCCESS;
	}

};

#endif //TRANSFERITEMMISCCOMMAND_H_

