/*
 * StructureObjectImplementation.cpp
 *
 *  Created on: Aug 15, 2010
 *      Author: crush
 */

#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/structure/events/StructureMaintenanceTask.h"
#include "server/zone/objects/building/components/CityHallZoneComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"

#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/managers/city/PayPropertyTaxTask.h"
#include "server/zone/objects/pathfinding/NavArea.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/credit/CreditManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/transaction/TransactionLog.h"

void StructureObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isSharedStructureObjectTemplate())
		return;

	SharedStructureObjectTemplate* structureTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateData);

	structureTemplate->getPortalLayout();
	structureTemplate->getAppearanceTemplate();
}

void StructureObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	Logger::setLoggingName("StructureObject");
}

void StructureObjectImplementation::finalize() {
}

void StructureObjectImplementation::createNavMesh() {
	if (server->getZoneServer()->shouldDeleteNavAreas() && navArea != nullptr) {
		ManagedReference<NavArea*> nav = navArea;
		zone->getPlanetManager()->dropNavArea(nav->getMeshName());

		Core::getTaskManager()->executeTask([nav] {
			Locker locker(nav);
			nav->destroyObjectFromWorld(true);
			nav->destroyObjectFromDatabase(true);
		}, "destroyStructureNavAreaLambda");

		navArea = nullptr;
	}

	if (navArea == nullptr) {
		navArea = zone->getZoneServer()->createObject(STRING_HASHCODE("object/region_navmesh.iff"), "navareas", isPersistent()).castTo<NavArea *>();

		if (navArea == nullptr) {
			error("Failed to create navmesh");
			return;
		}

		Locker clocker(navArea, _this.getReferenceUnsafeStaticCast());

		String name = String::valueOf(getObjectID());

		float length = 32.0f;

		for (const auto& child : childObjects) {
			const BaseBoundingVolume* boundingVolume = child->getBoundingVolume();
			if (boundingVolume) {
				const AABB& box = boundingVolume->getBoundingBox();
				float distance = (child->getWorldPosition() - getWorldPosition()).length();
				float radius = box.extents()[box.longestAxis()];
				if (distance + radius > length)
					length = radius + distance;
			}
		}

		const BaseBoundingVolume* boundingVolume = getBoundingVolume();
		if (boundingVolume) {
			const AABB& box = boundingVolume->getBoundingBox();
			float radius = box.extents()[box.longestAxis()];
			if (radius > length)
				length = radius;
		}

		Vector3 position = Vector3(getPositionX(), 0, getPositionY());
		// This is invoked when a new faction base is placed, always force a rebuild
		navArea->initializeNavArea(position, length * 1.25f, zone, name, true);

		zone->transferObject(navArea, -1, false);

		zone->getPlanetManager()->addNavArea(name, navArea);

	} else if (!navArea->isNavMeshLoaded()) {
		navArea->updateNavMesh(navArea->getBoundingBox());
	}
}

void StructureObjectImplementation::notifyLoadFromDatabase() {
	TangibleObjectImplementation::notifyLoadFromDatabase();

	if (structurePermissionList.getOwner() != getOwnerObjectID()) {
		structurePermissionList.setOwner(getOwnerObjectID());
	}

	if (permissionsFixed == false) {

		class MigratePermissionsTask : public Task {
			ManagedReference<StructureObject*> structure;

		public:
			MigratePermissionsTask(StructureObject* st) {
				structure = st;
			}

			void run() {
				if (structure == nullptr)
					return;

				ZoneServer* zoneServer = structure->getZoneServer();

				if (zoneServer == nullptr)
					return;

				if (zoneServer->isServerLoading()) {
					reschedule(15000);
					return;
				}

				Locker locker(structure);

				structure->migratePermissions();
			}
		};

		Reference<MigratePermissionsTask*> task = new MigratePermissionsTask(_this.getReferenceUnsafeStaticCast());

		task->execute();
	}
}

void StructureObjectImplementation::notifyInsertToZone(Zone* zone) {
#if DEBUG_STRUCTURE_MAINT
	if (!staticObject && isBuildingObject())
		info("notifyInsertToZone", true);
#endif // DEBUG_STRUCTURE_MAINT
	StringBuffer logName;

	logName << getLoggingName()
		// << " 0x" << String::hexvalueOf((int64)getObjectID())
		<< " owner: " << String::valueOf(getOwnerObjectID())
		<< " " << String::valueOf((int)getPositionX()) << " " << String::valueOf((int)getPositionY())
		<< " " << zone->getZoneName()
		<< " " << String::valueOf((int)getPositionZ())
		<< " " << getObjectName()->getFullPath();

	setLoggingName(logName.toString());

	TangibleObjectImplementation::notifyInsertToZone(zone);

	if (isCivicStructure()) {
		if (structurePermissionList.containsList("ADMIN"))
			structurePermissionList.dropList("ADMIN");

		if (structurePermissionList.containsList("ENTRY"))
			structurePermissionList.dropList("ENTRY");

		if (structurePermissionList.containsList("HOPPER"))
			structurePermissionList.dropList("HOPPER");

		if (structurePermissionList.containsList("BAN"))
			structurePermissionList.dropList("BAN");

		if (structurePermissionList.containsList("VENDOR"))
			structurePermissionList.dropList("VENDOR");
	}

	if (!staticObject && getBaseMaintenanceRate() != 0 && !isTurret() && !isMinefield() && !isScanner()) {
		//Decay is 4 weeks.
		maxCondition = getBaseMaintenanceRate() * 24 * 7 * 4;

		scheduleMaintenanceExpirationEvent();
	} else if(getOwnerObjectID() != 0 && getCityRegion().get() == nullptr && !isTurret() && !isMinefield() && !isScanner()) {
		auto ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

		if (ssot == nullptr)
			error("SharedStructureObjectTemplate is null?");
		else if (ssot->getCityRankRequired() > 0 || ssot->isCivicStructure())
			destroyOrphanCivicStructure();
	}

	if (isGCWBase() && !isClientObject()) {
		createNavMesh();
	} else if (isClientObject()) {
		String configKey = "Core3.StructureManager.CreateNavMesh." + objectName.getFullPath();

		if (ConfigManager::instance()->getBool(configKey, false)) {
			info() << configKey << " = true; building navArea around this structure.";
			createNavMesh();
		}
	}
}

void StructureObjectImplementation::destroyOrphanCivicStructure() {
	error("Civic structure but not in a city!");

	if (!ConfigManager::instance()->getBool("Core3.Tweaks.StructureObject.DestoryOrphans", false))
		return;

	auto chatManager = getZoneServer()->getChatManager();
	auto structureManager = StructureManager::instance();

	if (chatManager == nullptr || structureManager == nullptr) {
		error("destroyOrphanCivicStructure failed to get chat or struture manager.");
		return;
	}

	auto name = getZoneServer()->getPlayerManager()->getPlayerName(getOwnerObjectID());

	if (!name.isEmpty()) {
		UnicodeString subject = "Orphaned city structure destroyed!";

		StringBuffer msg;

		msg << name << "," << endl << endl;
		msg << "You are the last known mayor releated to a " << StringIdManager::instance()->getStringId(getObjectName()->getFullPath().hashCode()).toString();
		msg << " at " << (int)getPositionX() << ", " << (int)getPositionY() << " on " << getZone()->getZoneName() << "." << endl;
		msg << endl;
		msg << "This structre has been destroyed because it did not belong to an active city." << endl;
		msg << endl;
		msg << "-- The Planetary Civic Authority" << endl;

		UnicodeString body = msg.toString();

		chatManager->sendMail("@city/city:new_city_from", subject, body, name);
	} else {
		error("destroyOrphanCivicStructure: Unable to find owner oid: " + String::valueOf(getOwnerObjectID()) + ", destruction email not sent.");
	}

	String path = exportJSON("Destroyed by destroyOrphanCivicStructure");

	error() << "Destroyed orphan civic structure and exported to " << path;

	structureManager->destroyStructure(_this.getReferenceUnsafeStaticCast());
}

int StructureObjectImplementation::getLotSize() const {
	const SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == nullptr)
		return 0;

	return ssot->getLotSize();
}

CreatureObject* StructureObjectImplementation::getOwnerCreatureObject() const {
	//Get the owner of the structure
	ManagedReference<SceneObject*> owner = getZoneServer()->getObject(getOwnerObjectID());

	if (owner != nullptr && owner->isCreatureObject()) {
		return cast<CreatureObject* >(owner.get());
	} else {
		return nullptr;
	}
}

float StructureObjectImplementation::getMaintenanceRate() const {
	float rate = getBaseMaintenanceRate();

#if DEBUG_STRUCTURE_RAPID_DECAY
	rate *= 10000.0f; // Make structures really expensive
#endif // DEBUG_STRUCTURE_RAPID_DECAY

	if (maintenanceReduced) {
		rate *= 0.8f;
	}

	return (float)((int)rate); // Round to nearest int
}

String StructureObjectImplementation::getMaintenanceMods() const {
	if (maintenanceReduced) {
			return "-20%";
	}

	return "-";
}

String StructureObjectImplementation::getTimeString(uint32 timestamp) const {
	const static String abbrvs[4] = {"seconds", "minutes", "hours", "days"};

	int intervals[4] = {1, 60, 3600, 86400};
	int values[4] = {0, 0, 0, 0};

	StringBuffer str;

	for (int i = 3; i > -1; --i) {
		values[i] = floor((float)(timestamp / intervals[i]));
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0)
				str << ", ";

			str << ((i == 0) ? "and " : "") << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}

//Only gets called when maintenance has been changed by an outside source
void StructureObjectImplementation::scheduleMaintenanceExpirationEvent() {
	if (getMaintenanceRate() <= 0) {
		if (getOwnerObjectID() == 0)
			return;

		if (getCityRegion().get() == nullptr && !isTurret() && !isMinefield() && !isScanner())
			error("scheduleMaintenanceExpirationEvent: getMaintenanceRate() <= 0 but not in a city!");

		// No maintenance cost, structure maintenance cannot expire.
		return;
	}

#if DEBUG_STRUCTURE_MAINT
	info("scheduleMaintenanceExpirationEvent: surplusMaintenance = " + String::valueOf(surplusMaintenance)
		+ " maintenanceRate = " + String::valueOf(getMaintenanceRate())
	, true);
#endif // DEBUG_STRUCTURE_MAINT

	int secondsRemaining;

	if (structureMaintenanceTask != nullptr) {
		updateStructureStatus();

		float cityTax = 0.0f;

		ManagedReference<CityRegion*> city = _this.getReferenceUnsafeStaticCast()->getCityRegion().get();

		if(city != nullptr) {
			cityTax = city->getPropertyTax();
		}

		secondsRemaining = (int) (surplusMaintenance * 3600.0f / (getMaintenanceRate() + (getMaintenanceRate() * cityTax / 100) ));

		if (secondsRemaining <= 0) {
			//Decaying structures should be scheduled as soon as possible. Maintenance task will handle
			//any further rescheduling.
			secondsRemaining = 1;
		} else if (secondsRemaining > 24 * 60 * 60) {
			//Run maintenance task at least one time every day but randomized to spread it out.
			secondsRemaining = 12 * 60 * 60 + System::random(12 * 60 * 60);
		}

#if DEBUG_STRUCTURE_MAINT
	    info("scheduleMaintenanceExpirationEvent: secondsRemaining = " + String::valueOf(secondsRemaining), true);
#endif // DEBUG_STRUCTURE_MAINT
		maintenanceExpires.updateToCurrentTime();
		maintenanceExpires.addMiliTime((uint64)secondsRemaining * 1000);
	}
	else
	{
		updateStructureStatus();

		secondsRemaining = (int) (surplusMaintenance * 3600.0f / getMaintenanceRate());

		if (secondsRemaining <= 0) {
			//Decaying structures should be scheduled as soon as possible. Maintenance task will handle
			//any further rescheduling.

			//Randomize maintenance tasks over the first hour after server restart.
			secondsRemaining = ConfigManager::instance()->getInt("Core3.StructureObject.MaintenanceBootDelay", 600) + System::random(60 * 60);
		} else if (secondsRemaining > 24 * 60 * 60) {
			//Run maintenance task at least one time every day but randomized to spread it out.
			secondsRemaining = 12 * 60 * 60 + System::random(12 * 60 * 60);
		}

#if DEBUG_STRUCTURE_MAINT
	    info("scheduleMaintenanceExpirationEvent: secondsRemaining = " + String::valueOf(secondsRemaining), true);
#endif // DEBUG_STRUCTURE_MAINT

		maintenanceExpires.updateToCurrentTime();
		maintenanceExpires.addMiliTime((uint64)secondsRemaining * 1000);
	}

	scheduleMaintenanceTask(secondsRemaining);
}

void StructureObjectImplementation::scheduleMaintenanceTask(int secondsFromNow) {
	if(getBaseMaintenanceRate() == 0) {
		if (getOwnerObjectID() == 0)
			return;

		if (getCityRegion().get() == nullptr && !isTurret() && !isMinefield() && !isScanner())
			error("scheduleMaintenanceTask: getMaintenanceRate() <= 0 but not in a city!");

		return;
	}

#if DEBUG_STRUCTURE_RAPID_DECAY
	secondsFromNow = secondsFromNow * 0.001f; // Accelerate scheduling of tasks
#endif // DEBUG_STRUCTURE_RAPID_DECAY

	if (structureMaintenanceTask == nullptr) {
		structureMaintenanceTask = new StructureMaintenanceTask(_this.getReferenceUnsafeStaticCast());
	}

	if (structureMaintenanceTask->isScheduled()) {
		structureMaintenanceTask->reschedule((uint64)secondsFromNow * 1000);
	} else {
		structureMaintenanceTask->schedule((uint64)secondsFromNow * 1000);
	}
}

void StructureObjectImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	if (structureMaintenanceTask != nullptr) {
		if (structureMaintenanceTask->isScheduled()) {
			structureMaintenanceTask->cancel();
		}

		structureMaintenanceTask = nullptr;
	}

	if (navArea != nullptr) {
		ManagedReference<NavArea*> nav = navArea;
		Core::getTaskManager()->executeTask([nav, sendSelfDestroy] () {
			Locker locker(nav);
			nav->destroyObjectFromWorld(sendSelfDestroy);
		}, "destroyStructureNavAreaLambda2");
	}

	TangibleObjectImplementation::destroyObjectFromWorld(sendSelfDestroy);
}

void StructureObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	if (navArea != nullptr)
		navArea->destroyObjectFromDatabase(true);

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

bool StructureObjectImplementation::isOwnerOf(SceneObject* obj) const {
	if (obj == nullptr || !obj->isPlayerCreature()) {
		return false;
	}

	ManagedReference<PlayerObject*> ghost = (cast<CreatureObject*>( obj))->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged())
		return true;

	return obj->getObjectID() == ownerObjectID;
}

bool StructureObjectImplementation::isOwnerOf(uint64 objid) const {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objid);

	if (obj == nullptr || !obj->isPlayerCreature()) {
		return false;
	}

	CreatureObject* player = cast<CreatureObject*>( obj.get());

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged())
		return true;

	return objid == ownerObjectID;
}

void StructureObjectImplementation::updateStructureStatus() {
	/** Points when updateStructureStatus should occur:
	 * Prior to inserting or withdrawing maintenance or power, and after the deposit/withdrawal.
	 * When requesting a Structure Status report.
	 * When correct maintenance/power values are needed.
	 * Any time the maintenance or power surplus is changed by a hand other than this method.
	 */

	if(isCivicStructure()) {
		if (getCityRegion().get() == nullptr && !isTurret() && !isMinefield() && !isScanner())
			error("updateStructureStatus: isCivicStructure() but not in a city!");

		return;
	}

#if DEBUG_STRUCTURE_MAINT
	info("updateStructureStatus: surplusMaintenance = " + String::valueOf(surplusMaintenance)
		+ " maintenanceRate = " + String::valueOf(getMaintenanceRate())
	, true);
#endif // DEBUG_STRUCTURE_MAINT

	float timeDiff = ((float) lastMaintenanceTime.miliDifference()) / 1000.0f;
	float maintenanceDue = (getMaintenanceRate() / 3600.0f) * timeDiff;
	float cityTaxDue = 0.0f;

#if DEBUG_STRUCTURE_MAINT
	info("updateStructureStatus: timeDiff = " + String::valueOf(timeDiff)
		+ " maintenanceDue = " + String::valueOf(maintenanceDue)
	, true);
#endif // DEBUG_STRUCTURE_MAINT

	if (maintenanceDue > 0.0f) {
		//Only update last time if we actually progressed to get correct consumption.
		lastMaintenanceTime.updateToCurrentTime();
	}

	ManagedReference<CityRegion*> city = getCityRegion().get();

	if(isBuildingObject() && city != nullptr && !city->isClientRegion() && city->getPropertyTax() > 0){
		cityTaxDue = city->getPropertyTax() / 100.0f * maintenanceDue;

		// sometimes a creature and building will be locked here
		if(cityTaxDue > 0.0f){
			Reference<PayPropertyTaxTask*> taxTask = new PayPropertyTaxTask(city, cityTaxDue);
			taxTask->execute();
		}

	}

#if DEBUG_STRUCTURE_MAINT
	info("updateStructureStatus: maintenanceDue = " + String::valueOf(maintenanceDue)
		+ " cityTaxDue = " + String::valueOf(cityTaxDue)
	, true);
#endif // DEBUG_STRUCTURE_MAINT

	//Maintenance is used as decay as well so let it go below 0.
	surplusMaintenance -= ( maintenanceDue + cityTaxDue );

#if DEBUG_STRUCTURE_MAINT
	info("updateStructureStatus: surplusMaintenance = " + String::valueOf(surplusMaintenance), true);
#endif // DEBUG_STRUCTURE_MAINT

	//Update structure condition.
	if (surplusMaintenance < 0) {
		setConditionDamage(-surplusMaintenance, true);
	} else {
		setConditionDamage(0, true);
	}
}

// Basic checks to see if structure is running tasks etc.
String StructureObjectImplementation::getDebugStructureStatus() const {
	StringBuffer status;

	if (structureMaintenanceTask != nullptr) {
		int ss = (int) (structureMaintenanceTask->getNextExecutionTime().miliDifference() / 1000.f * -1) + 1;
		int dd = (int)(ss / 86400);
		ss -= dd * 86400;
		int hh = (int)(ss / 3600);
		ss -= hh * 3600;
		int mm = (int)(ss / 60);
		ss -= mm * 60;
		status << "Next maintenance check in";

		if (dd > 0)
			status << " " << dd << "d";

		if (dd > 0 || hh > 0)
			status << " " << hh << "h";

		if (dd > 0 || hh > 0 || mm > 0)
			status << " " << mm << "m";

		status << " " << ss << "s";
	} else {
		if (getBaseMaintenanceRate() > 0) {
			status << "WARNING: No maintenance task running on this structure";
			error("getDebugStructureStatus: structureMaintenanceTask == nullptr");
		} else if (getOwnerObjectID() != 0 && getCityRegion().get() == nullptr && !isTurret() && !isMinefield() && !isScanner()) {
			status << "WARNING: City object without a city!";
			error("getDebugStructureStatus: City structure but not in a city!");
		}
	}

	return status.toString();
}

bool StructureObjectImplementation::isDecayed() {
	return (getDecayPercentage() == 0);
}

int StructureObjectImplementation::getDecayPercentage() {
	int percentage = 100;

	// Update structure status.
	updateStructureStatus();

	// Calculate decay (if any)
	int maxCond = getMaxCondition();

	if (maxCond != 0) {
		percentage = (maxCond - getConditionDamage()) * 100 / maxCond;

		// Calculation above truncates the percentage value but we want to round it upwards.
		percentage += 1;
		if (percentage < 0) {
			percentage = 0;
		} else if (percentage > 100) {
			percentage = 100;
		}
	} else {
		// Structure has 0 in max condition, i.e. it cannot decay. Condition is therefore always 100 %.
		percentage = 100;
	}

#if DEBUG_STRUCTURE_MAINT
	info("getDecayPercentage() = " + String::valueOf(percentage), true);
#endif // DEBUG_STRUCTURE_MAINT

	return percentage;
}

void StructureObjectImplementation::payMaintenance(int maintenance, CreditObject* creditObj, bool cashFirst) {
	//Pay maintenance.

	auto structure = _this.getReferenceUnsafeStaticCast();
	int payedSoFar;
	if (cashFirst) {
		if (creditObj->getCashCredits() >= maintenance) {
			TransactionLog trx(creditObj, structure, TrxCode::STRUCTUREMAINTANENCE, maintenance, true);
			creditObj->subtractCashCredits(maintenance);
			addMaintenance(maintenance);
		} else {
			payedSoFar = creditObj->getCashCredits();

			TransactionLog trxCash(creditObj, structure, TrxCode::STRUCTUREMAINTANENCE, payedSoFar, true);
			creditObj->subtractCashCredits(payedSoFar);
			addMaintenance(payedSoFar);

			TransactionLog trxBank(creditObj, structure, TrxCode::STRUCTUREMAINTANENCE, maintenance - payedSoFar, false);
			trxBank.groupWith(trxCash);
			creditObj->subtractBankCredits(maintenance - payedSoFar);
			addMaintenance(maintenance - payedSoFar);
		}
	} else {
		if (creditObj->getBankCredits() >= maintenance) {
			TransactionLog trx(creditObj, structure, TrxCode::STRUCTUREMAINTANENCE, maintenance, false);
			creditObj->subtractBankCredits(maintenance);
			addMaintenance(maintenance);
		} else {
			payedSoFar = creditObj->getBankCredits();

			TransactionLog trxCash(creditObj, structure, TrxCode::STRUCTUREMAINTANENCE, payedSoFar, false);
			creditObj->subtractBankCredits(payedSoFar);
			addMaintenance(payedSoFar);

			TransactionLog trxBank(creditObj, structure, TrxCode::STRUCTUREMAINTANENCE, maintenance - payedSoFar, true);
			trxBank.groupWith(trxCash);
			creditObj->subtractCashCredits(maintenance - payedSoFar);
			addMaintenance(maintenance - payedSoFar);
		}
	}
}

bool StructureObjectImplementation::isCampStructure() const {
	return templateObject->isCampStructureTemplate();
}

void StructureObjectImplementation::addTemplateSkillMods(TangibleObject* targetObject) const {
	if(!targetObject->isPlayerCreature())
		return;

	const SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == nullptr)
		return;

	const auto mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		const auto& entry = mods->elementAt(i);

		targetObject->addSkillMod(SkillModManager::STRUCTURE, entry.getKey(), entry.getValue());
	}

	SkillModManager::instance()->verifyStructureSkillMods(targetObject);
}

void StructureObjectImplementation::removeTemplateSkillMods(TangibleObject* targetObject) const {
	if(!targetObject->isPlayerCreature())
		return;

	const SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == nullptr)
		return;

	const auto mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		const auto& entry = mods->elementAt(i);

		targetObject->removeSkillMod(SkillModManager::STRUCTURE, entry.getKey(), entry.getValue());
	}

	SkillModManager::instance()->verifyStructureSkillMods(targetObject);
}

bool StructureObjectImplementation::isCivicStructure() const {
	const SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == nullptr)
		return false;


	return ssot->isCivicStructure();
}

bool StructureObjectImplementation::isCityHall() {
	return dynamic_cast<CityHallZoneComponent*>(getZoneComponent()) != nullptr;
}

bool StructureObjectImplementation::isCommercialStructure() const {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == nullptr)
		return false;


	return ssot->isCommercialStructure();
}

bool StructureObjectImplementation::isGuildHall() const {
	for (int i = 0; i < childObjects.size(); i++) {
		GuildTerminal* child = childObjects.get(i).castTo<GuildTerminal*>();

		if (child != nullptr) {
			return true;
		}
	}

	return false;
}

int StructureObjectImplementation::getBaseMaintenanceRate() const {
	const SharedStructureObjectTemplate* tmpl = cast<SharedStructureObjectTemplate*>(getObjectTemplate());

	if(tmpl == nullptr)
		return 0;

	return tmpl->getBaseMaintenanceRate();
}

int StructureObjectImplementation::getBasePowerRate() const {
	const SharedStructureObjectTemplate* tmpl = cast<SharedStructureObjectTemplate*>(getObjectTemplate());

	if(tmpl == nullptr)
		return 0;

	return tmpl->getBasePowerRate();
}

float StructureObjectImplementation::getDelayDestroyHours() const {
    return 30.0f * 24.0f; // Destroy after 30 days in the hole on maintenance
}

bool StructureObjectImplementation::isOnAdminList(CreatureObject* player) const {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged())
		return true;
	else if (structurePermissionList.isOnPermissionList("ADMIN", player->getObjectID())) {
		return true;
	} else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != nullptr && structurePermissionList.isOnPermissionList("ADMIN", guild->getObjectID()))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnEntryList(CreatureObject* player) const {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->hasGodMode())
		return true;
	else if (structurePermissionList.isOnPermissionList("ADMIN", player->getObjectID())
			|| structurePermissionList.isOnPermissionList("ENTRY", player->getObjectID())
			|| structurePermissionList.isOnPermissionList("VENDOR", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != nullptr && (structurePermissionList.isOnPermissionList("ADMIN", guild->getObjectID())
				|| structurePermissionList.isOnPermissionList("ENTRY", guild->getObjectID())
				|| structurePermissionList.isOnPermissionList("VENDOR", guild->getObjectID())))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnBanList(CreatureObject* player) const {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->hasGodMode())
		return false;
	else if (structurePermissionList.isOnPermissionList("BAN", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != nullptr && structurePermissionList.isOnPermissionList("BAN", guild->getObjectID()))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnHopperList(CreatureObject* player) const {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged())
		return true;
	else if (structurePermissionList.isOnPermissionList("HOPPER", player->getObjectID())
			|| structurePermissionList.isOnPermissionList("ADMIN", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != nullptr && (structurePermissionList.isOnPermissionList("HOPPER", guild->getObjectID())
				|| structurePermissionList.isOnPermissionList("ADMIN", guild->getObjectID())))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnPermissionList(const String& listName, CreatureObject* player) const {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged()) {
		if (listName == "BAN")
			return false;
		else
			return true;
	} else if (structurePermissionList.isOnPermissionList(listName, player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != nullptr && structurePermissionList.isOnPermissionList(listName, guild->getObjectID()))
			return true;
	}

	return false;
}
