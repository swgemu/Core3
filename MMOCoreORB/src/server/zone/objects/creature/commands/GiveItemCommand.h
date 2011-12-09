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

#ifndef GIVEITEMCOMMAND_H_
#define GIVEITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "../../../managers/player/PlayerManager.h"

#include "server/zone/objects/tangible/attachment/Attachment.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"

class GiveItemCommand : public QueueCommand {
public:

	GiveItemCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (object->isAttachment()) {
				Attachment* attachment = cast<Attachment*>( object.get());

				if (!args.hasMoreTokens())
					return GENERALERROR;

				uint64 targetObjectID = args.getLongToken();

				ManagedReference<SceneObject*> scenObj = server->getZoneServer()->getObject(targetObjectID);

				if (scenObj->isWearableObject()) {
					WearableObject* wearable = cast<WearableObject*>( scenObj.get());
					wearable->applyAttachment(creature, attachment);
					return SUCCESS;
				}

			} else if (object->isWearableObject() || object->isWeaponObject()) {
				CreatureObject* player = cast<CreatureObject*>(creature);
				if (player->getSkillMod("hiring") < 90) {
					player->sendSystemMessage("You lack the necessary skills to perform that action");
					return GENERALERROR;
				}
				TangibleObject* clothing = cast<TangibleObject*>( object.get());

				if (!args.hasMoreTokens())
					return GENERALERROR;

				uint64 targetObjectID = args.getLongToken();

				ManagedReference<SceneObject*> sceno = server->getZoneServer()->getObject(targetObjectID);

				if (sceno->isVendor() && sceno->isCreatureObject()) {
					VendorCreature* vendor = dynamic_cast<VendorCreature*>(sceno.get());
					vendor->addClothingItem(creature, clothing);
					return SUCCESS;

				}
			}
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL || !ghost->isPrivileged()) {
			creature->sendSystemMessage("@error_message:insufficient_permissions"); //You do not have sufficient permissions to perform the requested action.
			return INSUFFICIENTPERMISSION;
		}

		try {
			String commandType;
			args.getStringToken(commandType);

			if (commandType.beginsWith("object")) {
				Reference<SharedObjectTemplate*> shot = TemplateManager::instance()->getTemplate(commandType.hashCode());

				if (shot == NULL || !shot->isSharedTangibleObjectTemplate()) {
					creature->sendSystemMessage("Templates must be tangible objects, or descendants of tangible objects, only.");
					return INVALIDPARAMETERS;
				}

				ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

				if (inventory == NULL || inventory->isContainerFull()) {
					creature->sendSystemMessage("Your inventory is full, so the item could not be created.");
					return INVALIDPARAMETERS;
				}

				ManagedReference<SceneObject*> object = server->getZoneServer()->createObject(shot->getServerObjectCRC(), 1);

				if (object == NULL) {
					creature->sendSystemMessage("The object '" + commandType + "' could not be created because the template could not be found.");
					return INVALIDPARAMETERS;
				}

				inventory->broadcastObject(object, true);
				inventory->transferObject(object, -1, true);
			} else if (commandType.beginsWith("resource")) {
				String resourceName;
				args.getStringToken(resourceName);

				int quantity = 100000;

				if (args.hasMoreTokens())
					quantity = args.getIntToken();

				ManagedReference<ResourceManager*> resourceManager = server->getZoneServer()->getResourceManager();
				resourceManager->givePlayerResource(creature, resourceName, quantity);
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /giveItem <objectTemplatePath>");
			creature->sendSystemMessage("SYNTAX: /giveItem <resource> <resourceName> [<quantity>]");

			return INVALIDPARAMETERS;
		}

		return SUCCESS;
	}

};

#endif //GIVEITEMCOMMAND_H_
