/*
 * CityRegionImplementation.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: xyborn
 */

#include "CityRegion.h"
#include "events/CityUpdateEvent.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/ServerCore.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/commands/BoardShuttleCommand.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/tangible/components/vendor/AuctionTerminalDataComponent.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/Zone.h"

int BoardShuttleCommand::MAXIMUM_PLAYER_COUNT = 3000;

void CityRegionImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	loaded = false;
}

void CityRegionImplementation::notifyLoadFromDatabase() {
	ManagedObjectImplementation::notifyLoadFromDatabase();

	if (cityRank == CityManager::CLIENT)
		return;

	//if (zone !=)

	Zone* zone = getZone();

	if (zone == NULL)
		return;


	zone->addCityRegionToUpdate(_this.get());

	if (isRegistered())
		zone->getPlanetManager()->addRegion(_this.get());

	//Add taxes if they dont exist.
	if (taxes.size() <= 0) {
		info("Adding taxes for existing city that had no taxes.", true);
		taxes.add(0);
		taxes.add(0);
		taxes.add(0);
		taxes.add(0);
		taxes.add(0);
	}

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

	cityMissionTerminals.setNoDuplicateInsertPlan();
	cityDecorations.setNoDuplicateInsertPlan();
	citySkillTrainers.setNoDuplicateInsertPlan();

	bazaars.setNoDuplicateInsertPlan();
	bazaars.setNullValue(NULL);

	setLoggingName("CityRegion");
	setLogging(true);

}

Region* CityRegionImplementation::addRegion(float x, float y, float radius, bool persistent) {
	if (zone == NULL) {
		return NULL;
	}

	String temp = "object/region_area.iff";
	ManagedReference<SceneObject*> obj = zone->getZoneServer()->createObject(temp.hashCode(), persistent ? 1 : 0);

	if (obj == NULL || !obj->isRegion()) {
		return NULL;
	}

	ManagedReference<Region*> region = cast<Region*>(obj.get());
	region->setCityRegion(_this.get());
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
		cityUpdateEvent = new CityUpdateEvent(_this.get(), ServerCore::getZoneServer());
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
	if (object->getCityRegion().get() != _this.get() && object->isPlayerCreature())
		currentPlayers.increment();

	object->setCityRegion(_this.get());

	if (object->isBazaarTerminal() || object->isVendor()) {

		if (object->isBazaarTerminal())
			bazaars.put(object->getObjectID(), cast<TangibleObject*>(object));

		AuctionTerminalDataComponent* terminalData = NULL;
		DataObjectComponentReference* data = object->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isAuctionTerminalData())
			terminalData = cast<AuctionTerminalDataComponent*>(data->get());

		if(terminalData != NULL)
			terminalData->updateUID();
	}

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

		applySpecializationModifiers(creature);
	}

	if (object->isStructureObject()){
		StructureObject* structure = cast<StructureObject*>(object);

		/*uint64 creatureID = structure->getOwnerObjectID();

		if (structure->isBuildingObject() && !citizenList.contains(creatureID)) {
			BuildingObject* building = cast<BuildingObject*>(object);
			CreatureObject* owner = building->getOwnerCreatureObject();

			if (owner != NULL) {
				PlayerObject* playerObject = owner->getPlayerObject();

				if (playerObject != NULL && playerObject->getDeclaredResidence() == building) {
					addCitizen(creatureID);
				}
			}
		}*/

		Locker slocker(&structureListMutex);

		completeStructureList.put(structure->getObjectID());

		if (structure->isCivicStructure())
			addStructure(structure);
	}
}

void CityRegionImplementation::notifyExit(SceneObject* object) {
	//pre: no 2 different city regions should ever overlap, only 2 Regions of the same city region
	ManagedReference<Region*> activeRegion = cast<Region*>(object->getActiveRegion());

	if (activeRegion != NULL) {
		ManagedReference<CityRegion*> city = activeRegion->getCityRegion();

		object->setCityRegion(city);

		if (city == _this.get()) // if its the same city we wait till the object exits the last region
			return;
	} else {
		object->setCityRegion(NULL);
	}


	if (object->isBazaarTerminal() || object->isVendor()) {
		if (object->isBazaarTerminal())
			bazaars.drop(object->getObjectID());

		AuctionTerminalDataComponent* terminalData = NULL;
		DataObjectComponentReference* data = object->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isAuctionTerminalData())
			terminalData = cast<AuctionTerminalDataComponent*>(data->get());

		if(terminalData != NULL)
			terminalData->updateUID();
	}

	if (object->isPlayerCreature())
		currentPlayers.decrement();

	if (isClientRegion())
		return;

	if (object->isCreatureObject()){

		CreatureObject* creature = cast<CreatureObject*>(object);

		StringIdChatParameter params("city/city", "city_leave_city"); //You have left %TO.
		params.setTO(getRegionName());

		creature->sendSystemMessage(params);

		removeSpecializationModifiers(creature);
	}

	if (object->isStructureObject()) {
		float x = object->getWorldPositionX();
		float y = object->getWorldPositionY();

		//StructureObject* structure = cast<StructureObject*>(object);

		StructureObject* structure = cast<StructureObject*>(object);

		/*uint64 creatureID = structure->getOwnerObjectID();

		if (structure->isBuildingObject() && citizenList.contains(creatureID)) {
			BuildingObject* building = cast<BuildingObject*>(object);

			CreatureObject* owner = building->getOwnerCreatureObject();

			if (owner != NULL) {
				PlayerObject* playerObject = owner->getPlayerObject();

				if (playerObject != NULL && playerObject->getDeclaredResidence() == building){
					removeCitizen(creatureID);
				}
			}
		}*/

		Locker slocker(&structureListMutex);

		completeStructureList.drop(structure->getObjectID());

		if (structure->isCivicStructure())
			removeStructure(structure);
	}
}

void CityRegionImplementation::cleanupCitizens() {
	Locker slocker(&structureListMutex);

	SortedVector<uint64> ownerIds;
	ownerIds.setNoDuplicateInsertPlan();

	for (int i = 0; i < completeStructureList.size(); ++i) {
		uint64 oid = completeStructureList.get(i);

		ManagedReference<BuildingObject*> building = dynamic_cast<BuildingObject*>(zone->getZoneServer()->getObject(oid));

		if (building != NULL) {
			uint64 owner = building->getOwnerObjectID();

			ownerIds.put(owner);
		}
	}

	SortedVector<uint64> removeIds;
	removeIds.setNoDuplicateInsertPlan();

	for (int i = 0; i < citizenList.size(); ++i) {
		uint64 id = citizenList.get(i);

		if (!ownerIds.contains(id))
			removeIds.put(id);
	}

	for (int i = 0; i < removeIds.size(); ++i) {
		removeCitizen(removeIds.get(i));
	}
}

void CityRegionImplementation::setRegionName(const StringId& name) {
	regionName = name;
}

Vector<ManagedReference<TangibleObject*> >* CityRegionImplementation::getVendorsInCity() {
	Vector<ManagedReference<TangibleObject*> >* vendors = new Vector<ManagedReference<TangibleObject*> >();

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

bool CityRegionImplementation::hasUniqueStructure(uint32 crc){
	Locker locker(_this.get());

	for (int i = 0; i < structures.size(); ++i) {
		ManagedReference<StructureObject*> structure = structures.get(i);

		if (structure->getObjectTemplate()->getServerObjectCRC() == crc)
			return true;
	}

	return false;
}

void CityRegionImplementation::destroyAllStructuresForRank(uint8 rank){
	Locker locker(_this.get());

	if (zone == NULL)
		return;

	StructureManager* structureManager = StructureManager::instance();

	for (int i = structures.size() - 1; i >= 0; --i) {
		ManagedReference<StructureObject*> structure = structures.get(i);

		SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());

		//We only want to destroy civic structures.
		if (ssot == NULL || ssot->getCityRankRequired() < rank || !ssot->isCivicStructure())
			continue;

		Locker _clocker(structure, _this.get());

		structureManager->destroyStructure(structure);

		structures.drop(structure);
	}
}

void CityRegionImplementation::updateMilitia(){

	Locker locker (_this.get());

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

void CityRegionImplementation::removeAllSkillTrainers(){

	for (int i = 0; i < citySkillTrainers.size(); i++){
		citySkillTrainers.get(i)->destroyObjectFromWorld(false);
		citySkillTrainers.get(i)->destroyObjectFromDatabase(false);
	}

	citySkillTrainers.removeAll();
}

void CityRegionImplementation::resetVotingPeriod() {
	nextInauguration.updateToCurrentTime();
	nextInauguration.addMiliTime(CityManagerImplementation::cityVotingDuration * 60000);
}

void CityRegionImplementation::applySpecializationModifiers(CreatureObject* creature) {
	if (getZone() == NULL)
		return;

	CityManager* cityManager = getZone()->getZoneServer()->getCityManager();
	CitySpecialization* cityspec = cityManager->getCitySpecialization(citySpecialization);

	if (cityspec == NULL)
		return;

	//Remove all current city skillmods
	creature->removeAllSkillModsOfType(SkillModManager::CITY);

	VectorMap<String, int>* mods = cityspec->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		VectorMapEntry<String, int> entry = mods->elementAt(i);

		creature->addSkillMod(SkillModManager::CITY, entry.getKey(), entry.getValue());
	}
}

void CityRegionImplementation::removeSpecializationModifiers(CreatureObject* creature) {
	creature->removeAllSkillModsOfType(SkillModManager::CITY);
}
