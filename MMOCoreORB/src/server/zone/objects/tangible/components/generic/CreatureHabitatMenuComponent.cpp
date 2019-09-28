/*
 * CreatureHabitatMenuComponent
 *
 *  Created on: 12/1/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "CreatureHabitatMenuComponent.h"
#include "templates/tangible/LiveSampleTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/objects/building/BuildingObject.h"

void CreatureHabitatMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	if (!sceneObject->isCreatureHabitat())
		return;

	TangibleObject* creatureHabitat = cast<TangibleObject*>(sceneObject);
	if( creatureHabitat == nullptr )
		return;

	// Get live sample from habitat
	ManagedReference<TangibleObject*> creatures = getLiveCreatures( creatureHabitat );
	if( creatures == nullptr )
		return;

	// Check permissions if item is in a building
	ManagedReference<SceneObject*> parent = creatureHabitat->getParent().get();
	if( parent != nullptr && parent->isCellObject() ){

		ManagedReference<SceneObject*> obj = parent->getParent().get();
		if( obj != nullptr && obj->isBuildingObject() ){

			ManagedReference<BuildingObject*> buio = cast<BuildingObject*>( obj.get());
			if ( buio != nullptr && buio->isOnAdminList(player) ){
				menuResponse->addRadialMenuItem(69, 3, "@lair_n:release_creatures");
			}
		}
	}
	else{
		menuResponse->addRadialMenuItem(69, 3, "@lair_n:release_creatures");
	}

}

ManagedReference<TangibleObject*> CreatureHabitatMenuComponent::getLiveCreatures(TangibleObject* creatureHabitat) const {

	ManagedReference<SceneObject*> craftedContainer = creatureHabitat->getSlottedObject("crafted_components");
	if(craftedContainer == nullptr || craftedContainer->getContainerObjectsSize() == 0)
		return nullptr;

	SceneObject* satchel = craftedContainer->getContainerObject(0);
	if(satchel != nullptr && satchel->getContainerObjectsSize() > 0) {

		for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {

			ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);
			if( sceno != nullptr && sceno->isLiveSample() ){
				return cast<TangibleObject*>(sceno.get());
			}

		}
	}

	return nullptr;
}

int CreatureHabitatMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) const {

	if(selectedID == 69) {

		if (!sceneObject->isCreatureHabitat())
			return 0;

		if (!player->isPlayerCreature())
			return 0;

		if (player->getZone() == nullptr)
			return 0;

		TangibleObject* creatureHabitat = cast<TangibleObject*>(sceneObject);
		if( creatureHabitat == nullptr )
			return 0;

		// Get live sample from habitat
		ManagedReference<TangibleObject*> creatures = getLiveCreatures( creatureHabitat );
		if(creatures == nullptr) {
			player->sendSystemMessage("There are no creatures in this habitat");
			return 0;
		}

		Reference<LiveSampleTemplate*> liveSampleTemplate = cast<LiveSampleTemplate*>(creatures->getObjectTemplate());
		if (liveSampleTemplate == nullptr) {
			player->sendSystemMessage("Invalid Creature Template");
			error("No LiveSampleTemplate for: " + String::valueOf(creatures->getServerObjectCRC()));
			return 0;
		}

		String animation = liveSampleTemplate->getAnimation();

		if(!animation.isEmpty()) {
			PlayClientEffectObjectMessage* release = new PlayClientEffectObjectMessage(player, animation, "");
			player->broadcastMessage(release, true);

			player->sendSystemMessage("@lair_n:release");
			creatureHabitat->decreaseUseCount();
		} else {
			player->sendSystemMessage("Invalid Animation");
		}

		return 0;
	} else {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,	player, selectedID);
	}
}


