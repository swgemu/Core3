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

		/*StringBuffer infoMsg;
		infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
		creature->info(infoMsg.toString(), true);*/

		StringTokenizer tokenizer(arguments.toString());

		uint64 destinationID = tokenizer.getLongToken();
		int transferType = tokenizer.getIntToken(); // I've seen -1 usually.. 4 when equipping most clothes (I think -1 is remove)
		float unknown1 = tokenizer.getFloatToken();
		float unknown2 = tokenizer.getFloatToken();
		float unknown3 = tokenizer.getFloatToken();

		ManagedReference<SceneObject*> objectToTransfer = server->getZoneServer()->getObject(target);

		if (objectToTransfer == NULL) {
			creature->error("objectToTransfer NULL in transfermisc command");
			return GENERALERROR;
		}

		if (objectToTransfer->isCreatureObject() && !objectToTransfer->isVendor()) {
			//creature->sendSystemMessage("You cant pickup creatures");
			return GENERALERROR;
		}

		// Check if the object is a Vendor and if its initalized before attempting to drop/pickup
		if (objectToTransfer->isVendor()) {
			SceneObject* vendorObj = objectToTransfer.get();
			Vendor* vendor = NULL;
			if (vendorObj->isCreatureObject()) {
				VendorCreature* vendorCreature = dynamic_cast<VendorCreature*>(vendorObj);
				vendor = vendorCreature->getVendor();
			} else if (vendorObj->isTerminal()) {
				VendorTerminal* vendorTerminal = dynamic_cast<VendorTerminal*>(vendorObj);
				vendor = vendorTerminal->getVendor();
			}

			if (vendor == NULL)
				return GENERALERROR;

			if (vendor->getOwnerID() != creature->getObjectID()) {
				creature->sendSystemMessage("Only the vendor owner can do that.");
				return GENERALERROR;
			}

			if (vendor->isInitialized()) {
				creature->sendSystemMessage("@player_structure:cant_move");
				return GENERALERROR;
			}
		}

		SceneObject* objectsParent = objectToTransfer->getParent();

		// TODO: Maybe a better way to handle this. (If its a world loot container, ignore parent) ??
		if (objectsParent != NULL && objectsParent->getGameObjectType() != SceneObjectType::STATICLOOTCONTAINER) {
			if (objectsParent->isCellObject()) {

				ManagedReference<BuildingObject*> building = cast<BuildingObject*>( objectsParent->getParent());

				if (!building->isOnAdminList(creature->getFirstName())) {
					return GENERALERROR;
				}

				if (objectToTransfer->isTerminal() && !objectToTransfer->isVendor())
					return GENERALERROR;
			} else {
				SceneObject* rootParent = objectToTransfer->getRootParent();

				if (rootParent->isPlayerCreature() && rootParent != creature)
					return GENERALERROR;
			}
		}

		ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == NULL) {
			creature->error("destinationObject NULL in tansfermisc command");
			return GENERALERROR;
		}

		String errorDescription;
		int errorNumber = 0;

		if ((errorNumber = destinationObject->canAddObject(objectToTransfer, transferType, errorDescription)) != 0) {
			if (errorDescription.length() > 1)
				creature->sendSystemMessage(errorDescription);
			else
				creature->error("cannot add objectToTransfer to destinationObject " + String::valueOf(errorNumber));

			return GENERALERROR;
		}

		ZoneServer* zoneServer = server->getZoneServer();
		ObjectController* objectController = zoneServer->getObjectController();

		//TODO: This needs to be looked at more!
		//If transferring the object to a cell, ensure that the creature has permission to drop the item to the cell.
		if (destinationObject->isCellObject()) {
			ManagedReference<BuildingObject*> building = cast<BuildingObject*>( destinationObject->getParent());

			if (!building->isOnAdminList(creature->getFirstName())) {
				return GENERALERROR;
			}

			//Set the objects position to the creature that is transferring it?
			objectToTransfer->initializePosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
		}

		bool clearWeapon = objectToTransfer->isWeaponObject() && (creature == objectToTransfer->getParent());

		if (objectsParent == NULL)
			return GENERALERROR;

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

