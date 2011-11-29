/*
 * StructureMaintenanceTask.h
 *
 *  Created on: Aug 19, 2010
 *      Author: crush
 */

#ifndef STRUCTUREMAINTENANCETASK_H_
#define STRUCTUREMAINTENANCETASK_H_

#include "../StructureObject.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/structure/StructureManager.h"

namespace server {
namespace zone {
namespace objects {
namespace structure {
namespace events {

class StructureMaintenanceTask : public Task, public Logger {
protected:
	WeakReference<StructureObject* > structureObject;
	WeakReference<BuildingObject* > buildingObject;
	const static int oneDayTime = 24 * 60 * 60 * 1000;

public:
	StructureMaintenanceTask(StructureObject* structure) : Task(), Logger("StructureMaintenanceTask") {
		structureObject = structure;
		if (structureObject->isBuildingObject()) {
			buildingObject = cast<BuildingObject* >(structure);
		} else {
			buildingObject = NULL;
		}
	}

	void run() {
		ManagedReference<StructureObject*> strongRef = structureObject.get();

		if (structureObject == NULL) {
			return;
		}

		if (structureObject->getSurplusMaintenance() > 0) {
			//Incorrect scheduling, reschedule.
			structureObject->scheduleMaintenanceExpirationEvent();
			return;
		}

		//Structure is out of maintenance. Start the decaying process...
		structureObject->updateStructureStatus();
		ManagedReference<CreatureObject* > owner = structureObject->getOwnerCreatureObject();
		if (owner == NULL) {
			//structureObject->error("Could not find CreatureObject for the structure owner.");
			//TODO: Decide if object should be destroyed or transferred to someone else.
			return;
		}
		ManagedReference<PlayerObject* > ghost = owner->getPlayerObject();
		if (ghost == NULL) {
			//structureObject->error("Could not find PlayerObject for the structure owner.");
			//TODO: Decide if object should be destroyed or transferred to someone else.
			return;
		}

		//Calculate one week of maintenance +- any existing maintenance/decay.
		int oneWeekMaintenance = 7 * 24 * structureObject->getMaintenanceRate() - structureObject->getSurplusMaintenance();

		Locker _ownerLock(owner);
		Locker _lock(structureObject, owner);

		//Check if owner got money in the bank and structure not decaying.
		if (owner->getBankCredits() >= oneWeekMaintenance && !structureObject->isDecaying()) {
			//Withdraw 1 week maintenance from owner bank account and add to the structure
			//maintenance pool.
			structureObject->payMaintenance(oneWeekMaintenance, owner);

			//Send email notification to owner.
			sendMailMaintenanceWithdrawnFromBank(owner);

			//Reschedule task in 1 week.
			structureObject->scheduleMaintenanceExpirationEvent();
		} else {
			//Start decay process.

			//Notify owner about decay.
			sendMailDecay(owner);
			if (!structureObject->isDecayed()) {
				//Reschedule task in 1 day.
				reschedule(oneDayTime);
			} else {
				if (structureObject->isBuildingObject() && buildingObject != NULL) {
					//Building is condemned since it has decayed.
					sendMailCondemned(owner);
					structureObject->info("Structure decayed, it is now condemned.");
					buildingObject->updateSignName(true);
				} else {
					structureObject->info("Structure decayed, destroying it.");
					StructureManager* structureManager = structureObject->getZone()->getStructureManager();
					structureManager->destroyStructure(structureObject);
				}
			}
		}
	}

	void sendMailMaintenanceWithdrawnFromBank(CreatureObject* owner) {
		//Create an email.
		ManagedReference<ChatManager*> chatManager =  structureObject->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:structure_maintenance_empty_subject";

			//Your %TT %TO has an empty maintenance pool. It will start deducting from your bank account automatically.
			StringIdChatParameter emailBody("@player_structure:structure_maintenance_empty_body");
			emailBody.setTT(structureObject->getObjectName());
			emailBody.setTO("(" + String::valueOf((int)structureObject->getPositionX()) + ", " + String::valueOf((int)structureObject->getPositionY()) + ")");

			chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, owner->getFirstName());
		}
	}

	void sendMailDecay(CreatureObject* owner) {
		//Create an email.
		ManagedReference<ChatManager*> chatManager = structureObject->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:mail_structure_damage_sub";

			//Your %TT %TO is currently at %DI percent condition. It will be destroyed if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
			String bodyName = "mail_structure_damage";
			if (structureObject->isBuildingObject()) {
				//Your %TT %TO is currently at %DI percent condition. It will be condemned if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
				bodyName = "mail_structure_damage_condemn";
			}

			StringIdChatParameter emailBody("@player_structure:" + bodyName);
			emailBody.setTT(structureObject->getObjectName());
			emailBody.setTO("(" + String::valueOf((int)structureObject->getPositionX()) + ", " + String::valueOf((int)structureObject->getPositionY()) + ")");
			emailBody.setDI(structureObject->getDecayPercentage());

			chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, owner->getFirstName());
		}
	}

	void sendMailCondemned(CreatureObject* owner) {
		//Create an email.
		ManagedReference<ChatManager*> chatManager = structureObject->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:structure_condemned_subject";

			//Your %TT %TO has been condemned by the order of the Empire due to lack of maintenance. You must pay %DI credits to uncondemn this structure.
			StringIdChatParameter emailBody("@player_structure:structure_condemned_body");
			emailBody.setTT(structureObject->getObjectName());
			emailBody.setTO("(" + String::valueOf((int)structureObject->getPositionX()) + ", " + String::valueOf((int)structureObject->getPositionY()) + ")");
			emailBody.setDI(-structureObject->getSurplusMaintenance());
			chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, owner->getFirstName());
		}
	}

};

}
}
}
}
}

using namespace server::zone::objects::structure::events;

#endif /* STRUCTUREMAINTENANCETASK_H_ */
