/*
 * LootContainerComponent.cpp
 *
 *  Created on: Jan 24, 2012
 *      Author: xyborn
 */

#include "LootContainerComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/group/GroupObject.h"

int LootContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) {
	if (destination != NULL) {
		ManagedReference<SceneObject*> rootParent = destination->getParent();

		if (rootParent != NULL && rootParent->isCreatureObject()) {
			CreatureObject* creature = cast<CreatureObject*>(rootParent.get());

			if (creature != NULL) {
				ManagedReference<GroupObject*> group = creature->getGroup();

				if (group != NULL) {
					StringIdChatParameter params("group", "notify_single_loot"); //[GROUP] %TU looted %TO from %TT.
					params.setTO(object->getDisplayedName());
					params.setTU(creature->getDisplayedName());
					params.setTT(sceneObject->getParent().get());

					group->sendSystemMessage(params);
				} else {
					StringIdChatParameter params("base_player", "prose_item_looted_self"); //You looted: %TT.
					params.setTT(object);

					creature->sendSystemMessage(params);
				}
			}
		}
	}

	return 0;
}


bool LootContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {
	ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	if (permissions->getOwnerID() == creature->getObjectID() || permissions->getOwnerID() == creature->getGroupID()) {
		return true;
	}

	return false;
}

