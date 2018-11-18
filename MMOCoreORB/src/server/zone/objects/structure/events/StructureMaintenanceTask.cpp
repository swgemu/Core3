/*
 * StructureMaintenanceTask.cpp
 *
 *  Created on: Aug 1, 2012
 *      Author: swgemu
 */

#include "StructureMaintenanceTask.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/credit/CreditManager.h"

void StructureMaintenanceTask::run() {
	ManagedReference<StructureObject*> strongRef = structureObject.get();

	if (strongRef == nullptr)
		return;

	ZoneServer* zoneServer = strongRef->getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerShuttingDown())
		return;

	if (zoneServer->isServerLoading()) {
		schedule(1000);

		return;
	}

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	uint64 oid = strongRef->getOwnerObjectID();
	String name = playerManager->getPlayerName(oid);

	ManagedReference<CreditObject*> creditObj = CreditManager::getCreditObject(oid);

	if (creditObj == nullptr) {
		strongRef->info("Player does not have a valid credit object, destroying.", true);
		StructureManager::instance()->destroyStructure(strongRef);

		return;
	}

	if (name.isEmpty()) {
		strongRef->info("Player structure has nullptr owner ghost, destroying.", true);
		StructureManager::instance()->destroyStructure(strongRef);
		return;
	}

	if (strongRef->getSurplusMaintenance() > 0) {
		//Incorrect scheduling, reschedule.
		Locker locker(strongRef);

		strongRef->scheduleMaintenanceExpirationEvent();
		return;
	}

	Locker _lock(strongRef);
	Locker locker(creditObj, strongRef);

	//Structure is out of maintenance. Start the decaying process...
	strongRef->updateStructureStatus();

	//Calculate one week of maintenance +- any existing maintenance/decay.
	int oneWeekMaintenance = 7 * 24 * strongRef->getMaintenanceRate() - strongRef->getSurplusMaintenance();

	// add city tax to the week maintenance
	ManagedReference<CityRegion*> city = strongRef->getCityRegion().get();
	if(strongRef->isBuildingObject() && city != nullptr){
		oneWeekMaintenance += city->getPropertyTax() / 100.0f * oneWeekMaintenance;
	}

	int uncondemnCost = -strongRef->getSurplusMaintenance();

	if (uncondemnCost > 0)
		oneWeekMaintenance += uncondemnCost;

	//Check if owner got money in the bank and structure not decaying.
	if (creditObj->getBankCredits() >= oneWeekMaintenance) {
		//Withdraw 1 week maintenance from owner bank account and add to the structure
		//maintenance pool.
		strongRef->payMaintenance(oneWeekMaintenance, creditObj, false);

		if (strongRef->isDecayed() && strongRef->isBuildingObject()) {
			BuildingObject* building = strongRef.castTo<BuildingObject*>();

			if (building != nullptr)
				building->updateSignName(true);
		}

		//Send email notification to owner.
		sendMailMaintenanceWithdrawnFromBank(name, strongRef);

		//Reschedule task in 1 week.
		strongRef->scheduleMaintenanceExpirationEvent();
	} else {
		//Start decay process.

		//Notify owner about decay.
		sendMailDecay(name, strongRef);

		int decay_cycle_seconds = 24 * 60 * 60; // Default to daily schedule

#if DEBUG_STRUCTURE_MAINT
		decay_cycle_seconds = 60; // Every minute for debugging
#endif // DEBUG_STRUCTURE_MAINT

		if (!strongRef->isDecayed()) {
			// Reschedule task
			reschedule(decay_cycle_seconds * 1000);
		} else {
			if (strongRef->isBuildingObject() && !shouldBuildingBeDestroyed(strongRef)) {
				BuildingObject* building = strongRef.castTo<BuildingObject*>();

				//Building is condemned since it has decayed.
				sendMailCondemned(name, strongRef);

				strongRef->info("Structure decayed, it is now condemned.", true);

				building->updateSignName(true);
				reschedule(decay_cycle_seconds * 1000);
			} else {
				strongRef->info("Structure decayed, destroying it.", true);

				StructureManager::instance()->destroyStructure(strongRef);
			}
		}
	}
}

void StructureMaintenanceTask::sendMailMaintenanceWithdrawnFromBank(const String& creoName, StructureObject* structure) {
	ManagedReference<ChatManager*> chatManager = structure->getZoneServer()->getChatManager();

	if (chatManager != nullptr) {
		UnicodeString subject = "@player_structure:structure_maintenance_empty_subject";

		String zoneName = "the void";
		if (structure->getZone() != nullptr) {
			zoneName = structure->getZone()->getZoneName();
		}

		//Your %TT %TO has an empty maintenance pool. It will start deducting from your bank account automatically.
		StringIdChatParameter emailBody("@player_structure:structure_maintenance_empty_body");
		emailBody.setTT(structure->getObjectName());
		emailBody.setTO("(" + String::valueOf((int)structure->getPositionX()) + ", " + String::valueOf((int)structure->getPositionY()) + " on " + zoneName + ")");

		chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, creoName);
	}
}

void StructureMaintenanceTask::sendMailDecay(const String& creoName, StructureObject* structure) {
	ManagedReference<ChatManager*> chatManager = structure->getZoneServer()->getChatManager();

	if (chatManager != nullptr) {
		UnicodeString subject = "@player_structure:mail_structure_damage_sub";

		//Your %TT %TO is currently at %DI percent condition. It will be destroyed if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
		String bodyName = "mail_structure_damage";
		if (structure->isBuildingObject()) {
			//Your %TT %TO is currently at %DI percent condition. It will be condemned if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
			bodyName = "mail_structure_damage_condemn";
		}

		String zoneName = "the void";
		if (structure->getZone() != nullptr) {
			zoneName = structure->getZone()->getZoneName();
		}

		StringIdChatParameter emailBody("@player_structure:" + bodyName);
		emailBody.setTT(structure->getObjectName());
		emailBody.setTO("(" + String::valueOf((int)structure->getPositionX()) + ", " + String::valueOf((int)structure->getPositionY()) + " on " + zoneName + ")");
		emailBody.setDI(structure->getDecayPercentage());

		chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, creoName);
	}
}

void StructureMaintenanceTask::sendMailCondemned(const String& creoName, StructureObject* structure) {
	//Create an email.
	ManagedReference<ChatManager*> chatManager = structure->getZoneServer()->getChatManager();

	if (chatManager != nullptr) {
		UnicodeString subject = "@player_structure:structure_condemned_subject";

		String zoneName = "the void";
		if (structure->getZone() != nullptr) {
			zoneName = structure->getZone()->getZoneName();
		}

		//Your %TT %TO has been condemned by the order of the Empire due to lack of maintenance. You must pay %DI credits to uncondemn this structure.
		StringIdChatParameter emailBody("@player_structure:structure_condemned_body");
		emailBody.setTT(structure->getObjectName());
		emailBody.setTO("(" + String::valueOf((int)structure->getPositionX()) + ", " + String::valueOf((int)structure->getPositionY()) + " on " + zoneName + ")");
		emailBody.setDI(-structure->getSurplusMaintenance());
		chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, creoName);
	}
}

bool StructureMaintenanceTask::shouldBuildingBeDestroyed(StructureObject* structure) {
	int destroy_delay_hours = 30 * 24; // By default delay destruction by 30 days

#if DEBUG_STRUCTURE_MAINT
	destroy_delay_hours = 1; // Delay destruction by 1 hour in debug mode
#endif // DEBUG_STRUCTURE_MAINT

	// Still not negative enough to destroy?
	if ((destroy_delay_hours * structure->getMaintenanceRate()) + structure->getSurplusMaintenance() > 0) {
		return false;
	}

	return true;
}
