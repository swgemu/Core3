/*
 * PlayerCreatureImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerCreature.h"

#include "server/zone/managers/object/ObjectManager.h"

PlayerCreatureImplementation::PlayerCreatureImplementation(LuaObject* templateData, SceneObject* par) :
	CreatureObjectImplementation(templateData, par) {

	owner = NULL;
	nextAction = NULL;

	nextTip = NULL;

	firstIncapacitationTime = NULL;

}
