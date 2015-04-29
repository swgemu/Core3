/*
 * CityRegionImplementation.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: xyborn
 */

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/region/events/CityUpdateEvent.h"
#include "server/zone/objects/region/events/CitizenAssessmentEvent.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/ServerCore.h"
#include "server/chat/ChatManager.h"
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
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/commands/TransferstructureCommand.h"

int BoardShuttleCommand::MAXIMUM_PLAYER_COUNT = 3000;

void CityRegionImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	loaded = false;
	completeStructureList.setNoDuplicateInsertPlan();
}

void CityRegionImplementation::notifyLoadFromDatabase() {
	ManagedObjectImplementation::notifyLoadFromDatabase();

	if (cityRank == CityManager::CLIENT)
		return;

	if (cityRank < CityManager::TOWNSHIP) {
		citySpecialization = "";
	}

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

	citizenAssessmentEvent = NULL;

	assessmentPending = false;

	zoningRights.setAllowOverwriteInsertPlan();
	zoningRights.setNullValue(0);

	cityMissionTerminals.setNoDuplicateInsertPlan();
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

	static const String temp = "object/region_area.iff";
	ManagedReference<SceneObject*> obj = zone->getZoneServer()->createObject(temp.hashCode(), persistent ? 1 : 0);

	if (obj == NULL || !obj->isRegion()) {
		return NULL;
	}
	
	Locker clocker(obj, _this.get());

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

void CityRegionImplementation::scheduleCitizenAssessment(uint32 seconds) {


	if (citizenAssessmentEvent == NULL) {
		citizenAssessmentEvent = new CitizenAssessmentEvent(_this.get(), ServerCore::getZoneServer());
	} else if (citizenAssessmentEvent->isScheduled()) {
		citizenAssessmentEvent->cancel();
	}

	citizenAssessmentEvent->schedule(seconds * 1000);

	Core::getTaskManager()->getNextExecutionTime(citizenAssessmentEvent, nextCitizenAssessment);
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

	if (object->isCreatureObject()) {
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

	if (object->isStructureObject()) {
		StructureObject* structure = cast<StructureObject*>(object);
		CityManager* cityManager = getZone()->getZoneServer()->getCityManager();

		Locker slocker(&structureListMutex);

		if (isLoaded() && !completeStructureList.contains(structure->getObjectID()) && structure->getBaseMaintenanceRate() > 0) {
			cityManager->sendAddStructureMails(_this.get(), structure);
		}

		if (structure->isBuildingObject()) {

			BuildingObject* building = cast<BuildingObject*>(object);
			uint64 ownerID = structure->getOwnerObjectID();

			ManagedReference<CreatureObject*> owner = zone->getZoneServer()->getObject(ownerID).castTo<CreatureObject*>();

			if(owner != NULL && owner->isPlayerCreature() && building->isResidence() && !isCitizen(ownerID)) {
				cityManager->registerCitizen(_this.get(), owner);
			}
		 }

		completeStructureList.put(structure->getObjectID());

		if (structure->isCivicStructure() && !structure->isDecoration()) {
			addStructure(structure);
		} else if (structure->isCommercialStructure()) {
			addCommercialStructure(structure);
		}

		if (registered) {
			zone->registerObjectWithPlanetaryMap(structure);
		}
	}

	if (object->isDecoration() && object->getParent().get() == NULL) {
		addDecoration(object);
	}

	if (registered && cityMissionTerminals.contains(object)) {
		zone->registerObjectWithPlanetaryMap(object);
	}

	if (!registered && citySkillTrainers.contains(object)) {
		zone->unregisterObjectWithPlanetaryMap(object);
	}
}

void CityRegionImplementation::notifyExit(SceneObject* object) {
	//pre: no 2 different city regions should ever overlap, only 2 Regions of the same city region
	if (object->isTangibleObject()) {
		TangibleObject* tano = cast<TangibleObject*>(object);

		ManagedReference<Region*> activeRegion = tano->getActiveRegion().castTo<Region*>();

		if (activeRegion != NULL) {
			ManagedReference<CityRegion*> city = activeRegion->getCityRegion();

			object->setCityRegion(city);

			if (city == _this.get()) // if its the same city we wait till the object exits the last region
				return;
		} else {
			object->setCityRegion(NULL);
		}
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

	if (object->isCreatureObject()) {

		CreatureObject* creature = cast<CreatureObject*>(object);

		StringIdChatParameter params("city/city", "city_leave_city"); //You have left %TO.
		params.setTO(getRegionName());

		creature->sendSystemMessage(params);

		removeSpecializationModifiers(creature);
	}

	if (object->isStructureObject()) {
		float x = object->getWorldPositionX();
		float y = object->getWorldPositionY();

		StructureObject* structure = cast<StructureObject*>(object);

		Locker slocker(&structureListMutex);

		if (structure->isBuildingObject()) {

			BuildingObject* building = cast<BuildingObject*>(object);
			uint64 ownerID = structure->getOwnerObjectID();

			ManagedReference<CreatureObject*> owner = zone->getZoneServer()->getObject(ownerID).castTo<CreatureObject*>();

			if(owner != NULL && owner->isPlayerCreature() && building->isResidence() && isCitizen(ownerID)) {
				CityManager* cityManager = getZone()->getZoneServer()->getCityManager();
				cityManager->unregisterCitizen(_this.get(), owner);
			}
		}

		completeStructureList.drop(structure->getObjectID());

		if (structure->isCivicStructure()) {
			removeStructure(structure);
		} else if (structure->isCommercialStructure()) {
			removeCommercialStructure(structure);
		}
	}

	if (object->isDecoration() && object->getParent().get() == NULL) {
		removeDecoration(object);
	}
}


void CityRegionImplementation::cleanupCitizens() {
	Locker slocker(&structureListMutex);

	SortedVector<uint64> ownerIds;
	ownerIds.setNoDuplicateInsertPlan();

	for (int i = 0; i < completeStructureList.size(); ++i) {
		uint64 oid = completeStructureList.get(i);

		ManagedReference<BuildingObject*> building = zone->getZoneServer()->getObject(oid).castTo<BuildingObject*>();

		if (building != NULL) {
			if (building->isResidence()) {
				uint64 owner = building->getOwnerObjectID();
				ownerIds.put(owner);
			}
		}
	}

	SortedVector<uint64> removeIds;
	removeIds.setNoDuplicateInsertPlan();

	for (int i = 0; i < citizenList.size(); ++i) {
		uint64 id = citizenList.get(i);

		if (!ownerIds.contains(id))
			removeIds.put(id);
		else if (isBanned(id))
			removeBannedPlayer(id);
	}

	for (int i = 0; i < removeIds.size(); ++i) {
		removeCitizen(removeIds.get(i));
	}

	if(getMayorID() != 0 && !isCitizen(getMayorID()))
		addCitizen(getMayorID());
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
	if(getMayorID() != 0 && objectid == getMayorID())
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

	ManagedReference<Region*> oldRegion = regions.get(0).get();

	ManagedReference<Region*> newRegion = addRegion(oldRegion->getPositionX(), oldRegion->getPositionY(), rad, true);

	Locker locker(oldRegion, _this.get());

	zone->removeObject(oldRegion, NULL, false);
	regions.drop(oldRegion);
	oldRegion->destroyObjectFromDatabase(true);

	locker.release();

	if (registered) {
		Reference<PlanetMapCategory*> cityCat = TemplateManager::instance()->getPlanetMapCategoryByName("city");

		newRegion->setPlanetMapCategory(cityCat);
		newRegion->getZone()->registerObjectWithPlanetaryMap(newRegion);
	}
}

void CityRegionImplementation::destroyActiveAreas() {
	for (int i = 0; i < regions.size(); ++i) {
		ManagedReference<Region*> aa = regions.get(i);

		if (aa != NULL) {
			Locker clocker(aa, _this.get());
			aa->destroyObjectFromWorld(false);
			aa->destroyObjectFromDatabase(true);
		}
	}

	regions.removeAll();
}

void CityRegionImplementation::cancelTasks() {
	if (cityUpdateEvent != NULL) {
		if (cityUpdateEvent->isScheduled())
			cityUpdateEvent->cancel();

		cityUpdateEvent = NULL;
	}

	if (citizenAssessmentEvent != NULL) {
		if (citizenAssessmentEvent->isScheduled())
			citizenAssessmentEvent->cancel();

		citizenAssessmentEvent = NULL;
	}
}

String CityRegionImplementation::getRegionName() {
	if(!customRegionName.isEmpty())
		return customRegionName;

	return regionName.getFullPath();
}

String CityRegionImplementation::getRegionDisplayedName() {
	if(!customRegionName.isEmpty())
		return customRegionName;

	return StringIdManager::instance()->getStringId(regionName.getFullPath().hashCode()).toString();
}

bool CityRegionImplementation::hasUniqueStructure(uint32 crc) {
	Locker locker(_this.get());

	for (int i = 0; i < structures.size(); ++i) {
		ManagedReference<StructureObject*> structure = structures.get(i);

		if (structure->getObjectTemplate()->getServerObjectCRC() == crc)
			return true;
	}

	return false;
}

void CityRegionImplementation::destroyAllStructuresForRank(uint8 rank, bool sendMail) {
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

		sendDestroyObjectMail(structure);

		Locker _clocker(structure, _this.get());

		structureManager->destroyStructure(structure);

		structures.removeElement(structure);
	}

	for (int i = cityDecorations.size() - 1; i >= 0; --i) {
		ManagedReference<SceneObject*> decoration = cityDecorations.get(i);
		StructureObject* structure = decoration.castTo<StructureObject*>();

		if (structure == NULL)
			continue;

		SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());

		//We only want to destroy civic structures.
		if (ssot == NULL || ssot->getCityRankRequired() < rank || !ssot->isCivicStructure())
			continue;

		sendDestroyObjectMail(structure);

		Locker _clocker(structure, _this.get());

		structureManager->destroyStructure(structure);

		cityDecorations.removeElement(decoration);
	}
}

void CityRegionImplementation::removeAllTerminals() {
	for (int i = cityMissionTerminals.size() - 1; i >= 0 ; --i) {
		Reference<SceneObject*> terminal = cityMissionTerminals.get(i);

		Locker locker(terminal);

		terminal->destroyObjectFromWorld(false);
		terminal->destroyObjectFromDatabase(true);
	}

	cityMissionTerminals.removeAll();
}

void CityRegionImplementation::removeAllSkillTrainers() {
	for (int i = citySkillTrainers.size() - 1; i >= 0 ; --i) {
		Reference<SceneObject*> trainer = citySkillTrainers.get(i);

		Locker locker(trainer);

		trainer->destroyObjectFromWorld(false);
		trainer->destroyObjectFromDatabase(true);
	}

	citySkillTrainers.removeAll();
}

void CityRegionImplementation::removeAllDecorations() {
	Locker slocker(&structureListMutex);

	for (int i = cityDecorations.size() - 1; i >= 0 ; --i) {
		ManagedReference<SceneObject*> dec = cityDecorations.get(i);

		Locker locker(dec);

		if(dec->isStructureObject()) {
			StructureManager::instance()->destroyStructure(cast<StructureObject*>(dec.get()));
		} else {
			dec->destroyObjectFromWorld(false);
			dec->destroyObjectFromDatabase(true);
		}
	}

	cityDecorations.removeAll();
}

void CityRegionImplementation::removeCandidate(uint64 candidateoid) {
	candidates.drop(candidateoid);

	// Remove votes for the candidate
	for (int i = mayoralVotes.size() - 1; i >= 0; --i) {
		if (mayoralVotes.get(i) == candidateoid) {
			mayoralVotes.drop(mayoralVotes.elementAt(i).getKey());
		}
	}
}

bool CityRegionImplementation::isVotingLocked() {
	Time rightnow;
	rightnow.updateToCurrentTime();

	int lockedCycles = CityManagerImplementation::cityVotingCycles - CityManagerImplementation::cityVotingCyclesUntilLocked;
	int64 minimumDifference = CityManagerImplementation::cityUpdateInterval * lockedCycles * 60000;

	int64 dif = rightnow.miliDifference(nextInauguration);

	return ( dif < minimumDifference);

}

void CityRegionImplementation::resetVotingPeriod() {
	nextInauguration.updateToCurrentTime();
	nextInauguration.addMiliTime(CityManagerImplementation::cityVotingCycles * CityManagerImplementation::cityUpdateInterval * 60000);
}

void CityRegionImplementation::applySpecializationModifiers(CreatureObject* creature) {
	if (getZone() == NULL)
		return;

	CityManager* cityManager = getZone()->getZoneServer()->getCityManager();
	CitySpecialization* cityspec = cityManager->getCitySpecialization(citySpecialization);

	if (cityspec == NULL)
		return;

	if (isBanned(creature->getObjectID())) {
		return;
	}

	Reference<CreatureObject*> creatureReference = creature;
	Reference<CityRegion*> city = _this.get();

	typedef VectorMap<String, int> SkillMods;
	typedef VectorMapEntry<String, int> SkillModsEntry;

	EXECUTE_ORDERED_TASK_3(creature, creatureReference, cityspec, city, {
			Locker locker(creatureReference_p);

			//Remove all current city skillmods
			creatureReference_p->removeAllSkillModsOfType(SkillModManager::CITY);

			SkillMods* mods = cityspec_p->getSkillMods();

			for (int i = 0; i < mods->size(); ++i) {
				SkillModsEntry& entry = mods->elementAt(i);

				if (entry.getKey() == "private_defense" && !city_p->isMilitiaMember(creatureReference_p->getObjectID()))
					continue;

				creatureReference_p->addSkillMod(SkillModManager::CITY, entry.getKey(), entry.getValue());
			}
	});
}

void CityRegionImplementation::removeSpecializationModifiers(CreatureObject* creature) {
	Reference<CreatureObject*> creatureReference = creature;

	EXECUTE_ORDERED_TASK_1(creature, creatureReference, {
			Locker locker(creatureReference_p);

			creatureReference_p->removeAllSkillModsOfType(SkillModManager::CITY);
	});

}

void CityRegionImplementation::transferCivicStructuresToMayor() {
	Locker tlock(&structureListMutex);

	if(zone == NULL)
		return;

	ZoneServer* server = zone->getZoneServer();

	if(server == NULL)
		return;

	StructureManager* structureManager = StructureManager::instance();

	if(structureManager == NULL)
		return;

	ManagedReference<SceneObject*> mayorObject = server->getObject(getMayorID());

	if(mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	ManagedReference<CreatureObject*> newMayor = cast<CreatureObject*>(mayorObject.get());

	if(newMayor == NULL)
		return;

	// transfer civic structures
	for(int i = 0; i < structures.size(); ++i) {
		ManagedReference<StructureObject*> structure = structures.get(i);

		if(!structure->isCivicStructure()) {
			continue;
		}

		ManagedReference<CreatureObject*> oldOwner = structure->getOwnerCreatureObject();

		if(newMayor != oldOwner) {
			TransferstructureCommand::doTransferStructure(oldOwner, newMayor, structure,true);
		}
	}

	// transfer decorations
	for(int i = 0; i < cityDecorations.size(); ++i) {
		ManagedReference<SceneObject*> str = cityDecorations.get(i);

		if(str == NULL || !str->isStructureObject())
			continue;

		StructureObject* structure = cast<StructureObject*>(str.get());

		if(structure == NULL)
			continue;

		ManagedReference<CreatureObject*> oldOwner = structure->getOwnerCreatureObject();

		if(newMayor != oldOwner) {
			TransferstructureCommand::doTransferStructure(oldOwner, newMayor, structure,true);
		}
	}

	// declare new mayor at the city hall
	ManagedReference<StructureObject* > cityhall = getCityHall();
	PlayerObject* mayorPlayer = newMayor->getPlayerObject();
	uint64 oldResidenceID = mayorPlayer->getDeclaredResidence();

	if(mayorPlayer != NULL && cityhall != NULL && oldResidenceID != cityhall->getObjectID()) {
		ManagedReference<CreatureObject*> creature = cityhall->getOwnerCreatureObject();
		if(creature != NULL) {
			PlayerObject* oldMayor = creature->getPlayerObject();

			if (oldMayor != NULL) {
				Locker clocker(creature, _this.get());

				oldMayor->setDeclaredResidence(NULL);

				clocker.release();
			}
		}

		BuildingObject* cityBuilding = cast<BuildingObject*>(cityhall.get());

		if(cityBuilding != NULL) {
			ManagedReference<BuildingObject*> oldResidence = server->getObject(oldResidenceID).castTo<BuildingObject*>();

			if (oldResidence != NULL) {
				Locker olocker(oldResidence, _this.get());

				oldResidence->setResidence(false);

				olocker.release();
			}

			Locker clock(newMayor, _this.get());

			mayorPlayer->setDeclaredResidence(cityBuilding);
		}
	}

}

void CityRegionImplementation::cleanupDuplicateCityStructures() {
	Locker tlock(&structureListMutex);

	Vector<ManagedReference<StructureObject*> > singleStructures;

	for(int i = 0; i < getStructuresCount(); i++){

		if(!singleStructures.contains(structures.get(i))){
			singleStructures.add(structures.get(i));
		}

	}

	structures.removeAll();
	structures.addAll(singleStructures);

	singleStructures.removeAll();

	for(int i = 0; i < getCommercialStructuresCount(); i++){

		if(!singleStructures.contains(commercialStructures.get(i)))
			singleStructures.add(commercialStructures.get(i));

	}

	commercialStructures.removeAll();
	commercialStructures.addAll(singleStructures);

	Vector<ManagedReference<SceneObject*> > singleDecorations;

	for(int i = 0; i < getDecorationCount(); i++){

		if(!singleDecorations.contains(cityDecorations.get(i)))
			singleDecorations.add(cityDecorations.get(i));

	}

	cityDecorations.removeAll();
	cityDecorations.addAll(singleDecorations);
}

void CityRegionImplementation::removeDecorationsOutsideCity(int newRadius) {
	if(cityHall == NULL)
		return;

	for(int i = getDecorationCount() - 1; i >= 0; i--) {
		ManagedReference<SceneObject*> obj = getCityDecoration(i);
		if(obj != NULL && !isInsideRadius(obj, newRadius)) {
			//info("need to destroy the decoration" + obj->getObjectNameStringIdName(),true);

			removeDecoration(obj);
			sendDestroyOutsideObjectMail(obj);

			if(obj->isStructureObject()) {
				StructureManager* structureManager = StructureManager::instance();
				structureManager->destroyStructure(obj.castTo<StructureObject*>());
			} else {

				Locker clock(obj, _this.get());
				obj->destroyObjectFromWorld(true);
				obj->destroyObjectFromDatabase(true);
			}

		}
	}
}

void CityRegionImplementation::removeTrainersOutsideCity(int newRadius) {
	if(cityHall == NULL)
		return;

	for(int i = getSkillTrainerCount() -1; i >=0; i--) {
		ManagedReference<SceneObject*> obj = getCitySkillTrainer(i);

		if(obj != NULL && !isInsideRadius(obj, newRadius)) {
			//info("need to destroy the skill trainer" + obj->getObjectNameStringIdName(),true);

			removeSkillTrainers(obj);
			sendDestroyOutsideObjectMail(obj);

			Locker clock(obj, _this.get());
			obj->destroyObjectFromWorld(true);
			obj->destroyObjectFromDatabase(true);
		}
	}
}

void CityRegionImplementation::removeTerminalsOutsideCity(int newRadius) {
	if(cityHall == NULL)
		return;

	for(int i = getMissionTerminalCount() - 1; i >= 0; i--) {
		ManagedReference<SceneObject*> obj = getCityMissionTerminal(i);
		if(obj != NULL && !isInsideRadius(obj, newRadius)) {
			//info("need to destroy the mission terminal" + obj->getObjectNameStringIdName(),true);

			removeMissionTerminal(obj);
			sendDestroyOutsideObjectMail(obj);

			Locker clock(obj, _this.get());
			obj->destroyObjectFromWorld(true);
			obj->destroyObjectFromDatabase(true);
		}
	}
}

void CityRegionImplementation::removeStructuresOutsideCity(int newRadius) {
	if(cityHall == NULL)
		return;

	for(int i = getStructuresCount() - 1; i >= 0; i--) {
		ManagedReference<SceneObject*> obj = this->getCivicStructure(i);
		if(obj != NULL && !isInsideRadius(obj, newRadius) ) {
			//info("need to destroy the civic structure " + obj->getObjectNameStringIdName() + " based on cityRegionCheck",true);
			removeStructure(obj.castTo<StructureObject*>());
			sendDestroyOutsideObjectMail(obj);
			StructureManager* structureManager = StructureManager::instance();
			structureManager->destroyStructure(obj.castTo<StructureObject*>());

		}
	}
}

bool CityRegionImplementation::isInsideRadius(SceneObject* obj, int radiusToUse) {
	Vector3 cityCenter(cityHall->getPositionX(), cityHall->getPositionY(), 0);
	Vector3 loc(obj->getPositionX(), obj->getPositionY(),0);
	//info("checking inside city for " + obj->getObjectNameStringIdName() + " " + String::valueOf(cityCenter.squaredDistanceTo(loc) <= (getRadius() * getRadius())),true);
	return (cityCenter.squaredDistanceTo(loc) <= (radiusToUse * radiusToUse));

}

void CityRegionImplementation::sendDestroyOutsideObjectMail(SceneObject* obj) {
	if(cityHall == NULL)
		return;

	ManagedReference<CreatureObject*> mayor = cityHall->getZoneServer()->getObject(getMayorID()).castTo<CreatureObject*>();
	ChatManager* chatManager = cityHall->getZoneServer()->getChatManager();

	if (mayor != NULL && obj != NULL) {
		StringIdChatParameter params("city/city", "structure_destroyed_radius_body");
		params.setTO(mayor->getFirstName());
		params.setTT(obj->getObjectName());
		UnicodeString subject = "@city/city:structure_destroyed_subject"; // Structure Removed!

		chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
	}
}

void CityRegionImplementation::sendDestroyObjectMail(SceneObject* obj) {
	if(cityHall == NULL)
		return;

	ManagedReference<CreatureObject*> mayor = cityHall->getZoneServer()->getObject(getMayorID()).castTo<CreatureObject*>();
	ChatManager* chatManager = cityHall->getZoneServer()->getChatManager();

	if (mayor != NULL && obj != NULL) {
		StringIdChatParameter params("city/city", "structure_destroyed_body");
		params.setTO(mayor->getFirstName());
		params.setTT(obj->getObjectName());
		UnicodeString subject = "@city/city:structure_destroyed_subject"; // Structure Removed!

		chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
	}
}

void CityRegionImplementation::sendStructureInvalidMails() {
	if(cityHall == NULL)
		return;

	ManagedReference<CreatureObject*> mayor = cityHall->getZoneServer()->getObject(getMayorID()).castTo<CreatureObject*>();
	ChatManager* chatManager = cityHall->getZoneServer()->getChatManager();

	for (int i = structures.size() - 1; i >= 0; --i) {
		ManagedReference<StructureObject*> structure = structures.get(i);

		SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());

		if (ssot == NULL || ssot->getCityRankRequired() <= cityRank || !ssot->isCivicStructure())
			continue;

		if (mayor != NULL) {
			StringIdChatParameter params("city/city", "structure_invalid_body");
			params.setTO(mayor->getFirstName());
			params.setTT(structure->getObjectName());
			UnicodeString subject = "@city/city:structure_invalid_subject"; // City Can't Support Structure!

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		}
	}

	for (int i = cityDecorations.size() - 1; i >= 0; --i) {
		ManagedReference<StructureObject*> structure = cityDecorations.get(i).castTo<StructureObject*>();

		if (structure == NULL)
			continue;

		SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());

		if (ssot == NULL || ssot->getCityRankRequired() <= cityRank || !ssot->isCivicStructure())
			continue;

		if (mayor != NULL) {
			StringIdChatParameter params("city/city", "structure_invalid_body");
			params.setTO(mayor->getFirstName());
			params.setTT(structure->getObjectName());
			UnicodeString subject = "@city/city:structure_invalid_subject"; // City Can't Support Structure!

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		}
	}
}

void CityRegionImplementation::sendStructureValidMails() {
	if(cityHall == NULL)
		return;

	ManagedReference<CreatureObject*> mayor = cityHall->getZoneServer()->getObject(getMayorID()).castTo<CreatureObject*>();
	ChatManager* chatManager = cityHall->getZoneServer()->getChatManager();

	for (int i = structures.size() - 1; i >= 0; --i) {
		ManagedReference<StructureObject*> structure = structures.get(i);

		SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());

		if (ssot == NULL || ssot->getCityRankRequired() < cityRank || !ssot->isCivicStructure())
			continue;

		if (mayor != NULL) {
			StringIdChatParameter params("city/city", "structure_valid_body");
			params.setTO(mayor->getFirstName());
			params.setTT(structure->getObjectName());
			UnicodeString subject = "@city/city:structure_valid_subject"; // Structure Support Reestablished!

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		}
	}

	for (int i = cityDecorations.size() - 1; i >= 0; --i) {
		ManagedReference<StructureObject*> structure = cityDecorations.get(i).castTo<StructureObject*>();

		if (structure == NULL)
			continue;

		SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());

		if (ssot == NULL || ssot->getCityRankRequired() < cityRank || !ssot->isCivicStructure())
			continue;

		if (mayor != NULL) {
			StringIdChatParameter params("city/city", "structure_valid_body");
			params.setTO(mayor->getFirstName());
			params.setTT(structure->getObjectName());
			UnicodeString subject = "@city/city:structure_valid_subject"; // Structure Support Reestablished!

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		}
	}
}

void CityRegionImplementation::cleanupDecorations(int limit) {

	int decorationsToRemove = cityDecorations.size() - limit;

	if(decorationsToRemove <= 0)
		return;

	for(int i =  0; i < decorationsToRemove; i++) {

		SceneObject* dec = getCityDecoration(0);
		if(dec != NULL) {

			sendDestroyObjectMail(dec);

			if(dec->isStructureObject()){
				StructureManager* structureManager = StructureManager::instance();
				structureManager->destroyStructure(cast<StructureObject*>(dec));

			} else {
				Locker clock(dec, _this.get());
				dec->destroyObjectFromWorld(true);
				dec->destroyObjectFromDatabase(true);
			}

			cityDecorations.removeElementAt(0);
		}
	}
}

void CityRegionImplementation::cleanupTrainers(int limit) {

	int trainersToRemove = citySkillTrainers.size() - limit;

	if(trainersToRemove <= 0)
		return;

	for(int i =  0; i < trainersToRemove; i++) {

		SceneObject* trainer = getCitySkillTrainer(0);
		if(trainer != NULL) {

			sendDestroyObjectMail(trainer);

			Locker clock(trainer, _this.get());
			trainer->destroyObjectFromWorld(true);
			trainer->destroyObjectFromDatabase(true);

			citySkillTrainers.removeElementAt(0);
		}
	}
}

void CityRegionImplementation::cleanupMissionTerminals(int limit) {

	int terminalsToRemove = cityMissionTerminals.size() - limit;

	if(terminalsToRemove <= 0)
		return;

	for(int i =  0; i < terminalsToRemove; i++) {

		SceneObject* terminal = getCityMissionTerminal(0);
		if(terminal != NULL) {

			sendDestroyObjectMail(terminal);

			Locker clock(terminal, _this.get());
			terminal->destroyObjectFromWorld(true);
			terminal->destroyObjectFromDatabase(true);

			cityMissionTerminals.removeElementAt(0);
		}
	}
}

uint64 CityRegionImplementation::getObjectID() {
	return _this.get()->_getObjectID();
}

