/*
 * DeleteAllItemsConfirmSuiCallback.h
 *
 *  Created on: Aug 14, 2011
 *      Author: crush
 */

#ifndef DELETEALLITEMSCONFIRMSUICALLBACK_H_
#define DELETEALLITEMSCONFIRMSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class DeleteAllItemsConfirmSuiCallback : public SuiCallback {
public:
	DeleteAllItemsConfirmSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->getMessageBox() || cancelPressed)
			return;
	}
};

#endif /* DELETEALLITEMSCONFIRMSUICALLBACK_H_ */
