/*
 * InstallationObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: crush
 */

#include "server/zone/objects/installation/InstallationObject.h"
#include "sui/InsertPowerSuiCallback.h"

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/faction/FactionManager.h"

#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/Zone.h"
#include "templates/installation/SharedInstallationObjectTemplate.h"
#include "components/TurretDataComponent.h"
#include "InstallationTickTask.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/params/OptionBitmask.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"

void InstallationObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	StructureObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isSharedInstallationObjectTemplate())
		return;

	SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(templateData);

	installationType = inso->getInstallationType();

}

void InstallationObjectImplementation::doTick() {
	if(isCivicStructure())
		return;

	if (surplusMaintenance < 0) {
		setConditionDamage(-surplusMaintenance, true);
	} else {
		setConditionDamage(0, true);
	}
}

void InstallationObjectImplementation::activate(CreatureObject* player) {
	if (activated)
		return;

	int curPower = getSurplusPower();

	if (curPower <= 0 && getBasePowerRate() > 0) {
		player->sendSystemMessage("@shared:harvester_no_power"); // No power available. Shutting down. (Choose "deposit power" to add power.)
		return;
	}

	activated = true;
	setOptionBit(OptionBitmask::ACTIVATED, false);

	scheduleTickTask();
}

void InstallationObjectImplementation::deactivate(CreatureObject* player) {
	if (!activated)
		return;

	activated = false;
	clearOptionBit(OptionBitmask::ACTIVATED, false);

	scheduleTickTask(true);
}

void InstallationObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	//TangibleObjectImplementation::fillAttributeList(alm, object);

	if (isOnAdminList(object)) {

		//Add the owner name to the examine window.
		ManagedReference<SceneObject*> obj = object->getZoneServer()->getObject(ownerObjectID);

		if(obj != nullptr) {
			alm->insertAttribute("owner", obj->getDisplayedName());
		}
	}
	if(isTurret() && dataObjectComponent != nullptr){

		TurretDataComponent* turretData = cast<TurretDataComponent*>(dataObjectComponent.get());
			if(turretData == nullptr)
				return;

			turretData->fillAttributeList(alm);
	}

}

void InstallationObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	StructureObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (!destroyContainedObjects)
		return;

	ManagedReference<SceneObject*> deed = getZoneServer()->getObject(deedObjectID);

	if (deed != nullptr) {
		Locker locker(deed);
		deed->destroyObjectFromDatabase(true);
	}

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);

		Locker locker(container);
		container->destroyObjectFromDatabase(true);
	}
}

bool InstallationObjectImplementation::isAggressiveTo(CreatureObject* target) {
	// info(true) << "InstallationObjectImp isAggressiveTo check called";

	if (target == nullptr || target->isVehicleObject() || target->isInvisible())
		return false;

	bool targetIsPlayer = target->isPlayerCreature();
	bool targetIsAgent = target->isAiAgent();

	// Get factions
	uint32 thisFaction = getFaction();
	uint32 targetFaction = target->getFaction();

	PlayerObject* ghost = target->getPlayerObject();

	if (targetIsPlayer && ghost != nullptr && ghost->hasCrackdownTefTowards(thisFaction)) {
		return true;
	}

	if (thisFaction != 0 && targetFaction != 0 && thisFaction != targetFaction)
		return true;

	SharedInstallationObjectTemplate* instTemplate = templateObject.castTo<SharedInstallationObjectTemplate*>();

	if (instTemplate != nullptr) {
		String factionString = instTemplate->getFactionString();

		if (!factionString.isEmpty()) {
			if (targetIsAgent) {
				AiAgent* targetAi = target->asAiAgent();

				if (FactionManager::instance()->isEnemy(factionString, targetAi->getFactionString()))
					return true;
			} else if (targetIsPlayer) {
				PlayerObject* ghost = target->getPlayerObject();

				if (ghost == nullptr)
					return false;

				if (ghost->getFactionStanding(factionString) <= -3000)
					return true;

				FactionMap* fMap = FactionManager::instance()->getFactionMap();

				const Faction& faction = fMap->get(factionString);
				const SortedVector<String>* enemies = faction.getEnemies();

				for (int i = 0; i < enemies->size(); ++i) {
					const String& enemy = enemies->get(i);

					if (ghost->getFactionStanding(enemy) >= 3000)
						return true;
				}

				if (thisFaction == 0 && isAttackableBy(target))
					return true;
			}
		}
	}

	// info(true) << "InstallationObjectImp isAggressiveTo returning false";

	return false;
}

bool InstallationObjectImplementation::isAttackableBy(CreatureObject* creature) {
	if (creature == nullptr)
		return false;

	// info(true) << "InstallationObjectImp isAttackableBy called for " << getObjectID() << "  with attacker creature of " << creature->getObjectID();

	if (!(getPvpStatusBitmask() & CreatureFlag::ATTACKABLE)) {
		return false;
	}

	// Check attacker types
	bool creatureIsPlayer = creature->isPlayerCreature();
	bool creatureIsAgent = creature->isAiAgent();

	// Get Faction Strings
	uint32 thisFaction = getFaction();
	uint32 otherFaction = creature->getFaction();

	if (creature->isPet()) {
		ManagedReference<PetControlDevice*> pcd = creature->getControlDevice().get().castTo<PetControlDevice*>();

		if (pcd != nullptr && pcd->getPetType() == PetManager::FACTIONPET && isNeutral()) {
			return false;
		}

		ManagedReference<CreatureObject*> owner = creature->getLinkedCreature().get();

		if (owner == nullptr)
			return false;

		return isAttackableBy(owner);

	} else if (creatureIsPlayer && thisFaction != 0) {
		Reference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost != nullptr && ghost->hasCrackdownTefTowards(thisFaction)) {
			return true;
		}

		if (creature->getFactionStatus() == 0) {
			return false;
		}

		if ((getPvpStatusBitmask() & CreatureFlag::OVERT) && creature->getFactionStatus() != FactionStatus::OVERT) {
			return false;
		}
	}

	if (otherFaction != 0 && thisFaction != 0 && otherFaction == thisFaction) {
		return false;
	}

	SharedInstallationObjectTemplate* instTemplate = templateObject.castTo<SharedInstallationObjectTemplate*>();

	if (instTemplate != nullptr) {
		String factionString = instTemplate->getFactionString();

		if (!factionString.isEmpty()) {
			if (creature->isAiAgent() && !FactionManager::instance()->isEnemy(factionString, creature->asAiAgent()->getFactionString()))
				return false;
			else if (creatureIsPlayer && getObjectTemplate()->getFullTemplateString().contains("turret_fs_village"))
				return false;
		}
	}

	// info(true) << "InstallationObjectImp isAttackableBy returning true";

	return true;
}

void InstallationObjectImplementation::createChildObjects() {
	if (isTurret()) {
		SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(getObjectTemplate());

		if (inso != nullptr) {
			uint32 defaultWeaponCRC = inso->getWeapon().hashCode();

			if (getZoneServer() != nullptr) {
				Reference<WeaponObject*> defaultWeapon = (getZoneServer()->createObject(defaultWeaponCRC, getPersistenceLevel())).castTo<WeaponObject*>();

				if (defaultWeapon == nullptr) {
					return;
				}

				if (!transferObject(defaultWeapon, 4)) {
					defaultWeapon->destroyObjectFromDatabase(true);
					return;
				}

				if (dataObjectComponent != nullptr) {
					TurretDataComponent* turretData = cast<TurretDataComponent*>(dataObjectComponent.get());

					if (turretData != nullptr) {
						turretData->setWeapon(defaultWeapon);
					}
				}
			}
		}
	} else if (isMinefield()) {
		this->setContainerDefaultAllowPermission(ContainerPermissions::MOVEIN);
		this->setContainerDefaultDenyPermission(ContainerPermissions::MOVEOUT);
		this->setContainerDefaultAllowPermission(ContainerPermissions::OPEN);

	} else {
		StructureObjectImplementation::createChildObjects();
	}
}

float InstallationObjectImplementation::getHitChance() const {
	const SharedInstallationObjectTemplate* inso = dynamic_cast<const SharedInstallationObjectTemplate*>(getObjectTemplate());

	if (inso == nullptr)
		return 0;

	return inso->getChanceHit();
}
