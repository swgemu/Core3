/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.caught in void ZoneImplementation::updateActiveAreas(SceneObject* object) {");
		managedRef->wlock(!readlock);
		throw;
	}

	managedRef->wlock(!readlock);
}

void ZoneImplementation::addSceneObject(SceneObject* object) {
	objectMap->put(object->getObjectID(), object);
	
	//Civic and commercial structures map registration will be handled by their city
	if (object->isStructureObject()) {
		StructureObject* structure = cast<StructureObject*>(object);
		if (structure->isCivicStructure() || structure->isCommercialStructure()) {
			return;
		}
	//Same thing for player city bank/mission terminals
	} else if (object->isTerminal()) {
		Terminal* terminal = cast<Terminal*>(object);
		ManagedReference<SceneObject*> controlledObject = terminal->getControlledObject();
		if (controlledObject != NULL && controlledObject->isStructureObject()) {
			StructureObject* structure = controlledObject.castTo<StructureObject*>();
			if (structure->isCivicStructure())
				return;
		}
	}
	
	registerObjectWithPlanetaryMap(object);
}

//TODO: Do we need to send out some type of update when this happens?
void ZoneImplementation::registerObjectWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->transferObject(object);
}

void ZoneImplementation::unregisterObjectWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->dropObject(object);
}

bool ZoneImplementation::isObjectRegisteredWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	return mapLocations->containsObject(object);
}

void ZoneImplementation::updatePlanetaryMapIcon(SceneObject* object, byte icon) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->updateObjectsIcon(object, icon);
}

void ZoneImplementation::dropSceneObject(SceneObject* object)  {
	objectMap->remove(object->getObjectID());
	unregisterObjectWithPlanetaryMap(object);
}

void ZoneImplementation::sendMapLocationsTo(SceneObject* player) {
	GetMapLocationsResponseMessage* gmlr = new GetMapLocationsResponseMessage(zoneName, mapLocations, player);
	player->sendMessage(gmlr);
}

Reference<SceneObject*> ZoneImplementation::getNearestPlanetaryObject(SceneObject* object, const String& mapObjectLocationType) {
	Reference<SceneObject*> planetaryObject = NULL;

#ifndef WITH_STM
	mapLocations->rlock();
#endif

	SortedVector<MapLocationEntry>& sortedVector = mapLocations->getLocation(mapObjectLocationType);

	float distance = 16000.f;

	for (int i = 0; i < sortedVector.size(); ++i) {
		SceneObject* obj = sortedVector.get(i).getObject();

		float objDistance = object->getDistanceTo(obj);

		if (objDistance < distance) {
			planetaryObject = obj;
			distance = objDistance;
		}
	}

#ifndef WITH_STM
	mapLocations->runlock();
#endif

	return planetaryObject;
}

SortedVector<ManagedReference<SceneObject*> > ZoneImplementation::getPlanetaryObjectList(const String& mapObjectLocationType) {
	SortedVector<ManagedReference<SceneObject*> > retVector;
	retVector.setNoDuplicateInsertPlan();

#ifndef WITH_STM
	mapLocations->rlock();
#endif

	try {
		SortedVector<MapLocationEntry>& entryVector = mapLocations->getLocation(mapObjectLocationType);

		for (int i = 0; i < entryVector.size(); ++i) {
			MapLocationEntry entry = entryVector.get(i);
			retVector.put(entry.getObject());
		}
	} catch (...) {

	}

#ifndef WITH_STM
	mapLocations->runlock();
#endif

	return retVector;
}

float ZoneImplementation::getMinX() {
	return planetManager->getTerrainManager()->getMin();
}

float ZoneImplementation::getMaxX() {
	return planetManager->getTerrainManager()->getMax();
}

float ZoneImplementation::getMinY() {
	return planetManager->getTerrainManager()->getMin();
}

float ZoneImplementation::getMaxY() {
	return planetManager->getTerrainManager()->getMax();
}

void ZoneImplementation::updateCityRegions() {
	info("scheduling updates for " + String::valueOf(cityRegionUpdateVector.size()) + " cities", true);

	for (int i = 0; i < cityRegionUpdateVector.size(); ++i) {
		CityRegion* city = cityRegionUpdateVector.get(i);

		Locker locker(city);

		Time* nextUpdateTime = city->getNextUpdateTime();
		int seconds = -1 * round(nextUpdateTime->miliDifference() / 1000.f);

		if (seconds < 0) //If the update occurred in the past, force an immediate update.
			seconds = 0;

		city->setRadius(city->getRadius());
		city->setLoaded();

		city->cleanupCitizens();
		city->cleanupDuplicateCityStructures();

		city->rescheduleUpdateEvent(seconds);

		if (city->hasAssessmentPending()) {
			Time* nextAssessmentTime = city->getNextAssessmentTime();
			int seconds2 = -1 * round(nextAssessmentTime->miliDifference() / 1000.f);

			if (seconds2 < 0)
				seconds2 = 0;

			city->scheduleCitizenAssessment(seconds2);
		}

		if (!city->isRegistered())
			continue;

		if (city->getRegionsCount() == 0)
			continue;

		Region* region = city->getRegion(0);

		unregisterObjectWithPlanetaryMap(region);
		registerObjectWithPlanetaryMap(region);
		
		for(int i = 0; i < city->getStructuresCount(); i++){
			ManagedReference<StructureObject*> structure = city->getCivicStructure(i);
			unregisterObjectWithPlanetaryMap(structure);
			registerObjectWithPlanetaryMap(structure);
		}

		for(int i = 0; i < city->getCommercialStructuresCount(); i++){
			ManagedReference<StructureObject*> structure = city->getCommercialStructure(i);
			unregisterObjectWithPlanetaryMap(structure);
			registerObjectWithPlanetaryMap(structure);
		}
	}

	cityRegionUpdateVector.removeAll();
}

bool ZoneImplementation::isWithinBoundaries(const Vector3& position) {
	//Remove 1/16th of the size to match client limits. NOTE: it has not been verified to work like this in the client.
	//Normal zone size is 8192, 1/16th of that is 512 resulting in 7680 as the boundary value.
	float maxX = getMaxX() * 15 / 16;
	float minX = getMinX() * 15 / 16;
	float maxY = getMaxY() * 15 / 16;
	float minY = getMinY() * 15 / 16;

	if (maxX >= position.getX() && minX <= position.getX() &&
			maxY >= position.getY() && minY <= position.getY()) {
		return true;
	} else {
		return false;
	}
}

float ZoneImplementation::getBoundingRadius() {
	return planetManager->getTerrainManager()->getMax();
}
