/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.caught in PlayerCreatureImplementation::logout(boolean doLock)");
	}

}


void PlayerObjectImplementation::doRecovery() {
	if (getZoneServer()->isServerLoading()) {
		activateRecovery();

		return;
	}

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return;

	/*if (!creature->isInQuadTree() && creature->getParent() != NULL && creature->getParent()->isCellObject() && creature->getClient() == NULL) {
		SceneObject* building = creature->getParent()->getParent();

		if (building != NULL && building->getZone() != NULL)
			//creature->insertToZone(building->getZone());
			building->getZone()->transferObject(creature, -1, true);
	}*/

	if (isLinkDead()) {
		if (logoutTimeStamp.isPast()) {
			info("unloading dead link player");

			unload();

			setOffline();

			if (creature->getClient() != NULL)
				creature->getClient()->closeConnection(false, true);

			return;
		} else {
			info("keeping dead linked player in game");
		}
	}

	creature->activateHAMRegeneration();
	creature->activateStateRecovery();

	CooldownTimerMap* cooldownTimerMap = creature->getCooldownTimerMap();

	if (cooldownTimerMap->isPast("digestEvent")) {
		Time currentTime;

		int timeDelta = currentTime.getMiliTime() - lastDigestion.getMiliTime();
		int fillingReduction = timeDelta / 18000;

		doDigest(fillingReduction);

		lastDigestion.updateToCurrentTime();
		cooldownTimerMap->updateToCurrentAndAddMili("digestEvent", 18000);
	}

	DamageOverTimeList* damageOverTimeList = creature->getDamageOverTimeList();

	if (damageOverTimeList->hasDot() && damageOverTimeList->isNextTickPast()) {
		damageOverTimeList->activateDots(creature);
	}

	if (creature->isBleeding() && !damageOverTimeList->hasDot(CreatureState::BLEEDING))
		creature->clearState(CreatureState::BLEEDING);
	if (creature->isPoisoned() && !damageOverTimeList->hasDot(CreatureState::POISONED))
		creature->clearState(CreatureState::POISONED);
	if (creature->isDiseased() && !damageOverTimeList->hasDot(CreatureState::DISEASED))
		creature->clearState(CreatureState::DISEASED);
	if (creature->isOnFire() && !damageOverTimeList->hasDot(CreatureState::ONFIRE))
		creature->clearState(CreatureState::ONFIRE);

	CommandQueueActionVector* commandQueue = creature->getCommandQueue();

	if (creature->isInCombat() && creature->getTargetID() != 0 && !creature->isPeaced()
			&& (commandQueue->size() == 0) && creature->isNextActionPast() && !creature->isDead() && !creature->isIncapacitated()) {
		creature->sendCommand(String("attack").hashCode(), "", creature->getTargetID());
	}

	if (!getZoneServer()->isServerLoading()) {
		if(creature->getZone() != NULL && creature->getZone()->getPlanetManager() != NULL) {
			ManagedReference<WeatherManager*> weatherManager = creature->getZone()->getPlanetManager()->getWeatherManager();

			if (weatherManager != NULL)
				weatherManager->sendWeatherTo(creature);
		}
	}

	activateRecovery();
}

void PlayerObjectImplementation::activateRecovery() {
	if (recoveryEvent == NULL) {
		recoveryEvent = new PlayerRecoveryEvent(_this.get());

		recoveryEvent->schedule(3000);
	}
}

void PlayerObjectImplementation::activateForcePowerRegen() {
	if (forceRegenerationEvent == NULL) {
		forceRegenerationEvent = new ForceRegenerationEvent(_this.get());

		float timer = getForcePowerRegen() / 5;
		float scheduledTime = 10 / timer;
		uint64 miliTime = scheduledTime * 1000;
		forceRegenerationEvent->schedule(miliTime);
	}
}

void PlayerObjectImplementation::setLinkDead() {
	onlineStatus = LINKDEAD;

	logoutTimeStamp.updateToCurrentTime();
	logoutTimeStamp.addMiliTime(30000);

	setCharacterBit(PlayerObjectImplementation::LD, true);

	activateRecovery();
}

void PlayerObjectImplementation::setOnline() {
	onlineStatus = ONLINE;

	clearCharacterBit(PlayerObjectImplementation::LD, true);

	doRecovery();

	activateMissions();
}

void PlayerObjectImplementation::reload(ZoneClientSession* client) {
	if (disconnectEvent != NULL) {
		disconnectEvent->cancel();
		disconnectEvent = NULL;
	}

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return;

	if (isLoggingIn()) {
		creature->unlock();

		ZoneClientSession* owner = creature->getClient();

		if (owner != NULL && owner != client)
			owner->disconnect();

		creature->wlock();
	}

	setOnline();

	creature->setMovementCounter(0);

	//notifiedSentObjects.removeAll();

	if (creature->isRidingMount() && creature->getParent() == NULL) {
		creature->clearState(CreatureState::RIDINGMOUNT);
	}

	//creature->insertToZone(creature->getZone());
	creature->getZone()->transferObject(creature, -1, true);
}

void PlayerObjectImplementation::disconnect(bool closeClient, bool doLock) {
	Locker locker(parent.get());

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return;

	if (!isOnline()) {
		ZoneClientSession* owner = creature->getClient();

		if (closeClient && owner != NULL)
			owner->closeConnection(false, true);

		creature->setClient(NULL);

		return;
	}

	if (/*isInCombat() && */!isLinkDead()) {
		info("link dead");

		setLinkDead();
	} else {
		info ("disconnecting player");

		unload();

		setOffline();
	}

	if (disconnectEvent != NULL)
		disconnectEvent = NULL;

	/*if (logoutEvent != NULL) {
			server->removeEvent(logoutEvent);
			delete logoutEvent;

			logoutEvent = NULL;
		}*/

	ZoneClientSession* owner = creature->getClient();

	if (closeClient && owner != NULL)
		owner->closeConnection(false, true);

	creature->setClient(NULL);
}

void PlayerObjectImplementation::clearDisconnectEvent() {
	disconnectEvent = NULL;
}

void PlayerObjectImplementation::clearRecoveryEvent() {
	recoveryEvent = NULL;
}

void PlayerObjectImplementation::clearForceRegenerationEvent() {
	forceRegenerationEvent = NULL;
}

void PlayerObjectImplementation::maximizeExperience() {
	VectorMap<String, int>* xpCapList = getXpTypeCapList();

	for (int i = 0; i < xpCapList->size(); ++i) {
		addExperience(xpCapList->elementAt(i).getKey(), xpCapList->elementAt(i).getValue(), true);
	}
}

void PlayerObjectImplementation::activateMissions() {
	ManagedReference<CreatureObject*> creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL) {
		return;
	}

	SceneObject* datapad = creature->getSlottedObject("datapad");

	if (datapad == NULL) {
		return;
	}

	int datapadSize = datapad->getContainerObjectsSize();

	for (int i = datapadSize - 1; i >= 0; --i) {
		if (datapad->getContainerObject(i)->isMissionObject()) {
			Reference<MissionObject*> mission = datapad->getContainerObject(i).castTo<MissionObject*>();

			if (mission != NULL) {
				//Check if it is target or destination NPC
				MissionObjective* objective = mission->getMissionObjective();
				if (objective != NULL) {
					objective->activate();
				}
			}
		}
	}
}

void PlayerObjectImplementation::setForcePowerMax(int newValue, bool notifyClient) {
	if(newValue == getForcePowerMax())
		return;

	forcePowerMax = newValue;

	if(forcePower > forcePowerMax)
		setForcePower(forcePowerMax, true);

	if (notifyClient == true){
		// Update the force power bar max.
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->updateForcePowerMax();
		dplay8->close();

		sendMessage(dplay8);
	}
}

void PlayerObjectImplementation::setForcePower(int fp, bool notifyClient) {

	if(fp == getForcePower())
		return;

	// Set forcepower back to 0 incase player goes below	
	if (fp < 0)
		fp = 0;	

	// Set force back to max incase player goes over
	if (fp > getForcePowerMax())
		fp = getForcePowerMax();


	// Activate regeneration.
	if (fp < getForcePowerMax()) {
		activateForcePowerRegen();
	}

	forcePower = fp;			

	if (notifyClient == true){
		// Update the force power bar.
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->updateForcePower();
		dplay8->close();

		sendMessage(dplay8);
	}

}

void PlayerObjectImplementation::doForceRegen() {
	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL || creature->isIncapacitated() || creature->isDead())
		return;

	uint32 tick = 5;

	uint32 modifier = 1;

	// TODO: Re-factor Force Meditate so TKA meditate doesn't effect.
	if (creature->isMeditating())
		modifier = 3.f;

	uint32 forceTick = tick * modifier;

	if (forceTick < 1)
		forceTick = 1;

	if (forceTick > getForcePowerMax() - getForcePower()){   // If the player's Force Power is going to regen again and it's close to max,
		setForcePower(getForcePowerMax());             // Set it to max, so it doesn't go over max.
	} else {
		setForcePower(getForcePower() + forceTick); // Otherwise regen normally.
	}
}

void PlayerObjectImplementation::clearScreenPlayData(const String& screenPlay) {
	for (int i = screenPlayData.size() - 1; i >= 0; --i) {
		if (screenPlayData.elementAt(i).getKey().contains(screenPlay + "_"))
			screenPlayData.drop(screenPlayData.elementAt(i).getKey());
	}
}

void PlayerObjectImplementation::addToBountyLockList(uint64 playerId) {
	if (bountyLockList.contains(playerId)) {
		if (bountyLockList.get(playerId)->isScheduled()) {
			bountyLockList.get(playerId)->cancel();
		}
	} else {
		bountyLockList.put(playerId, new BountyHunterTefRemovalTask(_this.get(), playerId));
		updateBountyPvpStatus(playerId);
	}
}

void PlayerObjectImplementation::removeFromBountyLockList(uint64 playerId, bool immediately) {
	int tefTime = 15 * 60 * 1000;
	if (immediately) {
		//Schedule tef removal to happen soon but delay it enough for any bh mission to be dropped correctly.
		tefTime = 100;
	}
	if (bountyLockList.contains(playerId)) {
		if (bountyLockList.get(playerId)->isScheduled()) {
			//Reschedule for another 15 minutes tef.
			bountyLockList.get(playerId)->reschedule(tefTime);
		} else {
			bountyLockList.get(playerId)->schedule(tefTime);
		}
	}
}

void PlayerObjectImplementation::removeFromBountyLockListDirectly(uint64 playerId) {
	if (bountyLockList.contains(playerId)) {
		if (bountyLockList.get(playerId)->isScheduled()) {
			bountyLockList.get(playerId)->cancel();
		}
	}
	bountyLockList.drop(playerId);
	updateBountyPvpStatus(playerId);
}

void PlayerObjectImplementation::updateBountyPvpStatus(uint64 playerId) {
	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(getParent().get().get());

	if (creature == NULL) {
		return;
	}

	ZoneServer* zoneServer = creature->getZoneServer();
	if (zoneServer == NULL) {
		return;
	}

	ManagedReference<CreatureObject*> target = zoneServer->getObject(playerId).castTo<CreatureObject*>();

	if (target == NULL) {
		return;
	}

	creature->sendPvpStatusTo(target);
	target->sendPvpStatusTo(creature);
}

bool PlayerObjectImplementation::isBountyLocked() {
	return bountyLockList.size() > 0;
}

bool PlayerObjectImplementation::isInBountyLockList(uint64 playerId) {
	return bountyLockList.contains(playerId);
}

Time PlayerObjectImplementation::getLastVisibilityUpdateTimestamp() {
	return lastVisibilityUpdateTimestamp;
}

Time PlayerObjectImplementation::getLastPvpCombatActionTimestamp() {
	return lastPvpCombatActionTimestamp;
}

void PlayerObjectImplementation::updateLastPvpCombatActionTimestamp() {
	ManagedReference<CreatureObject*> parent = getParent().get().castTo<CreatureObject*>();

	if (parent == NULL)
		return;

	bool alreadyHasTef = hasPvpTef();

	lastPvpCombatActionTimestamp.updateToCurrentTime();
	lastPvpCombatActionTimestamp.addMiliTime(300000); // 5 minutes

	if (pvpTefTask == NULL) {
		pvpTefTask = new PvpTefRemovalTask(parent);
	}

	if (!pvpTefTask->isScheduled()) {
		pvpTefTask->schedule(300000); // 5 minutes
	}

	if (!alreadyHasTef) {
		updateInRangeBuildingPermissions();
		parent->setPvpStatusBit(CreatureFlag::TEF);
	}
}

bool PlayerObjectImplementation::hasPvpTef() {
	return !lastPvpCombatActionTimestamp.isPast();
}

Vector3 PlayerObjectImplementation::getTrainerCoordinates() {
	return trainerCoordinates;
}

void PlayerObjectImplementation::setTrainerCoordinates(const Vector3& trainer) {
	trainerCoordinates = trainer;
}

void PlayerObjectImplementation::addPermissionGroup(const String& group, bool updatePermissions) {
	permissionGroups.put(group);

	if (updatePermissions)
		updateInRangeBuildingPermissions();
}

void PlayerObjectImplementation::removePermissionGroup(const String& group, bool updatePermissions) {
	permissionGroups.drop(group);

	if (updatePermissions)
		updateInRangeBuildingPermissions();
}

void PlayerObjectImplementation::updateInRangeBuildingPermissions() {
	ManagedReference<CreatureObject*> parent = getParent().get().castTo<CreatureObject*>();

	if (parent == NULL)
		return;

	Zone* zone = parent->getZone();

	if (zone == NULL)
		return;

	CloseObjectsVector* vec = (CloseObjectsVector*) parent->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
	vec->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		BuildingObject* building = closeObjects.get(i).castTo<BuildingObject*>();

		if (building != NULL) {
			building->updateCellPermissionsTo(parent);
		}
	}
}

bool PlayerObjectImplementation::hasPermissionGroup(const String& group) {
	return permissionGroups.contains(group);
}

void PlayerObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	removeAllFriends();

	for (int i = 0; i < currentEventPerks.size(); ++i) {
		uint64 oid = currentEventPerks.get(i);

		ManagedReference<EventPerkDeed*> perk = getZoneServer()->getObject(oid).castTo<EventPerkDeed*>();

		if (perk != NULL) {
			perk->activateRemoveEvent(true);
		}
	}

	for (int i = 0; i < ownedVendors.size(); ++i) {
		uint64 oid = ownedVendors.get(i);

		ManagedReference<TangibleObject*> vendor = getZoneServer()->getObject(oid).castTo<TangibleObject*>();

		if (vendor != NULL) {
			VendorManager::instance()->destroyVendor(vendor);
		}
	}

	for (int i = 0; i < ownedStructures.size(); ++i) {
		uint64 oid = ownedStructures.get(i);

		ManagedReference<StructureObject*> structure = getZoneServer()->getObject(oid).castTo<StructureObject*>();

		if (structure != NULL) {
			Zone* zone = structure->getZone();

			if (zone != NULL) {
				if (structure->isCivicStructure()) {
					StructureSetOwnerTask* task = new StructureSetOwnerTask(structure, 0);
					task->execute();
					continue;
				}

				StructureManager::instance()->destroyStructure(structure);
			} else {
				structure->destroyObjectFromDatabase(true);
			}
		}
	}

	if (isMarried()) {
		PlayerManager* playerManager = server->getPlayerManager();
		ManagedReference<CreatureObject*> spouse = playerManager->getPlayer(spouseName);

		if (spouse != NULL) {
			PlayerObject* spouseGhost = spouse->getPlayerObject();

			if (spouseGhost != NULL) {
				RemoveSpouseTask* task = new RemoveSpouseTask(spouse);
				task->execute();
			}
		}
	}
}

int PlayerObjectImplementation::getLotsRemaining() {
	Locker locker(_this.get());

	int lotsRemaining = maximumLots;

	for (int i = 0; i < ownedStructures.size(); ++i) {
		unsigned long oid = ownedStructures.get(i);

		Reference<StructureObject*> structure = getZoneServer()->getObject(oid).castTo<StructureObject*>();

		if (structure != NULL) {
			lotsRemaining = lotsRemaining - structure->getLotSize();
		}
	}

	return lotsRemaining;
}

void PlayerObjectImplementation::setJediState(int state, bool notifyClient) {
	if (jediState == state)
		return;

	jediState = state;

	if (!notifyClient)
		return;

	PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.get());
	delta->setJediState(state);
	delta->close();

	sendMessage(delta);
}

void PlayerObjectImplementation::setActiveQuestsBit(int bitIndex, byte value, bool notifyClient) {
	activeQuests.setBit(bitIndex, value);

	if (!notifyClient)
		return;

	PlayerObjectDeltaMessage8* delta = new PlayerObjectDeltaMessage8(this);
	delta->startUpdate(5);
	activeQuests.insertToMessage(delta);
	delta->close();

	sendMessage(delta);
}

void PlayerObjectImplementation::setCompletedQuestsBit(int bitIndex, byte value, bool notifyClient) {
	completedQuests.setBit(bitIndex, value);

	if (!notifyClient)
		return;

	PlayerObjectDeltaMessage8* delta = new PlayerObjectDeltaMessage8(this);
	delta->startUpdate(4);
	completedQuests.insertToMessage(delta);
	delta->close();

	sendMessage(delta);
}

void PlayerObjectImplementation::setPlayerQuestData(uint32 questHashCode, PlayerQuestData& data, bool notifyClient) {
	if (notifyClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->startUpdate(6);
		playerQuestsData.set(questHashCode, data, dplay8, 1);
		dplay8->close();

		sendMessage(dplay8);
	} else {
		playerQuestsData.set(questHashCode, data);
	}
}

PlayerQuestData PlayerObjectImplementation::getQuestData(uint32 questHashCode) {
	return playerQuestsData.get(questHashCode);
}

int PlayerObjectImplementation::getVendorCount() {
	// Cleanup vendor list before returning the count
	for (int i = ownedVendors.size() - 1; i >= 0; --i) {
		ManagedReference<SceneObject*> vendor = server->getZoneServer()->getObject(ownedVendors.get(i)).get();

		if (vendor == NULL) {
			ownedVendors.remove(i);
			continue;
		}

		if (vendor->getParent().get() == NULL)
			vendor->destroyObjectFromDatabase(true);
	}

	return ownedVendors.size();
}

bool PlayerObjectImplementation::hasChosenVeteranReward( const String& rewardTemplate ){

	for( int i = 0; i < chosenVeteranRewards.size(); i++){
		if( rewardTemplate == chosenVeteranRewards.get(i) ){
			return true;
		}
	}

	return false;

}

void PlayerObjectImplementation::updateForceSensitiveElegibleExperiences(int type) {
	DeltaVectorMap<String, int>* xpList = getExperienceList();

	// Clear the vector for new strings...
	fsEligibleExperiences.removeAll();


	for (int i=0; i < xpList->size(); ++i){
		String xpString = xpList->getKeyAt(i);
		if (FsExperienceTypes::isValid(type, xpString) && (!fsEligibleExperiences.contains(xpList->getKeyAt(i)))) {
			fsEligibleExperiences.add(xpList->getKeyAt(i));
		}
	}
}

int PlayerObjectImplementation::getCharacterAgeInDays() {
	ManagedReference<CreatureObject*> creature = dynamic_cast<CreatureObject*>(parent.get().get());

	PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();

	ManagedReference<Account*> account = playerManager->getAccount(getAccountID());
	if(account == NULL) {
		return 0;
	}

	CharacterList* list = account->getCharacterList();
	if (list == NULL) {
		return 0;
	}

	Time currentTime;
	Time age;

	for (int i = 0; i < list->size(); i++) {
		CharacterListEntry entry = list->get(i);
		if (entry.getObjectID() == creature->getObjectID() && entry.getGalaxyID() == creature->getZoneServer()->getGalaxyID()) {
			age = entry.getCreationDate();
			break;
		}
	}

	uint32 timeDelta = currentTime.getTime() - age.getTime();

	int days = timeDelta / 60 / 60 / 24;

	return days;
}

String PlayerObjectImplementation::getForceSensitiveExperienceRatio(const String& type) {
	if (!FsExperienceTypes::getFsRatio(type).isEmpty())
		return FsExperienceTypes::getFsRatio(type);
	else return "";
}
