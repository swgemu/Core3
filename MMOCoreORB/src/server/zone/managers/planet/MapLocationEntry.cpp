/*
 * MapLocationEntry.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 *  Updated on: Sun Oct 16 16:30:54 PDT 2011 by lordkator - resolve displayName on add in setObject() with cleaner names for maps
 *
 */

#include "MapLocationEntry.h"
#include "MapLocationType.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "templates/building/CloningBuildingObjectTemplate.h"
#include "templates/faction/Factions.h"

uint64 MapLocationEntry::getObjectID() const {
	return object->getObjectID();
}

int MapLocationEntry::compareTo(const MapLocationEntry& entry) const {
	if (getObjectID() < entry.getObjectID())
		return 1;
	else if (getObjectID() > entry.getObjectID())
		return -1;
	else
		return 0;
}

MapLocationEntry& MapLocationEntry::operator=(const MapLocationEntry& entry) {
	if (this == &entry)
		return *this;

	object = entry.object;
	icon = entry.icon;
	displayName = entry.displayName;

	return *this;
}

void MapLocationEntry::setObject(SceneObject *obj) {
	displayName = "";
	object = obj;
	icon = 0;

	if(object == NULL)
		return;

	PlanetMapCategory* category = object->getPlanetMapCategory();

	if (category == NULL)
		return;

	ManagedReference<Zone*> zone = object->getZone();

	if(zone == NULL)
		return;

	if (object->isBuildingObject()) {
		BuildingObject* building = cast<BuildingObject*>(object.get());
		if (building->canPlayerRegisterWithin())
			icon = 1;
	}

	// Default is the result of getDisplayedName()
	String newName = object->getDisplayedName();

	if (object->isVendor()) {
		newName = newName.subString(8); // Removes the "Vendor: " prefix
	} else if (object->isCreatureObject()) { // Try FirstName + LastName if it's a creature
		CreatureObject* creature = object->asCreatureObject();

		String fName = creature->getFirstName();
		String lName = creature->getLastName();

		if(fName.length() > 0) {
			newName = fName;

			if(lName.length() > 0)
				newName += " " + lName;
		}
	} else if(category->getIndex() == MapLocationType::SHUTTLEPORT) { // Shuttleports take on the name of nearest travel point
		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();
		PlanetTravelPoint* ptp = planetManager->getNearestPlanetTravelPoint(object, 64.f);

		if(ptp != NULL) {
			newName = ptp->getPointName();
		}
	} else if(category->getIndex() == MapLocationType::TERMINAL && (object->getPlanetMapSubCategory() != NULL)) {
		newName = object->getPlanetMapSubCategory()->getName();

		if (newName == "terminal_bank") {
			newName = "@map_loc_cat_n:terminal_bank";
		} else if (newName == "terminal_bazaar") {
			newName = "@map_loc_cat_n:terminal_bazaar";
		} else if (newName == "terminal_mission") {
			if (object->isMissionTerminal()) {
				ManagedReference<MissionTerminal*> terminal = dynamic_cast<MissionTerminal*>(object.get());

				if (terminal != NULL)
					newName = terminal->getTerminalName();
			}
		} else {
			newName = "@map_loc_cat_n:terminal";
		}

	} else if (!object->isGCWBase()) { // Everything else except faction bases are just named by the city it's in
		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		ManagedReference<CityRegion *> region = planetManager->getRegionAt(object->getWorldPositionX(), object->getWorldPositionY());

		if(region != NULL) {
			newName = region->getRegionName();
		}
	}


	displayName = newName;
}

bool MapLocationEntry::insertToMessage(BaseMessage* message, CreatureObject* player) {
	if (object == NULL)
		return false;

	PlanetMapCategory* category = object->getPlanetMapCategory();

	if (category == NULL)
		return false;

	if (category->isFactionVisibleOnly()) {
		unsigned int entryFaction = category->getFaction().hashCode();

		if (entryFaction != player->getFaction())
			return false;
	}

	if (category->getName() == "cloningfacility") {
		CloningBuildingObjectTemplate* cbot = cast<CloningBuildingObjectTemplate*>(object->getObjectTemplate());

		if (cbot == NULL)
			return false;

		if (cbot->getFacilityType() == CloningBuildingObjectTemplate::FACTION_IMPERIAL && player->getFaction() != Factions::FACTIONIMPERIAL)
			return false;
		else if (cbot->getFacilityType() == CloningBuildingObjectTemplate::FACTION_REBEL && player->getFaction() != Factions::FACTIONREBEL)
			return false;
		else if (cbot->getFacilityType() == CloningBuildingObjectTemplate::JEDI_ONLY && !player->hasSkill("force_title_jedi_rank_01"))
			return false;
		else if (cbot->getFacilityType() == CloningBuildingObjectTemplate::LIGHT_JEDI_ONLY && !player->hasSkill("force_rank_light_novice"))
			return false;
		else if (cbot->getFacilityType() == CloningBuildingObjectTemplate::DARK_JEDI_ONLY && !player->hasSkill("force_rank_dark_novice"))
			return false;
	}

	message->insertLong(object->getObjectID());

	message->insertUnicode(displayName);

	message->insertFloat(object->getWorldPositionX());
	message->insertFloat(object->getWorldPositionY());

	message->insertByte(category->getIndex());
	message->insertByte((object->getPlanetMapSubCategory() != NULL) ? object->getPlanetMapSubCategory()->getIndex() : 0);

	message->insertByte(icon);

	return true;
}
