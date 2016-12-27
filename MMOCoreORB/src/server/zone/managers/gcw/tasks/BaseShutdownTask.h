#ifndef BASESHUTDOWNTASK_H_
#define BASESHUTDOWNTASK_H_

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/BaseShutdownSuiCallback.h"

class BaseShutdownTask : public Task {
	ManagedWeakReference<BuildingObject*> building;
	ManagedWeakReference<GCWManager*> gcwMan;
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<SceneObject*> terminal;

public:
	BaseShutdownTask(GCWManager* gcwManager, BuildingObject* buildingObject, CreatureObject* creature, SceneObject* term) {
		gcwMan = gcwManager;
		building = buildingObject;
		terminal = term;
		play = creature;
	}

	void run() {
		ManagedReference<BuildingObject*> buildingObject = building.get();
		ManagedReference<GCWManager*> gcwManager = gcwMan.get();
		ManagedReference<CreatureObject*> player = play.get();
		ManagedReference<SceneObject*> hqTerminal = terminal.get();

		if (gcwManager == NULL || buildingObject == NULL || hqTerminal == NULL || player == NULL)
			return;

		ManagedReference<PlayerObject* > ghost = player->getPlayerObject();

		if (ghost == NULL)
			return;

		Locker locker(player);

		player->removePendingTask("base_shutdown");

		if (player->getParentID() == 0) {
			player->sendSystemMessage("@hq:vulnerability_reset_no_longer_in_structure"); // You don't appear to be in the structure any longer. Aborting structure shutdown.
			return;
		} else if (player->getParentID() != hqTerminal->getParentID()) {
			player->sendSystemMessage("@hq:vulnerability_reset_wrong_cell"); // You don't appear to be in the same cell you were in when you requested the facility shutdown. You need to be, in order to successfully shut down the facility. Aborting Facility Shutdown.
			return;
		} else if (player->isDead() || player->isIncapacitated()) {
			player->sendSystemMessage("@hq:vulnerability_reset_not_alive"); // 	You appear to be either incapacitated or dead. Aborting structure shutdown.
			return;
		}

		if (ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
			ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

		Observer* shutdownObserver = NULL;
		SortedVector<ManagedReference<Observer* > > observers = player->getObservers(ObserverEventType::PARENTCHANGED);

		for (int i = 0; i < observers.size(); i++) {
			Observer* observer = observers.get(i);

			if (observer->isObserverType(ObserverType::GCWBASESHUTDOWN)) {
				shutdownObserver = observer;
				break;
			}
		}

		if (shutdownObserver != NULL) {
			player->dropObserver(ObserverEventType::PARENTCHANGED, shutdownObserver);
			player->dropObserver(ObserverEventType::OBJECTDESTRUCTION, shutdownObserver);
		}

		ManagedReference<SuiMessageBox*> suiMessageBox = new SuiMessageBox(player, SuiWindowType::HQ_TERMINAL);
		suiMessageBox->setPromptTitle("@faction/faction_hq/faction_hq_response:terminal_response27"); // Confirm Facility Shutdown
		suiMessageBox->setPromptText("@faction/faction_hq/faction_hq_response:terminal_response28"); // Are you sure that you want to shut down the facility?
		suiMessageBox->setCancelButton(true, "Cancel");
		suiMessageBox->setUsingObject(hqTerminal);
		suiMessageBox->setCallback(new BaseShutdownSuiCallback(player->getZoneServer()));
		ghost->addSuiBox(suiMessageBox);
		player->sendMessage(suiMessageBox->generateMessage());
	}
};

#endif /* BASESHUTDOWNTASK_H_ */
