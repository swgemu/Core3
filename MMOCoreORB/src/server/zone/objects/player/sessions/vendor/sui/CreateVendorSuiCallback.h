/*
 * CreateVendorSuiCallback.h
 *
 *  Created on: Mar 18, 2011
 *      Author: polonel
 */

#ifndef CREATEVENDORCALLBACK_H_
#define CREATEVENDORCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sessions/vendor/CreateVendorSession.h"

class CreateVendorSuiCallback : public SuiCallback {
public:
	CreateVendorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox())
			return;

		if (args->size() < 1)
			return;

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::CREATEVENDOR);
		ManagedReference<CreateVendorSession*> session = dynamic_cast<CreateVendorSession*>(facade.get());

		if (session == NULL)
			return;

		if (cancelPressed) {
			session->cancelSession();
			return;
		}

		int idx = Integer::valueOf(args->get(0).toString());
		SuiListBox* box = (SuiListBox*) suiBox;
		byte menuID = box->getMenuObjectID(idx);

		session->handleMenuSelect(menuID);

	}
};

#endif /* CREATEVENDORCALLBACK_H_ */
