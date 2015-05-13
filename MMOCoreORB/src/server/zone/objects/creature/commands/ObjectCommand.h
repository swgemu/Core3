/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJECTCOMMAND_H_
#define OBJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/crafting/ComponentMap.h"


class ObjectCommand : public QueueCommand {
public:

	ObjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL || !ghost->isPrivileged()) {
			creature->sendSystemMessage("@error_message:insufficient_permissions"); //You do not have sufficient permissions to perform the requested action.
			return INSUFFICIENTPERMISSION;
		}

		try {
			String commandType;
			args.getStringToken(commandType);

			if (commandType.beginsWith("createitem")) {
				String objectTemplate;
				args.getStringToken(objectTemplate);

				ManagedReference<CraftingManager*> craftingManager = creature->getZoneServer()->getCraftingManager();
				if(craftingManager == NULL) {
					return GENERALERROR;
				}

				Reference<SharedObjectTemplate*> shot = TemplateManager::instance()->getTemplate(objectTemplate.hashCode());

				if (shot == NULL || !shot->isSharedTangibleObjectTemplate()) {
					creature->sendSystemMessage("Templates must be tangible objects, or descendants of tangible objects, only.");
					return INVALIDPARAMETERS;
				}

				ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

				if (inventory == NULL || inventory->getContainerVolumeLimit() < (inventory->getCountableObjectsRecursive() + 1)) {
					creature->sendSystemMessage("Your inventory is full, so the item could not be created.");
					return INVALIDPARAMETERS;
				}

				ManagedReference<TangibleObject*> object = (server->getZoneServer()->createObject(shot->getServerObjectCRC(), 1)).castTo<TangibleObject*>();

				if (object == NULL) {
					creature->sendSystemMessage("The object '" + commandType + "' could not be created because the template could not be found.");
					return INVALIDPARAMETERS;
				}

				Locker locker(object);

				object->createChildObjects();

				// Set Crafter name and generate serial number
				String name = "Generated with Object Command";
				object->setCraftersName(name);

				StringBuffer customName;
				customName << object->getDisplayedName() <<  " (System Generated)";

				object->setCustomObjectName(customName.toString(), false);

				String serial = craftingManager->generateSerial();
				object->setSerialNumber(serial);

				int quantity = 1;

				if (args.hasMoreTokens())
					quantity = args.getIntToken();

				if(quantity > 1 && quantity <= 100)
					object->setUseCount(quantity);

				// load visible components
				while (args.hasMoreTokens()) {
					String visName;
					args.getStringToken(visName);

					uint32 visId = visName.hashCode();
					if (ComponentMap::instance()->getFromID(visId).getId() == 0)
						continue;

					object->addVisibleComponent(visId, false);
				}

				if (inventory->transferObject(object, -1, true)) {
					inventory->broadcastObject(object, true);
				} else {
					object->destroyObjectFromDatabase(true);
					creature->sendSystemMessage("Error transferring object to inventory.");
				}
			} else if (commandType.beginsWith("createloot")) {
				String lootGroup;
				args.getStringToken(lootGroup);

				int level = 1;

				if (args.hasMoreTokens())
					level = args.getIntToken();

				ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

				if (inventory == NULL || inventory->getContainerVolumeLimit() < (inventory->getCountableObjectsRecursive() + 1)) {
					creature->sendSystemMessage("Your inventory is full, so the item could not be created.");
					return INVALIDPARAMETERS;
				}

				ManagedReference<LootManager*> lootManager = creature->getZoneServer()->getLootManager();

				if (lootManager == NULL)
					return INVALIDPARAMETERS;

				lootManager->createLoot(inventory, lootGroup, level);
			} else if (commandType.beginsWith("createresource")) {
				String resourceName;
				args.getStringToken(resourceName);

				int quantity = 100000;

				if (args.hasMoreTokens())
					quantity = args.getIntToken();

				ManagedReference<ResourceManager*> resourceManager = server->getZoneServer()->getResourceManager();
				resourceManager->givePlayerResource(creature, resourceName, quantity);
			} else if (commandType.beginsWith("createarealoot")) {
				String lootGroup;
				args.getStringToken(lootGroup);

				int range = 32;
				if (args.hasMoreTokens())
					range = args.getIntToken();

				if( range < 0 )
					range = 32;

				if( range > 128 )
					range = 128;

				int level = 1;
				if (args.hasMoreTokens())
					level = args.getIntToken();

				ManagedReference<LootManager*> lootManager = creature->getZoneServer()->getLootManager();
				if (lootManager == NULL)
					return INVALIDPARAMETERS;

				Zone* zone = creature->getZone();
				if (zone == NULL)
					return GENERALERROR;

				// Find all objects in range
				SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
				CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) creature->getCloseObjects();
				if (closeObjectsVector == NULL) {
					zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &closeObjects, true);
				} else {
					closeObjectsVector->safeCopyTo(closeObjects);
				}

				// Award loot group to all players in range
				for (int i = 0; i < closeObjects.size(); i++) {
					SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());

					if (targetObject->isPlayerCreature() && creature->isInRange(targetObject, range)) {

						CreatureObject* targetPlayer = cast<CreatureObject*>(targetObject);
						Locker tlock( targetPlayer, creature );

						ManagedReference<SceneObject*> inventory = targetPlayer->getSlottedObject("inventory");
						if (inventory != NULL) {
							if( lootManager->createLoot(inventory, lootGroup, level) )
								targetPlayer->sendSystemMessage( "You have received a loot item!");
						}

						tlock.release();
					}
				}
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /object createitem <objectTemplatePath> [<quantity>]");
			creature->sendSystemMessage("SYNTAX: /object createresource <resourceName> [<quantity>]");
			creature->sendSystemMessage("SYNTAX: /object createloot <loottemplate> [<level>]");
			creature->sendSystemMessage("SYNTAX: /object createarealoot <loottemplate> [<range>] [<level>]");

			return INVALIDPARAMETERS;
		}


		return SUCCESS;
	}

};

#endif //OBJECTCOMMAND_H_
