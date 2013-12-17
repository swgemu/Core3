/*
 * PetDeedImplementation.cpp
 *
 *  Created on: Aug 17, 2013
 *      Author: washu
 */

#include "server/zone/objects/tangible/deed/pet/PetDeed.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/templates/tangible/PetDeedTemplate.h"

void PetDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);
}

void PetDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	//alm->insertAttribute("hit_points", hitPoints);
}

void PetDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("PetDeed");
}

void PetDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	//hitPoints = (int) values->getCurrentValue("hit_points");
}

void PetDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if(isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@pet/pet_menu:menu_tame");
}

int PetDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (selectedID == 20) {

		if (generated || !isASubChildOf(player))
			return 1;

		if (player->isInCombat() || player->getParentRecursively(SceneObjectType::BUILDING) != NULL) {
			player->sendSystemMessage("@pet/pet_menu:cant_call"); //You can only unpack vehicles while Outside and not in Combat.
			return 1;
		}

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == NULL) {
			player->sendSystemMessage("Datapad doesn't exist when trying to call pet");
			return 1;
		}
		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}

