/*
 * DestroyStructureRequestSuiCallback.h
 *
 *  Created on: Jun 22, 2011
 *      Author: crush
 */

#ifndef DESTROYSTRUCTUREREQUESTSUICALLBACK_H_
#define DESTROYSTRUCTUREREQUESTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/DestroyStructureSession.h"

class DestroyStructureRequestSuiCallback : public SuiCallback {
public:
	DestroyStructureRequestSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<DestroyStructureSession*> session = player->getActiveSession(SessionFacadeType::DESTROYSTRUCTURE).castTo<DestroyStructureSession*>();

		if (session == NULL)
			return;

		if (cancelPressed) {
			session->cancelSession();
			return;
		}

		session->sendDestroyCode();
	}
};

#endif /* DESTROYSTRUCTUREREQUESTSUICALLBACK_H_ */
