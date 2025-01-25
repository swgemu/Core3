/*
 * ReverseEngineeringSuiCallback.h
 *
 *  Created on: Jan 25, 2025
 *      Author: Halyn
 */

#ifndef REVERSEENGINEERINGSUICALLBACK_H_
#define REVERSEENGINEERINGSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/player/sui/callbacks/NameComponentSuiCallback.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"


class ReverseEngineeringSuiCallback : public SuiCallback {
public:
	ReverseEngineeringSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (creature == nullptr || sui == nullptr)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == nullptr || creature == nullptr) {
			return;
		}

		auto ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return;

		ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(creature, SuiWindowType::OBJECT_NAME);

		inputBox->setUsingObject(obj);

		inputBox->setPromptTitle("@reverse_engineering_tool:title2"); // Name New Component
		inputBox->setPromptText("@reverse_engineering_tool:prompt2"); // That is a reserved name.

		inputBox->setMaxInputSize(20);

		inputBox->setCallback(new NameComponentSuiCallback(creature->getZoneServer()));
		inputBox->setForceCloseDistance(-1);

		ghost->addSuiBox(inputBox);

		creature->sendMessage(inputBox->generateMessage());
	}
};

#endif /* STRUCTURESTATUSSUICALLBACK_H_ */
