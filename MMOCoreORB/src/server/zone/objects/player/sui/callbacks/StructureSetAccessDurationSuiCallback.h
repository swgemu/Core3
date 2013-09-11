/*
 * StructureSetAccessDurationSuiCallback.h
 *
 *  Created on: Feb 5, 2012
 *      Author: Kyle
 */

#ifndef STRUCTURESETACCESSDURATIONSUICALLBACK_H_
#define STRUCTURESETACCESSDURATIONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class StructureSetAccessDurationSuiCallback : public SuiCallback {

public:
	StructureSetAccessDurationSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isInputBox() || cancelPressed || args->size() < 1)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject();
		ManagedReference<StructureSetAccessFeeSession*> session =
				creature->getActiveSession(SessionFacadeType::SETSTRUCTUREACCESSFEE).castTo<StructureSetAccessFeeSession*>();

		if (session == NULL)
			return;

		try {
			int duration = Integer::valueOf(args->get(0).toString());

			if(duration >= 15 && duration <= 60 * 48)
				session->setAccessDuration(duration);
			else
				session->promptSetAccessDuration();
		} catch(Exception& e) {
			session->promptSetAccessDuration();
		}

	}
};

#endif /* STRUCTURESETACCESSDURATIONSUICALLBACK_H_ */
