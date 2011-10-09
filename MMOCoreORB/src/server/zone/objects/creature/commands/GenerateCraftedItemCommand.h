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

#ifndef GENERATECRAFTEDITEMCOMMAND_H_
#define GENERATECRAFTEDITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/managers/crafting/CraftingManager.h"

class GenerateCraftedItemCommand : public QueueCommand {
public:

	GenerateCraftedItemCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);

		ManagedReference<CraftingManager*> craftingManager = player->getZoneServer()->getCraftingManager();

		try {

			StringTokenizer tokenizer(arguments.toString());

			if(!tokenizer.hasMoreTokens()) {
				creature->sendSystemMessage("Usage: /GenerateCraftedItem SERVERSCRIPTPATH [Quantity]");
				return GENERALERROR;
			}

			String file;
			tokenizer.getStringToken(file);

			ManagedReference<DraftSchematic* > draftSchematic =
					dynamic_cast<DraftSchematic*>(creature->getZoneServer()->createObject(file.hashCode(), 0));

			if(draftSchematic == NULL || !draftSchematic->isValidDraftSchematic()) {
				creature->sendSystemMessage("File entered not valid, please be sure to use the draft schematics server script path not client path");
				return GENERALERROR;
			}

			ManagedReference<ManufactureSchematic* > manuSchematic = cast<ManufactureSchematic*>( draftSchematic->createManufactureSchematic());

			if(manuSchematic == NULL) {
				creature->sendSystemMessage("Error creating ManufactureSchematic from DraftSchematic");
				return GENERALERROR;
			}

			manuSchematic->createChildObjects();

			ManagedReference<TangibleObject *> prototype = dynamic_cast<TangibleObject*> (
					creature->getZoneServer()->createObject(draftSchematic->getTanoCRC(), 2));

			if(prototype == NULL) {
				creature->sendSystemMessage("Unable to create target item, is it implemented yet?");
				return GENERALERROR;
			}

			prototype->createChildObjects();

			// Set Crafter name and generate serial number
			String name = "System Generated";
			prototype->setCraftersName(name);

			String serial = craftingManager->generateSerial();
			prototype->setCraftersSerial(serial);

			int quantity = 1;

			if(tokenizer.hasMoreTokens())
				quantity = tokenizer.getIntToken();

			if(quantity == 0)
				quantity = 1;

			ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

			if(inventory == NULL) {
				creature->sendSystemMessage("Error locating target inventory");
				return GENERALERROR;
			}

			prototype->updateToDatabase();

			if(quantity > 1) {

				ManagedReference<FactoryCrate* > crate = prototype->createFactoryCrate(true);
				crate->setUseCount(quantity);

				inventory->addObject(crate, -1, true);
				crate->sendTo(creature, true);

			} else {
				inventory->addObject(prototype, -1, true);
				prototype->sendTo(creature, true);
			}

		} catch (Exception& e) {
			creature->sendSystemMessage("Error in data input, try again");
			return GENERALERROR;
		}

		return SUCCESS;
	}
};

#endif //GENERATECRAFTEDITEMCOMMAND_H_
