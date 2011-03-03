/*
 * LoginPacketHandler.cpp
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#include "LoginPacketHandler.h"
#include "LoginClient.h"
#include "LoginSession.h"

void LoginPacketHandler::handleMessage(Message* pack) {
	//info("parsing " + pack->toStringData());

	sys::uint16 opcount = pack->parseShort();
	sys::uint32 opcode = pack->parseInt();

	switch (opcount) {
	case 02:
		switch (opcode) {
		case 0x65EA4574: // char create success
			handleEnumerateCharacterId(pack);
			break;
		}
		break;
	case 04:
		switch (opcode) {
		case 0xAAB296C6: // client token
			handleLoginClientToken(pack);
			break;
		}
		break;

	case 03:
		switch (opcode) {
		case 0xB5ABF91A:
			handleErrorMessage(pack);
			break;
		}
		break;

	default:
		//error("unhandled operand count" + pack->toString());
		break;
	}
}

void LoginPacketHandler::handleErrorMessage(Message* pack) {
	LoginClient* client = (LoginClient*) pack->getClient();
	client->info("received ErrorMessage", true);

	String errorType, errorMessage;

	pack->parseAscii(errorType);
	pack->parseAscii(errorMessage);

	client->error(errorType + " : " + errorMessage);
	//client->disconnect();
	//exit(1);
}

void LoginPacketHandler::handleLoginClientToken(Message* pack) {
	LoginClient* client = (LoginClient*) pack->getClient();
	client->info("received LoginClientToken", true);

	uint32 size = pack->parseInt();
	uint32 session = pack->parseInt();
	uint32 accountID = pack->parseInt();

	loginSession->setAccountID(accountID);
	loginSession->setSessionID(session);
}

void LoginPacketHandler::handleEnumerateCharacterId(Message* pack) {
	LoginClient* client = (LoginClient*) pack->getClient();
	client->info("received EnumerateCharacterId", true);

	uint32 characters = pack->parseInt();

	if (characters == 0) {
		client->info("no characters found", true);

		loginSession->setSelectedCharacter(-1);
		return;
	}

	for (int i = 0; i < characters; ++i) {
		UnicodeString name;
		pack->parseUnicode(name);

		uint32 crc = pack->parseInt();
		uint64 oid = pack->parseLong();
		uint32 galaxy = pack->parseInt();
		uint32 serverStatus = pack->parseInt();

		StringBuffer player;
		player << "Character [" << i << "]: [" << name.toString() << "]";

		client->info(player.toString(), true);
		loginSession->addCharacter(oid);
	}

	//client->info("please enter character to login... -1 to create a new one", true);

	//char characterID[32];
	//fgets(characterID, sizeof(characterID), stdin);

	//String selected = characterID;
	//selected = selected.replaceFirst("\n", "");

	int selectedInt = -1; //Integer::valueOf(selected);
	if (characters > 0)
		selectedInt = 0;

	client->info("selected character " + String::valueOf(selectedInt), true);

	loginSession->setSelectedCharacter(selectedInt);
}
