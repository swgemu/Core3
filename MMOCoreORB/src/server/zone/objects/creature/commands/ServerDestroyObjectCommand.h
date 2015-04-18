/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERDESTROYOBJECTCOMMAND_H_
#define SERVERDESTROYOBJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"


class ServerDestroyObjectCommand : public QueueCommand {
public:

	ServerDestroyObjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//creature->info("serverdestroy arguments: " + arguments.toString(), true);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL)
			return GENERALERROR;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		Locker crossLocker(object, creature);

		if (object->canBeDestroyed(creature) != 0)
			return GENERALERROR;

		// need to add checks.. inventory, datapad, bank, waypoint

		if (object->isWaypointObject()) {
			Reference<PlayerObject*> playerObject = creature->getSlottedObject("ghost").castTo<PlayerObject*>( );

			if (playerObject != NULL)
				playerObject->removeWaypoint(target);

			return SUCCESS;
		}

		ManagedReference<SceneObject*> objectParent = object->getParent();

		if (!object->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER))
			return GENERALERROR;

		if (objectParent != NULL && !objectParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT))
			return GENERALERROR;

		for (int i = 0; i < object->getArrangementDescriptorSize(); ++i) {
			Vector<String> descriptors = object->getArrangementDescriptor(i);
			for (int j = 0; j < descriptors.size(); ++j) {
				String descriptor = descriptors.get(j);

				if (descriptor == "inventory" || descriptor == "datapad" || descriptor == "default_weapon"
						|| descriptor == "mission_bag" || descriptor == "ghost" || descriptor == "bank" || descriptor == "hair")
					return GENERALERROR;
			}
		}

		if (object->isASubChildOf(creature)){

			if(object->isTangibleObject()){
				ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object.get());

				if(tano->hasAntiDecayKit()){
					ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

					if(inventory == NULL){
						creature->sendSystemMessage("@veteran_new:failed_kit_create"); // "This item has Anti Decay applied to it but there was a failure to recreate the Anti Decay Kit."
						return GENERALERROR;
					}

					if(inventory->getContainerVolumeLimit() < (inventory->getCountableObjectsRecursive() + 1)){
						creature->sendSystemMessage("@veteran_new:inventory_full"); // The item can not be deleted because it has Anti Decay applied to it but you do not have room in your inventory to retrieve the Anti Decay Kit that will be created after destroying this item.
						return GENERALERROR;
					}

					ManagedReference<SceneObject*> adk = tano->removeAntiDecayKit();

					if(adk == NULL){
						creature->sendSystemMessage("@veteran_new:failed_kit_create"); // "This item has Anti Decay applied to it but there was a failure to recreate the Anti Decay Kit."
						return GENERALERROR;
					}

					inventory->transferObject(adk, -1, false);
					adk->sendTo(creature, true);
					creature->sendSystemMessage("@veteran_new:kit_created"); // "This item had Anti Decay applied to it. A new Anti Decay Kit has been placed in your inventory."
				}
			}

			destroyObject(object, creature);
		}

		return SUCCESS;
	}

	void destroyObject(SceneObject* object, CreatureObject* creature) const {
		object->destroyObjectFromWorld(true);

		object->destroyObjectFromDatabase(true);
	}

};

#endif //SERVERDESTROYOBJECTCOMMAND_H_
