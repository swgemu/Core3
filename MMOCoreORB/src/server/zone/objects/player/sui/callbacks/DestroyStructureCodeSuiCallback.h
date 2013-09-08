/*
 * DestroyStructureCodeSuiCallback.h
 *
 *  Created on: Jun 22, 2011
 *      Author: crush
 */

#ifndef DESTROYSTRUCTURECODESUICALLBACK_H_
#define DESTROYSTRUCTURECODESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/DestroyStructureSession.h"


class DestroyStructureCodeSuiCallback : public SuiCallback {
public:
	DestroyStructureCodeSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<DestroyStructureSession*> session = player->getActiveSession(SessionFacadeType::DESTROYSTRUCTURE).castTo<DestroyStructureSession*>();

		if (session == NULL)
			return;

		if (cancelPressed) {
			session->cancelSession();
			return;
		}

		uint32 inputtedCode = Integer::valueOf(args->get(0).toString());

		if (!session->isDestroyCode(inputtedCode)) {
			player->sendSystemMessage("@player_structure:incorrect_destroy_code"); //You have entered an incorrect code. You will have to issue the /destroyStructure again if you wish to continue.
			session->cancelSession();
			return;
		}

		session->destroyStructure();
	}
};

#endif /* DESTROYSTRUCTURECODESUICALLBACK_H_ */
