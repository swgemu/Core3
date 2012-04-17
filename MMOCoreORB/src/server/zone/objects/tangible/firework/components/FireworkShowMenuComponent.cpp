/*
 * FireworkShowMenuComponent
 *
 *  Created on: 12/1/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "FireworkShowMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"


void FireworkShowMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isFireworkObject())
		return;

	//menuResponse->addRadialMenuItem(68, 3, "@fireworks:mnu_show_data");
	//menuResponse->addRadialMenuItemToRadialID(69, 68, 3, "@fireworks:mnu_add_event");
	//menuResponse->addRadialMenuItemToRadialID(70, 68, 3, "@fireworks:mnu_remove_event");
	//menuResponse->addRadialMenuItemToRadialID(71, 68, 3, "@fireworks:mnu_modify_event");
	//menuResponse->addRadialMenuItemToRadialID(72, 68, 3, "@fireworks:mnu_reorder_show");

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject,
			menuResponse, player);

}

int FireworkShowMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {
	if (!sceneObject->isFireworkObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if (player->getZone() == NULL)
		return 0;

	FireworkObject* firework = cast<FireworkObject*>(sceneObject);

	switch (selectedID) {
	case 20:
		startShow(player, firework);
		break;
	case 69: // Add Event
		addEvent(player, firework);
		break;
	case 70:  // Remove Event

		break;
	case 71:  // Modify Event

		break;
	case 72:  // Reorder Show

		break;
	default:
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,
			player, selectedID);
	}
	return 0;
}

void FireworkShowMenuComponent::startShow(CreatureObject* player, FireworkObject* firework) {

	//firework->launch(player, firework->getShowDuration());

	//int elapsedTime = 0;
	//for(int i = 0; i < firework->getEventCount(); ++i) {
		//ManagedReference<FireworkObject*> nextFirework = firework->getNextFirework();
		//if(nextFirework == NULL)
		//	continue;


	//}
}

void FireworkShowMenuComponent::addEvent(CreatureObject* player, FireworkObject* firework) {

	/*ManagedReference<SceneObject*> fireworkHopper = getSlottedObject("ingredient_hopper");

	if(fireworkHopper == NULL) {
		return;
	}

	fireworkHopper->sendWithoutContainerObjectsTo(player);
	fireworkHopper->openContainerTo(player);*/
}
