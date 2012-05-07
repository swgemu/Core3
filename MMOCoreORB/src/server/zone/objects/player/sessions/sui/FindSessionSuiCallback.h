/*
 * FindSessionSuiCallback.h
 *
 *  Created on: Jun 24, 2011
 *      Author: polonel
 */

#ifndef FINDSESSIONSUICALLBACK_H_
#define FINDSESSIONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/FindSession.h"

class FindSessionSuiCallback : public SuiCallback {
public:
	FindSessionSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
				return;

		if (args->size() < 1)
			return;

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::FIND);
		ManagedReference<FindSession*> session = dynamic_cast<FindSession*>(facade.get());

		if (session == NULL) {
			ManagedReference<CreatureObject*> pl = cast<CreatureObject*>( suiBox->getUsingObject());
			if (pl != NULL)
				pl->dropActiveSession(SessionFacadeType::FIND);

			return;
		}

		if (cancelPressed) {
			session->cancelSession();
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1) {
			session->cancelSession();
			return;
		}

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		String maploctype = listBox->getMenuItemName(index).subString(14);

		session->findPlanetaryObject(maploctype);
	}
};

#endif /* FINDSESSIONSUICALLBACK_H_ */
