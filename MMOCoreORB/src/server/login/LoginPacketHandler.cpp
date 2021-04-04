/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#include "objects.h"

#include "LoginPacketHandler.h"
#include "server/login/LoginServer.h"
#include "LoginProcessServerImplementation.h"

#include "account/AccountManager.h"

LoginPacketHandler::LoginPacketHandler(const String& s, LoginProcessServerImplementation* serv)
		: Logger(s) {

	processServer = serv;

	server = processServer->getLoginServer().get();

	setGlobalLogging(true);
	setLogging(false);
}

void LoginPacketHandler::handleMessage(Message* pack) {
	Reference<LoginClient*> client = server->getLoginClient(pack->getClient());

	if (client == nullptr)
		return;

	debug() << "parsing " << *pack;

	uint16 opcount = pack->parseShort();
	uint32 opcode = pack->parseInt();

	switch (opcount) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		switch (opcode) {
			case 0xE87AD031:
			handleDeleteCharacterMessage(client, pack);
			break;
		}
		break;
	case 4:
		switch (opcode) {
		case 0x41131F96: //LoginClientID CLIENT VERSION BUILD DATE AND LOGIN INFO
			handleLoginClientID(client, pack);
			break;
		}
		break;
	case 5:
		break;
	default:
		break;
	}
}

void LoginPacketHandler::handleLoginClientID(LoginClient* client, Message* pack) {
	AccountManager* accountManager = server->getAccountManager();
	accountManager->loginAccount(client, pack);
}

void LoginPacketHandler::handleDeleteCharacterMessage(LoginClient* client, Message* pack) {
	if (!client->hasAccount()) {
		auto* msg = new DeleteCharacterReplyMessage(1); //FAIL
		client->sendMessage(msg);
		return;
	}

	uint32 accountId = client->getAccountID();

	uint32 ServerId = pack->parseInt();

	//pack->shiftOffset(4);
	uint64 charId = pack->parseLong();

	StringBuffer moveStatement;
	moveStatement << "INSERT INTO deleted_characters SELECT *, 0 as db_deleted FROM characters WHERE character_oid = " << charId;
	moveStatement << " AND account_id = " << accountId << " AND galaxy_id = " << ServerId << ";";

	StringBuffer verifyStatement;
	verifyStatement << "SELECT * from deleted_characters WHERE character_oid = " << charId;
	verifyStatement << " AND account_id = " << accountId << " AND galaxy_id = " << ServerId << ";";

	StringBuffer deleteStatement;
	deleteStatement << "DELETE FROM characters WHERE character_oid = " << charId;
	deleteStatement << " AND account_id = " << accountId << " AND galaxy_id = " << ServerId << ";";

	int dbDelete = 0;

	try {
		UniqueReference<ResultSet*> moveResults(ServerDatabase::instance()->executeQuery(moveStatement.toString()));

		if (moveResults == nullptr || moveResults.get()->getRowsAffected() == 0) {
			dbDelete = 1;

			error() << "Could not move character to deleted_characters table. " << endl <<
				"QUERY: " << moveStatement;

		}

		UniqueReference<ResultSet*> verifyResults(ServerDatabase::instance()->executeQuery(verifyStatement.toString()));

		if (verifyResults == nullptr || verifyResults.get()->getRowsAffected() == 0) {
			dbDelete = 1;

			error() << "Could not verify character was moved to deleted_characters " << endl <<
				"QUERY: " << moveStatement;
		}

	} catch (const Exception& e) {
		dbDelete = 1;

		error() << e.getMessage();
	}

	if (!dbDelete) {
		try {
			UniqueReference<ResultSet*> deleteResults(ServerDatabase::instance()->executeQuery(deleteStatement));

			if (deleteResults == nullptr || deleteResults.get()->getRowsAffected() == 0) {
				error() << "Unable to delete character from character table. " << endl
					<< "QUERY: " << deleteStatement;

				dbDelete = 1;
			}
		} catch (const Exception& e) {
			error() << e.getMessage();
			dbDelete = 1;
		}
	}

	auto* msg = new DeleteCharacterReplyMessage(dbDelete);
	client->sendMessage(msg);
}


