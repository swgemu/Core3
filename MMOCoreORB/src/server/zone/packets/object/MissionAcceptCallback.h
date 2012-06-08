/*
 * MissionAcceptCallback.h
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#ifndef MISSIONACCEPTCALLBACK_H_
#define MISSIONACCEPTCALLBACK_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/objects/mission/MissionObject.h"


class MissionAcceptCallback : public MessageCallback {
	uint64 missionObjectID;
	uint64 terminalObjectID;
	uint8 terminalIndex;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	MissionAcceptCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		//System::out << message->toStringData() << endl;
		message->parseInt();
		missionObjectID = message->parseLong();
		terminalObjectID = message->parseLong();

		terminalIndex = message->parseByte();
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());

		ManagedReference<SceneObject*> terminal = server->getZoneServer()->getObject(terminalObjectID);

		if (terminal == NULL) {
			player->sendSystemMessage("@skill_teacher:skill_terminal_disabled");
			return;
		}

		if (!terminal->isMissionTerminal())
			return;

		ManagedReference<SceneObject*> mission = server->getZoneServer()->getObject(missionObjectID);

		if (mission == NULL)
			return;

		if (!mission->isMissionObject())
			return;

		MissionObject* missionObject = cast<MissionObject*>( mission.get());
		MissionTerminal* missionTerminal = cast<MissionTerminal*>( terminal.get());

		MissionManager* manager = server->getZoneServer()->getMissionManager();
		manager->handleMissionAccept(missionTerminal, missionObject, player);

		// MissionAcceptResponse
		ObjectControllerMessage* mar = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0xFA);
		mar->insertLong(missionObject->getObjectID());
		mar->insertByte(0x01);
		mar->insertByte(terminalIndex);
		player->sendMessage(mar);
	}
};

#endif /* MISSIONACCEPTCALLBACK_H_ */
