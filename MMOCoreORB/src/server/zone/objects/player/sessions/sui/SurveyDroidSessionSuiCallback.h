/*
 * SlicingSessionSuiCallback.h
 *
 *  Created on: Mar 5, 2011
 *      Author: polonel
 */

#ifndef SURVEYDRIODCALLBACK_H_
#define SURVEYDRIODCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

class SurveyDroidSessionSuiCallback : public SuiCallback {
public:
	SurveyDroidSessionSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox())
			return;

		if (args->size() < 1)
			return;

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::INTERPLANETARYSURVEYDROID);
		ManagedReference<InterplanetarySurveyDroidSession*> session = dynamic_cast<InterplanetarySurveyDroidSession*>(facade.get());

		if (session == NULL) {
			ManagedReference<TangibleObject*> obj = cast<TangibleObject*>( suiBox->getUsingObject().get().get());
			if (obj != NULL)
				Locker crosslock(obj, player);
				obj->dropActiveSession(SessionFacadeType::INTERPLANETARYSURVEYDROID);

			return;
		}

		if (cancelPressed) {
			session->cancelSession();
			return;
		}

		uint64 idx = Long::unsignedvalueOf(args->get(0).toString());
		SuiListBox* box = cast<SuiListBox*>( suiBox);
		session->handleMenuSelect(player, idx, box);

	}
};

#endif /* SURVEYDRIODCALLBACK_H_ */
