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
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/gcw/GCWManager.h"

void CampTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (!sceneObject->isTerminal())
		return;

	auto zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr)
		return;

	Terminal* terminal = cast<Terminal*>(sceneObject);

	if (terminal == nullptr) {
		error("Terminal is null in fillObjectMenuResponse");
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());

	if (camp == nullptr) {
		error("Camp is null in fillObjectMenuResponse");
		return;
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	// Get player object
	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		error("PlayerCreature has no ghost: " + String::valueOf(player->getObjectID()));
		return;
	}

	if (!player->isInRange(terminal, 16)) {
		return;
	}

	menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU1, 3, "@camp:mnu_status");

	uint64 campOwnerID = camp->getOwnerObjectID();

	SortedVector<ManagedReference<ActiveArea*>>* areas = camp->getActiveAreas();
	ManagedReference<CampSiteActiveArea*> campArea = nullptr;

	for (int i = 0; i < areas->size(); ++i) {
		auto checkArea = areas->get(i);

		if (checkArea == nullptr || !checkArea->isCampArea())
			continue;

		campArea = checkArea.castTo<CampSiteActiveArea*>();
	}

	if (campArea == nullptr) {
		error() << "Camp: " << camp->getObjectID() << " has null camp active area.";
		return;
	}

	// Camp area is abandoned, add menu item to assume ownership if player is able
	if (!campArea->isAbandoned()) {
		// Add option for the owner to disband the camp
		if (campOwnerID == player->getObjectID())
			menuResponse->addRadialMenuItem(RadialOptions::SERVER_CAMP_DISBAND, 3, "@camp:mnu_disband");
	} else {
		bool hasCamp = false;

		// Camp is abandoned, add option for player to
		for (int i = 0; i < ghost->getTotalOwnedStructureCount(); ++i) {
			uint64 oid = ghost->getOwnedStructure(i);

			auto structure = zoneServer->getObject(oid).castTo<StructureObject*>();

			// Ignore structures that are not camps and ignore this camp itself, allowing the owner to reclaim their camp
			if (structure == nullptr || !structure->isCampStructure() || structure->getObjectID() == camp->getObjectID())
				continue;

			// Player already has a camp
			hasCamp = true;
			break;
		}

		if (!hasCamp)
			menuResponse->addRadialMenuItem(RadialOptions::SERVER_CAMP_ASSUME_OWNERSHIP, 3, "@camp:mnu_assume_ownership");
	}

	// Faction Menu Items available to purchase by factionally aligned member using the camp terminal
	if (player->getFaction() == terminal->getFaction() && player->getFactionStatus() == FactionStatus::OVERT) {
		menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU3, 3, "@camp:mnu_requisition"); // requisition goods
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU3, RadialOptions::SERVER_MENU4, 3, "@camp:mnu_requisition_wpn"); // requisition weapons
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU3, RadialOptions::SERVER_MENU5, 3, "@camp:mnu_requisition_installation"); // requisition installations
	}
}

int CampTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	auto zone = player->getZone();

	if (zone == nullptr)
		return 0;

	auto gcwMan = zone->getGCWManager();

	if (gcwMan == nullptr)
		return 0;

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	if (lua == nullptr)
		return 0;

	/// Disband
	switch (selectedID) {
		case RadialOptions::SERVER_CAMP_DISBAND:
			disbandCamp(sceneObject, player);
			return 0;
		case RadialOptions::SERVER_CAMP_ASSUME_OWNERSHIP:
			assumeCampOwnership(sceneObject, player);
			return 0;
		case RadialOptions::SERVER_MENU1:
			showCampStatus(sceneObject, player);
			return 0;
		// requisition weapons
		case RadialOptions::SERVER_MENU4: {
			Reference<LuaFunction*> luaPurchaseSui = lua->createFunction("recruiterScreenplay", "sendPurchaseSui", 0);

			if (luaPurchaseSui != nullptr) {
				*luaPurchaseSui << player;
				*luaPurchaseSui << player;
				*luaPurchaseSui << "fp_weapons_armor";
				*luaPurchaseSui << (1.15 * gcwMan->getGCWDiscount(player));
				luaPurchaseSui->callFunction();
			}

			break;
		}
		// requisition installations
		case RadialOptions::SERVER_MENU5: {
			Reference<LuaFunction*> luaPurchaseSui = lua->createFunction("recruiterScreenplay", "sendPurchaseSui", 0);

			if (luaPurchaseSui != nullptr) {
				*luaPurchaseSui << player;
				*luaPurchaseSui << player;
				*luaPurchaseSui << "fp_installations";
				*luaPurchaseSui << (1.15 * gcwMan->getGCWDiscount(player));
				luaPurchaseSui->callFunction();
			}

			break;
		}
		default:
			return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}

	return 0;
}

void CampTerminalMenuComponent::disbandCamp(SceneObject* sceneObject, CreatureObject* player) const {
	Terminal* terminal = cast<Terminal*>(sceneObject);
	if (terminal == nullptr) {
		error("Terminal is null in disbandCamp");
		return;
	}

	if (!player->isInRange(terminal, 16)) {
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());
	if (camp == nullptr) {
		error("Camp is null in disbandCamp");
		return;
	}

	if (camp->getZone() == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return;
	}

	if (!ghost->isOwnedStructure(camp)) {
		return;
	}

	if (player->isSitting()) {
		player->setPosture(CreaturePosture::UPRIGHT, true);
	}

	// Find Camp Area
	SortedVector<ManagedReference<ActiveArea*>>* areas = camp->getActiveAreas();
	ManagedReference<ActiveArea*> area = nullptr;
	for (int i = 0; i < areas->size(); ++i) {
		area = areas->get(i);
		if (area->isCampArea()) {
			break;
		}
		area = nullptr;
	}

	CampSiteActiveArea* campArea = cast<CampSiteActiveArea*>(area.get());
	if (campArea != nullptr && campArea->despawnCamp())
		return;

	StructureManager::instance()->destroyStructure(camp);

	if (campArea != nullptr) {
		campArea->destroyObjectFromWorld(true);
		campArea->destroyObjectFromDatabase(true);
	}
}

void CampTerminalMenuComponent::assumeCampOwnership(SceneObject* sceneObject, CreatureObject* player) const {
	Terminal* terminal = cast<Terminal*>(sceneObject);

	if (terminal == nullptr) {
		error("Terminal is null in assumeCampOwnership");
		return;
	}

	if (!player->isInRange(terminal, 16)) {
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());

	if (camp == nullptr) {
		error("Camp is null in assumeCampOwnership");
		return;
	}

	// Find Camp Area
	SortedVector<ManagedReference<ActiveArea*>>* areas = camp->getActiveAreas();
	ManagedReference<ActiveArea*> area = nullptr;

	for (int i = 0; i < areas->size(); ++i) {
		auto activeArea = areas->get(i);

		if (activeArea == nullptr || !activeArea->isCampArea())
			continue;

		area = activeArea;
		break;
	}

	ManagedReference<CampSiteActiveArea*> campArea = cast<CampSiteActiveArea*>(area.get());

	if (campArea != nullptr) {
		if (!campArea->isAbandoned())
			return;

		ManagedReference<CreatureObject*> play = player;

		Core::getTaskManager()->executeTask(
			[=]() {
				Locker locker(campArea);
				campArea->assumeOwnership(play);
			},
			"AssumeOwnershipLambda");
	}
}

void CampTerminalMenuComponent::showCampStatus(SceneObject* sceneObject, CreatureObject* player) const {
	Terminal* terminal = cast<Terminal*>(sceneObject);
	if (terminal == nullptr) {
		error("Terminal is null in CampTerminalMenuComponent::showCampStatus");
		return;
	}

	if (!player->isInRange(terminal, 16)) {
		return;
	}

	StructureObject* camp = cast<StructureObject*>(terminal->getControlledObject());
	if (camp == nullptr) {
		error("Camp is null in CampTerminalMenuComponent::showCampStatus");
		return;
	}

	// Get Camp Area
	SortedVector<ManagedReference<ActiveArea*>>* areas = camp->getActiveAreas();
	ManagedReference<ActiveArea*> area = nullptr;
	for (int i = 0; i < areas->size(); ++i) {
		area = areas->get(i);
		if (area->isCampArea()) {
			break;
		}

		area = nullptr;
	}

	if (area == nullptr) {
		Reference<StructureManager*> structureManager = StructureManager::instance();
		if (structureManager == nullptr) {
			error("Unable to get StructureManager in CampTerminalMenuComponent::showCampStatus");
			return;
		}

		structureManager->destroyStructure(camp);
		player->sendSystemMessage("This camp is broken, removing from world.  Thanks!");
		error("CampSiteActiveArea is null in CampTerminalMenuComponent::showCampStatus");
		return;
	}

	CampSiteActiveArea* campArea = cast<CampSiteActiveArea*>(area.get());
	if (campArea == nullptr) {
		error("How the fuck did this happen");
		return;
	}
	/// Get Ghost
	Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();
	if (ghost == nullptr) {
		error("PlayerCreature has no ghost in CampTerminalMenuComponent::showCampStatus: " + String::valueOf(player->getObjectID()));
		return;
	}

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::CAMP_STATUS);
	suiBox->setPromptTitle("@camp:mnu_status");
	suiBox->setUsingObject(terminal);
	suiBox->setPromptText(terminal->getDisplayedName());

	StringBuffer owner, time, visitors;
	owner << "Owner: " << campArea->getOwner()->getFirstName() << " " << camp->getOwnerCreatureObject()->getLastName() << endl;
	suiBox->addMenuItem(owner.toString());

	time << "Time: " << (campArea->getUptime() / 60) << " minutes, " << (campArea->getUptime() % 60) << "seconds";
	suiBox->addMenuItem(time.toString());

	visitors << "Visitors: " << campArea->getVisitorCount() << endl;
	suiBox->addMenuItem(visitors.toString());

	ghost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void CampTerminalMenuComponent::awardCampExperience(PlayerObject* ghost, CampSiteActiveArea* campArea) const {
}
