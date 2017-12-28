/*
 * DelegateSuiCallback.cpp
 *
 *  Created on: 19/01/2012
 *      Author: victor
 */

#include "DelegateSuiCallback.h"

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "server/zone/objects/creature/commands/DelegateFactionPointsCommand.h"
#include "server/zone/objects/player/sui/SuiBox.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "system/lang/Integer.h"
#include "system/lang/String.h"
#include "system/lang/UnicodeString.h"
#include "system/lang/ref/Reference.h"
#include "system/util/Vector.h"

namespace server {
namespace zone {
class ZoneServer;
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

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
