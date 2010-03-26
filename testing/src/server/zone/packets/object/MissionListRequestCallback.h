/*
 * MissionListRequestCallback.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef MISSIONLISTREQUESTCALLBACK_H_
#define MISSIONLISTREQUESTCALLBACK_H_

#include "ObjectControllerMessageCallback.h"

class MissionListRequestCallback : public MessageCallback {
	uint16 unk1;
	uint16 unk2;
	uint64 terminalObjectID;

	ObjectControllerMessageCallback* objectControllerMain;

public:
	MissionListRequestCallback(ObjectControllerMessageCallback* objectControllerCallback) :
			MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;

	}

	void parse(Message* message) {
		message->parseInt();
		unk1 = message->parseByte();
		unk2 = message->parseByte();

		terminalObjectID = message->parseLong();

		//System::out << "mission list request with unk1: " << unk1 << " unk2: " << unk2 << endl;
	}

	void run() {
		PlayerCreature* player = (PlayerCreature*) client->getPlayer();

		if (player == NULL)
			return;

		ManagedReference<SceneObject*> terminal = server->getZoneServer()->getObject(terminalObjectID);

		if (terminal == NULL)
			player->sendSystemMessage("skill_teacher", "skill_terminal_disabled");

	}


};


#endif /* MISSIONLISTREQUESTCALLBACK_H_ */
