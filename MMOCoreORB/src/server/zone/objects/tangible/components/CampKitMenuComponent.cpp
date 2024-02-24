/*
 * CampKitMenuComponent
 *
 *  Created on: 12/1/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "CampKitMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "templates/tangible/CampKitTemplate.h"
#include "templates/building/CampStructureTemplate.h"
#include "server/zone/objects/area/CampSiteActiveArea.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "templates/faction/Factions.h"

// #define DEBUG_CAMPS

void CampKitMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (!sceneObject->isCampKit())
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int CampKitMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || !sceneObject->isTangibleObject())
		return 0;

	TangibleObject* campKit = sceneObject->asTangibleObject();

	if (campKit == nullptr || player == nullptr || !player->isPlayerCreature())
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	auto zone = player->getZone();

	if (zone== nullptr)
		return 0;

	if (selectedID == 20) {
		/// Get Camp Kit Template
		CampKitTemplate* campKitData = cast<CampKitTemplate*>(campKit->getObjectTemplate());

		if (campKitData == nullptr) {
			error("No CampKitTemplate for: " + String::valueOf(campKit->getServerObjectCRC()));
			return 0;
		}

		String campTemplate = campKitData->getSpawnObjectTemplate();

#ifdef DEBUG_CAMPS
		String appearanceFilename = campKitData->getAppearanceFilename();

		info(true) << "Spawning Camp Template: " << campTemplate << " Appearance Filename: " << appearanceFilename;
#endif

		// Get Camp Template
		CampStructureTemplate* campStructureData = dynamic_cast<CampStructureTemplate*>(TemplateManager::instance()->getTemplate(campTemplate.hashCode()));

		if (campStructureData == nullptr) {
			error("No CampStructureTemplate for: " + campTemplate);
			return 0;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			error("ZoneServer is null when trying to create camp");
			return 0;
		}

		auto planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			error("Unable to get PlanetManager when placing camp");
			return 0;
		}

		// Get player object
		auto ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			error("PlayerCreature has no ghost: " + String::valueOf(player->getObjectID()));
			return 0;
		}

		int playerSkill = player->getSkillMod("camp");
		int skillRequired = campStructureData->getSkillRequired();

		if (playerSkill < skillRequired) {
			player->sendSystemMessage("@camp:sys_nsf_skill");
			return 0;
		}

		if (player->isInCombat()) {
			player->sendSystemMessage("@camp:sys_not_in_combat");
			return 0;
		}

		if (player->getParent() != nullptr && player->getParent().get()->isCellObject()) {
			player->sendSystemMessage("@camp:error_inside");
			return 0;
		}

		if (!sceneObject->isASubChildOf(player)) {
			player->sendSystemMessage("@camp:sys_not_in_inventory");
			return 0;
		}

		if (!player->isStanding() || player->isRidingMount()) {
			player->sendSystemMessage("@camp:error_cmd_fail");
			return 0;
		}

		ManagedReference<CityRegion*> region = player->getCityRegion().get();

		if (region != nullptr) {
			player->sendSystemMessage("@camp:error_muni_true");
			return 0;
		}

		// Check if player is swimming or in water
		if (player->isSwimming() || player->isInWater()) {
			player->sendSystemMessage("@camp:error_in_water");
			return 0;
		}

		// Make sure player doesn't already have a camp setup somewhere else
		for (int i = 0; i < ghost->getTotalOwnedStructureCount(); ++i) {
			uint64 oid = ghost->getOwnedStructure(i);

			ManagedReference<StructureObject*> structure = zoneServer->getObject(oid).castTo<StructureObject*>();

			if (structure != nullptr && structure->isCampStructure()) {
				player->sendSystemMessage("@camp:sys_already_camping");
				return 0;
			}
		}

		/// Check if player is in another camp
		if (player->getCurrentCamp() != nullptr) {
			player->sendSystemMessage("@camp:error_camp_exists");
			return 0;
		}

		/// Check camps/lairs or buildings nearby
		SortedVector<ManagedReference<TreeEntry*>> nearbyObjects;
		zone->getInRangeObjects(player->getPositionX(), player->getPositionZ(), player->getPositionY(), 512, &nearbyObjects, true, false);

		for (int i = 0; i < nearbyObjects.size(); ++i) {
			SceneObject* scno = cast<SceneObject*>(nearbyObjects.get(i).get());

			if (scno != nullptr && scno->isCampStructure() && scno->getDistanceTo(player) <= scno->getObjectTemplate()->getNoBuildRadius() + campStructureData->getRadius()) {
				player->sendSystemMessage("@camp:error_camp_too_close");
				return 0;
			}

			if (scno != nullptr && !scno->isCampStructure() && scno->isStructureObject() && scno->getDistanceTo(player) <= 100) {
				player->sendSystemMessage("@camp:error_building_too_close");
				return 0;
			}

			if (scno != nullptr && scno->getDistanceTo(player) <= scno->getObjectTemplate()->getNoBuildRadius() + campStructureData->getRadius()) {
				if (scno->getObserverCount(ObserverEventType::OBJECTDESTRUCTION) > 0) {
					SortedVector<ManagedReference<Observer*>> observers = scno->getObservers(ObserverEventType::OBJECTDESTRUCTION);

					for (int j = 0; j < observers.size(); ++j) {
						if (observers.get(j)->isObserverType(ObserverType::LAIR)) {
							player->sendSystemMessage("@camp:error_lair_too_close");
							return 0;
						}
					}
				}

				if (scno->getObserverCount(ObserverEventType::CREATUREDESPAWNED) > 0) {
					SortedVector<ManagedReference<Observer*>> observers2 = scno->getObservers(ObserverEventType::CREATUREDESPAWNED);

					for (int j = 0; j < observers2.size(); ++j) {
						if (observers2.get(j)->isObserverType(ObserverType::LAIR)) {
							player->sendSystemMessage("@camp:error_lair_too_close");
							return 0;
						}
					}
				}
			}
		}

		/// Check to see if you can camp here (Allows building in city no-build zone but not within city limits which are checked above)
		if (!planetManager->isCampingPermittedAt(player->getPositionX(), player->getPositionY(), campStructureData->getRadius())) {
			player->sendSystemMessage("@camp:error_nobuild");
			return 0;
		}

		player->sendSystemMessage("@camp:starting_camp");

		// Apply proper color to deployed camp
		CustomizationVariables* customVars = campKit->getCustomizationVariables();

		/// Create Structure
		StructureObject* campObject = StructureManager::instance()->placeCamp(player, customVars, campTemplate, player->getPositionX(), player->getPositionY(), (int)player->getDirectionAngle());

		if (campObject == nullptr) {
			error("Unable to create camp: " + campTemplate);
			return 1;
		}

#ifdef DEBUG_CAMPS
		info(true) << "Camp has been placed";

		String strucAppearanceFilename = campObject->getObjectTemplate()->getAppearanceFilename();
		String clientDataFilename = campObject->getObjectTemplate()->getClientDataFile();

		info(true) << "Camp Appearance Filename: " << strucAppearanceFilename << " CDF: " << clientDataFilename;
#endif

		// Identify terminal for Active area
		Terminal* campTerminal = nullptr;

		SortedVector<ManagedReference<SceneObject*>>* childObjects = campObject->getChildObjects();

		for (int i = 0; i < childObjects->size(); ++i) {
			auto child = childObjects->get(i);

			if (child == nullptr || !child->isTerminal())
				continue;

			campTerminal = child.castTo<Terminal*>();
			break;
		}

		if (campTerminal == nullptr) {
			campObject->destroyObjectFromWorld(true);
			campObject->destroyObjectFromDatabase(true);

			error() << "Camp does not have terminal: " << campStructureData->getTemplateFileName();

			return 1;
		}

		String campName = player->getFirstName();

		if (!player->getLastName().isEmpty())
			campName += " " + player->getLastName();

		campName += "'s Camp";
		campTerminal->setCustomObjectName(campName, true);

		int campFaction = campObject->getFaction();

		if ((skillRequired >= MAP_REGISTER_MOD) && campFaction != Factions::FACTIONNEUTRAL) {
			campTerminal->setFaction(campFaction);
			campTerminal->setFactionStatus(player->getFactionStatus());
			campTerminal->broadcastPvpStatusBitmask();

			String categoryName = (campFaction == Factions::FACTIONIMPERIAL ? "imperial" : "rebel");

			Reference<const PlanetMapCategory*> campCat = TemplateManager::instance()->getPlanetMapCategoryByName(categoryName);

			if (campCat != nullptr) {
				campObject->setPlanetMapCategory(campCat);

				zone->registerObjectWithPlanetaryMap(campObject);
			}
		}

		// Create active area
		String areaPath = "object/camp_area.iff";
		ManagedReference<CampSiteActiveArea*> campArea = (zoneServer->createObject(areaPath.hashCode(), 1)).castTo<CampSiteActiveArea*>();

		if (campArea == nullptr) {
			campObject->destroyObjectFromWorld(true);
			campObject->destroyObjectFromDatabase(true);

			return 1;
		}

		Locker areaLocker(campArea, player);

		campArea->init(campStructureData);
		campArea->setTerminal(campTerminal);
		campArea->setCamp(campObject);
		campArea->setOwner(player);
		campArea->setAbandoned(false);

		campArea->addAreaFlag(ActiveArea::NOBUILDZONEAREA);
		campArea->initializePosition(player->getPositionX(), 0, player->getPositionY());

		if (!zone->transferObject(campArea, -1, true)) {
			campObject->destroyObjectFromWorld(true);
			campObject->destroyObjectFromDatabase(true);

			campArea->destroyObjectFromDatabase(true);
			return 1;
		}

		campObject->addActiveArea(campArea);

		player->sendSystemMessage("@camp:camp_complete");

		player->notifyObservers(ObserverEventType::DEPLOYEDCAMP, campArea, 0);

		// Decrease uses on camp
		campKit->decreaseUseCount();

		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
