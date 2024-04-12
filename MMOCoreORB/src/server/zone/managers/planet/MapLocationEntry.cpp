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

void MapLocationEntry::setObject(SceneObject* obj) {
	displayName = "";
	object = obj;
	icon = 0;

	if (object == nullptr)
		return;

	const PlanetMapCategory* category = object->getPlanetMapCategory();

	if (category == nullptr)
		return;

	ManagedReference<Zone*> zone = object->getZone();

	if (zone == nullptr)
		return;

	const PlanetMapSubCategory* subPmc = object->getPlanetMapSubCategory();

	if (object->isBuildingObject()) {
		BuildingObject* building = cast<BuildingObject*>(object.get());

		if (building->canPlayerRegisterWithin())
			icon = 1;
	}

	// Default is the result of getDisplayedName()
	String newName = object->getDisplayedName();

	if (object->isVendor()) {
		newName = newName.subString(8); // Removes the "Vendor: " prefix
	// Shuttleports take on the name of nearest travel point
	} else if (category->getIndex() == MapLocationType::SHUTTLEPORT) {
		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		if (planetManager != nullptr) {
			PlanetTravelPoint* ptp = planetManager->getNearestPlanetTravelPoint(object, 64.f);

			if (ptp != nullptr) {
				newName = ptp->getPointName();
			}
		}
	// Camp's Need to be registered by the owners name
	} else if (object->isCampStructure()) {
		auto campStructure = object.castTo<StructureObject*>();

		if (campStructure != nullptr) {
			SortedVector<ManagedReference<SceneObject*>>* childObjects = campStructure->getChildObjects();

			for (int i = 0; i < childObjects->size(); ++i) {
				auto child = childObjects->get(i);

				if (child == nullptr || !child->isTerminal())
					continue;

				newName = child->getDisplayedName();

				break;
			}
		}
	// Everything else except faction bases, terminals and trainers are just named by the city it's in
	} else if (!object->isGCWBase() && (category->getIndex() != MapLocationType::TERMINAL) && !object->isCreatureObject()) {
		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		ManagedReference<CityRegion*> cityRegion = planetManager->getCityRegionAt(object->getWorldPositionX(), object->getWorldPositionY());

		if (cityRegion != nullptr) {
			newName = cityRegion->getCityRegionName();
		}
	}

	displayName = newName;
}

bool MapLocationEntry::insertToMessage(BaseMessage* message, CreatureObject* player) {
	if (object == nullptr)
		return false;

	const PlanetMapCategory* category = object->getPlanetMapCategory();

	if (category == nullptr)
		return false;

	if (category->isFactionVisibleOnly()) {
		unsigned int entryFaction = category->getFaction().hashCode();

		if (entryFaction != player->getFaction())
			return false;
	}

	if (category->getName() == "cloningfacility") {
		CloningBuildingObjectTemplate* cbot = cast<CloningBuildingObjectTemplate*>(object->getObjectTemplate());

		if (cbot == nullptr)
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

	float x = object->getWorldPositionX();
	float y = object->getWorldPositionY();

	if (object->isRegion()) {
		Region* region = object.castTo<Region*>();

		if (region != nullptr) {
			AreaShape* shape = region->getAreaShape();

			if (shape != nullptr) {
				Vector3 location = shape->getAreaCenter();

				x = location.getX();
				y = location.getY();
			}
		}
	}

	message->insertFloat(x);
	message->insertFloat(y);

	message->insertByte(category->getIndex());
	message->insertByte((object->getPlanetMapSubCategory() != nullptr) ? object->getPlanetMapSubCategory()->getIndex() : 0);

	message->insertByte(icon);

	return true;
}
