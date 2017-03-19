/*
 * StructureSetAccessFeeSuiCallback.h
 *
 *  Created on: Feb 5, 2012
 *      Author: Kyle
 */

#ifndef STRUCTURESETACCESSFEESUICALLBACK_H_
#define STRUCTURESETACCESSFEESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class StructureSetAccessFeeSuiCallback : public SuiCallback {

public:
	StructureSetAccessFeeSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isInputBox() || cancelPressed || args->size() < 1)
			return;

		ManagedReference<StructureSetAccessFeeSession*> session =
				creature->getActiveSession(SessionFacadeType::SETSTRUCTUREACCESSFEE).castTo<StructureSetAccessFeeSession*>();

		if (session == NULL)
			return;

		try {
			int fee = Integer::valueOf(args->get(0).toString());

			if(fee > 0 && fee <= 50000)
				session->setAccessFee(fee);
			else
				session->promptSetAccessFee();
		} catch(Exception& e) {
			session->promptSetAccessFee();
		}

	}
};

#endif /* STRUCTURESETACCESSFEESUICALLBACK_H_ */
