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
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/templates/tangible/CampKitTemplate.h"
#include "server/zone/templates/tangible/CampStructureTemplate.h"
#include "server/zone/objects/area/CampSiteActiveArea.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/region/Region.h"

void CampKitMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isCampKit())
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject,
			menuResponse, player);

}

int CampKitMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);

	if (tano == NULL || !player->isPlayerCreature())
		return 0;

	if (player->getZone() == NULL)
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID == 20) {

		/// Get Camp Kit Template
		CampKitTemplate* campKitData = cast<CampKitTemplate*> (sceneObject->getObjectTemplate());
		if (campKitData == NULL) {
			error("No CampKitTemplate for: " + String::valueOf(sceneObject->getServerObjectCRC()));
			return 0;
		}

		/// Get Camp Template
		SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(campKitData->getSpawnObjectTemplate().hashCode());
		CampStructureTemplate* campStructureData = cast<CampStructureTemplate*> (templateData);
		if (campStructureData == NULL) {
			error("No CampStructureTemplate for: " + campKitData->getSpawnObjectTemplate());
			return 0;
		}

		ManagedReference<ZoneServer*> zoneServer = player->getZoneServer();
		if (zoneServer == NULL) {
			error("ZoneServer is null when trying to create camp");
			return 0;
		}

		ManagedReference<Zone*> zone = player->getZone();
		if (zone == NULL) {
			error("Zone is null when trying to create camp");
			return 0;
		}

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();
		if (planetManager == NULL) {
			error("Unable to get PlanetManager when placing camp");
			return 0;
		}


		/// Get Ghost
		Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();
		if (ghost == NULL) {
			error("PlayerCreature has no ghost: " + String::valueOf(player->getObjectID()));
			return 0;
		}

		int playerSkill = player->getSkillMod("camp");

		if(playerSkill < campStructureData->getSkillRequired()) {
			player->sendSystemMessage("@camp:sys_nsf_skill");
			return 0;
		}

		if(player->isInCombat()) {
			player->sendSystemMessage("@camp:sys_not_in_combat");
			return 0;
		}

		if(player->getParent() != NULL && player->getParent().get()->isCellObject()) {
			player->sendSystemMessage("@camp:error_inside");
			return 0;
		}

		if(!sceneObject->isASubChildOf(player)) {
			player->sendSystemMessage("@camp:sys_not_in_inventory");
			return 0;
		}

		if(!player->isStanding() || player->isRidingMount()) {
			player->sendSystemMessage("@camp:error_cmd_fail");
			return 0;
		}

		ManagedReference<CityRegion*> region = player->getCityRegion();
		if(region != NULL) {
			player->sendSystemMessage("@camp:error_muni_true");
			return 0;
		}

		/// Check for water
		if(player->isSwimming() || player->isInWater()) {
			player->sendSystemMessage("@camp:error_in_water");
			return 0;
		}

		/// Make sure player doesn't already have a camp setup somewhere else
		for (int i = 0; i < ghost->getTotalOwnedStructureCount(); ++i) {
			uint64 oid = ghost->getOwnedStructure(i);

			ManagedReference<StructureObject*> structure = ghost->getZoneServer()->getObject(oid).castTo<StructureObject*>();

			if (structure != NULL && structure->isCampStructure()) {
				player->sendSystemMessage("@camp:sys_already_camping");
				return 0;
			}
		}

		/// Check if player is in another camp
		if(player->getCurrentCamp() != NULL) {
			player->sendSystemMessage("@camp:error_camp_exists");
			return 0;
		}

		/// Check if player is elevated, on a building or porch

		/// Check camps/lairs nearby
		SortedVector<ManagedReference<QuadTreeEntry* > > nearbyObjects;
		zone->getInRangeObjects(player->getPositionX(), player->getPositionY(),
				512, &nearbyObjects, true);

		for(int i = 0; i < nearbyObjects.size(); ++i) {
			SceneObject* scno = cast<SceneObject*>(nearbyObjects.get(i).get());
			if (scno != NULL && scno->isCampStructure() && scno->getDistanceTo(
					player) <= scno->getObjectTemplate()->getNoBuildRadius() + campStructureData->getRadius()) {
				player->sendSystemMessage("@camp:error_camp_too_close");
				return 0;
			}

			if (scno != NULL && !scno->isCampStructure() && scno->isStructureObject() &&
					scno->getDistanceTo(player) <= 100) {
				player->sendSystemMessage("@camp:error_building_too_close");
				return 0;
			}

			if(scno != NULL && scno->getDistanceTo(player) <= scno->getObjectTemplate()->getNoBuildRadius() + campStructureData->getRadius()) {

				if (scno->getObserverCount(ObserverEventType::OBJECTDESTRUCTION) > 0) {
					SortedVector<ManagedReference<Observer* > > observers = scno->getObservers(ObserverEventType::OBJECTDESTRUCTION);
					for(int j = 0; j < observers.size(); ++j) {
						if(observers.get(j)->isObserverType(ObserverType::LAIR)) {
							player->sendSystemMessage("@camp:error_lair_too_close");
							return 0;
						}
					}
				}

				if (scno->getObserverCount(ObserverEventType::CREATUREDESPAWNED) > 0) {
					SortedVector<ManagedReference<Observer* > > observers2 = scno->getObservers(ObserverEventType::CREATUREDESPAWNED);
					for(int j = 0; j < observers2.size(); ++j) {
						if(observers2.get(j)->isObserverType(ObserverType::LAIR)) {
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

		/// Create Structure
		StructureObject* structureObject = StructureManager::instance()->placeStructure(
				player, campKitData->getSpawnObjectTemplate(),
				player->getPositionX(), player->getPositionY(),
				(int) player->getDirectionAngle());

		if (structureObject == NULL) {
			error("Unable to create camp: " + campKitData->getSpawnObjectTemplate());
			return 1;
		}

		/// Identify terminal for Active area
		Terminal* campTerminal = NULL;
		SortedVector < ManagedReference<SceneObject*> > *childObjects
				= structureObject->getChildObjects();

		for (int i = 0; i < childObjects->size(); ++i) {
			if (childObjects->get(i)->isTerminal()) {
				campTerminal = cast<Terminal*> (childObjects->get(i).get());
				break;
			}
		}

		if (campTerminal == NULL) {
			structureObject->destroyObjectFromDatabase(true);
			error("Camp does not have terminal: " + campStructureData->getTemplateFileName());
			return 1;
		}

		String campName = player->getFirstName();
		if(!player->getLastName().isEmpty())
			campName += " " + player->getLastName();
		campName += "'s Camp";
		campTerminal->setCustomObjectName(campName, true);

		/// Create active area
		String areaPath = "object/camp_area.iff";
		ManagedReference<CampSiteActiveArea*> campArea =
			(zoneServer->createObject( areaPath.hashCode(), 1)).castTo< CampSiteActiveArea*>();

		if (campArea == NULL) {
			structureObject->destroyObjectFromDatabase(true);
			return 1;
		}

		Locker areaLocker(campArea, player);

		campArea->init(campStructureData);
		campArea->setTerminal(campTerminal);
		campArea->setCamp(structureObject);
		campArea->setOwner(player);
		campArea->setNoBuildArea(true);
		campArea->initializePosition(player->getPositionX(), 0, player->getPositionY());

		if (!zone->transferObject(campArea, -1, false)) {
			structureObject->destroyObjectFromDatabase(true);
			campArea->destroyObjectFromDatabase(true);
			return 1;
		}

		structureObject->addActiveArea(campArea);

		player->sendSystemMessage("@camp:camp_complete");

		/// Remove Camp
		TangibleObject* tano = cast<TangibleObject*>(sceneObject);
		if(tano != NULL)
			tano->decreaseUseCount();


		return 0;
	} else
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,
				player, selectedID);

	return 0;
}

