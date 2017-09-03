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
	if (server->getZoneServer()->shouldDeleteNavAreas() && navArea != NULL) {
		ManagedReference<NavArea*> nav = navArea;
		zone->getPlanetManager()->dropNavArea(nav->getMeshName());

		Core::getTaskManager()->executeTask([nav] {
			Locker locker(nav);
			nav->destroyObjectFromWorld(true);
			nav->destroyObjectFromDatabase(true);
		}, "destroyStructureNavAreaLambda");

		navArea = NULL;
	}

	if (navArea == NULL) {
		navArea = zone->getZoneServer()->createObject(STRING_HASHCODE("object/region_navmesh.iff"), "navareas", isPersistent()).castTo<NavArea *>();

		if (navArea == NULL) {
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
				if (structure == NULL)
					return;

				ZoneServer* zoneServer = structure->getZoneServer();

				if (zoneServer == NULL)
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

	if (!staticObject && getBaseMaintenanceRate() != 0 && !isTurret() && !isMinefield()) {
		//Decay is 4 weeks.
		maxCondition = getBaseMaintenanceRate() * 24 * 7 * 4;

		scheduleMaintenanceExpirationEvent();
	}

	if (isGCWBase() && !isClientObject()) {
		createNavMesh();
	}
}

int StructureObjectImplementation::getLotSize() {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == NULL)
		return 0;

	return ssot->getLotSize();
}

CreatureObject* StructureObjectImplementation::getOwnerCreatureObject() {
 	//Get the owner of the structure
 	ManagedReference<SceneObject*> owner = getZoneServer()->getObject(getOwnerObjectID());

 	if (owner != NULL && owner->isCreatureObject()) {
 		return cast<CreatureObject* >(owner.get());
 	} else {
 		return NULL;
 	}
}

float StructureObjectImplementation::getMaintenanceRate() {
	if (maintenanceReduced) {
		return (int)((float)getBaseMaintenanceRate() * 0.8f);
	}

	return getBaseMaintenanceRate();
}

String StructureObjectImplementation::getMaintenanceMods() {
	if (maintenanceReduced) {
			return "-20%";
	}

	return "-";
}

String StructureObjectImplementation::getTimeString(uint32 timestamp) {
	String abbrvs[4] = {"seconds", "minutes", "hours", "days"};

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
		//No maintenance cost, structure maintenance cannot expire.
		return;
	}

	int timeRemaining;

	if (structureMaintenanceTask != NULL) {
		updateStructureStatus();

		float cityTax = 0.f;

		ManagedReference<CityRegion*> city = _this.getReferenceUnsafeStaticCast()->getCityRegion().get();

		if(city != NULL) {
			cityTax = city->getPropertyTax();
		}

		timeRemaining = (int) (surplusMaintenance * 3600.f / (getMaintenanceRate() + (getMaintenanceRate() * cityTax / 100) ));

		if (timeRemaining <= 0) {
			//Decaying structures should be scheduled as soon as possible. Maintenance task will handle
			//any further rescheduling.
			timeRemaining = 1;
		} else if (timeRemaining > 24 * 60 * 60 * 1000) {
			//Run maintenance task at least one time every day but randomized to spread it out.
			timeRemaining = 12 * 60 * 60 + System::random(12 * 60 * 60);
		}

		maintenanceExpires.updateToCurrentTime();
		maintenanceExpires.addMiliTime((uint64)timeRemaining * 1000);
	}
	else
	{
		updateStructureStatus();

		timeRemaining = (int) (surplusMaintenance * 3600.f / getMaintenanceRate());

		if (timeRemaining <= 0) {
			//Decaying structures should be scheduled as soon as possible. Maintenance task will handle
			//any further rescheduling.

			//Randomize maintenance tasks over the first hour after server restart.
			timeRemaining = System::random(60 * 60);
		} else if (timeRemaining > 24 * 60 * 60 * 1000) {
			//Run maintenance task at least one time every day but randomized to spread it out.
			timeRemaining = 12 * 60 * 60 + System::random(12 * 60 * 60);
		}

		maintenanceExpires.updateToCurrentTime();
		maintenanceExpires.addMiliTime((uint64)timeRemaining * 1000);
	}

	scheduleMaintenanceTask(timeRemaining);
}

void StructureObjectImplementation::scheduleMaintenanceTask(int timeFromNow) {
	if(getBaseMaintenanceRate() == 0) {
		return;
	}

	if (structureMaintenanceTask == NULL) {
		structureMaintenanceTask = new StructureMaintenanceTask(_this.getReferenceUnsafeStaticCast());
	}

	if (structureMaintenanceTask->isScheduled()) {
		structureMaintenanceTask->reschedule((uint64)timeFromNow * 1000);
	} else {
		structureMaintenanceTask->schedule((uint64)timeFromNow * 1000);
	}
}

void StructureObjectImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	if (structureMaintenanceTask != NULL) {
		if (structureMaintenanceTask->isScheduled()) {
			structureMaintenanceTask->cancel();
		}

		structureMaintenanceTask = NULL;
	}

	if (navArea != NULL) {
		ManagedReference<NavArea*> nav = navArea;
		Core::getTaskManager()->executeTask([nav, sendSelfDestroy] () {
			Locker locker(nav);
			nav->destroyObjectFromWorld(sendSelfDestroy);
		}, "destroyStructureNavAreaLambda2");
	}

	TangibleObjectImplementation::destroyObjectFromWorld(sendSelfDestroy);
}

void StructureObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	if (navArea != NULL)
		navArea->destroyObjectFromDatabase(true);

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

bool StructureObjectImplementation::isOwnerOf(SceneObject* obj) {
	if (obj == NULL || !obj->isPlayerCreature()) {
		return false;
	}

	ManagedReference<PlayerObject*> ghost = (cast<CreatureObject*>( obj))->getPlayerObject();

	if (ghost != NULL && ghost->isPrivileged())
		return true;

	return obj->getObjectID() == ownerObjectID;
}

bool StructureObjectImplementation::isOwnerOf(uint64 objid) {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objid);

	if (obj == NULL || !obj->isPlayerCreature()) {
		return false;
	}

	CreatureObject* player = cast<CreatureObject*>( obj.get());

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL && ghost->isPrivileged())
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

	if(isCivicStructure())
		return;

	float timeDiff = ((float) lastMaintenanceTime.miliDifference()) / 1000.f;
	float maintenanceDue = (getMaintenanceRate() / 3600.f) * timeDiff;
	float cityTaxDue = 0;

	if (maintenanceDue > 0) {
		//Only update last time if we actually progressed to get correct consumption.
		lastMaintenanceTime.updateToCurrentTime();
	}

	ManagedReference<CityRegion*> city = getCityRegion().get();

	if(isBuildingObject() && city != NULL && !city->isClientRegion() && city->getPropertyTax() > 0){
		cityTaxDue = city->getPropertyTax() / 100.0f * maintenanceDue;

		// sometimes a creature and building will be locked here
		if(cityTaxDue > 0){
			Reference<PayPropertyTaxTask*> taxTask = new PayPropertyTaxTask(city, cityTaxDue);
			taxTask->execute();
		}

	}

	//Maintenance is used as decay as well so let it go below 0.
	surplusMaintenance -= ( maintenanceDue + cityTaxDue );

	//Update structure condition.
	if (surplusMaintenance < 0) {
		setConditionDamage(-surplusMaintenance, true);
	} else {
		setConditionDamage(0, true);
	}
}

bool StructureObjectImplementation::isDecayed() {
	return (getDecayPercentage() == 0);
}

int StructureObjectImplementation::getDecayPercentage() {
	//Update structure status.
	updateStructureStatus();

	//Calculate decay.
	int decayedBelowMaintenance = getMaxCondition();

	if (decayedBelowMaintenance != 0) {
		int percentage = (decayedBelowMaintenance - getConditionDamage()) * 100 / decayedBelowMaintenance;

		//Calculation above truncates the percentage value but we want to round it upwards.
		percentage += 1;
		if (percentage < 0) {
			percentage = 0;
		} else if (percentage > 100) {
			percentage = 100;
		}

		return percentage;
	} else {
		//Structure has 0 in max condition, i.e. it cannot decay. Condition is therefore always 100 %.
		return 100;
	}
}

void StructureObjectImplementation::payMaintenance(int maintenance, CreditObject* creditObj, bool cashFirst) {
	//Pay maintenance.

	int payedSoFar;
	if (cashFirst) {
		if (creditObj->getCashCredits() >= maintenance) {
			creditObj->subtractCashCredits(maintenance);
		} else {
			payedSoFar = creditObj->getCashCredits();
			creditObj->subtractCashCredits(payedSoFar);
			creditObj->subtractBankCredits(maintenance - payedSoFar);
		}
	} else {
		if (creditObj->getBankCredits() >= maintenance) {
			creditObj->subtractBankCredits(maintenance);
		} else {
			payedSoFar = creditObj->getBankCredits();
			creditObj->subtractBankCredits(payedSoFar);
			creditObj->subtractCashCredits(maintenance - payedSoFar);
		}
	}
	addMaintenance(maintenance);
}

bool StructureObjectImplementation::isCampStructure() {
	return templateObject->isCampStructureTemplate();
}

void StructureObjectImplementation::addTemplateSkillMods(TangibleObject* targetObject) {
	if(!targetObject->isPlayerCreature())
		return;

	SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == NULL)
		return;

	VectorMap<String, int>* mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		VectorMapEntry<String, int> entry = mods->elementAt(i);

		targetObject->addSkillMod(SkillModManager::STRUCTURE, entry.getKey(), entry.getValue());
	}

	SkillModManager::instance()->verifyStructureSkillMods(targetObject);
}

void StructureObjectImplementation::removeTemplateSkillMods(TangibleObject* targetObject) {
	if(!targetObject->isPlayerCreature())
		return;

	SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == NULL)
		return;

	VectorMap<String, int>* mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		VectorMapEntry<String, int> entry = mods->elementAt(i);

		targetObject->removeSkillMod(SkillModManager::STRUCTURE, entry.getKey(), entry.getValue());
	}

	SkillModManager::instance()->verifyStructureSkillMods(targetObject);
}

bool StructureObjectImplementation::isCivicStructure() {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == NULL)
		return false;


	return ssot->isCivicStructure();
}

bool StructureObjectImplementation::isCityHall() {
	return dynamic_cast<CityHallZoneComponent*>(getZoneComponent()) != NULL;
}

bool StructureObjectImplementation::isCommercialStructure() {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == NULL)
		return false;


	return ssot->isCommercialStructure();
}

bool StructureObjectImplementation::isGuildHall() {
	for (int i = 0; i < childObjects.size(); i++) {
		GuildTerminal* child = childObjects.get(i).castTo<GuildTerminal*>();

		if (child != NULL) {
			return true;
		}
	}

	return false;
}

int StructureObjectImplementation::getBaseMaintenanceRate(){
	Reference<SharedStructureObjectTemplate*> tmpl = cast<SharedStructureObjectTemplate*>(getObjectTemplate());

	if(tmpl == NULL)
		return 0;

	return tmpl->getBaseMaintenanceRate();
}

int StructureObjectImplementation::getBasePowerRate(){
	Reference<SharedStructureObjectTemplate*> tmpl = cast<SharedStructureObjectTemplate*>(getObjectTemplate());

	if(tmpl == NULL)
		return 0;

	return tmpl->getBasePowerRate();
}

bool StructureObjectImplementation::isOnAdminList(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL && ghost->isPrivileged())
		return true;
	else if (structurePermissionList.isOnPermissionList("ADMIN", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != NULL && structurePermissionList.isOnPermissionList("ADMIN", guild->getObjectID()))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnEntryList(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL && ghost->hasGodMode())
		return true;
	else if (structurePermissionList.isOnPermissionList("ADMIN", player->getObjectID())
			|| structurePermissionList.isOnPermissionList("ENTRY", player->getObjectID())
			|| structurePermissionList.isOnPermissionList("VENDOR", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != NULL && (structurePermissionList.isOnPermissionList("ADMIN", guild->getObjectID())
				|| structurePermissionList.isOnPermissionList("ENTRY", guild->getObjectID())
				|| structurePermissionList.isOnPermissionList("VENDOR", guild->getObjectID())))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnBanList(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL && ghost->hasGodMode())
		return false;
	else if (structurePermissionList.isOnPermissionList("BAN", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != NULL && structurePermissionList.isOnPermissionList("BAN", guild->getObjectID()))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnHopperList(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL && ghost->isPrivileged())
		return true;
	else if (structurePermissionList.isOnPermissionList("HOPPER", player->getObjectID())
			|| structurePermissionList.isOnPermissionList("ADMIN", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != NULL && (structurePermissionList.isOnPermissionList("HOPPER", guild->getObjectID())
				|| structurePermissionList.isOnPermissionList("ADMIN", guild->getObjectID())))
			return true;
	}

	return false;
}

bool StructureObjectImplementation::isOnPermissionList(const String& listName, CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL && ghost->isPrivileged()) {
		if (listName == "BAN")
			return false;
		else
			return true;
	} else if (structurePermissionList.isOnPermissionList(listName, player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != NULL && structurePermissionList.isOnPermissionList(listName, guild->getObjectID()))
			return true;
	}

	return false;
}
