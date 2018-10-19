/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CREATESPAWNINGELEMENTCOMMAND_H_
#define CREATESPAWNINGELEMENTCOMMAND_H_

#include "templates/manager/TemplateManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "templates/mobile/LairTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"

class CreateSpawningElementCommand : public QueueCommand {
public:

	CreateSpawningElementCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ZoneServer* zserv = server->getZoneServer();

		ManagedReference<SceneObject* > object = zserv->getObject(target);

		StringTokenizer args(arguments.toString());

		CreatureObject* player = cast<CreatureObject*>(creature);

		if (player == nullptr)
			return GENERALERROR;

		if (!args.hasMoreTokens()) {
			creature->sendSystemMessage("Spawn Object/Building: /createSpawningElement spawn IffObjectPath [x z y heading]");
			creature->sendSystemMessage("Spawn Lair: /createSpawningElement lair lairTemplate [level]");
			creature->sendSystemMessage("Delete Object/Building: /createSpawningElement delete oid");
			creature->sendSystemMessage("Delete All: /createSpawningElement deleteall");
			return INVALIDPARAMETERS;
		}

		String action;
		args.getStringToken(action);

		Zone* zone = creature->getZone();

		if (zone == nullptr)
			return GENERALERROR;

		PlanetManager* planet = zone->getPlanetManager();

		try {
			if (action.toLowerCase() == "lair") {
				String objectTemplate;
				args.getStringToken(objectTemplate);
				float x = creature->getPositionX();
				float y = creature->getPositionY();
				float z = creature->getPositionZ();

				LairTemplate* lair = CreatureTemplateManager::instance()->getLairTemplate(objectTemplate.hashCode());

				if (lair != nullptr) {
					if (creature->getParent() != nullptr) {
						creature->sendSystemMessage("You need to be outside and unmounted to spawn that");

						return GENERALERROR;
					}

					CreatureManager* creatureManager = zone->getCreatureManager();

					int level = 10;
					if (args.hasMoreTokens()) {
						level = args.getIntToken();
					}

					if (level < 1)
						level = 1;
					else if (level > 300)
						level = 300;

					SceneObject* sceno = creatureManager->spawn(objectTemplate.hashCode(), level, 2, x, z, y, 25);

					if (sceno != nullptr) {
						creature->sendSystemMessage("lair spawned");
						return SUCCESS;
					} else {
						creature->sendSystemMessage("error spawning lair");
						return GENERALERROR;
					}

				}
			} else if (action.toLowerCase() == "spawn") {
				String objectTemplate;
				args.getStringToken(objectTemplate);
				float x = creature->getPositionX();
				float z = creature->getPositionZ();
				float y = creature->getPositionY();
				float heading = creature->getDirectionAngle();

				if (args.hasMoreTokens())
					x = args.getFloatToken();

				if (args.hasMoreTokens())
					z = args.getFloatToken();

				if (args.hasMoreTokens())
					y = args.getFloatToken();

				if (args.hasMoreTokens())
					heading = args.getFloatToken();

				ManagedReference<SceneObject*> parent = creature->getParent().get();
				SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(TemplateManager::instance()->getTemplate(objectTemplate.hashCode()));

				if (serverTemplate != nullptr && serverTemplate->getGameObjectType() != SceneObjectType::STATICOBJECT) {
					if (parent != nullptr) {
						creature->sendSystemMessage("You need to be outside and unmounted to spawn a structure");
						return GENERALERROR;
					}

					StructureObject* structure = StructureManager::instance()->placeStructure(creature, objectTemplate, x, y, heading, 0);

					if (structure == nullptr)
						return GENERALERROR;

					uint64 objectID = structure->getObjectID();
					creature->sendSystemMessage("oid: " + String::valueOf(objectID));
					planet->addEventStructure(objectID);
					return SUCCESS;
				}

				ManagedReference<SceneObject*> object =  zserv->createObject(objectTemplate.hashCode(), 0);

				if (object == nullptr)
					return GENERALERROR;

				if (object->isIntangibleObject())
					return GENERALERROR;

				Locker clocker(object, creature);

				object->initializePosition(x, z, y);
				object->setDirection(heading);

				if (parent != nullptr && parent->isCellObject())
					parent->transferObject(object, -1);
				else
					zone->transferObject(object, -1, true);

				object->createChildObjects();

				uint64 objectID = object->getObjectID();
				creature->sendSystemMessage("oid: " + String::valueOf(objectID));

				planet->addEventObject(objectID);

			} else if (action.toLowerCase() == "delete") {

				String chatObjectID;
				args.getStringToken(chatObjectID);
				uint64 oid = UnsignedLong::valueOf(chatObjectID);

				int result = planet->destroyEventObject(oid);

				if (result)
					creature->sendSystemMessage("Object " + chatObjectID + " deleted.");
				else
					creature->sendSystemMessage("Could not delete object " + chatObjectID + ".");

			} else if (action.toLowerCase() == "deleteall") {
				int result = planet->destroyAllEventObjects();
				creature->sendSystemMessage("Deleted " + String::valueOf(result) + " event objects.");
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("Spawn: /createSpawningElement spawn IffObjectPath [x z y heading]");
			creature->sendSystemMessage("Spawn: /createSpawningElement lair lairTemplate [level]");
			creature->sendSystemMessage("Delete: /createSpawningElement delete oid");
		}

		return SUCCESS;
	}

};

#endif //CREATESPAWNINGELEMENTCOMMAND_H_
