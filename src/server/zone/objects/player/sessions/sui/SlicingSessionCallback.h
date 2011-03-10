/*
 * SlicingSessionCallback.h
 *
 *  Created on: Mar 5, 2011
 *      Author: polonel
 */

#ifndef SLICINGSESSIONCALLBACK_H_
#define SLICINGSESSIONCALLBACK_H_

#include "server/zone/objects/player/sui/SuiMessageCallback.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

class SlicingSessionCallback : public SuiMessageCallback {
public:
	SlicingSessionCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiMessageCallback(client, server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox())
			return;

		if (args->size() < 1)
			return;

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::SLICING);
		ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());

		if (session == NULL) {
			ManagedReference<TangibleObject*> obj = (TangibleObject*) suiBox->getUsingObject();
			if (obj != NULL)
				obj->dropActiveSession(SessionFacadeType::SLICING);

			return;
		}

		if (cancelPressed) {
			session->cancelSession();
			return;
		}

		int idx = Integer::valueOf(args->get(0).toString());

		SuiListBox* box = (SuiListBox*) suiBox;

		byte menuID = box->getMenuObjectID(idx);

		session->handleMenuSelect(player, menuID, box);

	}
};

#endif /* SLICINGSESSIONCALLBACK_H_ */
