/*
 * CityRegionImplementation.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: xyborn
 */

#include "CityRegion.h"
#include "events/CityUpdateEvent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/ServerCore.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/PlayerObject.h"


void CityRegionImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();
}

void CityRegionImplementation::notifyLoadFromDatabase() {
	ManagedObjectImplementation::notifyLoadFromDatabase();

	if (cityRank == CityManager::CLIENT)
		return;

	//if (zone !=)

	Zone* zone = getZone();

	if (zone == NULL)
		return;


	zone->addCityRegionToUpdate(_this);

	if (isRegistered())
		zone->getPlanetManager()->addRegion(_this);

	/*
	int seconds = -1 * round(nextUpdateTime.miliDifference() / 1000.f);

	if (seconds < 0) //If the update occurred in the past, force an immediate update.
		seconds = 0;

	rescheduleUpdateEvent(seconds);
	*/

	if (hasShuttle){
		CreatureObject* shuttle = cast<CreatureObject*>( zone->getZoneServer()->getObject(shuttleID, false));

		if (shuttle == NULL) {
			hasShuttle = false;
			shuttleID = 0;
			return;
		}

		float x = shuttle->getWorldPositionX();
		float y = shuttle->getWorldPositionY();
		float z = shuttle->getWorldPositionZ();

		Vector3 arrivalVector(x, y, z);
		PlanetTravelPoint* planetTravelPoint = new PlanetTravelPoint(zone->getZoneName(), getRegionName(), arrivalVector, arrivalVector, shuttle);
		zone->getPlanetManager()->addPlayerCityTravelPoint(planetTravelPoint);

		if (shuttle != NULL)
			zone->getPlanetManager()->scheduleShuttle(shuttle);
	}
}

void CityRegionImplementation::initialize() {
	zoningEnabled = true;

	registered = false;

	cityTreasury = 0;

	cityRank = RANK_CLIENT; //Default to client city

	cityHall = NULL;

	mayorID = 0;

	shuttleID = 0;

	hasShuttle = false;

	zone = NULL;

	cityUpdateEvent = NULL;

	zoningRights.setAllowOverwriteInsertPlan();
	zoningRights.setNullValue(0);

	limitedPlacementStructures.setNoDuplicateInsertPlan();

	cityStructureInventory.put(uint8(1), SortedVector<ManagedReference<SceneObject*> >());
	cityStructureInventory.put(uint8(2), SortedVector<ManagedReference<SceneObject*> >());
	cityStructureInventory.put(uint8(3), SortedVector<ManagedReference<SceneObject*> >());
	cityStructureInventory.put(uint8(4), SortedVector<ManagedReference<SceneObject*> >());

	cityStructureInventory.get(0).setNoDuplicateInsertPlan();
	cityStructureInventory.get(1).setNoDuplicateInsertPlan();
	cityStructureInventory.get(2).setNoDuplicateInsertPlan();
	cityStructureInventory.get(3).setNoDuplicateInsertPlan();

	cityMissionTerminals.setNoDuplicateInsertPlan();
	cityDecorations.setNoDuplicateInsertPlan();
	citySkillTrainers.setNoDuplicateInsertPlan();

	setLoggingName("CityRegion");
	setLogging(true);

}

Region* CityRegionImplementation::addRegion(float x, float y, float radius, bool persistent) {
	if (zone == NULL) {
		return NULL;
	}

	String temp = "object/region_area.iff";
	SceneObject* obj = zone->getZoneServer()->createObject(temp.hashCode(), persistent ? 1 : 0);

	if (obj == NULL || !obj->isRegion()) {
		return NULL;
	}

	ManagedReference<Region*> region = cast<Region*>(obj);
	region->setCityRegion(_this);
	region->setRadius(radius);
	region->initializePosition(x, 0, y);
	region->setObjectName(regionName);

	if (isClientRegion())
		region->setNoBuildArea(true);

	zone->transferObject(region, -1, false);

	regions.put(region);

	return region;
}

void CityRegionImplementation::rescheduleUpdateEvent(uint32 seconds) {
	if (cityRank == CityManager::CLIENT)
		return;

	if (cityUpdateEvent == NULL) {
		cityUpdateEvent = new CityUpdateEvent(_this, ServerCore::getZoneServer());
	} else if (cityUpdateEvent->isScheduled()) {
		cityUpdateEvent->cancel();
	}

	cityUpdateEvent->schedule(seconds * 1000);
	Core::getTaskManager()->getNextExecutionTime(cityUpdateEvent, nextUpdateTime);
}

int CityRegionImplementation::getTimeToUpdate() {
	return round(nextUpdateTime.miliDifference() / -1000.f);
}

void CityRegionImplementation::notifyEnter(SceneObject* object) {
	object->setCityRegion(_this);

	if (isClientRegion())
		return;

	if (object->isCreatureObject()){
		CreatureObject* creature = cast<CreatureObject*>(object);

		StringIdChatParameter params("city/city", "city_enter_city"); //You have entered %TT (%TO).
		params.setTT(getRegionName());

		UnicodeString strRank = StringIdManager::instance()->getStringId(String("@city/city:rank" + String::valueOf(cityRank)).hashCode());

		if (citySpecialization.isEmpty()) {
			params.setTO(strRank);
		}
		else {
			UnicodeString citySpec = StringIdManager::instance()->getStringId(citySpecialization.hashCode());
			params.setTO(strRank + ", " + citySpec);
		}

		creature->sendSystemMessage(params);
	}

	if (object->isBuildingObject()) {
		//StructureObject* structure = cast<StructureObject*>(object);

		BuildingObject* building = cast<BuildingObject*>(object);

		CreatureObject* owner = building->getOwnerCreatureObject();

		if (owner != NULL){

			if (owner->getPlayerObject()->getDeclaredResidence() == building){

				uint64 creatureID = owner->getObjectID();

				if (!citizenList.contains(creatureID))
					addCitizen(creatureID);

			}
		}
	}

	//Apply skillmods for specialization
}

void CityRegionImplementation::notifyExit(SceneObject* object) {
	object->setCityRegion(NULL);

	if (isClientRegion())
		return;

	if (object->isCreatureObject()){

		CreatureObject* creature = cast<CreatureObject*>(object);

		StringIdChatParameter params("city/city", "city_leave_city"); //You have left %TO.
		params.setTO(getRegionName());

		creature->sendSystemMessage(params);

		//Remove skillmods for specialization
	}


	if (object->isBuildingObject()){

		float x = object->getWorldPositionX();
		float y = object->getWorldPositionY();

		//StructureObject* structure = cast<StructureObject*>(object);

		BuildingObject* building = cast<BuildingObject*>(object);

		CreatureObject* owner = building->getOwnerCreatureObject();

		if (owner != NULL){

			if (owner->getPlayerObject()->getDeclaredResidence() == building){

				uint64 creatureID = owner->getObjectID();

				if (citizenList.contains(creatureID))
					removeCitizen(creatureID);
			}

		}

	}
}

void CityRegionImplementation::setRegionName(const StringId& name) {
	regionName = name;
}

Vector<ManagedReference<SceneObject*> >* CityRegionImplementation::getVendorsInCity() {
	Vector<ManagedReference<SceneObject*> >* vendors = new Vector<ManagedReference<SceneObject*> >();

	return vendors;
}

void CityRegionImplementation::addZoningRights(uint64 objectid, uint32 duration) {
	Time now;

	zoningRights.put(objectid, duration + now.getTime());
}

bool CityRegionImplementation::hasZoningRights(uint64 objectid) {
	if (isMilitiaMember(objectid))
		return true;

	uint32 timestamp = zoningRights.get(objectid);

	if (timestamp == 0)
		return false;

	Time now;
	return (now.getTime() <= timestamp);
}

void CityRegionImplementation::setZone(Zone* zne) {
	zone = zne;
}

void CityRegionImplementation::setRadius(float rad) {
	if (regions.size() <= 0)
		return;

	ManagedReference<ActiveArea*> aa = regions.get(0).get();
	aa->setRadius(rad);

	zone->removeObject(aa, NULL, false);
	zone->transferObject(aa, -1, false);


}

void CityRegionImplementation::destroyActiveAreas() {
	for (int i = 0; i < regions.size(); ++i) {
		ManagedReference<Region*> aa = regions.get(i);

		if (aa != NULL) {
			aa->destroyObjectFromWorld(false);
			aa->destroyObjectFromDatabase(true);

			regions.drop(aa);
		}
	}
}

String CityRegionImplementation::getRegionName() {
	if(!customRegionName.isEmpty())
		return customRegionName;

	return regionName.getFullPath();
}

void CityRegionImplementation::addToCityStructureInventory(uint8 rankRequired, SceneObject* structure){
	Locker locker(_this);

	if(cityStructureInventory.contains(rankRequired)){
		cityStructureInventory.get(rankRequired).put(structure);

	}


}

void CityRegionImplementation::removeFromCityStructureInventory(SceneObject* structure){
	Locker locker(_this);

	if(cityStructureInventory.get(uint8(1)).contains(structure))
		cityStructureInventory.get(uint8(1)).drop(structure);

	else if(cityStructureInventory.get(uint8(2)).contains(structure))
		cityStructureInventory.get(uint8(2)).drop(structure);

	else if(cityStructureInventory.get(uint8(3)).contains(structure))
			cityStructureInventory.get(uint8(3)).drop(structure);

	else if(cityStructureInventory.get(uint8(4)).contains(structure))
			cityStructureInventory.get(uint8(4)).drop(structure);


}

bool CityRegionImplementation::checkLimitedPlacementStucture(uint32 id){
	Locker locker(_this);

	if (limitedPlacementStructures.contains(id))
		return true;

	return false;
}

bool CityRegionImplementation::addLimitedPlacementStructure(uint32 id){
	Locker locker(_this);

	if (!limitedPlacementStructures.contains(id)){
		limitedPlacementStructures.put(id);
		return true;
	}

	return false;
}

void CityRegionImplementation::removeLimitedPlacementStructure(uint32 id){
	Locker locker(_this);

	limitedPlacementStructures.drop(id);

}

void CityRegionImplementation::destroyAllStructuresForRank(uint8 rank){
	Locker locker(_this);

	SortedVector<ManagedReference<SceneObject*> >* sceneObjects = &cityStructureInventory.get(rank);

	int structureCount = sceneObjects->size();
	int i;

	StructureManager* manager = zone->getStructureManager();

	if (structureCount > 0){

		for(i = structureCount - 1; i >= 0; i--){

			ManagedReference<SceneObject*> sceo = sceneObjects->get(i);

			Locker locker(sceo, _this);

			if (sceo->isStructureObject()) {
				manager->destroyStructure(cast<StructureObject*>(sceo.get()));
			} else {
				sceo->destroyObjectFromWorld(true);
				sceo->destroyObjectFromDatabase(true);

				sceneObjects->drop(sceo);
			}
		}
	}


}

void CityRegionImplementation::updateMilitia(){

	Locker locker (_this);

	uint64 objectID;

	for (int i = militiaMembers.size() - 1;i >= 0; --i){

		objectID = militiaMembers.get(i);

		if (!isCitizen(objectID))
			removeMilitiaMember(objectID);
	}
}

void CityRegionImplementation::removeAllTerminals(){
	for (int i = 0; i < cityMissionTerminals.size(); i++){
		cityMissionTerminals.get(i)->destroyObjectFromWorld(false);
		cityMissionTerminals.get(i)->destroyObjectFromDatabase(false);
	}

	cityMissionTerminals.removeAll();
}

