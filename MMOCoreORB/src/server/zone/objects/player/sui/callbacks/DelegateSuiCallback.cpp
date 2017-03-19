/*
 * DelegateSuiCallback.cpp
 *
 *  Created on: 19/01/2012
 *      Author: victor
 */

#include "DelegateSuiCallback.h"
#include "server/zone/objects/creature/commands/DelegateFactionPointsCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneServer.h"

DelegateSuiCallback::DelegateSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
}

void DelegateSuiCallback::run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
	bool cancelPressed = (eventIndex == 1);

	if (!sui->isTransferBox() || cancelPressed)
		return;

	uint32 received = Integer::valueOf(args->get(0).toString());
	uint32 tipAmount = Integer::valueOf(args->get(1).toString());

	//printf("received %d transferred %d\n", received, transferred);

	if (tipAmount == 0)
		return;

	ManagedReference<SceneObject*> usingObject = sui->getUsingObject().get();

	if (usingObject == NULL || !usingObject->isPlayerCreature()) {
		return;
	}

	CreatureObject* targetPlayer = cast<CreatureObject*>(usingObject.get());

	if (targetPlayer == NULL)
		return;

	DelegateFactionPointsCommand::doDelegate(creature, targetPlayer, tipAmount);
}
