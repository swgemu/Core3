/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef TOTALHEALSELFCOMMAND_H_
#define TOTALHEALSELFCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "ForceHealQueueCommand.h"

class TotalHealSelfCommand : public ForceHealQueueCommand {
public:
	TotalHealSelfCommand(const String& name, ZoneProcessServer* server) : ForceHealQueueCommand(name, server) {}
};

#endif /* TOTALHEALSELFCOMMAND_H_ */
