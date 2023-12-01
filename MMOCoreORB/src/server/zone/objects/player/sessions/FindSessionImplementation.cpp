/*
 * FindSessionImplementation.cpp
 *
 *  Created on: Jun 24, 2011
 *      Author: polonel
 */

#include "server/zone/objects/player/sessions/FindSession.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/objects/player/sessions/sui/FindSessionSuiCallback.h"
#include "server/zone/objects/scene/WorldCoordinates.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/CellProperty.h"

void FindSessionImplementation::initalizeFindMenu() {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == nullptr)
		return;

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::FINDSESSION, 2);
	box->setCallback(new FindSessionSuiCallback(player->getZoneServer()));
	box->setPromptTitle("@base_player:find_title"); // /Find Category Selector
	box->setPromptText("@base_player:find_prompt"); // Select a category of planetary map locations to search for.
	box->setCancelButton(true, "@cancel");
	box->addMenuItem("@find_display:cantina");
	box->addMenuItem("@find_display:capitol");
	box->addMenuItem("@find_display:city");
	box->addMenuItem("@find_display:cloningfacility");
	box->addMenuItem("@find_display:guild_combat");
	box->addMenuItem("@find_display:guild_commerce");
	box->addMenuItem("@find_display:guild_theater");
	box->addMenuItem("@find_display:guild_university");
	box->addMenuItem("@find_display:salon");
	box->addMenuItem("@find_display:hotel");
	box->addMenuItem("@find_display:medicalcenter");
	box->addMenuItem("@find_display:garage");
	box->addMenuItem("@find_display:shuttleport");
	box->addMenuItem("@find_display:starport");
	box->addMenuItem("@find_display:vendor_junk");
	box->addMenuItem("@find_display:terminal_bank");
	box->addMenuItem("@find_display:terminal_bazaar");
	box->addMenuItem("@find_display:terminal_mission");
	box->addMenuItem("@find_display:trainer_brawler");
	box->addMenuItem("@find_display:trainer_artisan");
	box->addMenuItem("@find_display:trainer_scout");
	box->addMenuItem("@find_display:trainer_marksman");
	box->addMenuItem("@find_display:trainer_entertainer");
	box->addMenuItem("@find_display:trainer_medic");

	player->getPlayerObject()->addSuiBox(box);
	player->sendMessage(box->generateMessage());
	player->addActiveSession(SessionFacadeType::FIND, _this.getReferenceUnsafeStaticCast());
}

WaypointObject* FindSessionImplementation::addWaypoint(float x, float y, const String& name) {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == nullptr)
		return nullptr;

	PlayerObject* ghost = player->getPlayerObject();

	Zone* zone = player->getZone();
	String planet = zone->getZoneName();
	StringIdChatParameter msg;

	ManagedReference<WaypointObject*> wpt =
			( player->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>(); // 0xC456E788 Waypoint

	Locker locker(wpt);

	wpt->setPlanetCRC(planet.hashCode());
	wpt->setPosition(x, 0, y);
	wpt->setCustomObjectName(name, false);
	wpt->setActive(true);
	wpt->setSpecialTypeID(WaypointObject::SPECIALTYPE_FIND);
	msg.setStringId("@base_player:prose_find_set"); // An active waypoint has be set to the nearest '%TO'.
	msg.setTO(name);

	ghost->addWaypoint(wpt, true, true);

	player->sendSystemMessage(msg);
	return wpt;
}

void FindSessionImplementation::clearWaypoint() {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == nullptr)
		return;

	PlayerObject* po = player->getPlayerObject();

	po->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_FIND, true);
}

void FindSessionImplementation::findPlanetaryObject(const String& mapCategory, const String& mapSubCategory) {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == nullptr)
		return;

	Zone* zone = player->getZone();

	if (zone == nullptr) {
		cancelSession();
		return;
	}

	ManagedReference<SceneObject*> object = zone->getNearestPlanetaryObject(player, mapCategory, mapSubCategory);

	Zone* objectZone = nullptr;

	if (object == nullptr || ((objectZone = object->getZone()) == nullptr)) {
		player->sendSystemMessage("@find_display:no_registered_locs"); // There currently are not registered map locations on this planet.
		cancelSession();
		return;
	}

	ManagedReference<CityRegion*> cityRegion = object->getCityRegion().get();
	String regFullName = "";

	if (cityRegion != nullptr) {
		regFullName = cityRegion->getCityRegionName();
	}

	String objFullName = "@map_loc_cat_n:" + object->getPlanetMapCategoryName();

	StringIdManager* stringManager = StringIdManager::instance();

	String regClientString = stringManager->getStringId(regFullName.hashCode()).toString();
	String objClientString = stringManager->getStringId(objFullName.hashCode()).toString();

	if (regClientString.isEmpty()) {
		regClientString = objectZone->getZoneName();
		regClientString[0] = toupper(regClientString[0]);
	}

	String wptName = regClientString + " (" + objClientString + ")"; // Region (BuildingType)

	Vector3 playerPos = player->getWorldPosition();
	Vector3 objectPos = object->getWorldPosition();

	Reference<WaypointObject*> wpt = addWaypoint(objectPos.getX(), objectPos.getY(), wptName);

	SortedVector<ManagedReference<NavArea*> > areas;
	//fetch nav meshes near the target position
	zone->getInRangeNavMeshes(objectPos.getX(), objectPos.getY(), &areas, false);

	bool withinNavMesh = false;

	for (const auto& mesh : areas) {
		// test to see if our player is within the same nav mesh
		if (mesh->containsPoint(playerPos.getX(), playerPos.getY())) {
			withinNavMesh = true;
			break;
		}
	}

	if (withinNavMesh) {
		Vector <WorldCoordinates> endCoords;
		Reference < Vector < WorldCoordinates > * > path = nullptr;

		WorldCoordinates start(playerPos, nullptr);
		WorldCoordinates end(objectPos, nullptr);

		if (object->isBuildingObject()) {
			BuildingObject* building = object->asBuildingObject();

			SharedBuildingObjectTemplate* templateData = static_cast<SharedBuildingObjectTemplate*>(object->getObjectTemplate());

			if (building != nullptr && templateData != nullptr && building->getTotalCellNumber() > 1) {
				CellObject* cell = building->getCell(1);
				const PortalLayout* portalLayout = templateData->getPortalLayout();

				if (portalLayout != nullptr && cell != nullptr) {
					const FloorMesh* exteriorFloorMesh = portalLayout->getFloorMesh(0);

					if (exteriorFloorMesh != nullptr) {
						const PathGraph* exteriorPathGraph = exteriorFloorMesh->getPathGraph();

						if (exteriorPathGraph != nullptr) {
							Vector3 transformedPosition = PathFinderManager::instance()->transformToModelSpace(start.getPoint(), building);
							const PathNode* exteriorNode = exteriorPathGraph->findNearestGlobalNode(transformedPosition);

							if (exteriorNode != nullptr) {
								WorldCoordinates coord(exteriorNode->getPosition(), cell);

								endCoords.add(WorldCoordinates(coord.getWorldPosition(), nullptr));

								path = PathFinderManager::instance()->findPathFromWorldToWorld(start, endCoords, zone, true);
							}
						}
					}
				}
			}
		}

		if (path == nullptr) {
			path = PathFinderManager::instance()->findPath(start, end, zone);
		}

		if (path != nullptr && path->size() > 0) {
			CreateClientPathMessage* msg = new CreateClientPathMessage();

			if (msg != nullptr) {
				for (int i = 0; i < path->size(); i++) {
					const WorldCoordinates& point = path->get(i);
					msg->addCoordinate(point.getX(), point.getZ(), point.getY());
				}

				if (wpt != nullptr) {
					PlayerObject* ghost = player->getPlayerObject();
					if (ghost != nullptr)
						ghost->setClientPathWaypoint(wpt);
				}

				player->sendMessage(msg);
			}
		}
	}

	cancelSession();
}
