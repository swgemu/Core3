/*
 * LootSchematicMenuComponent.cpp
 *
 *  Created on: 10/30/2011
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "LootSchematicMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "server/zone/templates/tangible/LootSchematicTemplate.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"

void LootSchematicMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	uint32 gameObjectType = sceneObject->getGameObjectType();

	menuResponse->addRadialMenuItem(50, 3, "@ui_radial:item_use_deed");

}

int LootSchematicMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if(selectedID == 50) {
		PlayerObject* ghost = cast<PlayerObject*>(player->getSlottedObject("ghost"));

		SharedObjectTemplate* templateData =
				TemplateManager::instance()->getTemplate(sceneObject->getServerObjectCRC());

		if(templateData == NULL) {
			error("No template for: " + sceneObject->getServerObjectCRC());
			return 0;
		}

		LootSchematicTemplate* schematicData = cast<LootSchematicTemplate*>(templateData);

		if (schematicData == NULL) {
			error("No LootSchematicTemplate for: " + sceneObject->getServerObjectCRC());
			return 0;
		}

		ManagedReference<DraftSchematic* > schematic = SchematicMap::instance()->get(schematicData->getTargetDraftSchematic().hashCode());

		if (schematic == NULL) {
			error("Unable to create schematic: " + schematicData->getTargetDraftSchematic());
			return 0;
		}

		if(ghost->addRewardedSchematic(schematic, schematicData->getTargetUseCount(), true)) {

			TangibleObject* tano = cast<TangibleObject*>(sceneObject);
			if(tano != NULL)
				tano->decreaseUseCount(player);
		}

		return 0;
	} else
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

	return 0;
}

