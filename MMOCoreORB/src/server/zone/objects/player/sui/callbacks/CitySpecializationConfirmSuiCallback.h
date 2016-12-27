/*
 * CitySpecializationConfirmSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYSPECIALIZATIONCONFIRMSUICALLBACK_H_
#define CITYSPECIALIZATIONCONFIRMSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/CitySpecializationSession.h"

class CitySpecializationConfirmSuiCallback : public SuiCallback {
public:
	CitySpecializationConfirmSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<CitySpecializationSession*> session = player->getActiveSession(SessionFacadeType::CITYSPEC).castTo<CitySpecializationSession*>();

		if (session == NULL)
			return;

		if (!suiBox->isMessageBox() || cancelPressed) {
			session->cancelSession();
			return;
		}

		session->acceptChoice();
	}
};

#endif /* CITYSPECIALIZATIONCONFIRMSUICALLBACK_H_ */
