/*
 * GCWManagerImplementation.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: root
 */

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/consumable/Consumable.h"
#include "server/zone/objects/tangible/deed/Deed.h"

#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/objects/tangible/terminal/components/TurretControlTerminalDataComponent.h"
#include "server/zone/objects/installation/components/TurretDataComponent.h"

#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/gcw/tasks/StartVulnerabilityTask.h"
#include "server/zone/managers/gcw/tasks/EndVulnerabilityTask.h"
#include "server/zone/managers/gcw/tasks/BaseDestructionTask.h"
#include "server/zone/managers/gcw/tasks/CheckGCWTask.h"
#include "server/zone/managers/gcw/tasks/CheckWildContrabandScanTask.h"
#include "server/zone/managers/gcw/tasks/SecurityRepairTask.h"
#include "server/zone/managers/gcw/tasks/BaseShutdownTask.h"
#include "server/zone/managers/gcw/tasks/BaseRebootTask.h"
#include "server/zone/managers/gcw/tasks/UplinkTerminalResetTask.h"
#include "server/zone/managers/gcw/GCWBaseShutdownObserver.h"
#include "server/zone/managers/gcw/TerminalSpawn.h"

#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

#include "server/zone/objects/player/sui/callbacks/HQDefenseStatusSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/JamUplinkSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/OverrideTerminalSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PowerRegulatorSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/RemoveDefenseSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/DonateDefenseSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/TurretControlSuiCallback.h"

#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/managers/gcw/sessions/ContrabandScanSession.h"
#include "server/zone/managers/gcw/sessions/WildContrabandScanSession.h"
#include "server/zone/managers/gcw/SecurityPatrolSpawn.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/gcw/observers/SquadObserver.h"

void GCWManagerImplementation::initialize() {
	loadLuaConfig();
}

void GCWManagerImplementation::start() {
	auto checkGCWTask = new CheckGCWTask(_this.getReferenceUnsafeStaticCast());

	if (checkGCWTask != nullptr) {
		// typically gcwCheckTimer = 3600 - start 900 + random 450 seconds from now
		uint64 delay = ((gcwCheckTimer / 4) + System::random(gcwCheckTimer / 8));
		info(true) << "Scheduling checks to start in " << delay << " seconds.";
		checkGCWTask->schedule(delay * 1000);
	} else {
		error() << "Unable to create new CheckGCWTask";
		return;
	}

	if (crackdownScansEnabled && planetsWithWildScans.contains(zone->getZoneName())) {
		auto contrabandScanTask = new CheckWildContrabandScanTask(_this.getReferenceUnsafeStaticCast());

		if (contrabandScanTask != nullptr) {
			// Server start delay Minimum 10min + gcw_manager delay
			uint64 delay = getWildScanInterval() + 600000;
			info(true) << "Scheduling crackdown scans to start in " << int(delay / 1000) << " seconds.";
			contrabandScanTask->schedule(delay);
		} else {
			error() << "Unable to create new CheckWildContrabandScanTask";
			return;
		}
	}
}

void GCWManagerImplementation::loadLuaConfig() {
	Locker locker(&baseMutex);

	info("Loading gcw configuration file.");

	Lua* lua = new Lua();
	lua->init();
	lua->runFile("scripts/managers/gcw_manager.lua");

	gcwCheckTimer = lua->getGlobalInt("gcwCheckTimer");
	vulnerabilityDuration = lua->getGlobalInt("vulnerabilityDuration");
	vulnerabilityFrequency = lua->getGlobalInt("vulnerabilityFrequency");
	resetTimer = lua->getGlobalInt("resetTimer");
	sliceCooldown = lua->getGlobalInt("sliceCooldown");
	totalDNASamples = lua->getGlobalInt("totalDNASamples");
	dnaStrandLength = lua->getGlobalInt("dnaStrandLength");
	powerSwitchCount = lua->getGlobalInt("powerSwitchCount");
	destructionTimer = lua->getGlobalInt("destructionTimer");

	maxBasesPerPlanet = lua->getGlobalInt("maxBasesPerPlanet");
	maxBasesPerPlayer = lua->getGlobalInt("maxBasesPerPlayer");
	basePlacementDelay = lua->getGlobalInt("basePlacementDelay");
	placeInCombat = lua->getGlobalBoolean("placeInCombat");
	allowPveBases = lua->getGlobalBoolean("allowPveBases");
	allowBaseComplex = lua->getGlobalBoolean("allowBaseComplex");
	baseComplexSize = lua->getGlobalInt("baseComplexSize");
	nearbyBaseDistance = lua->getGlobalInt("nearbyBaseDistance");
	donationCooldown = lua->getGlobalInt("donationCooldown");

	overtCooldown = lua->getGlobalInt("overtCooldown");
	reactivationTimer = lua->getGlobalInt("reactivationTimer");
	turretAutoFireTimeout = lua->getGlobalInt("turretAutoFireTimeout");
	spawnBaseAlarms = lua->getGlobalBoolean("spawnBaseAlarms");
	bonusXP = lua->getGlobalInt("bonusXP");
	winnerBonus = lua->getGlobalInt("winnerBonus");
	loserBonus = lua->getGlobalInt("loserBonus");
	racialPenaltyEnabled = lua->getGlobalInt("racialPenaltyEnabled");
	initialVulnerabilityDelay = lua->getGlobalInt("initialVulnerabilityDelay");
	spawnDefenses = lua->getGlobalInt("spawnDefenses");
	crackdownScansEnabled = lua->getGlobalBoolean("crackdownScansEnabled");
	crackdownScanPrivilegedPlayers = lua->getGlobalBoolean("crackdownScanPrivilegedPlayers");
	wildScanInterval = lua->getGlobalInt("wildScanInterval") * 1000;
	wildScanLoginDelay = lua->getGlobalInt("wildScanLoginDelay") * 1000;
	wildScanChance = lua->getGlobalInt("wildScanChance");
	crackdownPlayerScanCooldown = lua->getGlobalInt("crackdownPlayerScanCooldown") * 1000;
	crackdownScannerCooldown = lua->getGlobalInt("crackdownScannerCooldown") * 1000;
	crackdownContrabandFineCredits = lua->getGlobalInt("crackdownContrabandFineCredits");
	crackdownContrabandFineFactionPoints = lua->getGlobalInt("crackdownContrabandFineFactionPoints");

	LuaObject nucleotides = lua->getGlobalObject("dnaNucleotides");
	if (nucleotides.isValidTable()) {
		for (int i = 1; i <= nucleotides.getTableSize(); ++i) {
			dnaNucleotides.add(nucleotides.getStringAt(i));
		}
	}
	nucleotides.pop();

	LuaObject pairs = lua->getGlobalObject("dnaPairs");
	if (pairs.isValidTable()) {
		for (int i = 1; i <= pairs.getTableSize(); ++i) {
			dnaPairs.add(pairs.getStringAt(i));
		}
	}
	pairs.pop();

	LuaObject planets = lua->getGlobalObject("crackdownPlanetsWithWildScans");
	if (planets.isValidTable()) {
		for (int i = 1; i <= planets.getTableSize(); ++i) {
			planetsWithWildScans.add(planets.getStringAt(i));
		}
	}
	planets.pop();

	LuaObject pointsObject = lua->getGlobalObject("HQValues");

	if (pointsObject.isValidTable()) {
		for (int i = 1; i <= pointsObject.getTableSize(); ++i) {
			LuaObject baseObject = pointsObject.getObjectAt(i);
			if (baseObject.isValidTable()) {
				String templateString = baseObject.getStringAt(1);
				int pointsValue = baseObject.getIntAt(2);
				addPointValue(templateString, pointsValue);
			}
			baseObject.pop();
		}
	}

	pointsObject.pop();

	info("Loaded " + String::valueOf(baseValue.size()) + " GCW base scoring values.");

	LuaObject penaltyObject = lua->getGlobalObject("imperial_racial_penalty");
	if (penaltyObject.isValidTable()) {
		for (int i = 1; i <= penaltyObject.getTableSize(); ++i) {
			LuaObject raceObject = penaltyObject.getObjectAt(i);
			if (raceObject.isValidTable()) {
				int race = raceObject.getIntAt(1);
				float penalty = raceObject.getFloatAt(2);
				addRacialPenalty(race, penalty);
			}
			raceObject.pop();
		}
	}

	penaltyObject.pop();

	info("Loaded " + String::valueOf(racialPenaltyMap.size()) + " racial penalties.");

	LuaObject strongholdsObject = lua->getGlobalObject("strongholdCities");
	if (strongholdsObject.isValidTable()) {
		LuaObject imperialObject = strongholdsObject.getObjectField("imperial");
		if (imperialObject.isValidTable()) {
			for (int i = 1; i <= imperialObject.getTableSize(); ++i) {
				imperialStrongholds.add(imperialObject.getStringAt(i));
			}
		}
		imperialObject.pop();

		LuaObject rebelObject = strongholdsObject.getObjectField("rebel");
		if (rebelObject.isValidTable()) {
			for (int i = 1; i <= rebelObject.getTableSize(); ++i) {
				rebelStrongholds.add(rebelObject.getStringAt(i));
			}
		}
		rebelObject.pop();
	}

	strongholdsObject.pop();

	LuaObject difficulties = lua->getGlobalObject("difficutlyScalingThresholds");
	if (difficulties.isValidTable()) {
		for (int i = 1; i <= difficulties.getTableSize(); ++i) {
			difficultyScalingThresholds.add(difficulties.getIntAt(i));
		}
	}
	difficulties.pop();

	info("Loaded " + String::valueOf(imperialStrongholds.size()) + " imperial strongholds and " + String::valueOf(rebelStrongholds.size()) +
		 " rebel strongholds.");

	LuaObject terminalSpawnTable = lua->getGlobalObject("terminalSpawns");

	if (terminalSpawnTable.isValidTable()) {
		for (int i = 1; i <= terminalSpawnTable.getTableSize(); ++i) {
			LuaObject terminalSpawn = terminalSpawnTable.getObjectAt(i);

			if (terminalSpawn.isValidTable()) {
				String baseTemplate = terminalSpawn.getStringAt(1);

				LuaObject terminalSpawnLocs = terminalSpawn.getObjectAt(2);

				if (terminalSpawn.isValidTable()) {
					Vector<Reference<TerminalSpawn*>>* spawnList = new Vector<Reference<TerminalSpawn*>>();

					for (int j = 1; j <= terminalSpawnLocs.getTableSize(); ++j) {
						LuaObject terminalLoc = terminalSpawnTable.getObjectAt(j);

						if (terminalLoc.isValidTable()) {
							float spawnX = terminalLoc.getFloatAt(1);
							float spawnZ = terminalLoc.getFloatAt(2);
							float spawnY = terminalLoc.getFloatAt(3);
							float ox = terminalLoc.getFloatAt(4);
							float oy = terminalLoc.getFloatAt(5);
							float oz = terminalLoc.getFloatAt(6);
							float ow = terminalLoc.getFloatAt(7);
							int cellID = terminalLoc.getIntAt(8);
							Quaternion termRot(ow, ox, oy, oz);

							Vector3 spLoc(spawnX, spawnY, spawnZ);
							Reference<TerminalSpawn*> termSpawn = new TerminalSpawn(baseTemplate, spLoc, cellID, termRot);
							spawnList->add(termSpawn);
						}

						terminalLoc.pop();
					}

					terminalSpawnLocations.put(baseTemplate, spawnList);
				}

				terminalSpawnLocs.pop();
			}

			terminalSpawn.pop();
		}
	}

	terminalSpawnTable.pop();

	LuaObject termTemps = lua->getGlobalObject("terminalTemplates");
	if (termTemps.isValidTable()) {
		for (int i = 1; i <= termTemps.getTableSize(); ++i) {
			terminalTemplates.add(termTemps.getStringAt(i));
		}
	}

	termTemps.pop();

	LuaObject squadFormationTable = lua->getGlobalObject("squadFormations");

	if (squadFormationTable.isValidTable()) {
		for (int i = 1; i <= squadFormationTable.getTableSize(); i++) {
			LuaObject squadFormation = squadFormationTable.getObjectAt(i);

			if (squadFormation.isValidTable()) {
				String squadType = squadFormation.getStringAt(1);
				LuaObject squadTemplates = squadFormation.getObjectAt(2);

				if (squadTemplates.isValidTable()) {
					Vector<String>* temps = new Vector<String>;

					for (int j = 1; j <= squadTemplates.getTableSize(); j++) {
						String temp = squadTemplates.getStringAt(j);

						temps->add(temp);
					}
					squadFormations.put(squadType, temps);
				}

				squadTemplates.pop();
			}

			squadFormation.pop();
		}
	}

	squadFormationTable.pop();

	info("Loaded " + String::valueOf(squadFormations.size()) + " total squad formations.", true);

	delete lua;
	lua = nullptr;
}

void GCWManagerImplementation::stop() {
	gcwBaseList.removeAll();
	gcwStartTasks.removeAll();
	gcwEndTasks.removeAll();
	gcwDestroyTasks.removeAll();
}

void GCWManagerImplementation::performGCWTasks() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	int totalBase = gcwBaseList.size();

	info("Checking " + String::valueOf(totalBase) + " bases", true);

	uint64 thisOid;
	int rebelCheck = 0, rebelsScore = 0;
	int imperialCheck = 0, imperialsScore = 0;
	int totalPlayerBases = 0;

	for (int i = 0; i < gcwBaseList.size(); i++) {
		thisOid = getBase(i)->getObjectID();

		Reference<BuildingObject*> building = zone->getZoneServer()->getObject(thisOid).castTo<BuildingObject*>();

		if (building == nullptr)
			continue;

		if (building->getFactionBaseType() == PLAYERFACTIONBASE) {
			// If PvE Bases are disallowed, schedule for destruct and do not add to count
			if (!allowPveBases && !(building->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
				building->info(true) << " GCW PvE Base scheduled for destruction -- Base ID: " << building->getObjectID();

				scheduleBaseDestruction(building, nullptr, true);
				continue;
			}

			// Update Base Count
			totalPlayerBases++;

			// Total bases on the planet are greater then the set amount in gcw_manager.lua schedule bases over the alowed amount for destruct
			if (totalPlayerBases > maxBasesPerPlanet) {
				building->info(true) << " GCW Base over Planet Capacity scheduled for destruction -- Base ID: " << building->getObjectID();

				scheduleBaseDestruction(building, nullptr, true);
				continue;
			}
		}

		String templateString = building->getObjectTemplate()->getFullTemplateString();
		int pointsValue = getPointValue(templateString);

		if (building->getFaction() == Factions::FACTIONREBEL) {
			rebelCheck++;

			if (pointsValue > -1)
				rebelsScore += pointsValue;
		} else if (building->getFaction() == Factions::FACTIONIMPERIAL) {
			imperialCheck++;

			if (pointsValue > -1)
				imperialsScore += pointsValue;
		}

		verifyMinefields(building);
		verifyScanners(building);
		verifyTurrets(building);
	}

	setRebelBaseCount(rebelCheck);
	setImperialBaseCount(imperialCheck);
	setRebelScore(rebelsScore);
	setImperialScore(imperialsScore);

	updateWinningFaction();
	spawnGcwControlBanners();

	CheckGCWTask* task = new CheckGCWTask(_this.getReferenceUnsafeStaticCast());
	task->schedule(gcwCheckTimer * 1000);
}

void GCWManagerImplementation::verifyMinefields(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();

	if (zoneServer == nullptr)
		return;

	Locker blocker(building);

	for (int i = 0; i < baseData->getTotalScannerCount(); ++i) {
		uint64 minefieldID = baseData->getMinefieldID(i);

		ManagedReference<SceneObject*> minefield = zoneServer->getObject(minefieldID);

		if (minefield == nullptr)
			baseData->setScannerID(i, 0);
	}
}

void GCWManagerImplementation::verifyScanners(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();

	if (zoneServer == nullptr)
		return;

	Locker blocker(building);

	for (int i = 0; i < baseData->getTotalScannerCount(); ++i) {
		uint64 scannerID = baseData->getScannerID(i);

		ManagedReference<SceneObject*> scanner = zoneServer->getObject(scannerID);

		if (scanner == nullptr)
			baseData->setScannerID(i, 0);
	}
}

void GCWManagerImplementation::verifyTurrets(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();

	if (zoneServer == nullptr)
		return;

	int turretCount = 0;

	Locker blocker(building);

	bool hasDefense = baseData->hasDefense();

	for (int i = 0; i < baseData->getTotalTurretCount(); ++i) {
		uint64 turretID = baseData->getTurretID(i);

		ManagedReference<SceneObject*> turret = zoneServer->getObject(turretID);

		if (turret != nullptr)
			turretCount++;
		else
			baseData->setTurretID(i, 0);
	}

	baseData->setDefense(turretCount != 0);

	if (!(hasDefense == baseData->hasDefense())) {
		building->broadcastCellPermissions();
	}
}

bool GCWManagerImplementation::canPlaceMoreBases(CreatureObject* creature) {
	if (creature == nullptr || !creature->isPlayerCreature())
		return false;

	int baseCount = getBaseCount(creature);

	if (baseCount >= maxBasesPerPlayer) {
		creature->sendSystemMessage("@faction_perk:not_enough_base_units"); // You do not have any base units allotments left, and so cannot place this factional base.
		return false;
	}

	return true;
}

int GCWManagerImplementation::getBaseCount(CreatureObject* creature, bool pvpOnly) {
	if (creature == nullptr || !creature->isPlayerCreature())
		return 0;

	PlayerObject* ghost = creature->getPlayerObject();
	if (ghost == nullptr)
		return 0;

	if (zone == nullptr)
		return 0;

	ZoneServer* server = zone->getZoneServer();

	if (server == nullptr)
		return 0;

	int baseCount = 0;
	for (int i = 0; i < ghost->getTotalOwnedStructureCount(); ++i) {
		ManagedReference<SceneObject*> structure = server->getObject(ghost->getOwnedStructure(i));

		if (structure != nullptr && structure->isGCWBase()) {
			if (pvpOnly) {
				Reference<BuildingObject*> building = structure->asBuildingObject();

				if (building != nullptr && (building->getPvpStatusBitmask() & CreatureFlag::OVERT))
					baseCount++;
			} else {
				baseCount++;
			}
		}
	}

	return baseCount;
}

void GCWManagerImplementation::updateWinningFaction() {
	int score = 0;
	int rebelScore = getRebelScore();
	int imperialScore = getImperialScore();

	if (rebelScore > imperialScore) {
		winningFaction = Factions::FACTIONREBEL;
		score = rebelScore - imperialScore;
	} else if (imperialScore > rebelScore) {
		winningFaction = Factions::FACTIONIMPERIAL;
		score = imperialScore - rebelScore;
	}

	int scaling = 0;
	if (score > 0) {
		for (int i = 0; i < difficultyScalingThresholds.size(); i++) {
			if (score >= difficultyScalingThresholds.get(i)) {
				scaling++;
			}
		}
	}
	winnerDifficultyScaling = scaling;
}

void GCWManagerImplementation::spawnGcwControlBanners() {

	if (zone == nullptr) {
		return;
	}

	String zoneName = zone->getZoneName();
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaSpawnCityControlBanners = lua->createFunction("CityControlBanners", "spawnGcwControlBanners", 0);

	*luaSpawnCityControlBanners << zoneName;
	luaSpawnCityControlBanners->callFunction();
}

bool GCWManagerImplementation::hasTooManyBasesNearby(float x, float y) {
	if (zone == nullptr)
		return true;

	SortedVector<QuadTreeEntry* > closeEntryObjects;
	zone->getInRangeObjects(x, y, nearbyBaseDistance, &closeEntryObjects, true, false);

	int count = 0;
	uint32 tempStrucHash = STRING_HASHCODE("temporary_structure");

	for (int i = 0; i < closeEntryObjects.size(); ++i) {
		SceneObject* scene = cast<SceneObject*>(closeEntryObjects.get(i));

		if (scene == nullptr)
			continue;

		// Check for other bases or structures being placed
		if (scene->isGCWBase() || (scene->isInstallationObject() && (scene->getObjectNameStringIdName().hashCode() == tempStrucHash)))
			count++;

		// Stop iteration if the count breaks the config options
		if (!allowBaseComplex && count > 0) {
			return true;
		} else if (allowBaseComplex && count >= baseComplexSize) {
			return true;
		}
	}

	return false;
}

void GCWManagerImplementation::registerGCWBase(BuildingObject* building, bool initializeBase) {
	if (!hasBase(building)) {
		if (building->getFaction() == Factions::FACTIONIMPERIAL)
			imperialBases++;
		else if (building->getFaction() == Factions::FACTIONREBEL)
			rebelBases++;

		if (initializeBase) {
			DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

			if (baseData == nullptr)
				return;

			ManagedReference<CreatureObject*> ownerCreature = building->getOwnerCreatureObject();

			if (ownerCreature == nullptr) {
				error("No owner when initializing a gcw base");
				return;
			}

			int delay = getInitialVulnerabilityDelay();

			Locker bLock(building, ownerCreature);

			initializeBaseTimers(building);

			if (delay == 0)
				initializeNewVulnerability(baseData);

			bLock.release();

			if (delay == 0) {
				Locker gLock(_this.getReferenceUnsafeStaticCast(), ownerCreature);
				addBase(building);
				startVulnerability(building);
			} else {
				Locker cLock(_this.getReferenceUnsafeStaticCast(), ownerCreature);
				Reference<Task*> newTask = new StartVulnerabilityTask(_this.getReferenceUnsafeStaticCast(), building);
				newTask->schedule(delay * 1000);
				addStartTask(building->getObjectID(), newTask);
			}
		} else {
			addBase(building);
			checkVulnerabilityData(building);
		}
	} else {
		error("Building already in gcwBaseList");
	}
}

void GCWManagerImplementation::unregisterGCWBase(BuildingObject* building) {
	if (hasBase(building)) {
		dropBase(building);

		if (building->getFaction() == Factions::FACTIONIMPERIAL)
			imperialBases--;

		else if (building->getFaction() == Factions::FACTIONREBEL)
			rebelBases--;
	}

	Reference<Task*> oldStartTask = getStartTask(building->getObjectID());
	if (oldStartTask != nullptr) {
		oldStartTask->cancel();
		dropStartTask(building->getObjectID());
	}

	Reference<Task*> oldEndTask = getEndTask(building->getObjectID());
	if (oldEndTask != nullptr) {
		oldEndTask->cancel();
		dropEndTask(building->getObjectID());
	}

	Reference<Task*> oldDestroyTask = getDestroyTask(building->getObjectID());
	if (oldDestroyTask != nullptr) {
		oldDestroyTask->cancel();
		dropDestroyTask(building->getObjectID());
	}
}

// pre: building is locked
// initializes times when a base is placed for the first time
void GCWManagerImplementation::initializeBaseTimers(BuildingObject* building) {
	// THESE WORK IF YOU DONT WANT A BASE VULN ON PLANT
	// IT DOES THE NEXT ONE
	/*
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	baseData->setPlacementTime(Time());
	baseData->setLastVulnerableTime(Time());

	Time nextTime;

	nextTime.addMiliTime(GCWManager::VULNERABILITYFREQUENCY*1000);
	baseData->setNextVulnerableTime(nextTime);

	nextTime.addMiliTime(GCWManager::VULNERABILITYDURATION*1000);
	baseData->setVulnerabilityEndTime(nextTime);

	baseData->setTerminalDamaged(false);
	baseData->setLastResetTime(Time(0)); // set it to a long, long time ago
	 */

	// try to do initial vuln on plant
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	baseData->setPlacementTime(Time());
	baseData->setLastVulnerableTime(Time());
	baseData->setNextVulnerableTime(Time());
	baseData->setVulnerabilityEndTime(Time());

	if (building->getPvpStatusBitmask() & CreatureFlag::OVERT) {
		Time endTime(baseData->getPlacementTime());
		endTime.addMiliTime((vulnerabilityDuration * 1000) + (getInitialVulnerabilityDelay() * 1000));
		baseData->setVulnerabilityEndTime(endTime);
	}

	baseData->setLastResetTime(Time(0)); // set it to a long, long time ago
}

void GCWManagerImplementation::addMinefield(BuildingObject* building, SceneObject* minefield) {
	if (building == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	Locker _lock(building);

	if (minefield != nullptr)
		baseData->addMinefield(baseData->getTotalMinefieldCount(), minefield->getObjectID());
	else
		baseData->addMinefield(baseData->getTotalMinefieldCount(), 0);

	verifyMinefields(building);
}

void GCWManagerImplementation::addScanner(BuildingObject* building, SceneObject* scanner) {
	if (building == nullptr || !ConfigManager::instance()->useCovertOvertSystem())
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	Locker _lock(building);

	if (scanner != nullptr)
		baseData->addScanner(baseData->getTotalScannerCount(), scanner->getObjectID());
	else
		baseData->addScanner(baseData->getTotalScannerCount(), 0);

	verifyScanners(building);
}

void GCWManagerImplementation::addTurret(BuildingObject* building, SceneObject* turret) {
	if (building == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	Locker _lock(building);

	if (turret != nullptr)
		baseData->addTurret(baseData->getTotalTurretCount(), turret->getObjectID());
	else {
		baseData->addTurret(baseData->getTotalTurretCount(), 0);
	}

	verifyTurrets(building);
}

void GCWManagerImplementation::addBaseAlarm(BuildingObject* building, SceneObject* alarm) {
	if (building == nullptr || alarm == nullptr) {
		return;
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return;
	}

	Locker _lock(building);

	String templateString = alarm->getObjectTemplate()->getTemplateFileName();

	if (baseData != nullptr) {
		if (templateString.contains("alarm_hack")) {
			baseData->addHackBaseAlarm(alarm->getObjectID());
		} else if (templateString.contains("alarm_destruct")) {
			baseData->addDestructBaseAlarm(alarm->getObjectID());
		}
	}
}

uint64 GCWManagerImplementation::spawnSecurityPatrol(BuildingObject* building, String &patrol, Vector3 &location, uint64 parentID, float direction, bool stationary, bool attackable) {
	if (zone == nullptr || patrol == "")
		return 0;

	Vector<String>* squadSpawns = nullptr;

	for (int i = 0; i < squadFormations.size(); i ++) {
		String formation = squadFormations.elementAt(i).getKey();

		// Check for proper faction and size in the squad string
		if (formation.hashCode() == patrol.hashCode()) {
			squadSpawns = squadFormations.elementAt(i).getValue();
			break;
		}
	}

	if (squadSpawns == nullptr || squadSpawns->size() <= 0) {
		return 0;
	}

	CreatureManager* creatureManager = zone->getCreatureManager();
	ManagedReference<SquadObserver*> squadObserver = new SquadObserver();

	if (creatureManager == nullptr || squadObserver == nullptr)
		return 0;

	AiAgent* squadLeader = nullptr;

	// Handle spawning squad in formation
	for (int j = 0; j < squadSpawns->size(); j++) {
		String spawn = squadSpawns->get(j);

		if (spawn == "")
			continue;

		float xOffset = 0.f;
		float yOffset = 0.f;

		if (j > 0) {
			if (j % 2) {
				xOffset = 0.5;
				yOffset = j* -1;
			} else {
				xOffset = -0.5;
				yOffset = (j - 1) * -1;
			}
		}

		// Get proper rotated coordinates
		float xOffsetRotated = xOffset * Math::cos(direction) + yOffset * Math::sin(direction);
		float yOffsetRotated = -xOffset * Math::sin(direction) + yOffset * Math::cos(direction);

		float x = location.getX() + xOffsetRotated;
		float y = location.getY() + yOffsetRotated;

		if (building != nullptr) {
			x += building->getPositionX();
			y += building->getPositionY();
		}

		float z = CollisionManager::getWorldFloorCollision(x, y, zone, false);

		AiAgent* agent = cast<AiAgent*>(creatureManager->spawnCreature(spawn.hashCode(), 0, x, z, y, 0, false, direction));

		if (agent == nullptr)
			continue;

		Locker lock(agent);

		// If gcw base is not null, add security patrols to the child creatures so they despawn if it is destroyed
		if (building != nullptr) {
			Locker bLocker(building, agent);
			building->addChildCreatureObject(agent);
		}

		if (!attackable)
			agent->setPvpStatusBitmask(0);

		squadObserver->addMember(agent);
		agent->registerObserver(ObserverEventType::SQUAD, squadObserver);

		if (j == 0) {
			squadLeader = agent;

			if (stationary) {
				squadLeader->addCreatureFlag(CreatureFlag::STATIC);
			} else {
				squadLeader->addCreatureFlag(CreatureFlag::SQUAD);
				squadLeader->setMovementState(AiAgent::PATROLLING);
			}

			// AI Template must be updated after the creature flags are set but before anything is written to Blackboard
			agent->setAITemplate();
			agent->clearPatrolPoints();
		} else {
			if (stationary) {
				agent->addCreatureFlag(CreatureFlag::STATIC);
			} else {
				agent->addCreatureFlag(CreatureFlag::FOLLOW);
				agent->addCreatureFlag(CreatureFlag::SQUAD);
			}

			agent->setAITemplate();
			agent->clearPatrolPoints();

			// Set their movement offset so they move in formation
			Vector3 formationOffset;
			formationOffset.setX(xOffset);
			formationOffset.setY(yOffset);
			agent->writeBlackboard("formationOffset", formationOffset);

			if (!stationary && squadLeader != nullptr) {
				Locker sLocker(squadLeader, agent);

				agent->setFollowObject(squadLeader);
				agent->setMovementState(AiAgent::FOLLOWING);
			}
		}
	}

	return squadLeader != nullptr ? squadLeader->getObjectID() : 0;
}

void GCWManagerImplementation::spawnBaseSecurityPatrols(BuildingObject* building) {
	if (building == nullptr)
		return;

	SharedBuildingObjectTemplate* baseTemplate = cast<SharedBuildingObjectTemplate*>(building->getObjectTemplate());

	if (baseTemplate == nullptr)
		return;

	int spawns = baseTemplate->getSecuritySpawnsSize();

	// Get the security spawns from the GCW base template
	for (int i = 0; i < spawns; i++) {
		const SecurityPatrolSpawn* patrolSpawn = baseTemplate->getSecurityPatrol(i);

		if (patrolSpawn == nullptr)
			continue;

		Vector3 location = patrolSpawn->getLocation();
		String patrol = patrolSpawn->getPatrol();

		float direction = building->getDirection()->getRadians();

		// Spawn each secuity patrol in the Vector
		spawnSecurityPatrol(building, patrol, location, 0, direction);
	}
}

// PRE: Nothing needs to be locked
// should only be called by the startvulnerabilityTask or when loading from the db in the middle of vuln
void GCWManagerImplementation::startVulnerability(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	renewUplinkBand(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	Locker block(building);
	baseData->setLastVulnerableTime(baseData->getNextVulnerableTime());
	block.release();

	dropStartTask(building->getObjectID());

	Locker block2(building);

	if (building->getZone() == nullptr)
		return;

	verifyMinefields(building);
	verifyScanners(building);
	verifyTurrets(building);

	spawnBaseTerminals(building);

	if (building->getPvpStatusBitmask() & CreatureFlag::OVERT)
		scheduleVulnerabilityEnd(building);

	building->broadcastCellPermissions();
}

// changes timers and schedules nextVulnerabilityStart task
void GCWManagerImplementation::endVulnerability(BuildingObject* building) {
	if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT))
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	Locker block(building);

	despawnBaseTerminals(building);

	Time nextTime = baseData->getNextVulnerableTime();

	baseData->setLastVulnerableTime(nextTime);

	while (nextTime.isPast()) {
		nextTime.addMiliTime(vulnerabilityFrequency * 1000);
	}

	baseData->setNextVulnerableTime(nextTime);
	nextTime.addMiliTime(vulnerabilityDuration * 1000);
	baseData->setVulnerabilityEndTime(nextTime);
	baseData->setState(DestructibleBuildingDataComponent::INVULNERABLE);
	baseData->setDefenseAddedThisVuln(false);

	block.release();

	if (!dropEndTask(building->getObjectID()))
		info("No endtask found to remove while scheduling new startvulnerability task", true);

	Reference<Task*> destroyTask = getDestroyTask(building->getObjectID());

	if (destroyTask != nullptr) {
		destroyTask->cancel();
		dropDestroyTask(building->getObjectID());
	}

	// schedule
	scheduleVulnerabilityStart(building);

	verifyMinefields(building);
	verifyScanners(building);
	verifyTurrets(building);

	deactivateBaseAlarms(building);
	building->broadcastCellPermissions();
}

void GCWManagerImplementation::initializeNewVulnerability(BuildingObject* building) {
	Locker _lock(building);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	initializeNewVulnerability(baseData);
}

// PRE:  building / objectdatacomponent are locked
void GCWManagerImplementation::initializeNewVulnerability(DestructibleBuildingDataComponent* baseData) {
	baseData->setTerminalDamaged(false);
	baseData->setState(DestructibleBuildingDataComponent::VULNERABLE);
	baseData->setDefenseAddedThisVuln(false);
}

// PRE: nothing needs to be locked!
void GCWManagerImplementation::scheduleVulnerabilityStart(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (!hasBase(building))
		return;

	if (baseData == nullptr)
		return;

	Time vulnTime = baseData->getNextVulnerableTime();
	int64 vulnDif = vulnTime.miliDifference();

	if (vulnDif >= 0)
		return;

	Reference<Task*> newTask = new StartVulnerabilityTask(_this.getReferenceUnsafeStaticCast(), building);
	newTask->schedule(llabs(vulnDif));
	addStartTask(building->getObjectID(), newTask);
}

// PRE:  nothing needs to be locked... building NOT locked
void GCWManagerImplementation::scheduleVulnerabilityEnd(BuildingObject* building) {
	if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT))
		return;

	if (!hasBase(building))
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	Time endTime = baseData->getVulnerabilityEndTime();
	int64 endDif = endTime.miliDifference();

	if (endDif >= 0)
		return;

	Reference<Task*> newTask = new EndVulnerabilityTask(_this.getReferenceUnsafeStaticCast(), building);
	newTask->schedule(llabs(endDif));
	addEndTask(building->getObjectID(), newTask);
}

// only call if the last expired time has already past and we need the timers
// back up to date.  usually after a long server down or something
void GCWManagerImplementation::refreshExpiredVulnerability(BuildingObject* building) {
	if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT))
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);
	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	Time thisStartTime(baseData->getLastVulnerableTime());

	while ((thisStartTime.getTime() + vulnerabilityFrequency) <= Time().getTime()) {
		int amountToAdd = vulnerabilityFrequency * 1000;
		thisStartTime.addMiliTime(amountToAdd);
	}

	// test time is the vulnerability end time for this current period.  it can be past or presetnt.
	Time testTime(thisStartTime);
	testTime.addMiliTime(vulnerabilityDuration * 1000);

	Locker block(building);

	if (!testTime.isPast()) {
		// if we're still in a vuln period
		info("Loaded while vulnerable in refresh", true);
		baseData->setLastVulnerableTime(thisStartTime);

		// testTime should the same thing as vEnd
		Time vEnd(thisStartTime);
		vEnd.addMiliTime((vulnerabilityDuration * 1000));
		baseData->setVulnerabilityEndTime(vEnd);

		Time nStartTime(thisStartTime);
		nStartTime.addMiliTime(vulnerabilityFrequency * 1000);
		baseData->setNextVulnerableTime(nStartTime);

		initializeNewVulnerability(baseData);
		spawnBaseTerminals(building);
		bool wasDropped = gcwStartTasks.drop(building->getObjectID());

		block.release();
		scheduleVulnerabilityEnd(building);
	} else {
		baseData->setLastVulnerableTime(thisStartTime);
		Time nStartTime(thisStartTime);
		nStartTime.addMiliTime(vulnerabilityFrequency * 1000);
		baseData->setNextVulnerableTime(nStartTime);

		Time vEnd(nStartTime);
		vEnd.addMiliTime(vulnerabilityDuration * 1000);
		baseData->setVulnerabilityEndTime(vEnd);

		baseData->setState(DestructibleBuildingDataComponent::INVULNERABLE);
		block.release();
		scheduleVulnerabilityStart(building);
	}

	renewUplinkBand(building);
}

// PRE: nothing locked
void GCWManagerImplementation::checkVulnerabilityData(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	if (building->getPvpStatusBitmask() & CreatureFlag::OVERT) {
		Time currentTime;
		Time vulnTime = baseData->getNextVulnerableTime();
		Time nextEnd = baseData->getVulnerabilityEndTime();

		if (!vulnTime.isPast()) {
			scheduleVulnerabilityStart(building);
		} else if (vulnTime.isPast() && !nextEnd.isPast()) {
			startVulnerability(building);
		} else if (nextEnd.isPast()) {
			refreshExpiredVulnerability(building);
		}
	} else {
		spawnBaseTerminals(building);

		//Resets PVE Bases state on server reset
		baseData->setState(DestructibleBuildingDataComponent::VULNERABLE);
	}

	if (baseData->getState() == DestructibleBuildingDataComponent::SHUTDOWNSEQUENCE) {
		scheduleBaseDestruction(building, nullptr);
	}
}

String GCWManagerImplementation::getVulnerableStatus(BuildingObject* building, CreatureObject* creature) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (creature == nullptr || baseData == nullptr)
		return "";

	double dif = 0;

	if (isBaseVulnerable(building)) {
		return "@player_structure:next_vulnerability_prompt Now";
	} else {
		dif = baseData->getNextVulnerableTime().getTime() - time(0);
	}

	int days = (int)floor(dif / 86400.f);
	dif = dif - (days * 86400);
	int hours = (int)floor(dif / 3600.f);
	dif = dif - (hours * 3600);
	int minutes = (int)ceil(dif / 60.f);

	return "@player_structure:next_vulnerability_prompt " + String::valueOf(days) + " days, " + String::valueOf(hours) + " hours, " + String::valueOf(minutes) +
		   " minutes";
}

bool GCWManagerImplementation::isBaseVulnerable(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() > DestructibleBuildingDataComponent::INVULNERABLE || !(building->getPvpStatusBitmask() & CreatureFlag::OVERT));
}

bool GCWManagerImplementation::isBandIdentified(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() >= DestructibleBuildingDataComponent::BAND);
}

bool GCWManagerImplementation::isUplinkJammed(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() >= DestructibleBuildingDataComponent::JAMMED);
}

bool GCWManagerImplementation::isTerminalDamaged(TangibleObject* securityTerminal) {
	if (securityTerminal == nullptr) {
		return true;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = securityTerminal->getObjectID();
	ZoneServer* zoneServer = securityTerminal->getZoneServer();

	if (zoneServer == nullptr) {
		return true;
	}

	switch (terminalID) {
		case 367428: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923854: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923864: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr) {
		return true;
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return true;

	return baseData->isTerminalDamaged();
}

bool GCWManagerImplementation::isSecurityTermSliced(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() >= DestructibleBuildingDataComponent::SLICED);
}

bool GCWManagerImplementation::isDNASampled(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() >= DestructibleBuildingDataComponent::DNA);
}

bool GCWManagerImplementation::isPowerOverloaded(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() == DestructibleBuildingDataComponent::OVERLOADED);
}

bool GCWManagerImplementation::isShutdownSequenceStarted(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() == DestructibleBuildingDataComponent::SHUTDOWNSEQUENCE);
}

bool GCWManagerImplementation::isFacilityRebooting(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return false;
	}

	return (baseData->getState() == DestructibleBuildingDataComponent::REBOOTSEQUENCE);
}

bool GCWManagerImplementation::isPlanetCapped() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	int totalBases = gcwBaseList.size();
	int totalPlayerBases = 0;

	for (int i = 0; i < totalBases; i++) {
		Reference<BuildingObject*> base = getBase(i);

		if (base == nullptr)
			continue;

		if (!(base->getFactionBaseType() == PLAYERFACTIONBASE))
			continue;

		totalPlayerBases++;
	}

	return maxBasesPerPlanet <= totalPlayerBases;
}

DestructibleBuildingDataComponent* GCWManagerImplementation::getDestructibleBuildingData(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = nullptr;

	if (building != nullptr && building->isGCWBase()) {
		DataObjectComponentReference* data = building->getDataObjectComponent();

		if (data != nullptr)
			baseData = cast<DestructibleBuildingDataComponent*>(data->get());
	}

	return baseData;
}

bool GCWManagerImplementation::canUseTerminals(CreatureObject* creature, BuildingObject* building, SceneObject* terminal) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return false;

	if (creature->isDead() || creature->isIncapacitated())
		return false;

	// Make sure the player is in the same cell & check distance for temrinals in large rooms
	uint64 creoParentID = creature->getParentID();
	uint64 terminalParentID = terminal->getParentID();

	if (creoParentID != terminalParentID || creature->getDistanceTo(terminal) > 5)  {
		creature->sendSystemMessage("@pvp_rating:ch_terminal_too_far"); // you are too far away from the terminal to use it
		return false;
	}

	if (ghost->isPrivileged())
		return true;

	// check for PvP base
	if (building->getPvpStatusBitmask() & CreatureFlag::OVERT) {
		if (creature->getFactionStatus() != FactionStatus::OVERT) {
			creature->sendSystemMessage("@hq:declared_only"); // Only Special Forces personnel may access this terminal!
			return false;
		}
	} else { // check for PvE base
		if (creature->getFactionStatus() < FactionStatus::COVERT) {
			// creature->sendSystemMessage("You must be at least combatant");
			return false;
		}
	}

	return true;
}

bool GCWManagerImplementation::areOpposingFactions(int faction1, int faction2) {
	if (faction1 == 0 || faction2 == 0)
		return false;

	return faction1 != faction2;
}

bool GCWManagerImplementation::isProperFactionStatus(CreatureObject* player) {
	if (player == nullptr || !player->isPlayerCreature())
		return false;

	if (ConfigManager::instance()->useCovertOvertSystem()) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr) {
			Locker lock(player);
			ghost->updateLastGcwPvpCombatActionTimestamp();
		}

		return true;
	}

	return player->getFactionStatus() > FactionStatus::ONLEAVE;
}

void GCWManagerImplementation::awardSlicingXP(CreatureObject* creature, const String& xpType, int val) {
	if (creature->getZoneServer() == nullptr)
		return;

	PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();

	if (playerManager == nullptr)
		return;

	playerManager->awardExperience(creature, xpType, val, true);
}

void GCWManagerImplementation::sendJamUplinkMenu(CreatureObject* creature, BuildingObject* building, TangibleObject* uplinkTerminal) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (ghost == nullptr || baseData == nullptr || uplinkTerminal == nullptr)
		return;

	if (!isBaseVulnerable(building))
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);

	status->setPromptTitle("JAMMING...");
	status->setUsingObject(uplinkTerminal);
	status->setOkButton(true, "@ok");
	status->setCancelButton(true, "@cancel");
	status->setCallback(new JamUplinkSuiCallback(zone->getZoneServer()));

	if (!isBandIdentified(building)) {
		status->setPromptText("Select the BAND that you wish to search.");

		for (int i = 0; i < 10; i++)
			status->addMenuItem("Band #" + String::valueOf(i + 1), 9);
	} else {
		status->setPromptText("Select the CHANNEL that you wish to search.");

		for (int i = 0; i < 10; i++)
			status->addMenuItem("Channel #" + String::valueOf(i + 1), 9);
	}

	ghost->addSuiBox(status);
	creature->sendSystemMessage("You begin scanning for baseline carrier signals...");
	creature->sendMessage(status->generateMessage());
}

void GCWManagerImplementation::verifyUplinkBand(CreatureObject* creature, BuildingObject* building, int band, TangibleObject* uplinkTerm) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (ghost == nullptr || baseData == nullptr) {
		return;
	}

	if (band == baseData->getUplinkBand()) {
		Locker block(building, creature);

		if (isBandIdentified(building)) {
			baseData->setState(DestructibleBuildingDataComponent::JAMMED);
			creature->sendSystemMessage("You isolate the carrier signal to Channel #" + String::valueOf(band + 1) + ".");
			creature->sendSystemMessage("Jamming complete! You disable the uplink...");
			awardSlicingXP(creature, "bountyhunter", 1000);

			//Schedule PVE base uplink reset
			if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
				GCWManager* gcwManager = zone->getGCWManager();

				UplinkTerminalResetTask* task = new UplinkTerminalResetTask(building, gcwManager, baseData);

				//Task Resets Base state 24 hours after uplink is jammed
				task->schedule(24 * 60 * 60 * 1000);
			}

			return;
		} else {
			baseData->setState(DestructibleBuildingDataComponent::BAND);
			creature->sendSystemMessage("You narrow the carrier signal down to Band #" + String::valueOf(band + 1) + ".");
		}
		renewUplinkBand(building);
		block.release();
	} else {
		int rand = System::random(300);

		if (rand >= 290) {
			creature->sendSystemMessage("You lose concentration and become lost in a sea of white noise...");
		} else if (band < baseData->getUplinkBand()) {
			creature->sendSystemMessage("You feel like you need to search higher...");
		} else {
			creature->sendSystemMessage("You feel like you need to search lower...");
		}
	}

	sendJamUplinkMenu(creature, building, uplinkTerm);
}

// PRE: no locks or only lock on building
// sets the bandwidth to guess during jamming of the uplink
void GCWManagerImplementation::renewUplinkBand(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	// 10 possible codes bands to guess
	int secretCode = System::random(0x9);

	Locker block(building);
	baseData->setUplinkBand(secretCode);
}

bool GCWManagerImplementation::canStartSlice(CreatureObject* creature, TangibleObject* tano) {
	if (tano == nullptr || creature == nullptr) {
		return false;
	}

	Locker _lock(creature);
	Locker clocker(tano, creature);

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = tano->getObjectID();
	ZoneServer* zoneServer = tano->getZoneServer();

	if (zoneServer == nullptr) {
		return false;
	}

	switch (terminalID) {
		case 367428: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923854: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923864: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = tano->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr) {
		return false;
	}

	if (!isBaseVulnerable(building))
		return false;

	if (!areOpposingFactions(creature->getFaction(), building->getFaction())) {
		creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_tamper"); // You are not an enemy of this structure. Why would you want to tamper?
		return false;
	} else if (isSecurityTermSliced(building)) {
		creature->sendSystemMessage("@slicing/slicing:not_again"); // There isn't anything more you can do to the terminal.
		return false;
	} else if (!isUplinkJammed(building)) {
		creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:other_objectives"); // Other objectives must be disabled prior to gaining access to this one.
		return false;
	} else if (creature->isInCombat()) {
		creature->sendSystemMessage("You cannot slice the terminal while you are in combat!");
		return false;
	} else if (tano->getParentID() != creature->getParentID()) {
		creature->sendSystemMessage("You cannot slice the terminal if you are not even in the same room!");
		return false;
	} else if (tano->getDistanceTo(creature) > 15) {
		creature->sendSystemMessage("You are too far away from the terminal to continue slicing!");
		return false;
	} else if (!creature->hasSkill("combat_smuggler_slicing_01")) {
		creature->sendSystemMessage("Only a smuggler with terminal slicing knowledge could expect to disable this security terminal!");
		return false;
	}

	return true;
}

// @pre: player is locked since called from Slicing session
// @post: player is locked
void GCWManagerImplementation::completeSecuritySlice(CreatureObject* creature, TangibleObject* securityTerminal) {
	if (securityTerminal == nullptr) {
		return;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = securityTerminal->getObjectID();
	ZoneServer* zoneServer = securityTerminal->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	switch (terminalID) {
		case 367428: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923854: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923864: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr) {
		return;
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	creature->sendSystemMessage("@slicing/slicing:hq_security_success"); // You have managed to slice into the terminal. The security protocol for the override terminal has been significantly relaxed.
	Locker block(building);
	baseData->setState(DestructibleBuildingDataComponent::SLICED);

	activateBaseAlarms(building, HACKALARM);
	spawnBaseSecurityPatrols(building);
}

void GCWManagerImplementation::failSecuritySlice(TangibleObject* securityTerminal) {
	if (securityTerminal == nullptr) {
		return;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = securityTerminal->getObjectID();
	ZoneServer* zoneServer = securityTerminal->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	switch (terminalID) {
		case 367428: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923854: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923864: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr)
		return;

	if (!isBaseVulnerable(building))
		return;

	Locker block(building);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	baseData->setTerminalBeingRepaired(false);
	baseData->setTerminalDamaged(true);
}

void GCWManagerImplementation::repairTerminal(CreatureObject* creature, TangibleObject* securityTerminal) {
	if (securityTerminal == nullptr || creature == nullptr) {
		return;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = securityTerminal->getObjectID();
	ZoneServer* zoneServer = securityTerminal->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	switch (terminalID) {
		case 367428: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923854: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923864: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		error("ERROR:  could not get base data for base");
		return;
	}

	if (!isBaseVulnerable(building) || !isTerminalDamaged(securityTerminal))
		return;

	if (baseData->isTerminalBeingRepaired()) {
		creature->sendSystemMessage("Terminal is already in the process of being repaired.");
	} else {
		creature->sendSystemMessage("You begin repairing the damage done by a prior slicing attempt...");
		SecurityRepairTask* repairTask = new SecurityRepairTask(_this.getReferenceUnsafeStaticCast(), securityTerminal, creature, 10);
		repairTask->schedule(5000);

		Locker locker(building);

		baseData->setTerminalBeingRepaired(true);
	}
}

void GCWManagerImplementation::sendDNASampleMenu(CreatureObject* creature, BuildingObject* building, TangibleObject* overrideTerminal) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (ghost == nullptr || baseData == nullptr || overrideTerminal == nullptr)
		return;

	if (!isBaseVulnerable(building))
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	if (baseData->getDnaStrand().size() == 0) {
		constructDNAStrand(building);
	}

	const Vector<String>& dnaStrand = baseData->getDnaStrand();
	const Vector<int>& dnaLocks = baseData->getDnaLocks();

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	status->setPromptTitle("DNA SEQUENCING");
	status->setUsingObject(overrideTerminal);
	status->setOkButton(true, "@ok");
	status->setCancelButton(true, "@cancel");

	int numLocks = 0;
	Vector<String> dnaEntries;

	for (int i = 0; i < dnaStrand.size(); i++) {
		const String& dna = dnaStrand.get(i);

		if (dnaLocks.get(i) == 0) {
			dnaEntries.add(dna);
		} else {
			numLocks++;
			for (int j = 0; j < dnaPairs.size(); j++) {
				const String& pair = dnaPairs.get(j);

				if (pair.beginsWith(dna)) {
					dnaEntries.add("\\#00FF00" + pair + " \\#.");
					break;
				}
			}
		}
	}

	String chain = baseData->getCurrentDnaChain();

	if (chain == "") {
		int length = 3;

		if (creature->hasSkill("outdoors_bio_engineer_master"))
			length = 8;
		else if (creature->hasSkill("outdoors_bio_engineer_dna_harvesting_04"))
			length = 7;
		else if (creature->hasSkill("outdoors_bio_engineer_dna_harvesting_03"))
			length = 6;
		else if (creature->hasSkill("outdoors_bio_engineer_dna_harvesting_02"))
			length = 5;
		else if (creature->hasSkill("outdoors_bio_engineer_dna_harvesting_01"))
			length = 4;

		for (int i = 0; i < length; i++) {
			chain += dnaNucleotides.get(System::random(dnaNucleotides.size() - 1));
		}
	}

	baseData->setCurrentDnaChain(chain);

	String prompt = "DNA Sequence Processing...\nComplete the missing pairs: AT,TA,GC,CG\nMatched Pairs: " + String::valueOf(numLocks) +
					"\nSampled Chain: " + chain + "\n\nSelect the DNA index to match the chain to...";
	status->setPromptText(prompt);

	for (int i = 0; i < dnaEntries.size(); i++)
		status->addMenuItem(dnaEntries.get(i), i);

	ghost->addSuiBox(status);
	status->setCallback(new OverrideTerminalSuiCallback(zone->getZoneServer()));
	creature->sendMessage(status->generateMessage());
}

void GCWManagerImplementation::processDNASample(CreatureObject* creature, TangibleObject* overrideTerminal, const int index) {
	if (overrideTerminal == nullptr) {
		return;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = overrideTerminal->getObjectID();
	ZoneServer* zoneServer = overrideTerminal->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	switch (terminalID) {
		case 367410: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923847: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923862: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = overrideTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr || creature == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	if (!isBaseVulnerable(building))
		return;

	if (isDNASampled(building)) {
		creature->sendSystemMessage("You stop sequencing as the fail-safe sequence has already been overridden.");
		return;
	}

	Locker clocker(building, creature);

	const Vector<String>& dnaStrand = baseData->getDnaStrand();
	Vector<int>& dnaLocks = baseData->getDnaLocks();
	int newLocks = 0;

	if (index > -1) {
		const String& chain = baseData->getCurrentDnaChain();

		for (int i = 0; i < chain.length(); i++) {
			int idx = index + i;

			if (idx < dnaStrand.size()) {
				String nucleotide = chain.subString(i, i + 1);
				String pair = dnaStrand.get(idx) + nucleotide;

				if (dnaLocks.get(idx) == 0 && dnaPairs.contains(pair)) {
					dnaLocks.set(idx, 1);
					newLocks++;
				}
			}
		}

		// baseData->setDnaLocks(dnaLocks); dnaLocks is a ref
	}

	int totalLocks = 0;

	for (int i = 0; i < dnaLocks.size(); i++) {
		if (dnaLocks.get(i) == 1)
			totalLocks++;
	}

	if (newLocks == 1) {
		creature->sendSystemMessage("You match 1 new set of nucleotides.");
	} else if (newLocks > 1) {
		creature->sendSystemMessage("You match " + String::valueOf(newLocks) + " new sets of nucleotides.");
	} else {
		creature->sendSystemMessage("You fail to match any new set of nucleotides.");
	}

	if (totalLocks == dnaLocks.size()) {
		creature->sendSystemMessage("Sequencing complete! You disable the security override for the facility...");
		baseData->setState(DestructibleBuildingDataComponent::DNA);
		awardSlicingXP(creature, "bio_engineer_dna_harvesting", 1000);
		constructDNAStrand(building);
		return;
	}

	baseData->setCurrentDnaChain("");
	creature->sendSystemMessage("\"Retrieving new DNA sample...\"");
	sendDNASampleMenu(creature, building, overrideTerminal);
}

void GCWManagerImplementation::constructDNAStrand(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	Vector<String> dnaStrand;

	for (int i = 0; i < dnaStrandLength; i++) {
		int randNucleotide = System::random(dnaNucleotides.size() - 1);
		dnaStrand.add(dnaNucleotides.get(randNucleotide));
	}

	baseData->setDnaStrand(dnaStrand);

	Vector<int> dnaLocks;

	for (int i = 0; i < dnaStrandLength; i++)
		dnaLocks.add(0);

	baseData->setDnaLocks(dnaLocks);
}

void GCWManagerImplementation::sendPowerRegulatorControls(CreatureObject* creature, BuildingObject* building, TangibleObject* powerRegulator) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (ghost == nullptr || baseData == nullptr)
		return;

	if (!isBaseVulnerable(building))
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	if (baseData->getPowerSwitchStates().size() == 0)
		randomizePowerRegulatorSwitches(building);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	status->setPromptTitle("@hq:mnu_set_overload"); // Set to Overload
	status->setUsingObject(powerRegulator);
	status->setOkButton(true, "@ok");
	status->setCancelButton(true, "@cancel");

	String prompt = "To successfully align the power flow to overload, you must activate all the flow regulators to ON.\n\n Select the switch to toggle...";

	status->setPromptText(prompt);
	status->setCallback(new PowerRegulatorSuiCallback(zone->getZoneServer()));

	for (int i = 0; i < powerSwitchCount; i++) {
		if (baseData->getPowerPosition(i))
			status->addMenuItem("Switch #" + String::valueOf(i + 1) + ": ON", i);
		else
			status->addMenuItem("Switch #" + String::valueOf(i + 1) + ": OFF", i);
	}

	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());
}

void GCWManagerImplementation::handlePowerRegulatorSwitch(CreatureObject* creature, TangibleObject* powerRegulator, int index) {
	if (powerRegulator == nullptr) {
		return;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = powerRegulator->getObjectID();
	ZoneServer* zoneServer = powerRegulator->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	switch (terminalID) {
		case 367432: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923849: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923861: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = powerRegulator->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr) {
		return;
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	if (!isBaseVulnerable(building))
		return;

	Locker block(building, creature);

	if (index < 0)
		return;

	Vector<bool> switchStates = baseData->getPowerSwitchStates();

	flipPowerSwitch(building, switchStates, index);

	baseData->setPowerSwitchStates(switchStates);

	bool checkStatus = true;

	for (int i = 0; i < powerSwitchCount; i++)
		checkStatus &= switchStates.get(i);

	if (checkStatus) {
		creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:alignment_complete"); // Alignment complete! The facility may now be set to overload from the primary terminal!
		baseData->setState(DestructibleBuildingDataComponent::OVERLOADED);
		awardSlicingXP(creature, "combat_rangedspecialize_heavy", 1000);
		randomizePowerRegulatorSwitches(building);
	} else {
		sendPowerRegulatorControls(creature, building, powerRegulator);
	}
}

void GCWManagerImplementation::randomizePowerRegulatorSwitches(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	createPowerRegulatorRules(building);

	Vector<bool> switchStates;

	for (int i = 0; i < powerSwitchCount; i++)
		switchStates.add(true);

	int numCycles = ((System::random(2) + 2) * 2) + 1; // 5 to 9 cycles

	for (int i = 0; i < numCycles; i++)
		flipPowerSwitch(building, switchStates, System::random(powerSwitchCount - 1));

	// Make sure the switches arent all set on
	bool doubleCheck = true;

	for (int i = 0; i < powerSwitchCount; i++)
		doubleCheck &= switchStates.get(i);

	if (doubleCheck)
		flipPowerSwitch(building, switchStates, System::random(powerSwitchCount - 1));

	baseData->setPowerSwitchStates(switchStates);
}

void GCWManagerImplementation::createPowerRegulatorRules(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	Vector<int> rules;

	for (int i = 0; i < powerSwitchCount; i++) {
		rules.add(System::random(powerSwitchCount - 1));
	}

	baseData->setPowerSwitchRules(rules);
}

void GCWManagerImplementation::flipPowerSwitch(BuildingObject* building, Vector<bool>& switchStates, int flipSwitch) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	const Vector<int>& rules = baseData->getPowerSwitchRules();

	switchStates.get(flipSwitch) = !switchStates.get(flipSwitch);

	int affectedSwitch = rules.get(flipSwitch);

	switchStates.get(affectedSwitch) = !switchStates.get(affectedSwitch);
}

void GCWManagerImplementation::scheduleBaseDestruction(BuildingObject* building, CreatureObject* creature, bool force) {
	if ((force || isBaseVulnerable(building)) && !hasDestroyTask(building->getObjectID())) {
		DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

		if (baseData == nullptr)
			return;

		if (isFacilityRebooting(building)) {
			if (creature != nullptr)
				creature->sendSystemMessage("You must wait for the facility to reboot before activating the overload again.");

			return;
		}

		Locker block(building);

		StringIdChatParameter destroyMessage("@faction/faction_hq/faction_hq_response:terminal_response40"); // COUNTDOWN INITIATED: estimated time to detonation: %DI minutes.
		int minutesRemaining = (int)ceil((double)destructionTimer / (double)60);
		destroyMessage.setDI(minutesRemaining);
		broadcastBuilding(building, destroyMessage);
		baseData->setState(DestructibleBuildingDataComponent::SHUTDOWNSEQUENCE);
		block.release();

		Reference<Task*> newTask = new BaseDestructionTask(_this.getReferenceUnsafeStaticCast(), building);
		newTask->schedule(60000);
		addDestroyTask(building->getObjectID(), newTask);

		activateBaseAlarms(building, DESTRUCTALARM);
	}
}

void GCWManagerImplementation::doBaseDestruction(StructureObject* structure) {
	if (structure == nullptr)
		return;

	BuildingObject* building = cast<BuildingObject*>(structure);

	if (building != nullptr)
		doBaseDestruction(building);
}

void GCWManagerImplementation::doBaseDestruction(BuildingObject* building) {
	if (building == nullptr)
		return;

	Reference<Task*> oldEndTask = getDestroyTask(building->getObjectID());

	if (oldEndTask != nullptr) {
		BaseDestructionTask* dTask = cast<BaseDestructionTask*>(oldEndTask.get());
		if (dTask != nullptr && dTask->getCountdown() > 0) {
			oldEndTask->reschedule(60000);
			StringIdChatParameter msg("@faction/faction_hq/faction_hq_response:terminal_response39"); // Countdown: Estimated time to detonation: %DI minutes
			int minutesRemaining = dTask->getCountdown();
			msg.setDI(minutesRemaining);
			broadcastBuilding(building, msg);
			return;
		}
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	// need to lock both.  building must be locked for destroyStructure() and then _this is locked when it calls unregister.
	Locker locker(_this.getReferenceUnsafeStaticCast());
	Locker block(building, _this.getReferenceUnsafeStaticCast());

	int baseType = building->getFactionBaseType();

	if (baseType == STATICFACTIONBASE) {
		building->notifyObservers(ObserverEventType::FACTIONBASEFLIPPED);
		return;
	} else if (baseType == PLAYERFACTIONBASE) {
		ManagedReference<CreatureObject*> owner = building->getOwnerCreatureObject();

		if (owner != nullptr && owner->isPlayerCreature()) {
			int baseCount = getBaseCount(owner);
			int maxCount = getMaxBasesPerPlayer();

			StringIdChatParameter message;

			if (maxCount == baseCount) {
				message.setStringId("@faction_perk:faction_base_refunded_one"); // A faction base you placed has been destroyed and you have been refunded a base unit. You can now place an additional base.
			} else if (baseCount < maxCount) {
				message.setStringId("@faction_perk:faction_base_unit_refunded"); // A faction base you placed has been destroyed and you have been refunded a base unit. You can now place up to %DI bases.
				message.setDI((maxCount - baseCount) + 1);
			}

			owner->sendSystemMessage(message);
		}
	}

	unregisterGCWBase(building);

	StructureManager::instance()->destroyStructure(building, true);
}

void GCWManagerImplementation::broadcastBuilding(BuildingObject* building, StringIdChatParameter& params) {
	// Default range of broadcast
	float range = 64;

	if (zone == nullptr)
		return;

	SortedVector<QuadTreeEntry*> closeObjects;
	if (building->getCloseObjects() == nullptr) {
#ifdef COV_DEBUG
		building->info("Null closeobjects vector in GCWManagerImplementation::broadcastBuilding", true);
#endif
		zone->getInRangeObjects(building->getPositionX(), building->getPositionY(), range, &closeObjects, true);
	} else {
		CloseObjectsVector* closeVector = (CloseObjectsVector*)building->getCloseObjects();
		closeVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);
	}

	// send message to all the players in range
	for (int i = 0; i < closeObjects.size(); i++) {
		SceneObject* targetObject = static_cast<SceneObject*>(closeObjects.get(i));

		if (targetObject->isPlayerCreature() && building->isInRange(targetObject, range)) {
			CreatureObject* targetPlayer = cast<CreatureObject*>(targetObject);

			if (targetPlayer != nullptr)
				targetPlayer->sendSystemMessage(params);
		}
	}
}

void GCWManagerImplementation::startAbortSequenceDelay(BuildingObject* building, CreatureObject* creature, SceneObject* hqTerminal) {
	if (!creature->checkCooldownRecovery("declare_overt_cooldown")) {
		StringIdChatParameter params("@faction/faction_hq/faction_hq_response:terminal_response41"); // You have recently joined Special Forces. Before issuing the shutdown command, you must wait %TO
		const Time* cooldownTimer = creature->getCooldownTime("declare_overt_cooldown");
		int minutes = ceil(cooldownTimer->miliDifference() / -60000.f);
		params.setTO(String::valueOf(minutes) + " minutes.");
		creature->sendSystemMessage(params);
		return;
	}

	creature->sendSystemMessage("@hq:vulnerability_reset_request_received"); // Structure shutdown request received. Please stand by while the command is processed. Remain with the terminal.
	Reference<Task*> newTask = new BaseShutdownTask(_this.getReferenceUnsafeStaticCast(), building, creature, hqTerminal);
	creature->addPendingTask("base_shutdown", newTask, 60000);

	GCWBaseShutdownObserver* observer = new GCWBaseShutdownObserver();
	observer->setObserverType(ObserverType::GCWBASESHUTDOWN);
	creature->registerObserver(ObserverEventType::PARENTCHANGED, observer);
	creature->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
}

void GCWManagerImplementation::abortShutdownSequence(BuildingObject* building, CreatureObject* creature) {
	if (isBaseVulnerable(building) && hasDestroyTask(building->getObjectID())) {
		Reference<Task*> oldDestroyTask = getDestroyTask(building->getObjectID());
		if (oldDestroyTask != nullptr) {
			oldDestroyTask->cancel();
			dropDestroyTask(building->getObjectID());
		}

		DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

		if (baseData == nullptr)
			return;

		Locker block(building);

		baseData->setState(DestructibleBuildingDataComponent::REBOOTSEQUENCE);
		StringIdChatParameter reloadMessage;
		reloadMessage.setStringId("@faction/faction_hq/faction_hq_response:terminal_response07"); // COUNTDOWN ABORTED: FACILITY SHUTTING DOWN!!
		broadcastBuilding(building, reloadMessage);

		Reference<Task*> newTask = new BaseRebootTask(_this.getReferenceUnsafeStaticCast(), building, baseData);
		newTask->schedule(60000);

		deactivateBaseAlarms(building);
	}
}

// time of the day
void GCWManagerImplementation::resetVulnerability(CreatureObject* creature, BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	if (isBaseVulnerable(building))
		return;

	if (!hasResetTimerPast(building))
		return;

	Locker clock(building, creature);

	debug() << "Resetting vulnerability timer";

	baseData->setLastResetTime(Time());

	Time nextTime = Time();

	clock.release();

	Locker glock(_this.getReferenceUnsafeStaticCast(), creature);
	baseData->setLastVulnerableTime(nextTime);

	nextTime.addMiliTime(vulnerabilityFrequency * 1000);
	baseData->setNextVulnerableTime(nextTime);

	nextTime.addMiliTime(vulnerabilityDuration * 1000);
	baseData->setVulnerabilityEndTime(nextTime);

	Reference<Task*> task = getStartTask(building->getObjectID());
	if (task != nullptr) {
		task->cancel();
		dropStartTask(building->getObjectID());
	}

	scheduleVulnerabilityStart(building);

	if (creature != nullptr)
		creature->sendSystemMessage("@hq:vulnerability_reset"); // The vulnerability for this structure has been reset.
}

bool GCWManagerImplementation::hasResetTimerPast(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return false;

	Time ttime = baseData->getLastResetTime();

	ttime.addMiliTime(resetTimer * 1000);

	return ttime.isPast();
}

void GCWManagerImplementation::sendBaseDefenseStatus(CreatureObject* creature, BuildingObject* building) {
	ZoneServer* zoneServer = zone->getZoneServer();
	if (zoneServer == nullptr)
		return;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);
	if (ghost == nullptr || baseData == nullptr)
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	if (building->getOwnerCreatureObject() != creature && !ghost->isPrivileged())
		return;

	if (baseData->getTotalTurretCount() == 0) {
		creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:terminal_response16"); // There are currently no active defenses for this headquarters.
		return;
	}

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	status->setPromptTitle("@faction/faction_hq/faction_hq_response:terminal_response22"); // HQ Defense status

	if (building->getPvpStatusBitmask() & CreatureFlag::OVERT)
		status->setPromptText("@faction/faction_hq/faction_hq_response:terminal_response21"); // If you want to remove a defense select it and press remove

	status->setUsingObject(building);
	status->setCancelButton(true, "@cancel");

	if (creature == building->getOwnerCreatureObject() && (building->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
		status->setOtherButton(true, "@ui:permission_remove");
	}
	status->setOkButton(true, "@ok");
	status->setCallback(new HQDefenseStatusSuiCallback(zone->getZoneServer()));

	for (int i = 0; i < baseData->getTotalTurretCount(); i++) {
		ManagedReference<SceneObject*> sceno = zoneServer->getObject(baseData->getTurretID(i));

		if (sceno != nullptr && sceno->isTurret()) {
			status->addMenuItem(sceno->getDisplayedName(), sceno->getObjectID());
		}
	}

	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());
}

void GCWManagerImplementation::sendRemoveDefenseConfirmation(BuildingObject* building, CreatureObject* creature, uint64 deedOID) {
	ZoneServer* zoneServer = zone->getZoneServer();
	if (zoneServer == nullptr)
		return;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (ghost == nullptr || baseData == nullptr)
		return;

	if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT))
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	if (building->getOwnerCreatureObject() != creature)
		return;

	if (!baseData->hasDefense(deedOID))
		return;

	ManagedReference<SceneObject*> defense = zoneServer->getObject(deedOID);

	if (defense == nullptr)
		return;

	StringBuffer text;
	text << "@faction/faction_hq/faction_hq_response:terminal_response25 " << endl << endl;				// Are you sure you want to remove the selected defense?
	text << "@faction/faction_hq/faction_hq_response:selected_defense " << defense->getDisplayedName(); // Selected Defense:

	ManagedReference<SuiMessageBox*> removeDefense = new SuiMessageBox(creature, SuiWindowType::HQ_TERMINAL);
	removeDefense->setPromptTitle("@faction/faction_hq/faction_hq_response:terminal_response24"); // Confirm Defense Removal?
	removeDefense->setPromptText(text.toString());
	removeDefense->setUsingObject(building);
	removeDefense->setOkButton(true, "@ok");
	removeDefense->setCancelButton(true, "@cancel");
	removeDefense->setCallback(new RemoveDefenseSuiCallback(zone->getZoneServer(), deedOID));

	ghost->addSuiBox(removeDefense);
	creature->sendMessage(removeDefense->generateMessage());
}

void GCWManagerImplementation::removeDefense(BuildingObject* building, CreatureObject* creature, uint64 deedOID) {
	ZoneServer* zoneServer = zone->getZoneServer();

	if (zoneServer == nullptr)
		return;

	if (building->getOwnerCreatureObject() != creature)
		return;

	if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT))
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr || !baseData->hasDefense(deedOID))
		return;

	ManagedReference<SceneObject*> defense = zoneServer->getObject(deedOID);

	if (defense == nullptr || !defense->isTurret())
		return;

	InstallationObject* turret = cast<InstallationObject*>(defense.get());

	creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:terminal_response58"); // Processing HQ defense removal...

	notifyInstallationDestruction(turret);
}

void GCWManagerImplementation::notifyInstallationDestruction(InstallationObject* installation) {
	if (installation == nullptr)
		return;

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", zone->getZoneName(), installation->getPositionX(),
															  installation->getPositionZ(), installation->getPositionY());
	installation->broadcastMessage(explodeLoc, false);

	uint64 ownerid = installation->getOwnerObjectID();

	ZoneServer* server = zone->getZoneServer();

	if (server == nullptr)
		return;

	Reference<SceneObject*> ownerObject = server->getObject(ownerid);

	if (ownerObject == nullptr) {
		PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", zone->getZoneName(), installation->getPositionX(),
																  installation->getPositionZ(), installation->getPositionY());
		installation->broadcastMessage(explodeLoc, false);

		Locker _lock(installation);
		installation->destroyObjectFromWorld(true);
		installation->destroyObjectFromDatabase(true);

		return;
	}

	if (ownerObject->isGCWBase()) {
		BuildingObject* building = cast<BuildingObject*>(ownerObject.get());

		Locker _lock(installation);

		if (building != nullptr) {
			Locker clock(building, installation);

			if (building->containsChildObject(installation)) {
				building->getChildObjects()->removeElement(installation);
			}

			DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

			if (baseData != nullptr && baseData->hasTurret(installation->getObjectID())) {
				if (installation->isTurret())
					notifyTurretDestruction(building, installation);
			} else if (baseData != nullptr && baseData->hasMinefield(installation->getObjectID())) {
				if (installation->isMinefield())
					notifyMinefieldDestruction(building, installation);
			} else if (baseData != nullptr && baseData->hasScanner(installation->getObjectID())) {
				if (installation->isScanner())
					notifyScannerDestruction(building, installation);
			} else {
				clock.release();
				StructureManager::instance()->destroyStructure(installation);
			}
		} else {
			StructureManager::instance()->destroyStructure(installation);
		}
	} else if (ownerObject->isCreatureObject()) {
		Locker plock(ownerObject);
		Locker tlock(installation, ownerObject);
		StructureManager::instance()->destroyStructure(installation);
		tlock.release();
		plock.release();
	}
}

void GCWManagerImplementation::notifyTurretDestruction(BuildingObject* building, InstallationObject* turret) {
	if (building == nullptr || turret == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	int indx = baseData->getIndexOfTurret(turret->getObjectID());

	if (indx < 0)
		return;

	baseData->setTurretID(indx, 0);

	turret->destroyObjectFromWorld(true);
	turret->destroyObjectFromDatabase(true);

	verifyTurrets(building);
}

void GCWManagerImplementation::notifyMinefieldDestruction(BuildingObject* building, InstallationObject* minefield) {
	if (building == nullptr || minefield == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	int indx = baseData->getIndexOfMinefield(minefield->getObjectID());

	if (indx < 0)
		return;

	baseData->setMinefieldID(indx, 0);

	minefield->destroyObjectFromWorld(true);
	minefield->destroyObjectFromDatabase(true);

	verifyMinefields(building);
}

void GCWManagerImplementation::notifyScannerDestruction(BuildingObject* building, InstallationObject* scanner) {
	if (building == nullptr || scanner == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	int indx = baseData->getIndexOfScanner(scanner->getObjectID());

	if (indx < 0)
		return;

	baseData->setScannerID(indx, 0);

	scanner->destroyObjectFromWorld(true);
	scanner->destroyObjectFromDatabase(true);

	verifyScanners(building);
}

void GCWManagerImplementation::sendSelectDeedToDonate(BuildingObject* building, CreatureObject* creature) {
	if (building == nullptr || creature == nullptr)
		return;

	Locker lock (building);

	if (!building->checkCooldownRecovery("defense_donation")) {
		creature->sendSystemMessage("This GCW base cannot have more defenses donated at this time.");
		return;
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return;

	if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT))
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SceneObject*> inv = creature->getSlottedObject("inventory");

	if (inv == nullptr)
		return;

	ManagedReference<SuiListBox*> donate = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);

	donate->setPromptTitle("@faction/faction_hq/faction_hq_response:terminal_response26"); // Donate Deed
	donate->setPromptText("@faction/faction_hq/faction_hq_response:terminal_response23");  // Which deed would you like to donate?
	donate->setUsingObject(building);
	donate->setOkButton(true, "@ok");
	donate->setCancelButton(true, "@cancel");
	donate->setCallback(new DonateDefenseSuiCallback(zone->getZoneServer()));

	for (int i = 0; i < inv->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> inventoryObject = inv->getContainerObject(i);

		if (inventoryObject->isDeedObject()) {
			ManagedReference<Deed*> deed = dynamic_cast<Deed*>(inventoryObject.get());

			if (deed != nullptr) {
				Reference<SharedObjectTemplate*> generatedTemplate = TemplateManager::instance()->getTemplate(deed->getGeneratedObjectTemplate().hashCode());

				if (generatedTemplate == nullptr)
					continue;

				int objectType = generatedTemplate->getGameObjectType();

				if (!ConfigManager::instance()->useCovertOvertSystem() && objectType == SceneObjectType::COVERTSCANNER)
					continue;

				if (objectType == SceneObjectType::MINEFIELD || objectType == SceneObjectType::DESTRUCTIBLE || objectType == SceneObjectType::COVERTSCANNER) {
					donate->addMenuItem(inventoryObject->getDisplayedName(), inventoryObject->getObjectID());
				}
			}
		}
	}

	if (donate->getMenuSize() == 0) {
		creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:terminal_response15"); // You do not possess any deeds to donate.
	} else {
		ghost->addSuiBox(donate);
		creature->sendMessage(donate->generateMessage());
	}
}

void GCWManagerImplementation::performDefenseDonation(BuildingObject* building, CreatureObject* creature, uint64 deedOID) {
	if (building == nullptr || creature == nullptr)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();

	if (zoneServer == nullptr)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return;

	if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT))
		return;

	ManagedReference<SceneObject*> defenseObj = zoneServer->getObject(deedOID);

	if (defenseObj == nullptr) {
		creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:terminal_response13"); // The selected defense is not available. Cancelling...
		return;
	}

	if (!defenseObj->isASubChildOf(creature)) {
		creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:terminal_response09"); // The selected deed is no longer in your inventory. Cancelling donation...
		return;
	}

	if (isBaseVulnerable(building) && baseData->wasDefenseAddedThisVuln() && !ghost->isPrivileged()) {
		StringIdChatParameter message;
		message.setStringId("@hq:under_attack"); // You cannot add defenses while this HQ is under attack. This function will be restored in %TO.

		int minutes = (baseData->getVulnerabilityEndTime().getTime() - Time().getTime()) / 60;
		String duration = String::valueOf(minutes) + " minutes";
		message.setTO(duration);

		creature->sendSystemMessage(message);
		return;
	}

	if (!defenseObj->isDeedObject())
		return;

	ManagedReference<Deed*> deed = dynamic_cast<Deed*>(defenseObj.get());

	if (deed == nullptr)
		return;

	Reference<SharedObjectTemplate*> generatedTemplate = TemplateManager::instance()->getTemplate(deed->getGeneratedObjectTemplate().hashCode());

	if (generatedTemplate == nullptr)
			return;

	const int objectType = generatedTemplate->getGameObjectType();

	if (objectType == SceneObjectType::MINEFIELD) {
		performDonateMinefield(building, creature, deed);
		return;
	} else if (objectType == SceneObjectType::COVERTSCANNER) {
		performDonateScanner(building, creature, deed);
		return;
	} else if (objectType == SceneObjectType::DESTRUCTIBLE) {
		performDonateTurret(building, creature, deed);
		return;
	} else {
		StringIdChatParameter param("@faction/faction_hq/faction_hq_response:terminal_response43"); // This facility does not accept deeds of type '%TO'. Cancelling donation..."
		param.setTO(defenseObj->getObjectName());
		creature->sendSystemMessage(param);
	}
}

void GCWManagerImplementation::performDonateMinefield(BuildingObject* building, CreatureObject* creature, Deed* deed) {
	String serverTemplatePath = deed->getGeneratedObjectTemplate();
	TemplateManager* templateManager = TemplateManager::instance();
	Reference<SharedObjectTemplate*> baseServerTemplate = building->getObjectTemplate();
	Reference<SharedObjectTemplate*> minefieldTemplate = nullptr;
	const ChildObject* child = nullptr;

	int currentMinefieldIndex = 0;

	Locker block(building, creature);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	// go through it and inf the first available mine
	int minefieldIndex = 0;
	for (minefieldIndex = 0; minefieldIndex < baseData->getTotalMinefieldCount(); minefieldIndex++) {
		if (baseData->getMinefieldID(minefieldIndex) == 0)
			break;
	}

	// Minefield donation
	int nextAvailableMinefield = 0;

	for (nextAvailableMinefield = 0; nextAvailableMinefield < baseData->getTotalTurretCount(); nextAvailableMinefield++) {
		if (baseData->getMinefieldID(nextAvailableMinefield) == 0)
			break;
	}

	if (nextAvailableMinefield >= baseData->getTotalMinefieldCount()) {
		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response44"); // This facility cannot accept deeds of type '%TO' at this time. Cancelling donation...
		params.setTO(deed->getObjectNameStringIdFile(), deed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);
		return;
	}

	// now find the coords of the nth minefield
	for (int i = 0; i < baseServerTemplate->getChildObjectsSize(); ++i) {
		child = baseServerTemplate->getChildObject(i);
		minefieldTemplate = nullptr;

		if (child != nullptr) {
			minefieldTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());

			if (minefieldTemplate != nullptr && minefieldTemplate->getGameObjectType() == SceneObjectType::MINEFIELD) {
				if (currentMinefieldIndex == nextAvailableMinefield) {
					break;
				} else {
					currentMinefieldIndex++;
				}
			}
		}
	}

	if (child == nullptr || minefieldTemplate == nullptr || minefieldTemplate->getGameObjectType() != SceneObjectType::MINEFIELD)
		return;

	uint64 minefieldID = addChildInstallationFromDeed(building, child, creature, deed);

	if (minefieldID > 0) {
		baseData->setMinefieldID(currentMinefieldIndex, minefieldID);

		if (isBaseVulnerable(building))
			baseData->setDefenseAddedThisVuln(true);

		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response45"); //"You successfully donate a %TO deed to the current facility."
		params.setTO(deed->getObjectNameStringIdFile(), deed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);

		building->addCooldown("defense_donation", donationCooldown * 1000);

		block.release();
		verifyMinefields(building);

		Locker clock(deed, creature);
		deed->destroyObjectFromWorld(true);
	}
}

void GCWManagerImplementation::performDonateScanner(BuildingObject* building, CreatureObject* creature,  Deed* scannerDeed) {
	if (building == nullptr || creature == nullptr || scannerDeed == nullptr)
		return;

	String serverTemplatePath = scannerDeed->getGeneratedObjectTemplate();
	TemplateManager* templateManager = TemplateManager::instance();
	Reference<SharedObjectTemplate*> baseServerTemplate = building->getObjectTemplate();

	Reference<SharedObjectTemplate*> scannerTemplate = nullptr;
	const ChildObject* child = nullptr;
	int currentScannerIndex = 0;

	Locker block(building,creature);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	int nextAvailableScanner = 0;

	for (nextAvailableScanner = 0; nextAvailableScanner < baseData->getTotalScannerCount(); nextAvailableScanner++) {
		uint64 scannerID = baseData->getScannerID(nextAvailableScanner);

		if (scannerID == 0)
			break;
	}

	if (nextAvailableScanner >= baseData->getTotalScannerCount()) {
		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response44"); // This facility cannot accept deeds of type '%TO' at this time. Cancelling donation...
		params.setTO(scannerDeed->getObjectNameStringIdFile(), scannerDeed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);
		return;
	}

	for (int i = 0; i < baseServerTemplate->getChildObjectsSize(); ++i) {
		child = baseServerTemplate->getChildObject(i);
		scannerTemplate = nullptr;

		if (child != nullptr) {
			scannerTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());

			if (scannerTemplate != nullptr && scannerTemplate->getGameObjectType() == SceneObjectType::COVERTSCANNER) {
				if (currentScannerIndex == nextAvailableScanner) {
					break;
				} else {
					currentScannerIndex++;
				}
			} else {
				info("Invalid scanner template: " + child->getTemplateFile());
			}
		}
	}

	if (child == nullptr || scannerTemplate == nullptr) {
		return;
	}

	uint64 scannerOID = addChildInstallationFromDeed(building, child, creature, scannerDeed);

	if (scannerOID > 0) {
		baseData->setScannerID(currentScannerIndex, scannerOID);

		if (isBaseVulnerable(building))
			baseData->setDefenseAddedThisVuln(true);

		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response45");  //"You successfully donate a %TO deed to the current facility."
		params.setTO(scannerDeed->getObjectNameStringIdFile(), scannerDeed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);

		building->addCooldown("defense_donation", donationCooldown * 1000);

		block.release();
		verifyScanners(building);

		Locker clock(scannerDeed, creature);
		scannerDeed->destroyObjectFromWorld(true);
	}
}

void GCWManagerImplementation::performDonateTurret(BuildingObject* building, CreatureObject* creature, Deed* turretDeed) {
	String serverTemplatePath = turretDeed->getGeneratedObjectTemplate();
	TemplateManager* templateManager = TemplateManager::instance();
	Reference<SharedObjectTemplate*> baseServerTemplate = building->getObjectTemplate();

	Reference<SharedObjectTemplate*> turretTemplate = nullptr;
	const ChildObject* child = nullptr;
	int currentTurretIndex = 0;

	Locker block(building, creature);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	// search through the baseData to find the first empty turret index
	int nextAvailableTurret = 0;
	for (nextAvailableTurret = 0; nextAvailableTurret < baseData->getTotalTurretCount(); nextAvailableTurret++) {
		uint64 turretID = baseData->getTurretID(nextAvailableTurret);

		if (turretID == 0)
			break;
	}

	if (nextAvailableTurret >= baseData->getTotalTurretCount()) {
		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response44"); // This facility cannot accept deeds of type '%TO' at this time. Cancelling donation...
		params.setTO(turretDeed->getObjectNameStringIdFile(), turretDeed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);
		return;
	}

	// now find the coords of the nth turret
	for (int i = 0; i < baseServerTemplate->getChildObjectsSize(); ++i) {
		child = baseServerTemplate->getChildObject(i);
		turretTemplate = nullptr;

		if (child != nullptr) {
			turretTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());

			if (turretTemplate != nullptr && turretTemplate->getGameObjectType() == SceneObjectType::DESTRUCTIBLE) {
				if (currentTurretIndex == nextAvailableTurret) {
					break;
				} else {
					currentTurretIndex++;
				}
			}
		}
	}

	if (child == nullptr || turretTemplate == nullptr || turretTemplate->getGameObjectType() != SceneObjectType::DESTRUCTIBLE)
		return;

	uint64 turretID = addChildInstallationFromDeed(building, child, creature, turretDeed);

	if (turretID > 0) {
		baseData->setTurretID(currentTurretIndex, turretID);

		if (isBaseVulnerable(building))
			baseData->setDefenseAddedThisVuln(true);

		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response45"); // You successfully donate a %TO deed to the current facility.
		params.setTO(turretDeed->getObjectNameStringIdFile(), turretDeed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);

		building->addCooldown("defense_donation", donationCooldown * 1000);

		block.release();
		verifyTurrets(building);

		Locker clock(turretDeed, creature);
		turretDeed->destroyObjectFromWorld(true);
	}
}

uint64 GCWManagerImplementation::addChildInstallationFromDeed(BuildingObject* building, const ChildObject* child, CreatureObject* creature, Deed* deed) {
	Vector3 position = building->getPosition();

	const Quaternion* direction = building->getDirection();
	Vector3 childPosition = child->getPosition();
	float angle = direction->getRadians();

	float x = (Math::cos(angle) * childPosition.getX()) + (childPosition.getY() * Math::sin(angle));
	float y = (Math::cos(angle) * childPosition.getY()) - (childPosition.getX() * Math::sin(angle));

	x += position.getX();
	y += position.getY();

	float z = position.getZ() + childPosition.getZ();

	float degrees = direction->getDegrees();
	Quaternion dir = child->getDirection();

	ManagedReference<SceneObject*> obj = zone->getZoneServer()->createObject(deed->getGeneratedObjectTemplate().hashCode(), building->getPersistenceLevel());

	if (obj == nullptr) {
		return 0;
	}

	Locker locker(obj);

	obj->initializePosition(x, z, y);
	obj->setDirection(dir.rotate(Vector3(0, 1, 0), degrees));

	if (!obj->isTangibleObject()) {
		obj->destroyObjectFromDatabase(true);
		return 0;
	}

	TangibleObject* tano = cast<TangibleObject*>(obj.get());

	if (tano != nullptr) {
		tano->setFaction(building->getFaction());
		tano->setPvpStatusBitmask(building->getPvpStatusBitmask() | tano->getPvpStatusBitmask());

		if (tano->isTurret())
			tano->setDetailedDescription("Donated Turret");

		if (tano->isInstallationObject()) {
			InstallationObject* instObject = cast<InstallationObject*>(tano);

			if (instObject != nullptr) {
				instObject->setOwner(building->getObjectID());
				instObject->createChildObjects();
				instObject->setDeedObjectID(deed->getObjectID());
			}
		}
	}

	zone->transferObject(obj, -1, true);
	building->getChildObjects()->put(obj);

	return obj->getObjectID();
}

void GCWManagerImplementation::sendTurretAttackListTo(CreatureObject* creature, SceneObject* turretControlTerminal) {
	if (turretControlTerminal == nullptr || creature == nullptr || creature->isInCombat())
		return;

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TURRET_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);

	ManagedReference<BuildingObject*> building = turretControlTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();

	if (building == nullptr)
		return;

	// get the base data component
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr)
		return;

	TurretControlTerminalDataComponent* controlData = getTurretControlDataComponent(turretControlTerminal);

	if (controlData == nullptr)
		return;

	uint64 tindex = baseData->getTurretID(controlData->getTurrteIndex());

	if (tindex == 0 || controlData->getTurrteIndex() < 0) {
		creature->sendSystemMessage("@hq:none_active"); //  There are no available turrets to control using this terminal.
		return;
	}

	ZoneServer* server = zone->getZoneServer();

	if (server == nullptr)
		return;

	Reference<SceneObject*> turret = server->getObject(tindex);

	if (turret == nullptr || !turret->isTurret()) {
		creature->sendSystemMessage("@hq:none_active"); // There are no available turrets to control using this terminal.
		return;
	}

	TangibleObject* turretObject = cast<TangibleObject*>(turret.get());

	if (turretObject == nullptr)
		return;

	TurretDataComponent* turretData = getTurretDataComponent(turret);

	if (turretData == nullptr)
		return;

	if (!canUseTurret(turretObject, turretControlTerminal, creature)) {
		creature->sendSystemMessage("@hq:in_use"); //  This turret control terminal is already in use."
		return;
	}

	generateTurretControlBoxTo(creature, turretObject, turretControlTerminal);
}

bool GCWManagerImplementation::canUseTurret(TangibleObject* turret, SceneObject* terminal, CreatureObject* creature) {
	TurretDataComponent* turretData = getTurretDataComponent(turret);

	if (turretData == nullptr)
		return false;

	TurretControlTerminalDataComponent* controlData = getTurretControlDataComponent(terminal);

	if (controlData == nullptr)
		return false;

	CreatureObject* controllerCreature = turretData->getController();

	if (controllerCreature != nullptr && controllerCreature != creature) {
		PlayerObject* controllerGhost = controllerCreature->getPlayerObject();

		// if there is no manual target, give it to the new guy, close it from the old guy
		if (turretData->getManualTarget() == nullptr) {
			// try to close it from the old controller if it's still up
			controllerGhost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);
		} else if (controllerGhost != nullptr) {
			// if the controller creatures has the same window up
			if (turretData->getManualTarget() != nullptr) {
				int controllingSuiBoxID = controlData->getSuiBoxID();

				if (controllingSuiBoxID >= 0) {
					// get the sui from the controllerGhost to see if it's still up
					if (controllerGhost->hasSuiBox(controllingSuiBoxID)) {
						return false;
					}
				}
			}
		}
	}

	return true;
}

TurretDataComponent* GCWManagerImplementation::getTurretDataComponent(SceneObject* turret) {
	DataObjectComponentReference* turretComponent = turret->getDataObjectComponent();

	if (turretComponent == nullptr)
		return nullptr;

	return cast<TurretDataComponent*>(turretComponent->get());
}

TurretControlTerminalDataComponent* GCWManagerImplementation::getTurretControlDataComponent(SceneObject* terminal) {
	DataObjectComponentReference* terminalData = terminal->getDataObjectComponent();

	if (terminalData == nullptr)
		return nullptr;

	return cast<TurretControlTerminalDataComponent*>(terminalData->get());
}

void GCWManagerImplementation::generateTurretControlBoxTo(CreatureObject* creature, TangibleObject* turret, SceneObject* terminal) {
	TurretControlTerminalDataComponent* controlData = getTurretControlDataComponent(terminal);

	if (controlData == nullptr)
		return;

	TurretDataComponent* turretData = getTurretDataComponent(turret);

	if (turretData == nullptr)
		return;

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return;

	Reference<WeaponObject*> weapon = turret->getSlottedObject("hold_r").castTo<WeaponObject*>();

	if (weapon == nullptr)
		return;

	CreatureObject* target = turretData->getManualTarget();

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TURRET_TERMINAL);
	status->setPromptTitle("@hq:control_title"); //"Turret Control Consule"
	status->setCancelButton(true, "@cancel");
	status->setCallback(new TurretControlSuiCallback(zone->getZoneServer(), turret, cast<TangibleObject*>(terminal)));
	status->setOtherButton(true, "@ui:refresh"); // refresh
	status->setOkButton(true, "@hq:btn_attack"); // Attack
	status->setUsingObject(terminal);
	status->setForceCloseDistance(5);

	int maxHp = turret->getMaxCondition();
	int hp = maxHp - turret->getConditionDamage();

	StringBuffer msg;
	msg << "@hq:turret_control " << turret->getDisplayedName() << " [" << hp << "/" << maxHp << "]" << endl << endl;
	msg << "@hq:current_target ";

	if (target != nullptr) {
		msg << target->getDisplayedName() << " "
			<< "hq:target_health " << target->getHAM(0);
	} else
		msg << "None";

	status->setPromptText(msg.toString());

	Vector<CreatureObject*> targets = turretData->getAvailableTargets(false);
	int targetTotal = 0;

	for (int i = 0; i < targets.size(); ++i) {
		CreatureObject* creo = targets.get(i);

		if (creo != nullptr) {
			int distance = turret->getDistanceTo(creo);

			status->addMenuItem(creo->getDisplayedName() + " - " + String::valueOf(distance) + "m", creo->getObjectID());

			targetTotal++;
		}

		if (targetTotal >= 20)
			break;
	}

	if (status->getMenuSize() > 0) {
		ghost->addSuiBox(status);
		creature->sendMessage(status->generateMessage());

		controlData->setSuiBoxID(status->getBoxID());

	} else
		creature->sendSystemMessage("@hq:no_targets"); // This turret has no valid targets.
}

// returns a cost multiplier for faction items
// includes racial penalty and Bonus&Penality for Loser and Winner side
float GCWManagerImplementation::getGCWDiscount(CreatureObject* creature) {
	float discount = 1.0f;

	if (getWinningFaction() != 0 && creature->getFaction() != 0) {
		if (getWinningFaction() == creature->getFaction())
			discount -= winnerBonus / 100.f;
		else
			discount -= loserBonus / 100.f;
	}

	if (creature->getFaction() == Factions::FACTIONIMPERIAL && racialPenaltyEnabled && getRacialPenalty(creature->getSpecies()) > 0) {
		discount *= getRacialPenalty(creature->getSpecies());
	}

	return discount;
}

int GCWManagerImplementation::isStrongholdCity(String& city) {
	for (int i = 0; i < imperialStrongholds.size(); i++) {
		if (city.contains(imperialStrongholds.get(i))) {
			return Factions::FACTIONIMPERIAL;
		}
	}

	for (int i = 0; i < rebelStrongholds.size(); i++) {
		if (city.contains(rebelStrongholds.get(i))) {
			return Factions::FACTIONREBEL;
		}
	}

	return 0;
}

bool GCWManagerImplementation::runCrackdownScan(AiAgent* scanner, CreatureObject* player) {
	if (!crackdownScansEnabled)
		return false;

	if (scanner == nullptr || player == nullptr)
		return false;

	if (player->isIncapacitated() || player->isDead())
		return false;

	if (!crackdownScanPrivilegedPlayers && player->isPlayerCreature()) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr && ghost->isPrivileged())
			return false;
	}

	if (!CollisionManager::checkLineOfSight(scanner, player))
		return false;

	if (!player->checkCooldownRecovery("crackdown_scan")) {
		scanner->info("Contraband scan of " + player->getDisplayedName() + " (" + String::valueOf(player->getObjectID()) + ") skipped due to player cooldown.");
		return false;
	}

	startContrabandScanSession(scanner, player, false);
	return true;
}

void GCWManagerImplementation::startContrabandScanSession(AiAgent* scanner, CreatureObject* player, bool enforced) {
	ContrabandScanSession* contrabandScanSession = new ContrabandScanSession(scanner, player, getWinningFaction(), getWinningFactionDifficultyScaling(), enforced);

	if (contrabandScanSession != nullptr)
		contrabandScanSession->initializeSession();
}

String GCWManagerImplementation::getCrackdownInfo(CreatureObject* player) const {
	auto zone = player->getZone();
	if (zone == nullptr) {
		return "No zone information";
	} else {
		return "Crackdown scan information:"
			"\nScans enabled - " + String::valueOf(crackdownScansEnabled) +
			"\nScans enabled (privileged players) - " + String::valueOf(crackdownScanPrivilegedPlayers) +
			"\nScans enabled on this planet - " + String::valueOf(planetsWithWildScans.find(zone->getZoneName()) != Vector<String>::npos) +
			"\nPlayer has no scan cooldown - " + String::valueOf(player->checkCooldownRecovery("crackdown_scan")) +
			"\nPlayer outside - " + String::valueOf(player->getParentID() == 0 || player->isRidingMount()) +
			"\nIs spawning permitted at the coordinates - " + String::valueOf(zone->getPlanetManager()->isSpawningPermittedAt(player->getWorldPositionX(), player->getWorldPositionY(), 0)) +
			"\nIs player privileged - " + String::valueOf(player->getPlayerObject()->isPrivileged());
	}
}

void GCWManagerImplementation::performCheckWildContrabandScanTask() {
	if (!crackdownScansEnabled || !planetsWithWildScans.contains(zone->getZoneName())) {
		return;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr)
		return;

	auto playerManager = zoneServer->getPlayerManager();

	if (playerManager == nullptr)
		return;

	auto playerList = playerManager->getOnlinePlayerList();

	for (int i = 0; i < playerList.size(); i++) {
		auto playerID = playerList.get(i);

		Reference<SceneObject*> object = zoneServer->getObject(playerID);

		if (object == nullptr || !object->isPlayerCreature())
			continue;

		auto player = object->asCreatureObject();

		if (player == nullptr)
			continue;

		if (player->getParentID() != 0 && !player->isRidingMount())
			continue;

		if (player->getCityRegion() != nullptr)
			continue;

		if (!player->checkCooldownRecovery("crackdown_scan"))
			continue;

		if (player->isDead() || player->isIncapacitated() || player->isFeigningDeath())
			continue;

		if (player->isInCombat())
			continue;

		auto ghost = player->getPlayerObject();

		if (ghost != nullptr) {
			if (ghost->isLinkDead())
				continue;

			if (!crackdownScanPrivilegedPlayers && ghost->isPrivileged())
				continue;

			// No scan until player session time passes the login delay
			if (ghost->getSessionMiliSecs() < getWildScanLoginDelay())
				continue;
		}

		if (zone->getPlanetManager()->isSpawningPermittedAt(player->getWorldPositionX(), player->getWorldPositionY(), 0) && getWildScanChance() >= System::random(100)) {
			WildContrabandScanSession* wildContrabandScanSession = new WildContrabandScanSession(player, getWinningFactionDifficultyScaling());
			wildContrabandScanSession->initializeSession();

			break;
		}
	}

	CheckWildContrabandScanTask* task = new CheckWildContrabandScanTask(_this.getReferenceUnsafeStaticCast());

	uint64 delay = getWildScanInterval() + System::random(600000);

	// Minimum Delay is 10 min
	task->schedule(delay);
}

bool GCWManagerImplementation::isContraband(SceneObject* item) {
	if (item->isTangibleObject()) {
		ManagedReference<TangibleObject*> tangibleItem = item->asTangibleObject();
		if (tangibleItem->isSliced()) {
			return true;
		} else if (tangibleItem->isConsumable()) {
			ManagedReference<Consumable*> consumable = tangibleItem.castTo<Consumable*>();
			if (consumable->isSpice()) {
				return true;
			}
		} else if (tangibleItem->isFactoryCrate()) {
			ManagedReference<FactoryCrate*> crate = tangibleItem.castTo<FactoryCrate*>();
			ManagedReference<TangibleObject*> prototype = crate->getPrototype();
			return isContraband(prototype.castTo<SceneObject*>());
		}
	}
	return false;
}

int GCWManagerImplementation::countContrabandItemsInContainer(SceneObject* container) {
	int numberOfContrabandItems = 0;
	int containerSize = container->getContainerObjectsSize();
	if (containerSize > 1) {
		for (int i = 0; i < containerSize; i++) {
			numberOfContrabandItems += countContrabandItemsInContainer(container->getContainerObject(i));
		}
	}
	if (isContraband(container)) {
		numberOfContrabandItems++;
	}
	return numberOfContrabandItems;
}

int GCWManagerImplementation::countContrabandItems(CreatureObject* player) {
	VectorMap<String, ManagedReference<SceneObject*>> slots;
	player->getSlottedObjects(slots);

	int numberOfSlots = slots.size();
	int numberOfContrabandItems = 0;

	for (int i = 0; i < numberOfSlots; i++) {
		VectorMapEntry<String, ManagedReference<SceneObject*>> container = slots.elementAt(i);
		if (container.getKey() != "bank" && container.getKey() != "datapad") {
			numberOfContrabandItems += countContrabandItemsInContainer(container.getValue());
		}
	}

	return numberOfContrabandItems;
}

void GCWManagerImplementation::spawnBaseTerminals(BuildingObject* bldg) {
	String baseName = bldg->getObjectTemplate()->getTemplateFileName();

	if (!baseName.beginsWith("hq_"))
		return;

	baseName = baseName.replaceFirst("_pvp", "");

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(bldg);

	if (baseData == nullptr)
		return;

	if (baseData->getBaseTerminalCount() > 0)
		despawnBaseTerminals(bldg);

	if (!terminalSpawnLocations.contains(baseName)) {
		error("Failed to grab terminal locations for GCW base type " + baseName);

		return;
	}

	Vector<Reference<TerminalSpawn*>>* spawnLocs = terminalSpawnLocations.get(baseName);
	Vector<Reference<TerminalSpawn*>>* copySpawnLocs = new Vector<Reference<TerminalSpawn*>>(*spawnLocs);

	if (copySpawnLocs->size() == 0) {
		delete copySpawnLocs;
		return;
	}

	for (int i = 0; i < terminalTemplates.size(); i++) {
		int randIndex = System::random(copySpawnLocs->size() - 1);
		String termTemplate = terminalTemplates.get(i);

		Reference<TerminalSpawn*> termLoc = copySpawnLocs->get(randIndex);

		if (termLoc == nullptr)
			continue;

		ManagedReference<SceneObject*> obj = zone->getZoneServer()->createObject(termTemplate.hashCode(), 0);

		if (obj == nullptr)
			continue;

		Locker locker(obj);

		Vector3* termCoords = termLoc->getSpawnLoc();

		obj->initializePosition(termCoords->getX(), termCoords->getZ(), termCoords->getY());

		Quaternion termRot = termLoc->getRotation();

		obj->setDirection(termRot);

		CellObject* cellObject = bldg->getCell(termLoc->getCellID());

		if (cellObject != nullptr) {
			if (!cellObject->transferObject(obj, -1, true)) {
				obj->destroyObjectFromDatabase(true);
			} else {
				baseData->addBaseTerminal(obj);
				bldg->addChildObject(obj);
			}
		} else {
			obj->destroyObjectFromDatabase(true);
		}

		copySpawnLocs->removeElementAt(randIndex);
	}

	delete copySpawnLocs;

	baseData->setTerminalsSpawned(true);
}

void GCWManagerImplementation::despawnBaseTerminals(BuildingObject* bldg) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(bldg);

	if (baseData == nullptr)
		return;

	int termCount = baseData->getBaseTerminalCount();

	if (termCount == 0)
		return;

	for (int i = termCount - 1; i >= 0; i--) {
		ManagedReference<SceneObject*> term = baseData->getBaseTerminal(i);

		if (term == nullptr)
			continue;

		Locker clocker(term, bldg);
		bldg->removeChildObject(term);
		term->destroyObjectFromWorld(true);
	}

	baseData->clearBaseTerminals();
	baseData->setTerminalsSpawned(false);
}

void GCWManagerImplementation::activateBaseAlarms(BuildingObject* building, int alarmType) {
	if (!spawnBaseAlarms) {
		return;
	}

	if (building == nullptr) {
		return;
	}

	ZoneServer* zoneServer = building->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	Locker blocker(building);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return;
	}

	Vector<uint64> alarmIds;

	if (alarmType == HACKALARM) {
		alarmIds = baseData->getHackAlarms();
	} else if (alarmType == DESTRUCTALARM) {
		alarmIds = baseData->getDestructAlarms();
	} else {
		error("Incorrect Base Alarm Type in activateBaseAlarms.");
		return;
	}

	for (int i = 0; i < alarmIds.size(); ++i) {
		uint64 alarmID = alarmIds.get(i);

		if (alarmID > 0) {
			SceneObject* alarm = zoneServer->getObject(alarmID).get();

			if (alarm == nullptr) {
				continue;
			}

			Locker alocker(alarm, building);

			if (alarm->isTangibleObject()) {
				TangibleObject* alarmTano = alarm->asTangibleObject();

				if (alarmTano != nullptr) {
					alarmTano->setOptionsBitmask(OptionBitmask::ACTIVATED);
					alarmTano->setMaxCondition(0);
				}
			}
		}
	}
}

void GCWManagerImplementation::deactivateBaseAlarms(BuildingObject* building) {
	if (building == nullptr) {
		return;
	}

	ZoneServer* zoneServer = building->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	Locker blocker(building);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if (baseData == nullptr) {
		return;
	}

	Vector<uint64> hackAlarmIDs = baseData->getHackAlarms();
	Vector<uint64> destructAlarmIDs = baseData->getDestructAlarms();

	for (int i = 0; i < hackAlarmIDs.size(); ++i) {
		uint64 hackAlarmID = hackAlarmIDs.get(i);

		if (hackAlarmID > 0) {
			SceneObject* hackAlarm = zoneServer->getObject(hackAlarmID).get();

			if (hackAlarm == nullptr) {
				continue;
			}

			if (hackAlarm->isTangibleObject()) {
				TangibleObject* hackTano = hackAlarm->asTangibleObject();

				if (hackTano == nullptr)
					continue;

				Locker hlocker(hackTano, building);

				hackTano->setOptionsBitmask(OptionBitmask::NONE, true);
			}
		}
	}

	for (int i = 0; i < destructAlarmIDs.size(); ++i) {
		uint64 destructAlarmID = destructAlarmIDs.get(i);

		if (destructAlarmID > 0) {
			SceneObject* destructAlarm = zoneServer->getObject(destructAlarmID).get();

			if (destructAlarm == nullptr) {
				continue;
			}

			if (destructAlarm->isTangibleObject()) {
				TangibleObject* destructTano = destructAlarm->asTangibleObject();

				Locker hlocker(destructTano, building);

				destructTano->setOptionsBitmask(OptionBitmask::NONE);
			}
		}
	}
}
