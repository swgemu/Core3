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
					params.setTO(object);
					params.setTU(creature);
					params.setTT(sceneObject->getParent());

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
