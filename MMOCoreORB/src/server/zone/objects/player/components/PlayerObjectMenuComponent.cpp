/*
 * PlayerObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "PlayerObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/player/sui/listbox/teachplayerlistbox/TeachPlayerListBox.h"

void PlayerObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!sceneObject->isCreatureObject())
		return;

	CreatureObject* creature = (CreatureObject*) sceneObject;
	GroupObject* group = creature->getGroup();

	if (group != NULL) {
		if (group->hasMember(player))
			menuResponse->addRadialMenuItem(51, 3, "@sui:teach");
	}

	if (creature->isPlayingMusic()) {
		if (!player->isListening())
			menuResponse->addRadialMenuItem(113, 3, "@radial_performance:listen");
		else
			menuResponse->addRadialMenuItem(115, 3, "@radial_performance:listen_stop");
	}

	if (creature->isDancing()) {
		if (!player->isWatching())
			menuResponse->addRadialMenuItem(114, 3, "@radial_performance:watch");
		else
			menuResponse->addRadialMenuItem(116, 3, "@radial_performance:watch_stop");
	}

}

int PlayerObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	CreatureObject* ownerPlayer = dynamic_cast<CreatureObject*>(sceneObject);
	PlayerObject* ghost = ownerPlayer->getPlayerObject();

	switch(selectedID) {
	case 113:
		player->executeObjectControllerAction(String("listen").hashCode(), sceneObject->getObjectID(), "");
		break;
	case 115:
		player->executeObjectControllerAction(String("stoplistening").hashCode(), sceneObject->getObjectID(), "");
		break;

	case 114:
		player->executeObjectControllerAction(String("watch").hashCode(), sceneObject->getObjectID(), "");
		break;

	case 116:
		player->executeObjectControllerAction(String("stopwatching").hashCode(), sceneObject->getObjectID(), "");
		break;

	case 51:

			if (ghost->isTeachingOrLearning() || ghost->isTeachingOrLearning()) {
				player->sendSystemMessage("teaching", "teaching_failed");
				return 1;
			}

			ghost->setTeachingOrLearning(true);

			ManagedReference<TeachPlayerListBox*> teachPlayerListBox = new TeachPlayerListBox(player);
			teachPlayerListBox->setCancelButton(true, "");

			bool completed = teachPlayerListBox->generateSkillList(player, ownerPlayer);

			if(!completed)
				ghost->setTeachingOrLearning(false);

		break;
	}

	return 0;
}

