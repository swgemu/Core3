/*
 * PlayerTeachConfirmSuiCallback.h
 *
 *  Created on: Mar 13, 2012
 *      Author: katherine
 */

#ifndef PLAYERTEACHCONFIRMSUICALLBACK_H_
#define PLAYERTEACHCONFIRMSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/variables/Skill.h"

class PlayerTeachConfirmSuiCallback: public SuiCallback {
	WeakReference<Skill*> skill;

public:
	PlayerTeachConfirmSuiCallback(ZoneServer* serv, Skill* skl) : SuiCallback(serv) {
		skill = skl;
	}

	void run(CreatureObject* student, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<SceneObject*> usingObject = sui->getUsingObject();

		if (usingObject == NULL || !usingObject->isCreatureObject())
			return;

		CreatureObject* teacher = cast<CreatureObject*>(usingObject.get());

		if (cancelPressed) {
			StringIdChatParameter params("teaching", "offer_refused"); //%TT has refused your offer to teach.
			params.setTT(student->getDisplayedName());
			teacher->sendSystemMessage(params);
			return;
		}

		Locker _lock(teacher, student);

		PlayerManager* playerManager = server->getPlayerManager();
		playerManager->acceptTeachingOffer(teacher, student, skill.get());
	}
};

#endif /* PLAYERTEACHCONFIRMSUICALLBACK_H_ */
