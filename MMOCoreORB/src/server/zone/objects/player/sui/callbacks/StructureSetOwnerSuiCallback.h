/*
 * StructureSetOwnerSuiCallback.h
 *
 *  Created on: Aug 18, 2011
 *      Author: crush
 */

#ifndef STRUCTURESETOWNERSUICALLBACK_H_
#define STRUCTURESETOWNERSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class StructureSetOwnerSuiCallback : public SuiCallback {
public:
	StructureSetOwnerSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isInputBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL || !obj->isStructureObject())
			return; //Not a structure object.

		StructureObject* structure = (StructureObject*) obj.get();

		String name = args->get(0).toString();

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		ManagedReference<CreatureObject*> targetCreature = playerManager->getPlayer(name);

		if (targetCreature == NULL) {
			creature->sendSystemMessage("That player does not exist.");
			return;
		}

		Locker _lock(structure, creature);

		structure->setOwnerObjectID(targetCreature->getObjectID());

		creature->sendSystemMessage("You have successfully set the player as the owner of this structure.");
	}
};

#endif /* STRUCTURESETOWNERSUICALLBACK_H_ */
