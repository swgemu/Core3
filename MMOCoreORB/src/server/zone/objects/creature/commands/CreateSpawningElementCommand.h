/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CREATESPAWNINGELEMENTCOMMAND_H_
#define CREATESPAWNINGELEMENTCOMMAND_H_

#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/templates/mobile/LairTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/structure/StructureManager.h"

class CreateSpawningElementCommand : public QueueCommand {
public:

	CreateSpawningElementCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const
	{

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

		StringTokenizer args(arguments.toString());

		CreatureObject* player = cast<CreatureObject*>(creature);


		if (player == NULL)
			return GENERALERROR;

		if (!args.hasMoreTokens()) {
			creature->sendSystemMessage("Spawn: /createSpawningElement spawn lairTemplate/IffObjectPath <level>");
			creature->sendSystemMessage("Delete: /createSpawningElement delete oid");
			return INVALIDPARAMETERS;
		}

		String action;
		args.getStringToken(action);

		ZoneServer* zserv = server->getZoneServer();

		if (creature->getZone() == NULL)
			return GENERALERROR;

		try {
			if (action.toLowerCase() == "spawn") {
				String objectTemplate;
				args.getStringToken(objectTemplate);
				float x = creature->getPositionX();
				float y = creature->getPositionY();
				float z = creature->getPositionZ();

				LairTemplate* lair = CreatureTemplateManager::instance()->getLairTemplate(objectTemplate.hashCode());

				if (lair != NULL) {
					if (creature->getParent() != NULL) {
						creature->sendSystemMessage("You need to be outside and unmounted to spawn that");

						return GENERALERROR;
					}

					CreatureManager* creatureManager = creature->getZone()->getCreatureManager();

					int level = 10;
					if (args.hasMoreTokens()) {
						level = args.getIntToken();
					}

					if (level < 1)
						level = 1;
					else if (level > 300)
						level = 300;

					SceneObject* sceno = creatureManager->spawn(objectTemplate.hashCode(), level, 2, x, z, y, 25);

					if (sceno != NULL) {
						creature->sendSystemMessage("lair spawned");
						return SUCCESS;
					} else {
						creature->sendSystemMessage("error spawning lair");
						return GENERALERROR;
					}

				}

				SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(TemplateManager::instance()->getTemplate(objectTemplate.hashCode()));
				if (serverTemplate != NULL) {
					if (creature->getParent() != NULL) {
						creature->sendSystemMessage("You need to be outside and unmounted to spawn a structure");

						return GENERALERROR;
					}

					StructureObject* structure = StructureManager::instance()->placeStructure(creature, objectTemplate, x, y, creature->getDirectionAngle(), 0);
					if (structure == NULL)
						return GENERALERROR;

					creature->sendSystemMessage("oid: " + String::valueOf(structure->getObjectID()));
					return SUCCESS;
				}

				ManagedReference<SceneObject*> object =  zserv->createObject(objectTemplate.hashCode(), 0);

				if (object == NULL)
					return GENERALERROR;

				if (object->isIntangibleObject())
					return GENERALERROR;

				ManagedReference<SceneObject*> parent = creature->getParent();

				Locker clocker(object, creature);

				object->initializePosition(x, z, y);
				object->setDirection(creature->getDirectionW(), creature->getDirectionX(), creature->getDirectionY(), creature->getDirectionZ());

				if (parent != NULL && parent->isCellObject())
					parent->transferObject(object, -1);
				else
					creature->getZone()->transferObject(object, -1, true);

				object->createChildObjects();

				uint64 objectID = object->getObjectID();
				creature->sendSystemMessage("oid: " + String::valueOf(objectID));

			} else if (action.toLowerCase() == "delete") {

				String chatObjectID;
				args.getStringToken(chatObjectID);
				uint64 oid = UnsignedLong::valueOf(chatObjectID);

				ManagedReference<SceneObject*> object = zserv->getObject(oid);

				if (object == NULL) {
					creature->sendSystemMessage("Error: Trying to delete invalid oid.");
					return GENERALERROR;
				}

				for (int i = 0; i < object->getArrangementDescriptorSize(); ++i) {
					const Vector<String>* descriptors = object->getArrangementDescriptor(i);

					for (int j = 0; j < descriptors->size(); ++j) {
						const String& descriptor = descriptors->get(j);

						if (descriptor == "inventory" || descriptor == "datapad" || descriptor == "default_weapon"
							|| descriptor == "mission_bag" || descriptor == "ghost" || descriptor == "bank" || descriptor == "hair")
						return GENERALERROR;
					}
				}

				Locker clocker(object, creature);

				object->destroyObjectFromWorld(true);

				if (object->isPersistent()) {
					object->destroyObjectFromDatabase(true);
				}

				creature->sendSystemMessage("Object " + chatObjectID + " deleted.");

			}
		} catch (Exception& e) {
			creature->sendSystemMessage("Spawn: /createSpawningElement spawn lairTemplate/IffObjectPath <level>");
			creature->sendSystemMessage("Delete: /createSpawningElement delete oid");
		}

		return SUCCESS;
	}

};

#endif //CREATESPAWNINGELEMENTCOMMAND_H_
