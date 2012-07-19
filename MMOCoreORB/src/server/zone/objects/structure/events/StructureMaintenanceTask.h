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
	ManagedWeakReference<StructureObject* > structureObject;
	ManagedWeakReference<BuildingObject* > buildingObject;
	const static int oneDayTime = 24 * 60 * 60 * 1000;

public:
	StructureMaintenanceTask(StructureObject* structure) : Task(), Logger("StructureMaintenanceTask") {
		structureObject = structure;
		if (structure->isBuildingObject()) {
			buildingObject = cast<BuildingObject* >(structure);
		} else {
			buildingObject = NULL;
		}
	}

	void run() {
		ManagedReference<StructureObject*> strongRef = structureObject.get();
		ManagedReference<BuildingObject*> strongBuildingRef = buildingObject.get();

		if (strongRef == NULL) {
			return;
		}

		if (strongRef->getZone() == NULL)
			return;

		if (strongRef->getSurplusMaintenance() > 0) {
			//Incorrect scheduling, reschedule.
			Locker locker(strongRef);

			strongRef->scheduleMaintenanceExpirationEvent();
			return;
		}

		//Structure is out of maintenance. Start the decaying process...
		strongRef->updateStructureStatus();
		ManagedReference<CreatureObject* > owner = strongRef->getOwnerCreatureObject();
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
		int oneWeekMaintenance = 7 * 24 * strongRef->getMaintenanceRate() - strongRef->getSurplusMaintenance();

		Locker _ownerLock(owner);
		Locker _lock(strongRef, owner);

		//Check if owner got money in the bank and structure not decaying.
		if (owner->getBankCredits() >= oneWeekMaintenance && !strongRef->isDecaying()) {
			//Withdraw 1 week maintenance from owner bank account and add to the structure
			//maintenance pool.
			strongRef->payMaintenance(oneWeekMaintenance, owner, false);

			//Send email notification to owner.
			sendMailMaintenanceWithdrawnFromBank(owner);

			//Reschedule task in 1 week.
			strongRef->scheduleMaintenanceExpirationEvent();
		} else {
			//Start decay process.

			//Notify owner about decay.
			sendMailDecay(owner);
			if (!strongRef->isDecayed()) {
				//Reschedule task in 1 day.
				reschedule(oneDayTime);
			} else {
				if (strongRef->isBuildingObject() && strongBuildingRef != NULL) {
					//Building is condemned since it has decayed.
					sendMailCondemned(owner);
					strongRef->info("Structure decayed, it is now condemned.");
					strongBuildingRef->updateSignName(true);
				} else {
					strongRef->info("Structure decayed, destroying it.");
					StructureManager* structureManager = strongRef->getZone()->getStructureManager();
					structureManager->destroyStructure(strongRef);
				}
			}
		}
	}

	void sendMailMaintenanceWithdrawnFromBank(CreatureObject* owner) {
		//Create an email.
		ManagedReference<StructureObject*> strongRef = structureObject.get();

		ManagedReference<ChatManager*> chatManager =  strongRef->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:structure_maintenance_empty_subject";

			//Your %TT %TO has an empty maintenance pool. It will start deducting from your bank account automatically.
			StringIdChatParameter emailBody("@player_structure:structure_maintenance_empty_body");
			emailBody.setTT(strongRef->getObjectName());
			emailBody.setTO("(" + String::valueOf((int)strongRef->getPositionX()) + ", " + String::valueOf((int)strongRef->getPositionY()) + ")");

			chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, owner->getFirstName());
		}
	}

	void sendMailDecay(CreatureObject* owner) {
		//Create an email.
		ManagedReference<StructureObject*> strongRef = structureObject.get();

		ManagedReference<ChatManager*> chatManager = strongRef->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:mail_structure_damage_sub";

			//Your %TT %TO is currently at %DI percent condition. It will be destroyed if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
			String bodyName = "mail_structure_damage";
			if (strongRef->isBuildingObject()) {
				//Your %TT %TO is currently at %DI percent condition. It will be condemned if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
				bodyName = "mail_structure_damage_condemn";
			}

			StringIdChatParameter emailBody("@player_structure:" + bodyName);
			emailBody.setTT(strongRef->getObjectName());
			emailBody.setTO("(" + String::valueOf((int)strongRef->getPositionX()) + ", " + String::valueOf((int)strongRef->getPositionY()) + ")");
			emailBody.setDI(strongRef->getDecayPercentage());

			chatManager->sendMail("@player_structure:your_structure_prefix", subject, emailBody, owner->getFirstName());
		}
	}

	void sendMailCondemned(CreatureObject* owner) {
		ManagedReference<StructureObject*> strongRef = structureObject.get();
		//Create an email.
		ManagedReference<ChatManager*> chatManager = strongRef->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:structure_condemned_subject";

			//Your %TT %TO has been condemned by the order of the Empire due to lack of maintenance. You must pay %DI credits to uncondemn this structure.
			StringIdChatParameter emailBody("@player_structure:structure_condemned_body");
			emailBody.setTT(strongRef->getObjectName());
			emailBody.setTO("(" + String::valueOf((int)strongRef->getPositionX()) + ", " + String::valueOf((int)strongRef->getPositionY()) + ")");
			emailBody.setDI(-strongRef->getSurplusMaintenance());
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
