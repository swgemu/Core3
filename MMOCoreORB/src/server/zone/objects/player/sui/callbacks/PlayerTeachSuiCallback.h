/*
 * PlayerTeachSuiCallback.h
 *
 *  Created on: Mar 13, 2012
 *      Author: katherine
 */

#ifndef PLAYERTEACHSUICALLBACK_H_
#define PLAYERTEACHSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PlayerTeachConfirmSuiCallback.h"

class PlayerTeachSuiCallback : public SuiCallback {

public:
	PlayerTeachSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* teacher, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isListBox() || cancelPressed || args->size() <= 0)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		SuiListBox* listBox = cast<SuiListBox*>(sui);

		if (listBox->getMenuSize() <= index || index < 0)
			return;

		ManagedReference<SceneObject*> usingObject = listBox->getUsingObject();

		if (usingObject == NULL || !usingObject->isCreatureObject())
			return;

		CreatureObject* student = cast<CreatureObject*>(usingObject.get());

		Locker _lock(student, teacher);

		Skill* skill = SkillManager::instance()->getSkill(listBox->getMenuObjectID(index));

		PlayerManager* playerManager = server->getPlayerManager();
		playerManager->offerTeaching(teacher, student, skill);
	}
};


#endif /* PLAYERTEACHSUICALLBACK_H_ */
