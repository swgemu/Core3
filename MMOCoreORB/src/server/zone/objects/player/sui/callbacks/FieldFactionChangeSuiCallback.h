#ifndef FIELDFACTIONCHANGESUICALLBACK_H_
#define FIELDFACTIONCHANGESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/FactionStatus.h"

class FieldFactionChangeSuiCallback : public SuiCallback {
private:
	int newStatus;
public:
	virtual ~FieldFactionChangeSuiCallback() { }

	FieldFactionChangeSuiCallback(ZoneServer* server, int status)
		: SuiCallback(server) {
		newStatus = status;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || args->size() < 1) {
			player->sendSystemMessage("@gcw:abort_field_change"); // You cancel your factional change.
			return;
		}

		String arg1 = args->get(0).toString();

		if (arg1.toLowerCase() != "yes") {
			player->sendSystemMessage("@gcw:abort_field_change"); // You cancel your factional change.
			return;
		}

		if (player->getFutureFactionStatus() != -1)
			return;

		int curStatus = player->getFactionStatus();

		if (curStatus == newStatus)
			return;

		if (newStatus == FactionStatus::COVERT) {
			if (curStatus == FactionStatus::OVERT) {
				player->sendSystemMessage("@gcw:cannot_change_from_combatant_in_field"); // You cannot change you status to combatant in the field. Go talk to a faction recruiter.
				return;
			}

			player->sendSystemMessage("@gcw:handle_go_covert"); // You will be flagged as a Combatant in 30 seconds.
			player->setFutureFactionStatus(FactionStatus::COVERT);

			ManagedReference<CreatureObject*> creo = player->asCreatureObject();

			Core::getTaskManager()->scheduleTask([creo]{
				if(creo != NULL) {
					Locker locker(creo);

					creo->setFactionStatus(FactionStatus::COVERT);
				}
			}, "UpdateFactionStatusTask", 30000);
		} else if (newStatus == FactionStatus::OVERT) {
			player->sendSystemMessage("You will be flagged as Special Forces in 5 minutes."); // No string available for overt.
			player->setFutureFactionStatus(FactionStatus::OVERT);

			ManagedReference<CreatureObject*> creo = player->asCreatureObject();

			Core::getTaskManager()->scheduleTask([creo]{
				if(creo != NULL) {
					Locker locker(creo);

					creo->setFactionStatus(FactionStatus::OVERT);
				}
			}, "UpdateFactionStatusTask", 300000);
		}
	}
};

#endif /* FIELDFACTIONCHANGESUICALLBACK_H_ */
