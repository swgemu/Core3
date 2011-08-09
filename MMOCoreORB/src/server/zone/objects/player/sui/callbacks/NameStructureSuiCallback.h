/*
 * NameStructureSuiCallback.h
 *
 *  Created on: Aug 9, 2011
 *      Author: crush
 */

#ifndef NAMESTRUCTURESUICALLBACK_H_
#define NAMESTRUCTURESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"


class NameStructureSuiCallback : public SuiCallback {
public:
	NameStructureSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isInputBox() || cancelPressed || args->size() < 1)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL)
			return;

		UnicodeString name = args->get(0);

		creature->executeObjectControllerAction(0xC367B461, obj->getObjectID(), name); //nameStructure
	}
};

#endif /* NAMESTRUCTURESUICALLBACK_H_ */
