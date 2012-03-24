/*
 * CreatureHabitatMenuComponent
 *
 *  Created on: 12/1/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "CreatureHabitatMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/DataObjectComponentReference.h"
#include "server/zone/templates/tangible/LiveSampleTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"

void CreatureHabitatMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isCreatureHabitat())
		return;

	ManagedReference<SceneObject*> craftedContainer = sceneObject->getSlottedObject("crafted_components");
	if(craftedContainer == NULL)
		return;

	ManagedReference<SceneObject*> creatures = NULL;

	for(int i = 0; i < craftedContainer->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> scno = craftedContainer->getContainerObject(i);
		if(scno->isLiveSample()) {
			creatures = cast<TangibleObject*>(scno.get());
			break;
		}
	}


	/// Release
	if(creatures != NULL)
		menuResponse->addRadialMenuItem(69, 3, "@lair_n:release_creatures");


	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject,
			menuResponse, player);
}

int CreatureHabitatMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {

	if(selectedID == 69) {

		if (!sceneObject->isCreatureHabitat())
			return 0;

		if (!player->isPlayerCreature())
			return 0;

		if (player->getZone() == NULL)
			return 0;

		ManagedReference<SceneObject*> craftedContainer = sceneObject->getSlottedObject("crafted_components");
		if(craftedContainer == NULL)
			return 0;

		ManagedReference<SceneObject*> creatures = NULL;

		for(int i = 0; i < craftedContainer->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> scno = craftedContainer->getContainerObject(i);
			if(scno->isLiveSample()) {
				creatures = cast<TangibleObject*>(scno.get());
				break;
			}
		}

		if(creatures == NULL) {
			player->sendSystemMessage("There are no creatures in this habitat");
			return 0;
		}

		/// Get LiveSampleTemplate
		SharedObjectTemplate* templateData =
				TemplateManager::instance()->getTemplate(creatures->getServerObjectCRC());
		if (templateData == NULL) {
			error("No template for: " + creatures->getServerObjectCRC());
			return 0;
		}
		LiveSampleTemplate* liveSampleTemplate = cast<LiveSampleTemplate*>(templateData);
		if (liveSampleTemplate == NULL) {
			error("No LiveSampleTemplate for: " + creatures->getServerObjectCRC());
			return 0;
		}

		String animation = liveSampleTemplate->getAnimation();

		if(!animation.isEmpty()) {
			PlayClientEffectObjectMessage* release = new PlayClientEffectObjectMessage(player, animation, "");
			player->broadcastMessage(release, true);

			player->sendSystemMessage("@lair_n:release");

			sceneObject->removeAllContainerObjects();
		} else {
			player->sendSystemMessage("Invalid Animation");
		}


	} else {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,
				player, selectedID);
	}


	return 0;
}


