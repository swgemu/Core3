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

#ifndef TRANSFERITEMWEAPONSLASHCOMMAND_H_

#define TRANSFERITEMWEAPONSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
#include "server/zone/managers/object/ObjectManager.h"

class TransferItemWeaponSlashCommand : public QueueCommand {
public:

	TransferItemWeaponSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	bool doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

	if (!checkStateMask(creature))
		return false;

	if (!checkInvalidPostures(creature))
		return false;

	StringBuffer infoMsg;
	infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
	creature->info(infoMsg.toString());

	StringTokenizer tokenizer(arguments.toString());

	uint64 destinationID = tokenizer.getLongToken();
	int transferType = tokenizer.getIntToken(); // I've seen -1 usually.. 4 when equipping most clothes (I think -1 is remove)
	float unknown1 = tokenizer.getFloatToken();
	float unknown2 = tokenizer.getFloatToken();
	float unknown3 = tokenizer.getFloatToken();

	ManagedReference<SceneObject*> objectToTransfer = server->getZoneServer()->getObject(target);

	if (objectToTransfer == NULL) {
		creature->error("objectToTransfer NULL in transfermiscweapon command");
		return false;
	}

	if (!objectToTransfer->isWeaponObject()) {
		creature->error("objectToTransfer is not an weapon object in transferitemweapon");
		return false;
	}

	ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

	if (destinationObject == NULL) {
		creature->error("destinationObject NULL in tansfermiscweapon command");
		return false;
	}

	if (destinationObject != creature) {
		creature->error("destinationObject is not creature in transfermiscweapon command");
		return false;
	}

	if (transferType == 4) {
		SceneObject* parent = objectToTransfer->getParent();

		if (parent == NULL) {
			creature->error("objectToTransfer parent is NULL in transfermiscweapon command");
			return false;
		}

		ZoneServer* zoneServer = server->getZoneServer();
		ObjectManager* objectManager = zoneServer->getObjectManager();

		if (!destinationObject->canAddObject(objectToTransfer)) {
			int arrangementSize = objectToTransfer->getArrangementDescriptorSize();

			if (arrangementSize > 0) {
				String childArrangement = objectToTransfer->getArrangementDescriptor(0);

				ManagedReference<SceneObject*> objectToRemove = destinationObject->getSlottedObject(childArrangement);

				if (!objectManager->transferObject(objectToRemove, parent, 0xFFFFFFFF, true))
					return false;
			}
		}

		if (!objectManager->transferObject(objectToTransfer, destinationObject, transferType, true))
			return false;

		if (creature == destinationObject)
			creature->setWeaponID(objectToTransfer->getObjectID(), true);

	} /*else if (transferType == 4) {

		}*/ else {
			creature->error("unknown transferType in transfermiscweapon command");
		}



	/*uint64 target = packet->parseLong();

	TangibleObject* targetTanoObject;
	targetTanoObject = (TangibleObject*) creature->getInventoryItem(target);

	if (targetTanoObject != NULL) {
		Inventory* inventory = creature->getInventory();

		if (inventory != NULL)
			inventory->moveObjectToTopLevel(creature, targetTanoObject);

		creature->changeWeapon(target, true);
	}*/
		return true;
	}

};

#endif //TRANSFERITEMWEAPONSLASHCOMMAND_H_

