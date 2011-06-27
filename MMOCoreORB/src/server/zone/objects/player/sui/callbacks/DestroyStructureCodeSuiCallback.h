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

	void run(PlayerCreature* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<DestroyStructureSession*> session = dynamic_cast<DestroyStructureSession*>(player->getActiveSession(SessionFacadeType::DESTROYSTRUCTURE));

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

		//Start a task to handle this????

		//ManagedReference<SceneObject*> deed = structureManager->destroyStructure();

		//if (deed == NULL) {
			//player->sendSystemMessage("@player_structure:structure_destroyed"); //Structure destroyed.
			//cancelSession();
			//return;
		//}

		//Return the deed
		session->cancelSession();
	}
};

#endif /* DESTROYSTRUCTURECODESUICALLBACK_H_ */
