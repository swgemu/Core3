/*
 * FindSessionImplementation.cpp
 *
 *  Created on: Jun 24, 2011
 *      Author: polonel
 */

#include "server/zone/objects/player/sessions/FindSession.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/planet/MapLocationType.h"

#include "server/zone/objects/player/sessions/sui/FindSessionSuiCallback.h"

void FindSessionImplementation::initalizeFindMenu() {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == NULL)
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
	player->addActiveSession(SessionFacadeType::FIND, _this.get());
}

void FindSessionImplementation::addWaypoint(float x, float y, const String& name) {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	Zone* zone = player->getZone();
	String planet = zone->getZoneName();
	StringIdChatParameter msg;

	ManagedReference<WaypointObject*> wpt =
			( player->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>(); // 0xC456E788 Waypoint

	wpt->setPlanetCRC(planet.hashCode());
	wpt->setPosition(x, 0, y);
	wpt->setCustomObjectName(name, false);
	wpt->setActive(true);
	wpt->setSpecialTypeID(WaypointObject::SPECIALTYPE_FIND);
	msg.setStringId("@base_player:prose_find_set"); // An active waypoint has be set to the nearest '%TO'.
	msg.setTO(name);

	ghost->addWaypoint(wpt, true, true);

	player->sendSystemMessage(msg);

}

void FindSessionImplementation::clearWaypoint() {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == NULL)
		return;

	PlayerObject* po = player->getPlayerObject();

	WaypointList* waypointlist = po->getWaypointList();
	uint64 wpid = waypointlist->getWaypointBySpecialType(
			WaypointObject::SPECIALTYPE_FIND);

	if (wpid != 0) {
		po->removeWaypoint(wpid, true);

	}
}

void FindSessionImplementation::findPlanetaryObject(String& maplocationtype) {
	ManagedReference<CreatureObject* > player = this->player.get();

	if (player == NULL)
		return;

	Zone* zone = player->getZone();
	ManagedReference<SceneObject*> object = zone->getNearestPlanetaryObject(player, maplocationtype);
	Zone* objectZone = NULL;

	if (object == NULL || ((objectZone = object->getZone()) == NULL)) {
		player->sendSystemMessage("@find_display:no_registered_locs"); // There currently are not registered map locations on this planet.
		cancelSession();
		return;
	}

	ManagedReference<CityRegion*> region = object->getCityRegion();
	String regFullName = "";

	if (region != NULL) {
		regFullName = region->getRegionName();
	}

	String objFullName = "@map_loc_cat_n:" + maplocationtype;

	StringIdManager* stringManager = StringIdManager::instance();

	String regClientString = stringManager->getStringId(regFullName.hashCode()).toString();
	String objClientString = stringManager->getStringId(objFullName.hashCode()).toString();

	if (regClientString.isEmpty()) {
		regClientString = objectZone->getZoneName();
		regClientString[0] = toupper(regClientString[0]);
	}

	String wptName = regClientString + " (" + objClientString + ")"; // Region (BuildingType)

	float objX, objY;
	objX = object->getWorldPositionX();
	objY = object->getWorldPositionY();

	addWaypoint(objX, objY, wptName);

	cancelSession();
}
