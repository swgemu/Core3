/*
 * CitySpecializationSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYSPECIALIZATIONSUICALLBACK_H_
#define CITYSPECIALIZATIONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

class CitySpecializationSuiCallback : public SuiCallback {
public:
	CitySpecializationSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CitySpecializationSession*> session = dynamic_cast<CitySpecializationSession*>(player->getActiveSession(SessionFacadeType::CITYSPEC));

		if (session == NULL)
			return;

		if (!suiBox->isListBox() || player == NULL || cancelPressed || args->size() <= 0) {
			session->cancelSession();
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		if (index < 0 || index > listBox->getMenuSize()) {
			session->cancelSession();
			return;
		}

		String choice = listBox->getMenuItemName(index);
		session->sendConfirmationBox(choice);
	}
};

#endif /* CITYSPECIALIZATIONSUICALLBACK_H_ */
