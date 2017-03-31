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

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isInputBox() || cancelPressed || args->size() < 1)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == NULL)
			return;

		if (obj->getGameObjectType() == SceneObjectType::PLAYERTERMINALSTRUCTURE) {
			ManagedReference<SceneObject*> root = obj->getRootParent();
			if (root != NULL)
				obj = root;
		}

		UnicodeString name = args->get(0);

		creature->executeObjectControllerAction(0xC367B461, obj->getObjectID(), name); //nameStructure
	}
};

#endif /* NAMESTRUCTURESUICALLBACK_H_ */
