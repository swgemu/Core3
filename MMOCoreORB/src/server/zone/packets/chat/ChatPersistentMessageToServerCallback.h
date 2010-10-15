/*
 * ChatPersistentMessageToServerCallback.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef CHATPERSISTENTMESSAGETOSERVERCALLBACK_H_
#define CHATPERSISTENTMESSAGETOSERVERCALLBACK_H_


#include "../MessageCallback.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/city/CityHallObject.h"

class ChatPersistentMessageToServerCallback : public MessageCallback {
	UnicodeString header, body, wpName;
	int wpInfoSize;
	uint32 planetCrc;
	float wpX, wpY;
	String recipientName;

public:
	ChatPersistentMessageToServerCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {
		wpInfoSize = 0;
	}

	void parse(Message* message) {
		message->parseUnicode(body);

		//Handle Attachments: (see docs for more info on unk's)
		wpInfoSize = message->parseInt();

		if (wpInfoSize > 0) {
			System::out << message->toStringData() << endl;
			return;
			/*message->shiftOffset(11); //Shift past the STF param start(7) + unk int(4)
				wpX = message->parseFloat();
				message->shiftOffset(4); //skip Z, always 0.0f
				wpY = message->parseFloat();
				message->shiftOffset(4); //skip blank WP objid
				planetCrc = message->parseInt();
				message->parseUnicode(wpName);
				message->shiftOffset(11); //skip attachment footer*/
		}

		message->shiftOffset(4); //skip the string count

		message->parseUnicode(header); //mail subject
		message->shiftOffset(4); //skip spacer

		message->parseAscii(recipientName);

	}

	void run() {
		ManagedReference<PlayerCreature*> player = (PlayerCreature*) client->getPlayer();

		if (player == NULL)
			return;

		if (wpInfoSize != 0) // we dont handle attachments yet
			return;

		ChatManager* chatManager = server->getChatManager();
		chatManager->sendMail(player->getFirstName(), header, body, recipientName);
	}

};


#endif /* CHATPERSISTENTMESSAGETOSERVERCALLBACK_H_ */
