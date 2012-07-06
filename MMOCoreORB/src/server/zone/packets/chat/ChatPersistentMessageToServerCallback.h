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
#include "server/zone/objects/guild/GuildObject.h"

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

	int sendMail(const String& recipient) {
		if (recipient == "guild") {
			ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());
			ManagedReference<GuildObject*> guild = player->getGuildObject();

			if (guild == NULL)
				return 0;

			if (!guild->hasMailPermission(player->getObjectID())) {
				player->sendSystemMessage("@guild:generic_fail_no_permission");
				return 0;
			}

			Locker locker(guild);

			int max = guild->getTotalMembers();

			for (int i = 0; i < max; ++i) {
				uint64 oid = guild->getMember(i);

				ManagedReference<SceneObject*> receiver = server->getZoneServer()->getObject(oid);

				if (receiver == NULL || !receiver->isPlayerCreature())
					continue;

				CreatureObject* receiverPlayer = cast<CreatureObject*>(receiver.get());

				sendMailToPlayer(receiverPlayer->getFirstName());
			}

			return 0;
		}

		return sendMailToPlayer(recipient);
	}

	int sendMailToPlayer(const String& recipientName) {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());
		ChatManager* chatManager = server->getChatManager();

		uint64 receiverObjectID = server->getPlayerManager()->getObjectID(recipientName);

		if (receiverObjectID == 0) {
			return 0;
		}

		ManagedReference<SceneObject*> receiver = server->getZoneServer()->getObject(receiverObjectID);

		if (receiver == NULL || !receiver->isPlayerCreature())
			return 0;

		CreatureObject* receiverPlayer = cast<CreatureObject*>(receiver.get());
		ManagedReference<PlayerObject*> ghost = receiverPlayer->getPlayerObject();

		if (ghost == NULL || ghost->isIgnoring(player->getFirstName().toLowerCase())) {
			StringIdChatParameter err("ui_pm", "recipient_ignored_prose");
			err.setTT(recipientName);
			player->sendSystemMessage(err);

			return ChatManager::IM_IGNORED;
		}

		return chatManager->sendMail(player->getFirstName(), header, body, recipientName, &stringIdParameters, &waypointParameters);
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());

		if (player == NULL)
			return;

		int result = 0;

		StringTokenizer tokenizer(recipientName);
		tokenizer.setDelimeter(";");

		if (tokenizer.hasMoreTokens()) {
			String receiver;

			while (tokenizer.hasMoreTokens()) {
				tokenizer.getStringToken(receiver);

				sendMail(receiver);
			}
		} else {
			result = sendMailToPlayer(recipientName);
		}

		ChatOnSendPersistentMessage* cospm = new ChatOnSendPersistentMessage(sequence, result);
		player->sendMessage(cospm);
	}

};


#endif /* CHATPERSISTENTMESSAGETOSERVERCALLBACK_H_ */
