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

	server = processServer->getLoginServer();

	setGlobalLogging(true);
	setLogging(true);
}

void LoginPacketHandler::handleMessage(Message* pack) {
	Reference<LoginClient*> client = server->getLoginClient(pack->getClient());

	if (client == NULL)
		return;

	StringBuffer msg;
	msg << "parsing " << pack->toStringData();
	//info(msg);

	uint16 opcount = pack->parseShort();
	uint32 opcode = pack->parseInt();

	switch (opcount) {
	case 01:
		break;
	case 02:
		break;
	case 03:
		switch (opcode) {
			case 0xE87AD031:
			handleDeleteCharacterMessage(client, pack);
			break;
		}
		break;
	case 04:
		switch (opcode) {
		case 0x41131F96: //LoginClientID CLIENT VERSION BUILD DATE AND LOGIN INFO
			handleLoginClientID(client, pack);
			break;
		}
		break;
	case 05:
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

	if(!client->hasAccount()) {
		Message* msg = new DeleteCharacterReplyMessage(1); //FAIL
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

    	Reference<ResultSet*> moveResults = ServerDatabase::instance()->executeQuery(moveStatement.toString());

    	if(moveResults == NULL || moveResults.get()->getRowsAffected() == 0){
    		dbDelete = 1;
    		StringBuffer errMsg;
    		errMsg << "ERROR: Could not move character to deleted_characters table. " << endl;
    		errMsg << "QUERY: " << moveStatement.toString();
    		info(errMsg.toString(),true);

    	}

    	Reference<ResultSet*> verifyResults  = ServerDatabase::instance()->executeQuery(verifyStatement.toString());

    	if(verifyResults == NULL || verifyResults.get()->getRowsAffected() == 0){
    		dbDelete = 1;
    		StringBuffer errMsg;
        	errMsg << "ERROR: Could not verify character was moved to deleted_characters " << endl;
        	errMsg << "QUERY: " << moveStatement.toString();

    	}

    } catch (DatabaseException& e) {
    	dbDelete = 1;
    	System::out << e.getMessage();
    } catch (Exception& e) {
    	dbDelete = 1;
       	System::out << e.getMessage();
    }

    if(!dbDelete){
    	try {
    		Reference<ResultSet*> deleteResults = ServerDatabase::instance()->executeQuery(deleteStatement);

    		if(deleteResults == NULL || deleteResults.get()->getRowsAffected() == 0){
    			StringBuffer errMsg;
    			errMsg << "ERROR: Unable to delete character from character table. " << endl;
    			errMsg << "QUERY: " << deleteStatement.toString();
    			dbDelete = 1;
    		}


    	} catch (DatabaseException& e) {
    		System::out << e.getMessage();
    		dbDelete = 1;
    	} catch (Exception& e) {
    		System::out << e.getMessage();
    		dbDelete = 1;
    	}
    }

   	Message* msg = new DeleteCharacterReplyMessage(dbDelete);
	client->sendMessage(msg);
}


