/*
 * DroidMaintenanceSessionRunMenuSuiCallback.h
 *
 */

#ifndef DROIDMAINTSESSIONPAYUSUICALLBACK_H_
#define DROIDMAINTSESSIONPAYUSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/DroidMaintenanceSession.h"

class DroidMaintenanceSessionAddCreditsSuiCallback : public SuiCallback {
public:
	DroidMaintenanceSessionAddCreditsSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isTransferBox() || cancelPressed || args->size() < 2)
			return;

		int amount = Integer::valueOf(args->get(1).toString());


		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::DROIDMAINTENANCERUN);
		ManagedReference<DroidMaintenanceSession*> session = dynamic_cast<DroidMaintenanceSession*>(facade.get());
		if (session == NULL) {
			player->dropActiveSession(SessionFacadeType::DROIDMAINTENANCERUN);
			return;
		}
		if (amount < 0 || amount > session->getAvailableCredits()) {
			player->sendSystemMessage("@pet/droid_modules:droid_maint_invalid_amount");
			session->cancelSession();
			return;
		} else {
			session->addCreditsToCurrentStructure(amount);
		}

		// no matter that they did send them back to the main screen
		session->sendMaintanceRunBox();
	}
};

#endif /* DROIDMAINTSESSIONPAYUSUICALLBACK_H_ */
