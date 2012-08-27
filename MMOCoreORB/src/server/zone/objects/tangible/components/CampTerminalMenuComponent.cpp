/*
 * CampKitMenuComponent
 *
 *  Created on: 12/1/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "CampTerminalMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/templates/tangible/CampStructureTemplate.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/structure/StructureManager.h"


void CampTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTerminal())
		return;

	Terminal* terminal = cast<Terminal*>(sceneObject);
	if(terminal == NULL) {
		error("Terminal is null in fillObjectMenuResponse");
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());
	if(camp == NULL) {
		error("Camp is null in fillObjectMenuResponse");
		return;
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject,
			menuResponse, player);

	/// Get Ghost
	PlayerObject* ghost = cast<PlayerObject*> (player->getSlottedObject("ghost"));
	if (ghost == NULL) {
		error("PlayerCreature has no ghost: " + String::valueOf(player->getObjectID()));
		return;
	}

	menuResponse->addRadialMenuItem(68, 3, "@camp:mnu_status");

	/// Make sure player doesn't already have a camp setup somewhere else
	for (int i = 0; i < ghost->getTotalOwnedStructureCount(); ++i) {
		uint64 oid = ghost->getOwnedStructure(i);

		ManagedReference<StructureObject*> structure = cast<StructureObject*>(ghost->getZoneServer()->getObject(oid));

		if (structure == camp) {
			menuResponse->addRadialMenuItem(182, 3, "@camp:mnu_disband");
			return;
		}
	}

	Vector < ManagedReference<ActiveArea*> > *areas = sceneObject->getActiveAreas();
	ManagedReference<ActiveArea*> area = NULL;
	for (int i = 0; i < areas->size(); ++i) {
		area = areas->get(i);
		if (area->isCampArea()) {
			break;
		}
		area == NULL;
	}

	if (area != NULL && cast<CampSiteActiveArea*> (area.get()) != NULL &&
			cast<CampSiteActiveArea*> (area.get())->isAbandoned())
		menuResponse->addRadialMenuItem(183, 3, "@camp:mnu_assume_ownership");
}

int CampTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	/// Disband
	switch(selectedID) {
	case 182:
		disbandCamp(sceneObject, player);
		return 0;
	case 183:
		assumeCampOwnership(sceneObject, player);
		return 0;
	case 68:
		showCampStatus(sceneObject, player);
		return 0;
	default:
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,
				player, selectedID);
	}


	return 0;
}

void CampTerminalMenuComponent::disbandCamp(SceneObject* sceneObject,
		CreatureObject* player) {

	Terminal* terminal = cast<Terminal*>(sceneObject);
	if(terminal == NULL) {
		error("Terminal is null in disbandCamp");
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());
	if(camp == NULL) {
		error("Camp is null in disbandCamp");
		return;
	}

	if (camp->getZone() == NULL)
		return;

	if(player->isSitting()) {
		player->setPosture(CreaturePosture::UPRIGHT, true);
	}

	// Find Camp Area
	Vector<ManagedReference<ActiveArea* > >* areas = camp->getActiveAreas();
	ManagedReference<ActiveArea*> area = NULL;
	for(int i = 0; i < areas->size(); ++i) {
		area = areas->get(i);
		if(area->isCampArea()) {
			break;
		}
		area == NULL;
	}

	CampSiteActiveArea* campArea = cast<CampSiteActiveArea*>(area.get());
	if(campArea != NULL && campArea->despawnCamp())
		return;

	// For some reason if the area is gone, clean up camp anyways
	ManagedReference<StructureManager*> structureManager = camp->getZone()->getStructureManager();
	if (structureManager == NULL) {
		error("Unable to get StructureManager when placing camp");
		return;
	}

	structureManager->destroyStructure(camp);
	campArea->destroyObjectFromWorld(true);
	campArea->destroyObjectFromDatabase(true);
}

void CampTerminalMenuComponent::assumeCampOwnership(SceneObject* sceneObject,
		CreatureObject* player) {

	Terminal* terminal = cast<Terminal*>(sceneObject);
	if(terminal == NULL) {
		error("Terminal is null in assumeCampOwnership");
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());
	if(camp == NULL) {
		error("Camp is null in assumeCampOwnership");
		return;
	}

	// Find Camp Area
	Vector<ManagedReference<ActiveArea* > >* areas = camp->getActiveAreas();
	ManagedReference<ActiveArea*> area = NULL;
	for(int i = 0; i < areas->size(); ++i) {
		area = areas->get(i);

		if(area->isCampArea()) {
			break;
		}

		area = NULL;
	}

	CampSiteActiveArea* campArea = cast<CampSiteActiveArea*>(area.get());

	if (campArea != NULL) {
		if(!campArea->isAbandoned())
			return;

		campArea->assumeOwnership(player);
	}
}

void CampTerminalMenuComponent::showCampStatus(SceneObject* sceneObject,
		CreatureObject* player) {

	Terminal* terminal = cast<Terminal*>(sceneObject);
	if(terminal == NULL) {
		error("Terminal is null in CampTerminalMenuComponent::showCampStatus");
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());
	if(camp == NULL) {
		error("Camp is null in CampTerminalMenuComponent::showCampStatus");
		return;
	}

	// Get Camp Area
	Vector<ManagedReference<ActiveArea* > >* areas = camp->getActiveAreas();
	ManagedReference<ActiveArea*> area = NULL;
	for(int i = 0; i < areas->size(); ++i) {
		area = areas->get(i);
		if(area->isCampArea()) {
			break;
		}
		area == NULL;
	}

	CampSiteActiveArea* campArea = cast<CampSiteActiveArea*>(area.get());

	if(area == NULL || campArea == NULL) {
		error("CampSiteActiveArea is null in CampTerminalMenuComponent::showCampStatus");
		return;
	}

	/// Get Ghost
	PlayerObject* ghost = cast<PlayerObject*> (player->getSlottedObject("ghost"));
	if (ghost == NULL) {
		error("PlayerCreature has no ghost in CampTerminalMenuComponent::showCampStatus: " + String::valueOf(player->getObjectID()));
		return;
	}

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::CAMP_STATUS);
	suiBox->setPromptTitle("@camp:mnu_status");
	suiBox->setUsingObject(terminal);
	suiBox->setPromptText(terminal->getDisplayedName());

	StringBuffer owner, time, visitors;
	owner << "Owner: " << campArea->getOwner()->getFirstName() << " " <<
			camp->getOwnerCreatureObject()->getLastName() << endl;
	suiBox->addMenuItem(owner.toString());

	time << "Time: " << (campArea->getUptime() / 60) << " minutes, "<< (campArea->getUptime() % 60) << "seconds";
	suiBox->addMenuItem(time.toString());

	visitors << "Visitors: " << campArea->getVisitorCount() << endl;
	suiBox->addMenuItem(visitors.toString());

	ghost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void CampTerminalMenuComponent::awardCampExperience(PlayerObject* ghost,
		CampSiteActiveArea* campArea) {

}

