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

#include "server/chat/StringIdChatParameterVector.h"
#include "server/chat/WaypointChatParameterVector.h"

#include "server/zone/packets/chat/ChatOnSendPersistentMessage.h"

class ChatPersistentMessageToServerCallback : public MessageCallback {
	UnicodeString header;
	UnicodeString body;
	String recipientName;
	uint32 sequence;

	StringIdChatParameterVector stringIdParameters;
	WaypointChatParameterVector waypointParameters;

public:
	ChatPersistentMessageToServerCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

		sequence = 0;
	}

	void parse(Message* message) {
		message->parseUnicode(body);

		int parametersSize = message->parseInt() * 2;

		if (parametersSize > 0) {
			int initialOffset = message->getOffset();

			while (message->getOffset() < initialOffset + parametersSize) {
				uint16 appendedByte = message->parseShort();
				message->shiftOffset(1); //Skip the initial type byte. We'll switch on the second type.
				int type = message->parseInt();

				switch (type) {
				default:
				case ChatParameter::STRINGID:
				{
					StringIdChatParameter param;
					param.parse(message);
					stringIdParameters.add(param);
					break;
				}
				case ChatParameter::WAYPOINT:
				{
					WaypointChatParameter param;
					param.parse(message);
					waypointParameters.add(param);
					break;
				}
				}

				if (appendedByte > 0)
					message->shiftOffset(1);
			}
		}

		sequence = message->parseInt();
		message->parseUnicode(header); //mail subject
		message->shiftOffset(4); //skip spacer
		message->parseAscii(recipientName);
	}

	void run() {
		ManagedReference<CreatureObject*> player = (CreatureObject*) client->getPlayer();

		if (player == NULL)
			return;

		ChatManager* chatManager = server->getChatManager();
		int result = chatManager->sendMail(player->getFirstName(), header, body, recipientName, &stringIdParameters, &waypointParameters);

		ChatOnSendPersistentMessage* cospm = new ChatOnSendPersistentMessage(sequence, result);
		player->sendMessage(cospm);
	}

};


#endif /* CHATPERSISTENTMESSAGETOSERVERCALLBACK_H_ */
