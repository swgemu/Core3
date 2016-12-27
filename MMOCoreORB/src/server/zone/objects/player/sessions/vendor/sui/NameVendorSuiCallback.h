/*
 * NameVendorSuiCallback.h
 *
 *  Created on: Mar 20, 2011
 *      Author: polonel
 */

#ifndef NAMEVENDORCALLBACK_H_
#define NAMEVENDORCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/CreateVendorSession.h"

class NameVendorSuiCallback : public SuiCallback {
public:
	NameVendorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isInputBox())
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

		String name = args->get(0).toString();

		session->createVendor(name);
	}
};

#endif /* NAMEVENDORCALLBACK_H_ */
